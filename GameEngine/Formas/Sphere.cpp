/*
 * Sphere.cpp
 *
 *  Created on: Apr 13, 2013
 *      Author: lucasmello
 */

#include "Sphere.h"

Sphere::Sphere(double raio,RealPoint c) : Forma(c){
	this->raio=raio;
}

void Sphere::draw() const {
    GLfloat mat_specular[] = { 0.5,0.5,0.5, 1};
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT,GL_SHININESS,50.0);
	glColor3f(color.x,color.y,color.z);
	glutSolidSphere(raio,100,100);
}

bool Sphere::collides(const Forma& f, RealPoint f_position) const {
	return false;
}



