/*!
\file Tire.cpp 
*/
#include "tire.h"
#include <iostream>

void Tire::createTire(b2World * world, const sf::Vector2f size, const sf::Vector2f pos)
{
	//! Apply values for tire shape
	setPosition(pos);
	setSize(size);
	setOrigin(size * 0.5f);
	setOutlineThickness(0.f);
	//! Load tire texture
	if (!m_tex.loadFromFile(".\\assets\\textures\\tire.png"))
	{
		std::cout << "tire tex error" << std::endl;
	}
	//! smooth and apply texture
	m_tex.setSmooth(true);
	setTexture(&m_tex);

	//! Body definition
	b2BodyDef m_bodyDef;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(pos.x, pos.y);
	//! Creating the body in the world
	m_body = world->CreateBody(&m_bodyDef);
	//! Set the user data for sensors
	m_body->SetUserData(this);

	//! Shape definition
	b2PolygonShape m_shape;
	m_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	m_shape.m_radius = 0.f;

	//! Fixture definiton
	b2FixtureDef m_fixture;
	m_fixture.shape = &m_shape;
	m_fixture.friction = m_kfFriction;
	m_fixture.density = m_kfDensity;
	m_fixture.restitution = m_kfRestitution;
	//! Creating the fixture in the world
	m_body->CreateFixture(&m_fixture);
	
}

void Tire::setProperties(float maxForward, float power, float turn, float skid, float drag)
{
	m_fMaxSpeed = maxForward;
	m_fPower = power;
	m_fTurnPower = turn;
	m_fSkiddingImpulse = skid;
	m_fDrag = drag;
}

void Tire::updatePhysics()
{	
	
	b2Vec2 bv2Impulse = m_body->GetMass()* -getLateralVelocity();
	if (bv2Impulse.Length() > m_fSkiddingImpulse) bv2Impulse *= m_fSkiddingImpulse / bv2Impulse.Length(); //skidding
	//! apply the impulse to kill the angular spin on object the and the lateral velocity
	m_body->ApplyLinearImpulse(bv2Impulse, m_body->GetWorldCenter(), true);
	m_body->ApplyAngularImpulse(0.1f * m_body->GetInertia() * -m_body->GetAngularVelocity(), true);

	
	b2Vec2 bv2Normal = getForwardVelocity();
	float fSpeed = bv2Normal.Normalize();
	float dragMagnitude = -m_fDrag * fSpeed;
	//! drag
	m_body->ApplyForce(dragMagnitude * bv2Normal, m_body->GetWorldCenter(), true);
	
	//! get position of hitbox to apply to sf shape
	b2Vec2 pos = m_body->GetPosition();
	setPosition(pos.x, pos.y);
	setRotation(m_body->GetAngle() * RAD2DEG);

}

void Tire::updateControls(int tire, bool input, int key, int turn)
{	
	float fForce = 0.f; 
	float fTurnForce = 0.f;
	float fCurrentSpeed = 0.f;
	float fMaxSpeed = 0.f;
	int iForward = 0;

	switch (key)
		{
		case 0:
			iForward = 1;
			fMaxSpeed = m_fMaxSpeed;
		switch (turn)
		{
		case 1: fTurnForce = m_fTurnPower; break;
		case 2: fTurnForce = -m_fTurnPower; break;
		}

		break;

	case 1:
		iForward = 2;
		fMaxSpeed = -m_fMaxSpeed;
		switch (turn)
		{
		case 1: fTurnForce = m_fTurnPower;  break;
		case 2: fTurnForce = -m_fTurnPower; break;
		}
		break;
	}

	b2Vec2 bv2ForwardNormal = m_body->GetWorldVector(b2Vec2(0, 1));
	fCurrentSpeed = getForwardVelocity().Normalize();
	if (fMaxSpeed > fCurrentSpeed) fForce = m_fPower;
	else if (fMaxSpeed < fCurrentSpeed) fForce = -m_fPower;

	if (input)
	{
		if (tire == 0 || tire == 1)
		{
			m_body->ApplyTorque(fTurnForce, true);
			m_body->ApplyForce(fForce *bv2ForwardNormal, m_body->GetWorldCenter(), true);
		}
		else if (tire == 2 || tire == 3)
		{
			if (iForward != 2) m_body->ApplyForce(fForce *bv2ForwardNormal, m_body->GetWorldCenter(), true);
		}
		
	}
}


b2Vec2 Tire::getLateralVelocity()
{
	b2Vec2 bv2RightNormal = m_body->GetWorldVector(b2Vec2(1, 0));
	return b2Dot(bv2RightNormal, m_body->GetLinearVelocity()) * bv2RightNormal;
}
b2Vec2 Tire::getForwardVelocity()
{
	b2Vec2 bv2ForwardNormal = m_body->GetWorldVector(b2Vec2(0, 1));
	return b2Dot(bv2ForwardNormal, m_body->GetLinearVelocity()) * bv2ForwardNormal;
}

b2Body * Tire::getBody()
{
	return m_body;
}



