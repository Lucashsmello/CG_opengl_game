/*
 * Box.cpp
 *
 *  Created on: Apr 12, 2013
 *      Author: lucasmello
 */

#include "Box.h"
#include "Formas/RectPrisma.h"
#include <iostream>

GLuint Box::boxtextureid;

using namespace std;

Box::Box(RealPoint position,float size) : MovParticipant(position,Space(),NOTHING_SPECIAL, true){
	RectPrisma* prism=new RectPrisma(size,size,size,RealPoint(1,1,1));
	prism->setTexture(Box::boxtextureid);
	space_ocuppied.addSolid(prism,RealPoint(0,0,0));
}

