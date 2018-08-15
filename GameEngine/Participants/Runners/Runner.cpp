/*
 * Runner.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: lucasmello
 */

#include "Runner.h"

#include <iostream>

using namespace std;

Runner::Runner(RealPoint position,Space s) :
		MovParticipant(position,
					s,
				RUNNER,false,0){

}

