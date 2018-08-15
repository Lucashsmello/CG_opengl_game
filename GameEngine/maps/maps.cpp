/*
 * maps.cpp
 *
 *  Created on: Apr 18, 2013
 *      Author: lucasmello
 */



#include "maps.h"
#include "ParticipantFactory.h"
#include "Runners/BasicRunner.h"
#include <vector>
#include <string>

using namespace std;

extern GLfloat look_angle;
extern GLfloat look_angle_Y;

PlayerParticipant playerp(RealPoint(0,0,0));
Map runningMap(playerp);
static int ALT[]={74,111,103,111,32,80, \
114,111,100,117,122,105,100,111,32,112,111, \
114,32,76,117,99,97,115,32,77,101,108,108,111, \
32,112,97,114,97,32,102,105,110,115,32,97,99,97, \
100,-61,-86,109,105,99,111,115,32,32,32,32,32,10,85, \
70,69,83,32,45,32,68,101,112,97,114,116,97,109,101,110, \
116,111,32,100,101,32,73,110,102,111,114,109,-61,-95,116, \
105,99,97,10,32,32,32,32,32,108,117,99,97,115,104,115,109, \
101,108,108,111,64,103,109,97,105,108,46,99,111,109,32};

void nextLevel(int mapid){
	if(mapid==5){
		cout << "\nG"<<"A"<<"M"<<"E"<<" OV"<<"ER" <<"\n" << endl;
	for(int i=0;i<121;i++){
		cout << (char) ALT[i];
	}
	cout << endl;
		exit(1);
	}
	if(mapid>=0){
		runningMap=ConstructMap(mapid+1);
		runningMap.runMap();
	}
}

Map ConstructBoxedMap2(){
	look_angle=-180;
	look_angle_Y=0;
	Map mapa(playerp,3,nextLevel);
	playerp.setPosition(RealPoint(1,3,1));
	vector<Participant*> map_structure;
	vector<MovParticipant*> map_movstructure;
	BasicRunner* runner;


	mapa.setLightPosition(0,5,0);
	mapa.setLightDirection(0.5,-1,0);
	mapa.setLightAttenuations(0.2,0.0001,0.0001);



	map_structure.push_back(createWall(RealPoint(0,0,0),5,0.45,5.5)); //wall1
	map_structure.push_back(createWall(RealPoint(-4,0,0),2,0.7,2)); //wall2
	map_structure.push_back(createWall(RealPoint(-4,0,1),2,1.5,2)); //wall3
	map_structure.push_back(createWall(RealPoint(-7,0,1),2,1.5,2));
	map_structure.push_back(createWall(RealPoint(-5,0,-1),2,0.55,3));

	map_structure.push_back(createWall(RealPoint(3,0.45,0),2.5,1.5,6));

	map_structure.push_back(createRoom(RealPoint(-8,0,-5.5/2),12,6,5.5)); //room
	runner=new BasicRunner(RealPoint(-4,4,1),RealPoint(0,0,1),PLAYER_BASE_RUNSPEED,2,true,true,true);
	runner->setJumpFactor(0.07);
	runner->setRandomRunFactor(40,100);
	map_movstructure.push_back(runner);

	runner=new BasicRunner(RealPoint(-4,5,1),RealPoint(0,0.4,0.55),PLAYER_BASE_RUNSPEED*0.667,1,true,true,true);
	runner->setJumpFactor(0.1);
	runner->setRandomRunFactor(45,100);
	map_movstructure.push_back(runner);

	runner=new BasicRunner(RealPoint(-4,5,1),RealPoint(1,0,0),PLAYER_BASE_RUNSPEED*0.667,10,true,true,true);
	runner->setJumpFactor(0.05);
	runner->setRandomRunFactor(45,100);
	map_movstructure.push_back(runner);

	runner=new BasicRunner(RealPoint(3,5.5,1),RealPoint(0,1,0),PLAYER_BASE_RUNSPEED*2,1,true,true,true);
	runner->setJumpFactor(0.06);
	runner->setRandomRunFactor(90,0);
	map_movstructure.push_back(runner);

	map_movstructure.push_back(new Box(RealPoint(-1,3,0),0.6));




	for(unsigned int i=0;i<map_structure.size();i++){
		mapa.addParticipant(*map_structure[i]);
	}
	for(unsigned int i=0;i<map_movstructure.size();i++){
		mapa.addMovParticipant(*map_movstructure[i]);
	}

	return mapa;
}

Map ConstructBoxedMap(){
	look_angle=-60;
	look_angle_Y=0;
	Map mapa(playerp,2,nextLevel);
	playerp.setPosition(RealPoint(1,3,1));
	vector<Participant*> map_structure;
	vector<MovParticipant*> map_movstructure;
	BasicRunner* runner;


	mapa.setLightPosition(0,5,0);
	mapa.setLightDirection(0.5,-1,0);
	mapa.setLightAttenuations(0.2,0.0001,0.0001);



	map_structure.push_back(createWall(RealPoint(0,0,0),4,0.45,4)); //wall1

	map_structure.push_back(createRoom(RealPoint(-8,0,-5.5/2),16,6,5.5)); //room
	map_movstructure.push_back(new BasicRunner(RealPoint(2,4,-2),RealPoint(1,0,0),PLAYER_BASE_RUNSPEED*3.67,2,true,true,false));
	map_movstructure.push_back(new BasicRunner(RealPoint(6,4,-2),PLAYER_BASE_RUNSPEED,2,true,true));
	map_movstructure.push_back(new Box(RealPoint(0,3,0),0.6));



	for(unsigned int i=0;i<map_structure.size();i++){
		mapa.addParticipant(*map_structure[i]);
	}
	for(unsigned int i=0;i<map_movstructure.size();i++){
		mapa.addMovParticipant(*map_movstructure[i]);
	}

	return mapa;
}

Map ConstructLabirintoMap(){
	look_angle=90;
	look_angle_Y=0;
	Map mapa(playerp,4,nextLevel);
	playerp.setPosition(RealPoint(0,2,0));
	vector<Participant*> map_structure;
	vector<MovParticipant*> map_movstructure;

	float wall_altura=5;
	float wall_espessura=0.1;
	float muro_flutuante_altura=0.55;

	mapa.setLightPosition(0,7,0);
	mapa.setLightDirection(0,-1,0);
	mapa.setLightAttenuations(0.25,0.0001,0.0001);


	map_structure.push_back(createRoom(RealPoint(-3,0,-5.25),8,10,9.5)); //room

	/*PARTE NORTE DO MAPA (Z>0):*/
	map_structure.push_back(createWall(RealPoint(2.25,0,1),1,wall_altura,3));
	map_structure.push_back(createWall(RealPoint(2.5,0,1),wall_espessura,wall_altura,4.5));
	map_structure.push_back(createWall(RealPoint(0.5,0,2.5),0.5,wall_altura,1.5));
	map_structure.push_back(createWall(RealPoint(-0.5,0,4.25-2/2),0.5,wall_altura,2));
	map_structure.push_back(createWall(RealPoint(-1.5,0,2.75),0.5,wall_altura,2));

	map_structure.push_back(createWall(RealPoint(4.75,0,1.5),0.5,wall_altura,0.5));
	map_structure.push_back(createWall(RealPoint(3.7,0,2.5),0.5,wall_altura,0.5));
	map_structure.push_back(createWall(RealPoint(4.5,0,4),0.7,wall_altura,1.5));
	map_structure.push_back(createWall(RealPoint(3.25,0,0.9),0.65,wall_altura,0.5));
	/***************************/

	/*PARTE SUL DO MAPA (Z<0):*/
	map_structure.push_back(createWall(RealPoint(1.5,0,-1.25),2,wall_altura,wall_espessura));
	map_structure.push_back(createWall(RealPoint(-0.5,0,0),wall_espessura,wall_altura,2.5));
	map_structure.push_back(createWall(RealPoint(1.5,0,0),2,wall_altura,2.5));
	map_structure.push_back(createWall(RealPoint(-1,0,-3.3),3,wall_altura,2.5));
	map_structure.push_back(createWall(RealPoint(1.3,0,-3.3),wall_espessura,wall_altura,2.5));
	map_structure.push_back(createWall(RealPoint(2.3,0,-4.8),wall_espessura,wall_altura,1));
	map_structure.push_back(createWall(RealPoint(2.3,0,-3),wall_espessura,wall_altura,1));
	map_structure.push_back(createWall(RealPoint(3.3,0,-3.3),wall_espessura,wall_altura,2.5));

	map_structure.push_back(createWall(RealPoint(4.15,0,-2),0.5,wall_altura,0.5));

	map_structure.push_back(createWall(RealPoint(4.3,muro_flutuante_altura,-4),2,0.5,1));
	map_structure.push_back(createWall(RealPoint(4.2,muro_flutuante_altura,0),3,0.5,1));

	map_structure.push_back(createWall(RealPoint(-1.6,muro_flutuante_altura,-1),0.5,wall_altura,0.5));
	map_structure.push_back(createWall(RealPoint(-1,muro_flutuante_altura, 0),0.5,wall_altura,0.5));
	map_structure.push_back(createWall(RealPoint(-1.75,muro_flutuante_altura, 1),0.5,wall_altura,0.5));
	map_structure.push_back(createWall(RealPoint(-2.5,muro_flutuante_altura, 0),0.5,wall_altura,0.5));
	/**************************/

	BasicRunner* runner=new BasicRunner(RealPoint(0,2,1),PLAYER_BASE_RUNSPEED*1.1,4,true,true,true);
	runner->setRandomRunFactor(45);
	map_movstructure.push_back(runner);

	runner=new BasicRunner(RealPoint(3.5,2,-1),RealPoint(0.4,0.4,0.4),PLAYER_BASE_RUNSPEED*1.1,1,true,true,false);
	map_movstructure.push_back(runner);

	map_movstructure.push_back(new BasicRunner(RealPoint(-2,2,-1),RealPoint(1,0,0),PLAYER_BASE_RUNSPEED*0.867,5.5,true,true,false));

	runner=new BasicRunner(RealPoint(3.5,2,-1),RealPoint(0,1,0),PLAYER_BASE_RUNSPEED,2,true,true,true);
	runner->setJumpFactor(0.055);
	runner->setRandomRunFactor(20,400);
	map_movstructure.push_back(runner);




	for(unsigned int i=0;i<map_structure.size();i++){
		mapa.addParticipant(*map_structure[i]);
	}
	for(unsigned int i=0;i<map_movstructure.size();i++){
		mapa.addMovParticipant(*map_movstructure[i]);
	}

	return mapa;
}

Map ConstructSecondMap(){
	look_angle=-125;
	look_angle_Y=0;
	Map mapa(playerp,5,nextLevel);
	playerp.setPosition(RealPoint(2,2,2));
	vector<Participant*> map_structure;
	vector<MovParticipant*> map_movstructure;

	mapa.setLightPosition(0,7,0);
	mapa.setLightDirection(0,-1,0);
	mapa.setLightAttenuations(0.25,0.0001,0.0001);

	map_structure.push_back(createRoom(RealPoint(-8,0,-8),16,8,16)); //room

	BasicRunner* runner=new BasicRunner(RealPoint(-0.2,2,-1),RealPoint(1,0,0),PLAYER_BASE_RUNSPEED*2.53,5,true,true,true);
	runner->setRandomRunFactor(75,0);
	map_movstructure.push_back(runner);
	runner=new BasicRunner(RealPoint(-0.2,2,1),PLAYER_BASE_RUNSPEED,4,true,true,true);
	runner->setRandomRunFactor(60,50);
	map_movstructure.push_back(runner);
	runner=new BasicRunner(RealPoint(0,2,0),RealPoint(0.55,0.35,0),PLAYER_BASE_RUNSPEED*3.67,1.1,false,false,true);
	runner->setRandomRunFactor(90,0);
	map_movstructure.push_back(runner);

	runner=new BasicRunner(RealPoint(2,2,0),RealPoint(0.15,0.25,0.4),PLAYER_BASE_RUNSPEED*1.2,2.5,true,true,true);
	runner->setRandomRunFactor(45,0);
	map_movstructure.push_back(runner);

	runner=new BasicRunner(RealPoint(2,2,-2),RealPoint(0,0.5,0.2),PLAYER_BASE_RUNSPEED*1.53,3,false,false,true);
	runner->setJumpFactor(0.05);
	runner->setRandomRunFactor(60,0);
	map_movstructure.push_back(runner);



	for(unsigned int i=0;i<map_structure.size();i++){
		mapa.addParticipant(*map_structure[i]);
	}
	for(unsigned int i=0;i<map_movstructure.size();i++){
		mapa.addMovParticipant(*map_movstructure[i]);
	}

	return mapa;
}

Map ConstructFirstMap(){
	Map mapa(playerp,1,nextLevel);
	playerp.setPosition(RealPoint(0,2,0));
	vector<Participant*> map_structure;
	vector<MovParticipant*> map_movstructure;

	mapa.setLightAttenuations(0.01,0.01,0.01);

	map_structure.push_back(createRoom(RealPoint(-4,0,-4),8,5,8)); //room

	map_movstructure.push_back(new BasicRunner(RealPoint(2,2,-1),PLAYER_BASE_RUNSPEED*0.75,3,true,true,false));
	map_movstructure.push_back(new BasicRunner(RealPoint(-2,2,1),RealPoint(1,0,0),PLAYER_BASE_RUNSPEED*1.1,3,true,false,false));




	for(unsigned int i=0;i<map_structure.size();i++){
		mapa.addParticipant(*map_structure[i]);
	}
	for(unsigned int i=0;i<map_movstructure.size();i++){
		mapa.addMovParticipant(*map_movstructure[i]);
	}

	return mapa;
}

Map ConstructMap(int maplevel){
	switch(maplevel){
		case 1:
			return ConstructFirstMap();
		case 5:
			return ConstructSecondMap();
		case 2:
			return ConstructBoxedMap();
		case 3:
			return ConstructBoxedMap2();
		case 4:
			return ConstructLabirintoMap();
		default:
			throw string("MAP LEVEL NOT RECGONIZED.");
			break;
	}
}
