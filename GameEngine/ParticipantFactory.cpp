/*
 * ParticipantFactory.cpp
 *
 *  Created on: Apr 12, 2013
 *      Author: lucasmello
 */



#include "ParticipantFactory.h"
#include "Formas/RectPrisma.h"
#include <vector>

using namespace std;


GLuint RoomWallTexture;
GLuint RoomGroundTexture;

Participant* createWall(RealPoint pos, double xsize, double altura,double zsize) {

   RectPrisma* prism=new RectPrisma(xsize,altura,zsize,RealPoint(1,1,1));
   prism->setTexture(RoomWallTexture);
//   prism->setRepeatTextureRate(xsize/7,2);
   Space space(prism);

   return new Participant(RealPoint(pos.x,pos.y+altura/2,pos.z),space);
}



Participant* createRoom(RealPoint position, double xsize, double ysize,
		double zsize) {

	vector<Forma*> walls;
	vector<RealPoint> positions;
	RealPoint color(0.5,0.5,0.5);

	walls.push_back(new RectPrisma(xsize,ysize,0.1,color));
	walls.back()->setTexture(RoomWallTexture); ((RectPrisma*)walls.back())->setRepeatTextureRate(xsize/7,2);
	walls.push_back(new RectPrisma(0.1,ysize,zsize,color));
	walls.back()->setTexture(RoomWallTexture);((RectPrisma*)walls.back())->setRepeatTextureRate(zsize/7,2);
	walls.push_back(new RectPrisma(xsize,0.1,zsize,color*1.5));
	walls.back()->setTexture(RoomGroundTexture);((RectPrisma*)walls.back())->setRepeatTextureRate(5*zsize/xsize,5);

	walls.push_back(new RectPrisma(xsize,ysize,0.1,color));
	walls.back()->setTexture(RoomWallTexture);((RectPrisma*)walls.back())->setRepeatTextureRate(xsize/7,2);
	walls.push_back(new RectPrisma(0.1,ysize,zsize,color));
	walls.back()->setTexture(RoomWallTexture);((RectPrisma*)walls.back())->setRepeatTextureRate(zsize/7,2);
	walls.push_back(new RectPrisma(xsize,0.1,zsize,color*1.5));
	walls.back()->setTexture(RoomGroundTexture);((RectPrisma*)walls.back())->setRepeatTextureRate(5*zsize/xsize,5);


	xsize/=2;ysize/=2;zsize/=2;
	position.x+=xsize;
	position.z+=zsize;
	xsize+=0.05;zsize+=0.05;

	positions.push_back(RealPoint(0,ysize,zsize));
	positions.push_back(RealPoint(xsize,ysize,0));
	positions.push_back(RealPoint(0,2*ysize+0.05,0));


	positions.push_back(RealPoint(0,ysize,-zsize));
	positions.push_back(RealPoint(-xsize,ysize,0));
	positions.push_back(RealPoint(0,-0.05,0));



	Space space(walls,positions);

	return new Participant(position,space);

}

