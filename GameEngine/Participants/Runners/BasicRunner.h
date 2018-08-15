/*
 * BasicRunner.h
 *
 *  Created on: Apr 14, 2013
 *      Author: lucasmello
 */

#ifndef BASICRUNNER_H_
#define BASICRUNNER_H_

#include "Runner.h"

class BasicRunner: public Runner {
	double random_ang;
	int random_mov_count;
	bool encurralado;
	bool desencurrulamento_enabled;
	RealPoint last_rundirection;
	bool fast_contorno_enabled; //Contorna obstaculos com maior rapidez;
	bool random_movement;
	bool randomRun_enabled;
	int max_angle;
	unsigned int rand_period;

protected:
	double run_speed;
	double raio_visao;

	RealPoint makeMove(const Map& ambiente);

public:
	BasicRunner(RealPoint position,double runspeed=0.01, double raiovisao=2, bool desencurrulamento_enabled=false,bool fastcontorno=true,bool randomRun=false);
	BasicRunner(RealPoint position, RealPoint color, double runspeed=0.01, double raiovisao=2, bool desencurrulamento_enabled=false,bool fastcontorno=true,bool randomRun=false);

	void setRandomRunFactor(unsigned int maxangle,unsigned int randperiod=200){max_angle=maxangle;rand_period=randperiod;}

	virtual RealPoint move(const Map& ambiente);

};

#endif /* BASICRUNNER_H_ */
