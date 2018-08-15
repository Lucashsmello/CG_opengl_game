/*
 * Participant.h
 *
 *  Created on: Mar 30, 2013
 *      Author: lucasmello
 */

#ifndef PARTICIPANT_H_
#define PARTICIPANT_H_

#include "Space.h"

enum ParticipantType{
	PLAYER,
	RUNNER,
	NOTHING_SPECIAL
};

class Participant {
	RealPoint position;
	const ParticipantType type;

protected:
	Space space_ocuppied;

public:
	Participant(RealPoint position,Space space,ParticipantType type=NOTHING_SPECIAL);


	void move(RealPoint direction);

	RealPoint getPosition() const {
		return position;
	}
	/*
	 * METODO PERIGOSO!
	 */
	void setPosition(RealPoint p){
		position=p;
	}

	bool collides(const Participant& p,RealPoint mov) const;

	void draw() const;

	ParticipantType getType() const{
		return type;
	}


	~Participant(){};
};

#endif /* PARTICIPANT_H_ */
