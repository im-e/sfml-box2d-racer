/*!
\file racetrack.cpp
*/
#include "racetrack.h"
#include <iostream>

void Racetrack::createRacetrack(b2World * world, std::vector<b2Vec2> innerPos, std::vector<b2Vec2> outerPos)
{
	
	int iTrackPoints = 0;
	//! Set the size for the first chain
	iTrackPoints = innerPos.size();
	//! Create the inner track
	InnerTrack.createTrack(world, innerPos, iTrackPoints);
	//! Set the user data for the track to be a pair for our sensors to use
	InnerTrack.setUserData(new std::pair<std::string, void *>(typeid(decltype(InnerTrack)).name(), &InnerTrack));

	//! Set the size for the second chain
	iTrackPoints = outerPos.size();
	//! Create the outer track
	OuterTrack.createTrack(world, outerPos, iTrackPoints);

	//! Set the user data for the track to be a pair for our sensors to use
	OuterTrack.setUserData(new std::pair<std::string, void *>(typeid(decltype(OuterTrack)).name(), &OuterTrack));
}

void Racetrack::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(OuterTrack);
	target.draw(InnerTrack);
}
