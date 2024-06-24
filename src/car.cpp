#include "car.h"
#include <iostream>
/*!
\file car.cpp
*/


void Car::createCar(b2World * world, const sf::Vector2f & pos, const sf::Vector2f size)
{
	// Apply the values for the car shape
	m_sfShape.setPosition(pos);
	m_sfShape.setSize(size);
	m_sfShape.setOrigin(size * 0.5f);
	m_sfShape.setOutlineThickness(0.f);
	// Load in car texture
	if (!m_tex.loadFromFile(".\\assets\\textures\\car.png"))
	{
		std::cout << "car tex error" << std::endl;
	}
	// Smooth and apply texture
	m_tex.setSmooth(true);
	m_sfShape.setTexture(&m_tex);

	// Body definition
	b2BodyDef m_bodyDef;
	m_bodyDef.position.Set(pos.x, pos.y);
	m_bodyDef.type = b2_dynamicBody;
	// Creating the body in the world
	m_body = world->CreateBody(&m_bodyDef);
	// Set the user data for sensors
	m_body->SetUserData(this);

	// Shape definition
	b2PolygonShape m_shape;
	m_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	m_shape.m_radius = 0.f;

	// Fixture definiton
	b2FixtureDef m_fixture;
	m_fixture.shape = &m_shape;
	m_fixture.friction = m_kfFriction;
	m_fixture.density = m_kfDensity;
	m_fixture.restitution = m_kfRestitution;
	// Creating the fixture in the world
	m_body->CreateFixture(&m_fixture);
	
	// Vector for storing the positions of the tires
	std::vector<sf::Vector2f> vv2fTirePos;
	vv2fTirePos.push_back(sf::Vector2f(.3f, .35f));	// front left tire
	vv2fTirePos.push_back(sf::Vector2f(-.3, .35f));	// front right
	vv2fTirePos.push_back(sf::Vector2f(.3f, -.35f));// back left
	vv2fTirePos.push_back(sf::Vector2f(-.3f, -.35f));// back right

	//Vector for storing all the properties of the tires
	std::vector<float> vfTireProperties;
	vfTireProperties.push_back(100.f);	//Max Forward
	vfTireProperties.push_back(25.f);	//Gas Power
	vfTireProperties.push_back(2.f);	//Turn Power 
	vfTireProperties.push_back(0.17f);	//Skidding
	vfTireProperties.push_back(1.7f);	//Drag

	// Tire + Joint Creation
	b2RevoluteJointDef frontLeftJointDef;
	// Create tires using properties and positions
	m_tires[0].createTire(world, sf::Vector2f(0.16f, 0.34f), sf::Vector2f((vv2fTirePos[0].x + pos.x), (vv2fTirePos[0].y + pos.y)));
	m_tires[0].setProperties(vfTireProperties[0], vfTireProperties[1], vfTireProperties[2], vfTireProperties[3], vfTireProperties[4]);
	// Set up the joints
	frontLeftJointDef.bodyA = getBody();
	frontLeftJointDef.localAnchorA.Set(vv2fTirePos[0].x, vv2fTirePos[0].y);
	frontLeftJointDef.bodyB = m_tires[0].getBody();
	frontLeftJointDef.localAnchorB.SetZero();
	frontLeftJointDef.collideConnected = false;
	frontLeftJointDef.enableLimit = true;
	// Create joints in the world
	frontLeftJoint = (b2RevoluteJoint*)world->CreateJoint(&frontLeftJointDef);

	// Apply for other tires
	b2RevoluteJointDef frontRightJointDef;
	m_tires[1].createTire(world, sf::Vector2f(0.16f, 0.34f), sf::Vector2f((vv2fTirePos[1].x + pos.x), (vv2fTirePos[1].y + pos.y)));
	m_tires[1].setProperties(vfTireProperties[0], vfTireProperties[1], vfTireProperties[2], vfTireProperties[3], vfTireProperties[4]);
	frontRightJointDef.bodyA = getBody();
	frontRightJointDef.bodyB = m_tires[1].getBody();
	frontRightJointDef.collideConnected = false;
	frontRightJointDef.localAnchorB.SetZero();
	frontRightJointDef.localAnchorA.Set(vv2fTirePos[1].x, vv2fTirePos[1].y);
	frontRightJointDef.enableLimit = true;
	frontRightJoint = (b2RevoluteJoint*)world->CreateJoint(&frontRightJointDef);

	b2WeldJointDef backLeftJointDef;
	m_tires[2].createTire(world, sf::Vector2f(0.16f, 0.34f), sf::Vector2f((vv2fTirePos[2].x + pos.x), (vv2fTirePos[2].y + pos.y)));
	m_tires[2].setProperties(vfTireProperties[0], vfTireProperties[1], vfTireProperties[2], vfTireProperties[3], vfTireProperties[4]);
	backLeftJointDef.bodyA = getBody();
	backLeftJointDef.bodyB = m_tires[2].getBody();
	backLeftJointDef.collideConnected = false;
	backLeftJointDef.localAnchorB.SetZero();
	backLeftJointDef.localAnchorA.Set(vv2fTirePos[2].x, vv2fTirePos[2].y);
	b2WeldJoint* backLeftJoint = (b2WeldJoint*)world->CreateJoint(&backLeftJointDef);

	b2WeldJointDef backRightJointDef;
	m_tires[3].createTire(world, sf::Vector2f(0.16f, 0.34f), sf::Vector2f((vv2fTirePos[3].x + pos.x), (vv2fTirePos[3].y + pos.y)));
	m_tires[3].setProperties(vfTireProperties[0], vfTireProperties[1], vfTireProperties[2], vfTireProperties[3], vfTireProperties[4]);
	backRightJointDef.bodyA = getBody();
	backRightJointDef.bodyB = m_tires[3].getBody();
	backRightJointDef.collideConnected = false;
	backRightJointDef.localAnchorB.SetZero();
	backRightJointDef.localAnchorA.Set(vv2fTirePos[3].x, vv2fTirePos[3].y);
	b2WeldJoint* backRightJoint = (b2WeldJoint*)world->CreateJoint(&backRightJointDef);

	//Set the user data for each tire to be a pair for our sensors to use
	for (Tire& tire : m_tires) tire.setUserData(new std::pair<std::string, void *>(typeid(decltype(tire)).name(), &tire));
}

void Car::update(bool input, int gas, int turn)
{
	// float for the current angle of a joint
	float fCurrentAngle = 0;
	// float for the angle that we want
	float fDesiredAngle = 0;
	// float for angle range which the wheels can turn
	float fWheelLock = 40 * DEG2RAD;
	// float for the wheel turning speed
	float fTurnSpeed = 320 * DEG2RAD;
	// float to control how much the wheel will turn per second
	float fTurnPerStep = fTurnSpeed / 60.0f;
	
	// If the player is inputting left/right
	switch (turn)
	{
	case 1: fDesiredAngle = fWheelLock; break;	//right
	case 2: fDesiredAngle = -fWheelLock; break;	//left
	}

	// Get the current angle
	fCurrentAngle = frontLeftJoint->GetJointAngle();
	// Find our new angle
	float fAdjustedAngle = fDesiredAngle - fCurrentAngle;
	// Clamps our angle to a certain value range
	fAdjustedAngle = b2Clamp(fAdjustedAngle, -fTurnPerStep, fTurnPerStep);
	// Add to our current angle
	float fNewAngle = fCurrentAngle + fAdjustedAngle;

	//If there is an input(player is moving), move the wheels
	if (input)
	{
		frontRightJoint->SetLimits(fNewAngle, fNewAngle);
		frontLeftJoint->SetLimits(fNewAngle, fNewAngle);
	}

	// Update tires
	for (int x = 0; x < 4; x++)
	{
		m_tires[x].updateControls(x, input, gas, turn);
		m_tires[x].updatePhysics();
	}

	// Update the shape
	b2Vec2 pos = m_body->GetPosition();
	m_sfShape.setPosition(pos.x, pos.y);
	m_sfShape.setRotation(m_body->GetAngle() * RAD2DEG);
}

b2Body * Car::getBody()
{
	return m_body;
}

void Car::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sfShape);
	// Draws every tire in m_tires
	for (Tire tire : m_tires) target.draw(tire);
	
}

void Car::carCollidedWithFinish(bool collision)
{
	// Start race : If the player has just spawned, and player has left the start
	if (m_bSpawned && !collision)
	{	
		// reset clocks
		m_clCourseTime.restart();
		m_clLapTime.restart();
		// set control values
		m_bRaceStarted = true;
		m_bSpawned = false;
	}
	// If the race has started
	if (!m_bSpawned)
	{
		//if Player has passed the checkpoint
		if (m_bCheckpointPassed)
		{
			// set time
			m_afTimes[m_iLaps] = m_clLapTime.getElapsedTime().asSeconds();
			// increase lap count
			m_iLaps++;
			// restart lap clock
			m_clLapTime.restart();
			// set control values
			m_bCheckpointPassed = false;
		}
		//if player is on the fifth lap
		if (m_iLaps == 5)
		{
			// Set the finished course time
			fCourseTime = m_clCourseTime.getElapsedTime().asSeconds();
			m_bCourseComplete = true;
		}

	}

}

