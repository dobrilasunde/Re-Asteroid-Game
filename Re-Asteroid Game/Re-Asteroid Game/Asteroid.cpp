#include "Asteroid.hpp"
#include "Game.hpp"
#include "Asteroid.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"
#include "Game.hpp"
#include "Random.hpp"
#include "CircleComponent.hpp"

Asteroid::Asteroid(Game* game):Actor(game), mCircle(nullptr)
{
	Vector2 randPos = Random::GetVector(Vector2(-512.0f, -384.0f), Vector2(512.0f, 384.0f));
	SetPosition(randPos);

	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);

	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}
