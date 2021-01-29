#include <cmath>
#include "SpaceShip.h"
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
	setType(SPACE_SHIP);
}

SpaceShip::~SpaceShip()
= default;

void SpaceShip::draw()
{
	TextureManager::Instance()->draw("spaceship", getTransform()->position.x, getTransform()->position.y,
		m_rotationAngle + 90, 255, true);

	Util::DrawLine(getTransform()->position, (getTransform()->position - m_destination) * -60.0f);
}

void SpaceShip::update()
{
	m_Move();
	updateRotation(m_orientation, getTransform()->position, m_destination);
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
	// Direction with magnitude
	m_targetDirection = m_destination - getTransform()->position;
	
	//Normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	getRigidBody()->velocity = m_targetDirection * m_maxSpeed;

	getTransform()->position += getRigidBody()->velocity;
}