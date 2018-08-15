/*
 * Runner.h
 *
 *  Created on: Apr 13, 2013
 *      Author: lucasmello
 */

#ifndef RUNNER_H_
#define RUNNER_H_

#include "MovParticipant.h"

class Runner: public MovParticipant {
public:
	Runner(RealPoint position, Space s);
	virtual RealPoint move(const Map& ambiente)=0;
};

#endif /* RUNNER_H_ */
