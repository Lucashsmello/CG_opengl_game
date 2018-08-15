/*
 * PlayerParticipant.h
 *
 *  Created on: Apr 4, 2013
 *      Author: lucasmello
 */

#ifndef PLAYERPARTICIPANT_H_
#define PLAYERPARTICIPANT_H_

#include "MovParticipant.h"

#ifndef PLAYER_BASE_RUNSPEED
#define PLAYER_BASE_RUNSPEED (0.018)
#endif

class PlayerParticipant: public MovParticipant {
	friend class Map;
public:
	PlayerParticipant(RealPoint position);



};

#endif /* PLAYERPARTICIPANT_H_ */
