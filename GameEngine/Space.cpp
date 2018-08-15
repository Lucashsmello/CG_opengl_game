/*
 * Space.cpp
 *
 *  Created on: Mar 30, 2013
 *      Author: lucasmello
 */

#include "Space.h"
#include "Formas/RectPrisma.h"
#include "Formas/Sphere.h"
#include <cmath>
#include <iostream>


using namespace std;


void Space::draw(Point<GLfloat> position) const {
	glPushMatrix();

	glTranslatef(position.x,position.y,position.z);
	for(unsigned int i=0;i<solids.size();i++){
		glPushMatrix();
		glTranslatef(relative_positions[i].x,relative_positions[i].y,relative_positions[i].z);

		solids[i]->draw();

		glPopMatrix();
	}

	glPopMatrix();
}

const std::vector<Forma*>& Space::getCollisionSolids() const {
	return collision_solids.size() > 0 ? collision_solids : solids;
}

const std::vector<RealPoint>& Space::getColSolidsPositions() const {
	return collision_solids.size() > 0 ? col_relative_positions : relative_positions;
}


void Space::addSolid(Forma* solid, RealPoint solidpos) {
	solids.push_back(solid);
	relative_positions.push_back(solidpos);
}

bool Space::collides(const Space& p, Point<GLfloat> position,Point<GLfloat> movement) const {
	const vector<Forma*>& col_solids(getCollisionSolids());
	const vector<Forma*>& p_col_solids(p.getCollisionSolids());

	const vector<RealPoint>& colpos_solids(getColSolidsPositions());
	const vector<RealPoint>& p_colpos_solids(p.getColSolidsPositions());

	for(unsigned int i=0;i<col_solids.size();i++){
		for(unsigned int j=0;j<p_col_solids.size();j++){
			RealPoint newlocation=position+(colpos_solids[i]-p_colpos_solids[j])+movement;
			if(col_solids[i]->collides(*p_col_solids[j],newlocation)){
				return true;
			}
		}
	}

	return false;
}



Space::Space(Forma* solid) {
	solids.push_back(solid);
	relative_positions.push_back(RealPoint(0,0,0));
}

Space::Space(const std::vector<Forma*>& solids, const std::vector<RealPoint >& relative_pos) {
	this->solids=solids;
	this->relative_positions=relative_pos;
}

Space::Space(const std::vector<Forma*>& solids,
		const std::vector<RealPoint>& relative_pos,
		const std::vector<Forma*>& colsolids,
		const std::vector<RealPoint>& colrelative_pos) {

	this->solids=solids;
	this->relative_positions=relative_pos;
	this->collision_solids=colsolids;
	this->col_relative_positions=colrelative_pos;
}

Space::Space(Forma* solid,Forma* colsolid) {
	solids.push_back(solid);
	relative_positions.push_back(RealPoint(0,0,0));
	collision_solids.push_back(colsolid);
	col_relative_positions.push_back(RealPoint(0,0,0));

}

Space::Space(Forma* solid, RealPoint solidpos, Forma* colsolid) {
	solids.push_back(solid);
	relative_positions.push_back(solidpos);
	collision_solids.push_back(colsolid);
	col_relative_positions.push_back(RealPoint(0,0,0));

}

