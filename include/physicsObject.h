#ifndef PHYSICSOBJECT_HEADER
#define PHYSICSOBJECT_HEADER
/*!
\file physicsObject.h
* \brief This file contains the definition for physicsObject class
*/

#include <Box2D/Box2D.h>
//! Degrees to radians
#define DEG2RAD 0.017453f
//! Radians to Degrees
#define RAD2DEG 57.29577f

/*!
\class physicsObject
* \brief physicsObject is a class which defines any object that will be added to the world, and will define its body and its properties
*/
class physicsObject 
{
protected:
	b2Body * m_body = nullptr; //!< Box2D body
	const float m_kfDensity = 1.0f; 
	const float m_kfFriction = 0.f;
	const float m_kfRestitution = 0.f;

public:

	void setUserData(void* data) { m_body->SetUserData(data); };
	b2Body * getBody() { return m_body; };
	
};
#endif