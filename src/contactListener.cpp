/*!
\file contactListener.cpp
*/
#include "contactListener.h"
#include <iostream>

void ContactListener::BeginContact(b2Contact * contact)
{
	//! Get the bodies from both sides of the contact
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	//! Set the data for the bodies
	std::pair<std::string, void *> dataA = *(std::pair<std::string, void *>*) bodyA->GetUserData();
	std::pair<std::string, void *> dataB = *(std::pair<std::string, void *>*) bodyB->GetUserData();

	//! If car Collides with
	if (typeid(Car).name() == dataA.first)
	{
		//! Start
		if (typeid(Start).name() == dataB.first)
		{
			Car * car = static_cast<Car*>(dataA.second); 
			//! if it doesnt return null (is colliding) then run the collision with finish function
			if (car != nullptr) car->carCollidedWithFinish(true);
		}
	}

	//! If car collides with Start
	if (typeid(Car).name() == dataB.first)
	{
		if (typeid(Start).name() == dataA.first)
		{
			Car * car = static_cast<Car*>(dataB.second);
			if (car != nullptr) car->carCollidedWithFinish(true);
		}
	}
	
	//! If car collides with checkpoint
	if (typeid(Car).name() == dataA.first)
	{
		if (typeid(Checkpoint).name() == dataB.first)
		{
			Car * car = static_cast<Car*>(dataA.second);
			//! if it doesnt return null (is colliding) then run the collision with checkpoint function
			if (car != nullptr) car->carCollidedWithCheckpoint();
		}
	}

	if (typeid(Car).name() == dataB.first)
	{
		if (typeid(Checkpoint).name() == dataA.first)
		{
			Car * car = static_cast<Car*>(dataB.second);
			if (car != nullptr) car->carCollidedWithCheckpoint();
		}
	}


}

void ContactListener::EndContact(b2Contact * contact)
{
	//! Get the bodies from both sides of the contact
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	//! Set the data for the bodies
	std::pair<std::string, void *> dataA = *(std::pair<std::string, void *>*) bodyA->GetUserData();
	std::pair<std::string, void *> dataB = *(std::pair<std::string, void *>*) bodyB->GetUserData();

	if (typeid(Car).name() == dataA.first)
	{
		if (typeid(Start).name() == dataB.first)
		{
			Car * car = static_cast<Car*>(dataA.second);
			if (car != nullptr) car->carCollidedWithFinish(false);
		}
	}

	if (typeid(Car).name() == dataB.first)
	{
		if (typeid(Start).name() == dataA.first)
		{
			Car * car = static_cast<Car*>(dataB.second);
			if (car != nullptr) car->carCollidedWithFinish(false);
		}
	}

	if (typeid(Car).name() == dataA.first)
	{
		if (typeid(Checkpoint).name() == dataB.first)
		{
			Car * car = static_cast<Car*>(dataA.second);
			if (car != nullptr) car->carCollidedWithCheckpoint();
		}
	}

	if (typeid(Car).name() == dataB.first)
	{
		if (typeid(Checkpoint).name() == dataA.first)
		{
			Car * car = static_cast<Car*>(dataB.second);
			if (car != nullptr) car->carCollidedWithCheckpoint();
		}
	}

}
