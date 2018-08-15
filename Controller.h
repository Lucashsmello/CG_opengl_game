/*
 * Controller.h
 *
 *  Created on: Apr 5, 2013
 *      Author: lucasmello
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_


#define MAX_ANGLE_VIEW 90

void mousePassiveFunc(int x, int y);

void keyboardReleased(unsigned char key, int x, int y);
void keyboardPressed(unsigned char key, int x, int y);

void updatePlayerSpeed();

void createMenu();

#endif /* CONTROLLER_H_ */
