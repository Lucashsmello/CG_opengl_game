/*
 * Map.cpp
 *
 *  Created on: Apr 4, 2013
 *      Author: lucasmello
 */

#include "Map.h"
#include <GL/glut.h>
#include <iostream>

using namespace std;

extern Map runningMap;
extern bool debugmode_on;
int Map::mapIDcount=0;


void desblink(int value){
	runningMap.stopBlink();
}


Map::Map(PlayerParticipant& p,int mapLevel,void (*mapEndCallback)(int)): mapID(mapIDcount++){
	player=&p;
	addMovParticipant(p);
	running=false;
	num_runners=0;
	this->mapEndCallback=mapEndCallback;
	this->mapLevel=mapLevel;

	setLightPosition(0,6,0);
	setLightDirection(0,-1,0);

	light_diffuse[0]=0.5;
	light_diffuse[1]=0.5;
	light_diffuse[2]=0.5;
	light_diffuse[3]=1;

	light_spec[0]=0.5;
	light_spec[1]=0.5;
	light_spec[2]=0.5;
	light_spec[3]=1;

	constAttenuation=0.05; linearAttenuation=0.05; quadAttenuation=0;

	blink_screen=false;
}

unsigned int Map::addParticipant(Participant& p) {
	participants.push_back(&p);
	return participants.size()-1;
}

unsigned int Map::addMovParticipant(MovParticipant& p) {
	movparticipants.push_back(&p);
	if(p.getType()==RUNNER)
		num_runners++;
	return movparticipants.size()-1;
}

bool Map::TryMoveParticipant(unsigned int pid, RealPoint direction) {

	Participant* movp=movparticipants[pid];
	if(debugmode_on){
		movp->move(direction);
		return true;
	}

	unsigned int i;

	for(i=0;i<participants.size();i++){
		if(movp->collides(*participants[i],direction)){
			return false;
		}
	}

	for(i=0;i<movparticipants.size();i++){
		if(i==pid) continue;
		if(movp->collides(*movparticipants[i],direction)){
			if(movparticipants[i]->isPushable() and movp->getType()==PLAYER){
				if(direction.x==0){
					if(direction.z==0){
						return false;
					}
				}
				if(moveParticipant(i,direction)==false){
					return false;
				}
			}else{
				if((movp->getType()==RUNNER) and (movparticipants[i]->getType()==RUNNER)){
					continue;
				}
				if(pid==0 and movparticipants[i]->getType()==RUNNER){
					delete(movparticipants[i]);
					movparticipants.erase(movparticipants.begin()+i);
					i--;
					num_runners--;
					blink_screen=true;
					glutTimerFunc(50,desblink,0);
					if(num_runners==0){
						throw string("MAP ENDED");
					}
				}else{
					return false;
				}
			}
		}
	}

	movp->move(direction);
	return true;
}

bool Map::moveParticipant(unsigned int pid, RealPoint direction) {
	if(running){
		try{
			if(TryMoveParticipant(pid,RealPoint(direction.x,0,0))==false){
				TryMoveParticipant(pid,RealPoint(direction.x/8,0,0));
			}
			if(TryMoveParticipant(pid,RealPoint(0,direction.y,0))==false){
				if(TryMoveParticipant(pid,RealPoint(0,direction.y/8,0)) == false){
					if(direction.y<=0){
						movparticipants[pid]->setVerticalSpeed(0);
						movparticipants[pid]->jumping=false;
					}
				}
			}
			if(TryMoveParticipant(pid,RealPoint(0,0,direction.z))==false){
				TryMoveParticipant(pid,RealPoint(0,0,direction.z/8));
			}
		}catch(string& s){
			endMap();
		}
	}else{
		return false;
	}

	return true;
}

bool Map::movePlayer(RealPoint direction) {
	return moveParticipant(0,direction);
}

void Map::movePlayer() {
	moveParticipant(0,player->getSpeed());

}

void Map::draw() const {
	if(blink_screen){
			glClearColor( 1, 1.0, 1.0, 1 );
			glClear (GL_COLOR_BUFFER_BIT);
			glClearColor( 0, 0, 0, 0 );
			return;
	}


	unsigned int i;

	for(i=0;i<participants.size();i++){
		participants[i]->draw();
	}
	for(i=1;i<movparticipants.size();i++){
		movparticipants[i]->draw();
	}


    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_spec);
	glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 90 );

	glPushMatrix();
	glColor3f(0,1,1);
	glBegin(GL_LINES);
		glVertex3f(light_position[0],light_position[1],light_position[2]);
		glVertex3f(light_position[0]+light_dir[0],light_position[1]+light_dir[1],light_position[2]+light_dir[2]);
	glEnd();
	glPopMatrix();

	glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir);
    glLightf( GL_LIGHT0, GL_CONSTANT_ATTENUATION, constAttenuation );
    glLightf( GL_LIGHT0, GL_LINEAR_ATTENUATION, linearAttenuation );
    glLightf( GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadAttenuation );
}

void Map::gravityTick() {
	if(not debugmode_on){
		for(unsigned int i=0;i<movparticipants.size();i++){
			if(movparticipants[i]->getSpeed().y >= -0.1){
				movparticipants[i]->AddVerticalSpeed(-0.001);
			}
		}
	}
}

void gravity(int value){
	if(runningMap.isRunning() and (value==runningMap.getMapID())){
		runningMap.gravityTick();
		glutTimerFunc(10,gravity,value);
	}
}

void moveParticipants(int value){
	if(runningMap.isRunning() and (value==runningMap.getMapID())){
		runningMap.moveUnits();
		glutPostRedisplay();
		glutTimerFunc(10,moveParticipants,value);
	}
}


void Map::runMap() {
	running=true;
	glutTimerFunc(10,gravity,getMapID());
	glutTimerFunc(10,moveParticipants,getMapID());
}

bool Map::isRunning() const {
	return running;
}



void Map::stopRunning() {
	running=false;
}

void Map::moveUnits() {
	RealPoint movement=player->move(*this);
	moveParticipant(0,RealPoint(movement.x,0,0));
	if(moveParticipant(0,RealPoint(0,movement.y,0))==false){
		player->setVerticalSpeed(0);
		player->jumping=false;
	}
	moveParticipant(0,RealPoint(0,0,movement.z));

	for(unsigned int i=1;i<movparticipants.size();i++){
		movement=movparticipants[i]->move(*this);
		moveParticipant(i,RealPoint(movement.x,0,0));
		moveParticipant(i,RealPoint(0,movement.y,0));
		moveParticipant(i,RealPoint(0,0,movement.z));
	}
}


bool Map::hasCollision(const MovParticipant* movp,RealPoint mov) const {
	unsigned int i;

	for(i=0;i<participants.size();i++){
		if(movp==participants[i]) continue;
		if(movp->collides(*participants[i],mov)){
			return true;
		}
	}

	for(i=0;i<movparticipants.size();i++){
		if(movp==movparticipants[i]) continue;
		if((movp->getType()==RUNNER) and (movparticipants[i]->getType()==RUNNER)){
			continue;
		}
		if(movp->collides(*movparticipants[i],mov)){
			return true;
		}
	}
	return false;
}
/**
*                                                                                                                                                                                                                                   UFES - Departamento de Informática
*/

void Map::endMap(){
	running=false;
	for(int i=0;i<participants.size();i++){
		delete(participants[i]);
	}
	participants.clear();

	for(int i=1;i<movparticipants.size();i++){
		delete(movparticipants[i]);
	}
	movparticipants.clear();
	if(mapEndCallback!=NULL)
		this->mapEndCallback(this->mapLevel);
}



//Map::~Map(){
//	endMap();
//}

void Map::setLightPosition(GLfloat x,GLfloat y, GLfloat z){
	light_position[0]=x;
	light_position[1]=y;
	light_position[2]=z;
	light_position[3]=1;
}
void Map::resetMap() {
	mapLevel--;
	endMap();
}

void Map::setLightDirection(GLfloat x,GLfloat y, GLfloat z){
	light_dir[0]=x;
	light_dir[1]=y;
	light_dir[2]=z;
}
