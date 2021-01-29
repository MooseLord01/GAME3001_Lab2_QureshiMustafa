#pragma once
#ifndef __SPACE_SHIP__
#define __SPACE_SHIP__
#include "DisplayObject.h"
#include "TextureManager.h"

class SpaceShip final : public DisplayObject
{
public:
	// constructor(s)
	SpaceShip();

	// destructor
	~SpaceShip();
	
	// life-cycle methods inherited from DisplayObject
	void draw() override;
	void update() override;
	void clean() override;

	// Setters
	void updateRotation(glm::vec2 orientation, glm::vec2 seeker, glm::vec2 target);
	void setDestination(glm::vec2 destination);
	void setOrientation(glm::vec2 orientation);
	void setAccelerationRate(float acceleration);
	void setRotationAngle(float angle);
	void setMaxSpeed(float speed);
	void setTurnRate(float rate);

	// Getters
	glm::vec2 getOrientation();
	
	float getAccelerationRate();
	float getRotationAngle();
	float getTurnRate();

private:

	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	float m_accelerationRate;
	float m_rotationAngle;
	float m_maxSpeed;
	float m_turnRate;

	void m_Move();
};

#endif /* defined (__SPACE_SHIP__) */