/*
 * Controller.cpp
 *
 *  Created on: Apr 5, 2013
 *      Author: lucasmello
 */

#include <iostream>
#include <vector>
#include "Controller.h"
#include "GameEngine/Participants/PlayerParticipant.h"
#include "GameEngine/Map.h"

using namespace std;


extern int window_weight;
extern int window_height;
extern int window_id;

extern PlayerParticipant playerp;
extern Map runningMap;

bool player_moving=false;
GLfloat look_angle=200;
GLfloat look_angle_Y=0;
GLfloat mov_angle=0;
float mouse_sensivity=0.35;
bool uppressed=false;
bool downpressed=false;
bool leftpressed=false;
bool rightpressed=false;
bool jumping=false;
bool travarMouse=true;

bool debugmode_on=false;





void updatePlayerSpeed(){
	if(!uppressed and !rightpressed and !leftpressed and !downpressed and player_moving){
		playerp.AddRunSpeed(-PLAYER_BASE_RUNSPEED);
		player_moving=false;
	}else{
		if(not player_moving){
			playerp.AddRunSpeed(PLAYER_BASE_RUNSPEED);
			player_moving=true;
		}
	}

	mov_angle=0;

	if(rightpressed)
		mov_angle+=45;
	if(leftpressed)
		mov_angle-=45;
	if(not uppressed and not downpressed)
		mov_angle*=2;
	if(downpressed){
		mov_angle=-mov_angle;
		mov_angle+=180;
	}


	  playerp.speed_ang_xz=look_angle+mov_angle;
	  if( playerp.speed_ang_xz>360)
		  playerp.speed_ang_xz-=360;
	  if( playerp.speed_ang_xz<0)
		  playerp.speed_ang_xz+=360;
}




//void mouseFunc(int button, int state, int x, int y){
//	cout << "button: " << button << "; state: " << state << "; x,y" << x << ',' << y << endl;
//}



void mousePassiveFunc(int x, int y){
	if(not travarMouse){
		return;
	}
	int dx,dz;

	dx=window_weight/2-x;
	dz=window_height/2-y;

	if(dx==0 and dz==0)
		return;

	look_angle_Y+=dz*mouse_sensivity;
	if(look_angle_Y > MAX_ANGLE_VIEW)
		look_angle_Y=MAX_ANGLE_VIEW;
	if(look_angle_Y < -MAX_ANGLE_VIEW)
		look_angle_Y=-MAX_ANGLE_VIEW;

	  look_angle-=dx*mouse_sensivity;
	  if(look_angle>360)
		  look_angle-=360;
	  if(look_angle<0)
		  look_angle+=360;

	  playerp.speed_ang_xz=look_angle+mov_angle;
	  if( playerp.speed_ang_xz>360)
		  playerp.speed_ang_xz-=360;
	  if( playerp.speed_ang_xz<0)
		  playerp.speed_ang_xz+=360;

	  glutWarpPointer(window_weight/2,window_height/2);

	  glutPostRedisplay();
}

void keyboardReleased(unsigned char key, int x, int y){
	switch (key) {
		case 'w':
			uppressed=false;
			break;
		case 'a':
			leftpressed=false;
			break;
		case 'd':
			rightpressed=false;
			break;
		case 's':
			downpressed=false;
			break;
	      case 'q':
	    	  playerp.AddVerticalSpeed(+0.02);
	    	  break;
	      case 'e':
	    	  playerp.AddVerticalSpeed(-0.02);
	    	  break;
		default:
			return;
	}

	   updatePlayerSpeed();
}

void keyboardPressed(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
      case '!':
    	  runningMap.resetMap();
    	  return;
      case '$':
    	  runningMap.endMap();
    	  return;
      case 'x': //+senbilidade
		if(mouse_sensivity < 1)
			mouse_sensivity+=0.05;
		return;
      case 'z':
		if(mouse_sensivity > 0.06)
			mouse_sensivity-=0.05;
		return;
      case ';':
		travarMouse=not travarMouse;
		glutWarpPointer(window_weight/2,window_height/2);
		return;
      case 'w':
    	  uppressed=true;
    	  break;
      case 'd':
    	  rightpressed=true;
    	  break;
      case 'a':
    	  leftpressed=true;
    	  break;
      case 's':
    	  downpressed=true;
    	  break;
      case 'q':
    	  if(debugmode_on)
    		  playerp.AddVerticalSpeed(-0.02);
    	  break;
      case 'e':
    	  if(debugmode_on)
    		  playerp.AddVerticalSpeed(+0.02);
    	  break;
      case '%':
    	  debugmode_on=!debugmode_on;
    	  return;
      case ' ': //SPACE
    	  if(not debugmode_on){
    		  playerp.jump();
    	  }
    	  return;
      default:
    	  return;

   }

   updatePlayerSpeed();
}


void menu(int num){
	switch(num){
	case 0:
		glutDestroyWindow(window_id);
		exit(0);
		break;
	case 1: //+senbilidade
		if(mouse_sensivity < 1)
			mouse_sensivity+=0.05;
		break;
	case 2:
		if(mouse_sensivity > 0.06)
			mouse_sensivity-=0.05;
		break;
	case 3:
		runningMap.resetMap();
		break;
	case 4:
		travarMouse=not travarMouse;
		glutWarpPointer(window_weight/2,window_height/2);
		break;
	}
}

void createMenu(void){
	glutCreateMenu(menu);
    glutAddMenuEntry("Recomecar Fase [!]", 3);
    glutAddMenuEntry("+Sensibilidade Mouse [x]", 1);
    glutAddMenuEntry("-Sensibilidade Mouse [z]", 2);
    glutAddMenuEntry("Travar/Destravar Mouse [;]", 4);
    glutAddMenuEntry("Quit [ESC]", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
