/*
 * ParticipantFactory.h
 *
 *  Created on: Apr 4, 2013
 *      Author: lucasmello
 */

#ifndef PARTICIPANTFACTORY_H_
#define PARTICIPANTFACTORY_H_

#include "Participants/Participant.h"
#include "Participants/Box.h"


Participant* createWall(RealPoint position,double xsize,double ysize,double zsize);
Participant* createRoom(RealPoint position,double xsize,double ysize,double zsize);


#endif /* PARTICIPANTFACTORY_H_ */
