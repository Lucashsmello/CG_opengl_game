/*
 * BasicRunner.cpp
 *
 *  Created on: Apr 14, 2013
 *      Author: lucasmello
 */

#include "BasicRunner.h"
#include "PlayerParticipant.h"
#include "Map.h"
#include "Formas/Sphere.h"
#include "Formas/RectPrisma.h"
#include <iostream>

using namespace std;

BasicRunner::BasicRunner(RealPoint p,double runspeed, double raiovisao, bool desencurrulamento,bool fastcontorno, bool randomRun)
		: Runner(p,Space(new Sphere(0.1,RealPoint(0.5,0,0.5)),RealPoint(0,0.2,0),new RectPrisma(0.2,0.25,0.2,RealPoint(0.5,0,0.5))))
{
	run_speed=runspeed;
	desencurrulamento_enabled=desencurrulamento;
	raio_visao=raiovisao;
	encurralado=false;
	fast_contorno_enabled=fastcontorno;
	randomRun_enabled=randomRun;
	max_angle=30;
	rand_period=200;
	random_ang=(rand() % 30) - 15;
}

BasicRunner::BasicRunner(RealPoint p,RealPoint color, double runspeed, double raiovisao, bool desencurrulamento,bool fastcontorno, bool randomRun)
		: Runner(p,Space(new Sphere(0.1,color),RealPoint(0,0.2,0),new RectPrisma(0.2,0.25,0.2,RealPoint(0.5,0,0.5))))
{
	run_speed=runspeed;
	desencurrulamento_enabled=desencurrulamento;
	raio_visao=raiovisao;
	encurralado=false;
	fast_contorno_enabled=fastcontorno;
	randomRun_enabled=randomRun;
	max_angle=30;
	rand_period=200;
	random_ang=(rand() % 30) - 15;
}

RealPoint BasicRunner::makeMove(const Map& ambiente) {
	const PlayerParticipant* player=ambiente.getPlayer();
	RealPoint rundirection=(getPosition()-player->getPosition());

	rundirection.y=0;
	if(rundirection.getMagnitude()==0){
		return RealPoint(run_speed,0,0);
	}

	rundirection*=run_speed/rundirection.getMagnitude();
	if(randomRun_enabled and (not encurralado)){
		if(rand_period==0){
			rundirection.rotateXZ(max_angle);
		}else{
			rundirection.rotateXZ(random_ang);
		}
	}


		if(desencurrulamento_enabled and encurralado){
			if(((last_rundirection.z < 0) and (rundirection.z < 0)) or ((last_rundirection.z >= 0) and (rundirection.z >= 0))){
				if(((last_rundirection.x < 0) and (rundirection.x < 0)) or ((last_rundirection.x >= 0) and (rundirection.x >= 0))){
					if(abs(rundirection.z) > abs(rundirection.x)){
						rundirection.z=0;
						rundirection.x=rundirection.x > 0 ? -run_speed : run_speed;
					}else{
						rundirection.x=0;
						rundirection.z=rundirection.z > 0 ? -run_speed : run_speed;
					}
					return getSpeed()+rundirection;
				}
			}

			encurralado=false;
			if(randomRun_enabled){
				random_ang=(rand() % (2*max_angle)) - max_angle;
				random_mov_count=0;
			}
		}


		if(ambiente.hasCollision(this,RealPoint(rundirection.x,0,0))){
			if(ambiente.hasCollision(this,RealPoint(0,0,rundirection.z > 0 ? run_speed : -run_speed))){
				if(desencurrulamento_enabled){
					last_rundirection=rundirection;
					encurralado=true;
				}

				if(abs(rundirection.z) > abs(rundirection.x)){
					rundirection.z=0;
					rundirection.x=rundirection.x > 0 ? -run_speed : run_speed;
				}else{
					rundirection.x=0;
					rundirection.z=rundirection.z > 0 ? -run_speed : run_speed;
				}
			}else{
				if(fast_contorno_enabled){
					rundirection.z=rundirection.z > 0 ? run_speed : -run_speed;
					rundirection.x=0;
				}
			}
		}else{
			if(fast_contorno_enabled){
				if(ambiente.hasCollision(this,RealPoint(0,0,rundirection.z))){
					rundirection.x=rundirection.x > 0 ? run_speed : -run_speed;
					rundirection.z=0;
				}
			}
		}

		return rundirection;
}

RealPoint BasicRunner::move(const Map& ambiente) {
	const PlayerParticipant* player=ambiente.getPlayer();
	RealPoint myPosition=getPosition();
	myPosition.y=player->getPosition().y;

	if(randomRun_enabled){
		random_mov_count++;
		if(rand_period==0){
			if(random_mov_count > (300-(rand() % 75))){
				max_angle=-max_angle;
				random_mov_count=0;
			}
		}else{
			if(random_mov_count>=rand_period){
				random_ang=(rand() % (2*max_angle)) - max_angle;
				random_mov_count=0;
			}
		}
	}


	if(myPosition.distance(player->getPosition()) <= raio_visao){
		jump();
		return getSpeed()+makeMove(ambiente);
	}else{
		encurralado=false;
		if(randomRun_enabled and (rand_period!=0)){
			RealPoint mov(run_speed,0,0);
			mov.rotateXZ(random_ang/max_angle * 180);
			return getSpeed()+mov;
		}
	}

	return getSpeed();
}
