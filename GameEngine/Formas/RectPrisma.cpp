/*
 * RectPrisma.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: lucasmello
 */

#include "RectPrisma.h"
#include <vector>

using namespace std;

bool RectPrisma::contains(Point<GLfloat> p) const {
	if(abs(p.x) < length/2){
		if(abs(p.y) < height/2){
			if(abs(p.z) < width/2){
				return true;
			}
		}
	}

	return false;
}

RectPrisma::RectPrisma(GLfloat l, GLfloat h, GLfloat z,RealPoint c) {
	length=l;
	height=h;
	width=z;
	color=c;

	repeatTextureRateX=1;repeatTextureRateZ=1;
}

void RectPrisma::draw() const{
	glPushMatrix();

	if(hasTexture()){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, getTextureId());
    	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}else{
		glDisable(GL_TEXTURE_2D);
	}
	glScalef(length,height,width);

	glColor3f(color.x,color.y,color.z);


    GLfloat mat_specular[] = { 0,0,0, 1};
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT,GL_SHININESS,0.0);


	   glBegin (GL_QUADS);
	     glNormal3f(0,0,1.0f);
	     glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f, -0.5f, 0.5f);
	     glTexCoord2f (repeatTextureRateX,0); glVertex3f ( 0.5f, -0.5f, 0.5f);
	     glTexCoord2f (repeatTextureRateX, repeatTextureRateZ); glVertex3f ( 0.5f,  0.5f, 0.5f);
	     glTexCoord2f (0.0f,repeatTextureRateZ); glVertex3f (-0.5f,  0.5f, 0.5f);

	     glNormal3f(0,0,-1.0f);
	     glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f, -0.5f, -0.5f);
	     glTexCoord2f (repeatTextureRateX,0); glVertex3f ( 0.5f, -0.5f, -0.5f);
	     glTexCoord2f (repeatTextureRateX, repeatTextureRateZ); glVertex3f ( 0.5f,  0.5f, -0.5f);
	     glTexCoord2f ( 0.0f,repeatTextureRateZ); glVertex3f (-0.5f,  0.5f, -0.5f);

	     glNormal3f(0,-1.0f,0);
	     glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f, -0.5f,-0.5f);
	     glTexCoord2f (repeatTextureRateX,0.0f); glVertex3f (-0.5f, -0.5f, 0.5f);
	     glTexCoord2f (repeatTextureRateX, repeatTextureRateZ); glVertex3f ( 0.5f, -0.5f, 0.5f);
	     glTexCoord2f (0.0f,repeatTextureRateZ); glVertex3f ( 0.5f, -0.5f,-0.5f);

	     glNormal3f(0,1.0f,0);
	     glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f,  0.5f, -0.5f);
	     glTexCoord2f (repeatTextureRateX,0.0f); glVertex3f (-0.5f,  0.5f,  0.5f);
	     glTexCoord2f (repeatTextureRateX, repeatTextureRateZ); glVertex3f ( 0.5f,  0.5f,  0.5f);
	      glTexCoord2f (0.0f,repeatTextureRateZ); glVertex3f ( 0.5f,  0.5f, -0.5f);

	     glNormal3f(-1.0f,0,0);
	     glTexCoord2f (0.0f, 0.0f); glVertex3f (-0.5f, -0.5f,-0.5f);
	     glTexCoord2f (repeatTextureRateX,0.0f); glVertex3f (-0.5f, -0.5f, 0.5f);
	     glTexCoord2f (repeatTextureRateX, repeatTextureRateZ); glVertex3f (-0.5f,  0.5f, 0.5f);
	     glTexCoord2f ( 0.0f,repeatTextureRateZ); glVertex3f (-0.5f,  0.5f,-0.5f);

	     glNormal3f(1,0,0);
	     glTexCoord2f (0.0f, 0.0f); glVertex3f ( 0.5f, -0.5f, -0.5f);
	     glTexCoord2f (repeatTextureRateX,0.0f); glVertex3f ( 0.5f, -0.5f,  0.5f);
	     glTexCoord2f (repeatTextureRateX, repeatTextureRateZ); glVertex3f ( 0.5f,  0.5f,  0.5f);
	     glTexCoord2f ( 0.0f,repeatTextureRateZ); glVertex3f ( 0.5f,  0.5f, -0.5f);
	   glEnd ();


	glPopMatrix();
}

bool RectPrisma::collides(const Forma& forma, RealPoint f_position) const {
		const RectPrisma* f = (const RectPrisma*)dynamic_cast<const RectPrisma*>(&forma);

		if(f != NULL){
			if(2*abs(f_position.x) < getLength() +f->getLength()){
				if(2*abs(f_position.y) < getHeight()+f->getHeight()){
					if(2*abs(f_position.z) < getWidth()+f->getWidth()){
						return true;
					}
				}
			}
		}

		return false;
}

