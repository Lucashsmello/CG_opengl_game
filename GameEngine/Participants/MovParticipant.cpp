/*
 * MovParticipant.cpp
 *
 *  Created on: Apr 12, 2013
 *      Author: lucasmello
 */

#include "MovParticipant.h"
#include <iostream>

using namespace std;

#define MIN_SPEED 0.0005

MovParticipant::MovParticipant(Point<GLfloat> position,Space space,ParticipantType tipo,bool ispushable, double jumpfactor)
	: Participant(position,space,tipo){
	speed=0;
	speedVertical=0;
	speed_ang_xz=0;
	pushable=ispushable;
	jumping=false;
	jump_factor=jumpfactor;
}



void MovParticipant::AddRunSpeed(double s) {
	speed+=s;
	if(abs(speed)<=MIN_SPEED){
		speed=0;
	}
}

void MovParticipant::AddVerticalSpeed(double s) {
	speedVertical+=s;
}

RealPoint MovParticipant::getSpeed() const {

	return RealPoint(speed*cos(speed_ang_xz * PI /180),
			speedVertical,
			speed*sin(speed_ang_xz * PI /180));
}



RealPoint MovParticipant::move(const Map& ambiente) {
	return getSpeed();
}

void MovParticipant::jump() {
  if(not jumping){
	  jumping=true;
	  AddVerticalSpeed(jump_factor);
  }
}
