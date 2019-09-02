#include "GameObjects/DrawableGameObjects/melee.hpp"
#include "GameObjects/DrawableGameObjects/Characters/player.hpp"
#include "gameData.hpp"

namespace ph {

Swing::Swing(const GameObject& nodeWithAtackableObjects, const sf::Vector2f direction, const sf::Vector2f position,
	const float damage, const float range, const float rotationRange)
	:mNodeWithAtackableObjects(nodeWithAtackableObjects)
	,mDirection(direction)
	,mStartPosition(position)
	,mDamage(damage)
	,mRange(range)
	,mRotationRange(rotationRange)
	,mRotation(0.f)
{
	setMeeleWeaponStartingPosition(direction);
	handleHitCharacters();
}

void Swing::setMeeleWeaponStartingPosition(const sf::Vector2f attackDirection)
{
	sf::Transform rotation;
	rotation.rotate(-mRotationRange / 2, mStartPosition);
	mHitArea[0].position = mStartPosition;
	mHitArea[1].position = mStartPosition + (attackDirection * mRange);
	mHitArea[1] = rotation.transformPoint(mHitArea[1].position);
}

void Swing::handleHitCharacters()
{
	auto atackableCharactersInHitArea = getAtackableCharactersInHitArea();
	if(atackableCharactersInHitArea.empty())
		return;
	auto firstChracterWhoWouldBeHit = getFirstCharacterWhoWouldBeHit(atackableCharactersInHitArea);
	if(firstChracterWhoWouldBeHit != nullptr)
		firstChracterWhoWouldBeHit->takeDamage(static_cast<unsigned>(mDamage));
}

auto Swing::getAtackableCharactersInHitArea() const -> std::vector<Character*>
{
	const sf::FloatRect hitArea(mStartPosition.x - 20, mStartPosition.y - 20, 40, 40);
	std::vector<Character*> atackableCharactersInHitArea;

	for(auto& atackableObject : mNodeWithAtackableObjects.getChildren()) {
		// TODO: Don't use exceptions here
		try {
			auto& c = dynamic_cast<Character&>(*atackableObject);
			if(c.isAtackable() && Math::areTheyOverlapping(hitArea, c.getGlobalBounds()))
				atackableCharactersInHitArea.emplace_back(&c);
		}
		catch(const std::exception&) {}
	}
	return atackableCharactersInHitArea;
}

auto Swing::getFirstCharacterWhoWouldBeHit(const std::vector<Character*>& atackableCharactersInHitArea) -> Character*
{
	while(mRotation < 100) {
		incrementRotation();
		for(auto* atackableCharacter : atackableCharactersInHitArea) {
			if(wasCharacterHit(atackableCharacter))
				return atackableCharacter;
		}
	}
	return nullptr;
}

void Swing::incrementRotation()
{
	mRotation += 5.f;
	sf::Transform rotation;
	rotation.rotate(5.f, mStartPosition);
	mHitArea[1] = rotation.transformPoint(mHitArea[1].position);
}

bool Swing::wasCharacterHit(Character* character)
{
	const sf::FloatRect hitbox = character->getGlobalBounds();
	return Math::isPointInsideRect(mHitArea[1].position, hitbox);
}

MeleeWeapon::MeleeWeapon(GameData* const gameData, const float damage, const float range, const float rotatationRange)
	:GameObject("sword")
	,mSprite(gameData->getTextures().get("textures/others/baseballStick.png"))
	,mGameData(gameData)
	,mDamage(damage)
	,mRange(range)
	,mRotationRange(rotatationRange)
	,mRotationFromStart(0.f)
	,mShouldBeDrawn(false)
{
}

void MeleeWeapon::attack(const sf::Vector2f attackDirection)
{
	mGameData->getSoundPlayer().playAmbientSound("sounds/swordAttack.wav");
	setOrigin(0.f, 12.f);
	setRotation(getStartAtackRotation(attackDirection));
	sf::Vector2f rightHandLocalPosition = getRightHandLocalPosition(attackDirection);
	setPosition(rightHandLocalPosition);
	auto& standingObjects = mRoot->getChild("LAYER_standingObjects");
	Swing swing(standingObjects, attackDirection, rightHandLocalPosition + getWorldPosition(), mDamage, mRange, mRotationRange);
	mShouldBeDrawn = true;
}

float MeleeWeapon::getStartAtackRotation(const sf::Vector2f attackDirection) const
{
	if(attackDirection == sf::Vector2f(1, 0))
		return 0.f;
	else if(attackDirection == sf::Vector2f(-1, 0))
		return 180.f;
	else if(attackDirection == sf::Vector2f(0, 1))
		return 90.f;
	else if(attackDirection == sf::Vector2f(0, -1))
		return -90.f;
	else if(attackDirection == sf::Vector2f(0.7f, -0.7f))
		return -45.f;
	else if(attackDirection == sf::Vector2f(-0.7f, -0.7f))
		return -135.f;
	else if(attackDirection == sf::Vector2f(0.7f, 0.7f))
		return 45.f;
	else if(attackDirection == sf::Vector2f(-0.7f, 0.7f))
		return 135.f;
	else
		PH_UNEXPECTED_SITUATION("Direction vector like this shouldn't exist.");
}

sf::Vector2f MeleeWeapon::getRightHandLocalPosition(const sf::Vector2f attackDirection)
{
	if (attackDirection == sf::Vector2f(1, 0))
		return {14, 17};
	else if(attackDirection == sf::Vector2f(-1, 0))
		return {5, 15};
	else if(attackDirection == sf::Vector2f(0, 1))
		return {3, 20};
	else if(attackDirection == sf::Vector2f(0, -1))
		return {15, 15};
	else if(attackDirection == sf::Vector2f(0.7f, -0.7f))
		return {15, 7};
	else if(attackDirection == sf::Vector2f(-0.7f, -0.7f))
		return {3, 3};
	else if(attackDirection == sf::Vector2f(0.7f, 0.7f))
		return {13, 17};
	else if(attackDirection == sf::Vector2f(-0.7f, 0.7f))
		return {0, 10};
	else
		PH_UNEXPECTED_SITUATION("Direction vector like this shouldn't exist.");
}

void MeleeWeapon::updateCurrent(const sf::Time delta)
{
	if(mShouldBeDrawn) {
		if(mRotationFromStart < mRotationRange) {
			rotate(3.f);
			mRotationFromStart += 3.f;
		}
		else {
			mShouldBeDrawn = false;
			setRotation(0.f);
			mRotationFromStart = 0.f;
		}
	}
}

void MeleeWeapon::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(mShouldBeDrawn)
		target.draw(mSprite, states);
}

}
