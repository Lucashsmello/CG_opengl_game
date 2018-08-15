/*
 * Sphere.h
 *
 *  Created on: Apr 13, 2013
 *      Author: lucasmello
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Forma.h"

class Sphere: public Forma {
	double raio;
public:
	Sphere(double raio,RealPoint color=1);

	virtual void draw() const;
	virtual bool collides(const Forma& f,RealPoint f_position) const;
};

#endif /* SPHERE_H_ */
