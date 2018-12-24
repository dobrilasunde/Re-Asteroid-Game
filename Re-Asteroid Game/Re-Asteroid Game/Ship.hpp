#pragma once
#include "Actor.hpp"

class Ship : public Actor
{
public:
	Ship(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const InputState& state) override;
private:
	float mLaserCooldown;
	Vector2 mVelocityDir;
	Vector2 mRotationDir;
	float mSpeed;
};
