#include "Ship.hpp"
#include "SpriteComponent.hpp"
#include "InputComponent.hpp"
#include "Game.hpp"
#include "Laser.hpp"
#include "InputSystem.hpp"

Ship::Ship(Game* game):Actor(game), mSpeed(400.0f), mLaserCooldown(0.0f)
{
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;

	Vector2 pos = GetPosition();
	pos += mVelocityDir * mSpeed * deltaTime;
	SetPosition(pos);

	float angle = Math::Atan2(mRotationDir.y, mRotationDir.x);
	SetRotation(angle);
}

void Ship::ActorInput(const InputState& state)
{
	if (state.Controller.GetRightTrigger() > 0.25f && mLaserCooldown <= 0.0f)
	{
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		mLaserCooldown = 0.25f;
	}

	if (state.Controller.GetIsConnected())
	{
		mVelocityDir = state.Controller.GetLeftStick();
		if (!Math::NearZero(state.Controller.GetRightStick().Length()))
		{
			mRotationDir = state.Controller.GetRightStick();
		}
	}
}