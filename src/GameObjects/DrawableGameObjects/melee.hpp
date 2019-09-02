#pragma once

#include "GameObjects/GameObject.hpp"
#include <array>

namespace ph{

class GameData;
class Character;

class Swing 
{
public:
	Swing(const GameObject& nodeWithAtackableObjects, const sf::Vector2f direction, const sf::Vector2f position,
		const float damage, const float range, const float rotationRange);

private:
	void setMeeleWeaponStartingPosition(const sf::Vector2f attackDirection);
	void handleHitCharacters();
	auto getFirstCharacterWhoWouldBeHit(const std::vector<Character*>&) -> Character*;
	auto getAtackableCharactersInHitArea() const -> std::vector<Character*>;
	bool wasCharacterHit(Character*);
	void incrementRotation();

private:
	const GameObject& mNodeWithAtackableObjects;
	const sf::Vector2f mDirection;
	const sf::Vector2f mStartPosition;
	const float mDamage;
	const float mRange;
	const float mRotationRange;
	float mRotation;
	std::array<sf::Vertex, 2> mHitArea;
};

class MeleeWeapon : public GameObject
{
public:
	MeleeWeapon(GameData* const, const float damage, const float range, const float rotationRange);

	void updateCurrent(const sf::Time delta) override;
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	void attack(const sf::Vector2f attackDirection);

private:
	float getStartAtackRotation(const sf::Vector2f attackDirection) const;
	sf::Vector2f getRightHandLocalPosition(const sf::Vector2f attackDirection);

private:
	sf::Sprite mSprite;
	GameData* const mGameData;
	const float mDamage;
	const float mRange;
	const float mRotationRange;
	float mRotationFromStart;
	bool mShouldBeDrawn;
};

}