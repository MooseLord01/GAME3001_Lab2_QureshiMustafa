#include <cmath>
#include "SpaceShip.h"

#include "Game.h"
#include "Util.h"

SpaceShip::SpaceShip():m_maxSpeed(10.0f)
{
	TextureManager::Instance()->load("../Assets/textures/spaceship.png", "spaceship");

	auto size = TextureManager::Instance()->getTextureSize("spaceship");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotationAngle(0.0f);
	setAccelerationRate(10.0f);
	setTurnRate(10.0f);
	setType(SPACE_SHIP);
}

SpaceShip::~SpaceShip()
= default;

void SpaceShip::draw()
{
	TextureManager::Instance()->draw("spaceship", getTransform()->position.x, getTransform()->position.y,
		m_rotationAngle, 255, true);

	Util::DrawLine(getTransform()->position, (getTransform()->position - m_destination) * -60.0f);
}

void SpaceShip::update()
{
	m_Move();
}

void SpaceShip::clean()
{
	
}

void SpaceShip::setDestination(glm::vec2 destination)
{
	m_destination = destination;
}

void SpaceShip::setOrientation(glm::vec2 orientation)
{
	m_orientation = orientation;
}

void SpaceShip::setAccelerationRate(float acceleration)
{
	m_accelerationRate = acceleration;
}

void SpaceShip::setTurnRate(float rate)
{
	m_turnRate = rate;
}

glm::vec2 SpaceShip::getOrientation()
{
	return m_orientation;
}

float SpaceShip::getAccelerationRate()
{
	return m_accelerationRate;
}

float SpaceShip::getRotationAngle()
{
	return m_rotationAngle;
}

float SpaceShip::getTurnRate()
{
	return m_turnRate;
}

void SpaceShip::setRotationAngle(float angle)
{
	m_rotationAngle = angle;
	const auto angle_in_radians = (angle - 90.0f) * Util::Deg2Rad;
	const auto x = cos(angle_in_radians);
	const auto y = sin(angle_in_radians);
	
	// Convert the angle to a normalized vector and store it in Orientation
	setOrientation(glm::vec2(x, y));
}


void SpaceShip::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

void SpaceShip::updateRotation(glm::vec2 orientation, glm::vec2 seeker, glm::vec2 target)
{
	m_rotationAngle = atan2(target.y - seeker.y, target.x - seeker.x) * 180/3.14;
}

void SpaceShip::m_Move()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();
	
	// Direction with magnitude
	m_targetDirection = m_destination - getTransform()->position;
	
	//Normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

	auto turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if(target_rotation > 0)
		{
			setRotationAngle(getRotationAngle() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setRotationAngle(getRotationAngle() - getTurnRate());
		}	
	}

	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	getRigidBody()->velocity += getOrientation() * (deltaTime) + 0.5f * getRigidBody()->acceleration * deltaTime;

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);
	
	getTransform()->position += getRigidBody()->velocity;
}