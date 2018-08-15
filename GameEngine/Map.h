/*
 * Map.h
 *
 *  Created on: Apr 4, 2013
 *      Author: lucasmello
 */

#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include "Participants/Participant.h"
#include "Participants/MovParticipant.h"
#include "Participants/PlayerParticipant.h"

class Map {
	static int mapIDcount;
	int mapID;
	int mapLevel;
	std::vector<Participant*> participants;
	std::vector<MovParticipant*> movparticipants;
	PlayerParticipant* player;
	unsigned int num_runners;


//	Space ground;
	void (*mapEndCallback)(int);
	bool running;
	bool blink_screen;


	GLfloat light_position[4];
	GLfloat light_diffuse[4];
	GLfloat light_spec[4];
	GLfloat light_dir[3];

	GLfloat constAttenuation, linearAttenuation, quadAttenuation;

//	GLfloat light_position[] = { 0, 4.0, 0, 1.0 };
//	GLfloat light_ambient[] = { 0, 0, 0,1};
//	GLfloat light_diffuse[] = { 0.5, 0.5, 0.5,1};
//	GLfloat light_spec[] = { 0, 0, 0,1};
//	GLfloat light_dir[] = { -1, -1, 0};


	bool TryMoveParticipant(unsigned int pid, RealPoint direction);


public:
	Map(PlayerParticipant& p,int mapid=-1,void (*mapEndCallback)(int)=NULL);
	unsigned int addParticipant(Participant& p);
	unsigned int addMovParticipant(MovParticipant& p);

	bool moveParticipant(unsigned int pid, RealPoint direction);
	bool movePlayer(RealPoint direction);
	void movePlayer();

	const PlayerParticipant* getPlayer() const{return player;};

	void draw() const;
	void runMap();
	bool isRunning() const;
	void stopRunning();
	void moveUnits();
	void gravityTick();

	int getMapID()const{return mapID;};

	bool hasCollision(const MovParticipant* p, RealPoint mov) const;
	void endMap();
	void resetMap();

	void setLightPosition(GLfloat x,GLfloat y, GLfloat z);
	void setLightDirection(GLfloat x,GLfloat y, GLfloat z);

	void setLightAttenuations(GLfloat constAtt,GLfloat linAtt,GLfloat quadAtt){
		constAttenuation=constAtt;linearAttenuation=linAtt;quadAttenuation=quadAtt;
	}

	void stopBlink(){blink_screen=false;}




	~Map(){};

};

#endif /* MAP_H_ */
