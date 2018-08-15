/*
 * Participant.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: lucasmello
 */

#include "Participant.h"

Participant::Participant(RealPoint p,Space s, ParticipantType tipo) : position(p), space_ocuppied(s), type(tipo){}

void Participant::move(RealPoint direction) {
	this->position+=direction;
}

bool Participant::collides(const Participant& p, RealPoint mov) const {
	return space_ocuppied.collides(p.space_ocuppied,position-p.position,mov);
}

void Participant::draw() const {
	space_ocuppied.draw(position);
}




