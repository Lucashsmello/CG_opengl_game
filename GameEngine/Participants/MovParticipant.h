/*
 * MovParticipant.h
 *
 *  Created on: Apr 12, 2013
 *      Author: lucasmello
 */

#ifndef MOVPARTICIPANT_H_
#define MOVPARTICIPANT_H_

#include "Participant.h"

class Map;

class MovParticipant: public Participant {
	friend class Map;
	bool jumping;
protected:
	double jump_factor;
	double speed;
	double speedVertical;
	bool pushable;



public:
	double speed_ang_xz;
	MovParticipant(Point<GLfloat> position,Space space,ParticipantType tipo=NOTHING_SPECIAL,bool ispushable=false,double jumpfactor=0.05);
	void AddRunSpeed(double speed);
	void AddVerticalSpeed(double speed);
	RealPoint getSpeed() const;
	void setVerticalSpeed(double s){speedVertical=0;};
	bool isPushable()const{return pushable;}
	virtual RealPoint move(const Map& ambiente);
	bool isJumping() const{return jumping;}
	void jump();
	void setJumpFactor(double jumpfactor){jump_factor=jumpfactor;}
};

#endif /* MOVPARTICIPANT_H_ */
