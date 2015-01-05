/*
 * TestApplication.cpp
 *
 */

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "EasyDriver.h"
#include "LockState.h"
#include "SimpleGPIO.h"
#include "LockCamera.h"
using namespace std;

int main(int argc, char * argv[]){

	int lock_state = 0; //Start with assumption of unlocked

	printf( "Running Lock Test \n");

	LockState lock(65); //gpio_lock
	LockCamera LockCamera; //LockCamera instance

	//gpio_coil1, gpio_coil2, gpio_coil3, gpio_coil4,  rpm speed, steps per revolution
	EasyDriver motor(45, 23, 47, 46, 150, 512);

	if (argc == 1) { //No arguments
		while (1) {

			// Sample requested state of lock
			lock.samplelockcontrolvalue();

			if ((lock_state == 0)&&(lock.getlockstate() == 1)) { //lock
				//In case the motor SLP (sleep) pin is low
				//motor1.wake();
				motor.rotate(95, 0);
				lock_state = 1;
                                LockCamera.switchon();
                                LockCamera.capture();
                                LockCamera.switchoff();
			}
			else if ((lock_state == 1)&&(lock.getlockstate() == 0)) { //unlock
				//In case the motor SLP (sleep) pin is low
				//motor1.wake();
				motor.rotate(95, 1);
				lock_state = 0;
			}
			//wait 5s before sampling again
			sleep (4);
		}
	} else { // Rotate once in specific direction
		motor.rotate(5,atoi(argv[1]));
	}
	cout << "*** Lock Test Finished" << endl;

	return 0;
}

