/*
 * Box.h
 *
 *  Created on: Apr 12, 2013
 *      Author: lucasmello
 */

#ifndef BOX_H_
#define BOX_H_

#include "MovParticipant.h"

class Box: public MovParticipant {

public:
	static GLuint boxtextureid;
	Box(RealPoint position,float size);
};

#endif /* BOX_H_ */
