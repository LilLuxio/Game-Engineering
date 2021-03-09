//ship.cpp
#include "ship.h"
#include "game.h"
using namespace sf;
using namespace std;

// Controls for the player to use
const Keyboard::Key controls[3] = {
	Keyboard::A, // Player1 Move Left
	Keyboard::D, // Player1 Move Right
	Keyboard::Space, // Player1 Shoot
};

Ship::Ship() {};

bool Invader::direction;
float Invader::speed;

Ship::Ship(IntRect ir) : Sprite() {
	_sprite = ir;
	setTexture(spritesheet);
	setTextureRect(_sprite);
};

void Ship::Update(const float& dt) {}

//Define the ship deconstructor. 
//Although we set this to pure virtual, we still have to define it.
Ship::~Ship() = default;

Invader::Invader() : Ship() {}

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
	setOrigin(16, 16);
	setPosition(pos);
}

void Invader::Update(const float& dt) {
	Ship::Update(dt);

	move(dt * (direction ? 1.0f : -1.0f) * speed, 0);

	if ((direction && getPosition().x > gameWidth - 16) || (!direction && getPosition().x < 16))
	{
		direction = !direction;

		for (int i = 0; i < ships.size(); ++i) {
			if (i != (ships.size()-1))
			{
				ships[i]->move(0, 24);
			}
		}

	}
}

Player::Player() : Ship(IntRect(160, 32, 32, 32)) {
	setPosition({ gameHeight * .5f, gameHeight - 32.f });
}

void Player::Update(const float& dt) {
	Ship::Update(dt);

	float playerSpeed = 100.0f;

	// Move Left
	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) {
		direction--;
	}
	// Move Right
	if (Keyboard::isKeyPressed(controls[1])) {
		direction++;
	}
	ships[ships.size()-1]->move(direction * playerSpeed * dt, 0);




}

