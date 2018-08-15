/*
 * RectPrisma.h
 *
 *  Created on: Apr 13, 2013
 *      Author: lucasmello
 */

#ifndef RECTPRISMA_H_
#define RECTPRISMA_H_

#include "Forma.h"
#include "Utilidades/Point.h"
#include <vector>

class RectPrisma: public Forma{
	GLfloat length,height,width;
	float repeatTextureRateX, repeatTextureRateZ;


public:
	RectPrisma(GLfloat length,GLfloat height,GLfloat z,RealPoint color=1);

	GLfloat getLength() const{ return length;}
	GLfloat getHeight() const{ return height;}
	GLfloat getWidth() const{ return width;}

	void setRepeatTextureRate(float rateX,float rateZ){repeatTextureRateX=rateX;repeatTextureRateZ=rateZ;};

	bool contains(Point<GLfloat> p) const;
	virtual void draw() const;
	virtual bool collides(const Forma& f,RealPoint f_position) const;
};

#endif /* RECTPRISMA_H_ */
