#ifndef POPHEAD_PHYSICS_COLLISIONSBODY_H_
#define POPHEAD_PHYSICS_COLLISIONSBODY_H_

#include <SFML/Graphics.hpp>

namespace PopHead{
namespace Physics{


class CollisionBody
{
public:
    CollisionBody(sf::FloatRect rect, float mass, PopHead::Base::GameData*);

    void move(sf::Vector2f velocity);

private:
    sf::FloatRect mRect;
    sf::Vector2f mVelocity;
    float mMass;
};


}}

#endif // POPHEAD_PHYSICS_COLLISIONSBODY_H_
