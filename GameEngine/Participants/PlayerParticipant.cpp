/*
 * PlayerParticipant.cpp
 *
 *  Created on: Apr 4, 2013
 *      Author: lucasmello
 */

#include "PlayerParticipant.h"
#include "Formas/RectPrisma.h"
#include <iostream>
#include <cmath>

using namespace std;

PlayerParticipant::PlayerParticipant(RealPoint position) : MovParticipant(position,Space(new RectPrisma(0.4,1,0.4)), PLAYER){
}







