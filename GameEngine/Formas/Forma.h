/*
 * Forma.h
 *
 *  Created on: Apr 13, 2013
 *      Author: lucasmello
 */

#ifndef FORMA_H_
#define FORMA_H_

#include "Utilidades/Point.h"

class Forma {
	GLuint texture_id;
	bool texture_defined;
protected:
	RealPoint color;
public:
	Forma(RealPoint color=1){this->color=color;texture_defined=false;};
	virtual void draw() const=0;
	virtual bool collides(const Forma& f,RealPoint f_position) const=0;
	void setTexture(GLuint texture){texture_id=texture;texture_defined=true;};

	bool hasTexture() const{return texture_defined;};
	GLuint getTextureId() const{return texture_id;};
	void setColor(GLfloat r,GLfloat g, GLfloat b){color.x=r;color.y=g;color.z=b;};
};

#endif /* FORMA_H_ */
