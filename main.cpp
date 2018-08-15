/**
* Jogo Produzido por Lucas Mello para fins acadêmicos
*   UFES - Departamento de Informática
*   lucashsmello@gmail.com
*/

#include <GL/glut.h>
#include <stdlib.h>
#include "GameEngine/Space.h"
#include <vector>
#include <iostream>
#include <cmath>
#include "GameEngine/Map.h"
#include "Controller.h"
#include "GameEngine/ParticipantFactory.h"
#include "Participants/Runners/Runner.h"
#include "Participants/Runners/BasicRunner.h"
#include "Box.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "LoadTexture/image.h"
#include "maps/maps.h"

using namespace std;


double ang=0;
int view_angX=0,view_angY=0;
GLfloat camerapos=5;
extern GLfloat look_angle;
extern GLfloat look_angle_Y;
int window_weight=800;
int window_height=800;
int window_id;

extern Map runningMap;
extern bool debugmode_on;

void drawEixos(float size,float altura=0){
	glColor3f(1,0,0);
	glBegin(GL_LINES);
		glVertex3f(0,altura,0);
		glVertex3f(size,altura,0);
	glEnd();

	glColor3f(0,1,0);
	glBegin(GL_LINES);
		glVertex3f(0,altura,0);
		glVertex3f(0,size+altura,0);
	glEnd();

	glColor3f(0,1,1);
	glBegin(GL_LINES);
		glVertex3f(0,altura,0);
		glVertex3f(0,altura,size);
	glEnd();
}

extern GLuint RoomWallTexture;
extern GLuint RoomGroundTexture;


void generateTextures(){
	glGenTextures(1, &Box::boxtextureid);
	glBindTexture(GL_TEXTURE_2D, Box::boxtextureid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	image_load_to_texture("textures/crate.jpeg");

	glGenTextures(1, &RoomWallTexture);
	glBindTexture(GL_TEXTURE_2D, RoomWallTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	image_load_to_texture("textures/portal-walltexture-4.jpeg");

	glGenTextures(1, &RoomGroundTexture);
	glBindTexture(GL_TEXTURE_2D, RoomGroundTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	image_load_to_texture("textures/portal2texture-2.jpeg");

}


void OpenGLInit(void)
{
	glShadeModel (GL_SMOOTH);
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);





    GLfloat lmodel_ambient[] = { 0.25, 0.25, 0.25, 1.0 };
//    GLfloat lmodel_ambient[] = { 0, 0, 0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    generateTextures();


}




void display(){
	glEnable(GL_TEXTURE_2D);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   glMatrixMode (GL_PROJECTION);
	   glLoadIdentity ();
	   gluPerspective(77,1,0.1,60);
	   glMatrixMode (GL_MODELVIEW);
	glColor3f (1.0, 1.0, 1.0);
	glLoadIdentity ();             /* clear the matrix */
		   /* viewing transformation  */

	const PlayerParticipant* player=runningMap.getPlayer();
	gluLookAt (player->getPosition().x, player->getPosition().y *1.2, player->getPosition().z,
			player->getPosition().x+cos(look_angle*PI / 180), player->getPosition().y * 1.2 + sin(look_angle_Y *PI/180), player->getPosition().z+sin(look_angle*PI / 180),
			0.0, 1.0, 0.0);

	if(debugmode_on){
		drawEixos(3);
	}

	runningMap.draw();






#ifdef USE_GLUT_DOUBLE_BUFFERS
	glutSwapBuffers();
#else
	glFlush ();
#endif
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(77,1,0.1,60);
   glMatrixMode (GL_MODELVIEW);

   window_weight=w;
   window_height=h;
   glutWarpPointer(window_weight/2,window_height/2);
}




int main(int argc, char** argv)
{
   glutInit(&argc, argv);
#ifdef USE_GLUT_DOUBLE_BUFFERS
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
#else
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
#endif
   glutInitWindowSize (window_weight, window_height);
   glutInitWindowPosition (0, 0);
   window_id=glutCreateWindow (argv[0]);

   OpenGLInit();
   runningMap=ConstructMap(1);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);

   glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
   glutKeyboardFunc(keyboardPressed);
   glutKeyboardUpFunc(keyboardReleased);
   glutPassiveMotionFunc(mousePassiveFunc);
   glutWarpPointer(window_weight/2,window_height/2);

   runningMap.runMap();
   createMenu();

   glutMainLoop();
   return 0;
}
