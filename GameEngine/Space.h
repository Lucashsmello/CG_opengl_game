/*
 * Space.h
 *
 *  Created on: Mar 30, 2013
 *      Author: lucasmello
 */

#ifndef SPACE_H_
#define SPACE_H_

#include <GL/glut.h>
#include "Utilidades/Point.h"
#include "Formas/Forma.h"
#include <vector>




class Space {
	std::vector<Forma*> solids;
	std::vector<RealPoint > relative_positions;
	std::vector<Forma*> collision_solids;
	std::vector<RealPoint > col_relative_positions;




public:
	Space(){};
	Space(const std::vector<Forma*>& solids,const std::vector<RealPoint >& relative_pos);
	Space(const std::vector<Forma*>& solids,const std::vector<RealPoint >& relative_pos,
			const std::vector<Forma*>& colsolids,const std::vector<RealPoint >& colrelative_pos);
	Space(Forma* solid);
	Space(Forma* solid,Forma* colsolid);
	Space(Forma* solid,RealPoint solidpos,Forma* colsolid);
	void draw(Point<GLfloat> position) const;
	const std::vector<Forma*>& getCollisionSolids() const;
	const std::vector<RealPoint>& getColSolidsPositions() const;

	void addSolid(Forma* solid,RealPoint solidpos);

	bool collides(const Space& p, Point<GLfloat> position, Point<GLfloat> ) const;
	~Space(){};
};

#endif /* SPACE_H_ */
