/*
 * EasyDriver.cpp
 *
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL I
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "EasyDriver.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

EasyDriver::EasyDriver(int gpio_coil1, int gpio_coil2, int gpio_coil3, int gpio_coil4,
					    int speedRPM, int stepsPerRevolution){

	this->gpio_coil1  = gpio_coil1;
	this->gpio_coil2  = gpio_coil2;
	this->gpio_coil3  = gpio_coil3;
	this->gpio_coil4  = gpio_coil4;

    cout << "exporting GPIO Number "<< this->gpio_coil1 << endl;
	gpio_export(this->gpio_coil1);
    cout << "exporting GPIO Number "<< this->gpio_coil2 << endl;
	gpio_export(this->gpio_coil2);
    cout << "exporting GPIO Number "<< this->gpio_coil3 << endl;
	gpio_export(this->gpio_coil3);
    cout << "exporting GPIO Number "<< this->gpio_coil4 << endl;
	gpio_export(this->gpio_coil4);

    cout << "Setting the direction of Motor control GPIOs to output" << endl;
    gpio_set_dir(this->gpio_coil1, OUTPUT_PIN);
    gpio_set_dir(this->gpio_coil2, OUTPUT_PIN);
    gpio_set_dir(this->gpio_coil3, OUTPUT_PIN);
    gpio_set_dir(this->gpio_coil4, OUTPUT_PIN);

	// default to clockwise direction
	clockwise = true;
	// default to full stepping
	setStepMode(STEP_FULL);
	// the default number of steps per revolution
	setStepsPerRevolution(stepsPerRevolution);
	// the default speed in rpm
	setSpeed(speedRPM);
	//wake up the controller - holding torque..
	wake();
}

void EasyDriver::setStepMode(STEP_MODE mode) {
	this->stepMode = mode;
	switch(stepMode){
	case STEP_FULL:
		gpio_set_value(this->gpio_coil1, LOW);
		gpio_set_value(this->gpio_coil2, LOW);
		gpio_set_value(this->gpio_coil3, LOW);
		gpio_set_value(this->gpio_coil4, LOW);
		this->delayFactor = 1;
		break;
	case STEP_HALF:
		break;
	case STEP_QUARTER:
		break;
	case STEP_EIGHT:
		break;
	}
}

void EasyDriver::setSpeed(float rpm) {
	this->speed = rpm;
	float delayPerSec = (60/rpm)/stepsPerRevolution;    // delay per step in seconds
	this->uSecDelay = (int)(delayPerSec * 1000 * 1000); // in microseconds
    cout << "rpm "<< rpm << "\n";

}

void EasyDriver::setGPIOs(int index){
    gpio_set_value(this->gpio_coil1, lookup[index][0]);
    gpio_set_value(this->gpio_coil2, lookup[index][1]);
    gpio_set_value(this->gpio_coil3, lookup[index][2]);
    gpio_set_value(this->gpio_coil4, lookup[index][3]);
}

void EasyDriver::step(int numberOfSteps){
    cout << "Doing "<< numberOfSteps << " steps and going to sleep for " << uSecDelay/delayFactor << "uS\n";

    int sleepDelay = uSecDelay/delayFactor;
    setGPIOs(9); //start with driving all pins LOW

	for(int i=0; i<numberOfSteps; i++) {
		if (direction==0) { //clockwise
			for(int j=0; j<8; j++) {
				setGPIOs(j);
				usleep(sleepDelay);
			}
		} else { // counter-clockwise
			for(int j=7; j>=0; j--) {
				setGPIOs(j);
				usleep(sleepDelay);
			}
		}
	}

    setGPIOs(9); //end with driving all pins LOW
	usleep (1); // sleep for 1us
}

void EasyDriver::rotate(int degrees, int direction_in){
	this->direction  = direction_in;
	float degreesPerStep = 360.0f/getStepsPerRevolution();
	int numberOfSteps = degrees/degreesPerStep;
	cout << "The number of steps is " << numberOfSteps << endl;
	cout << "The delay factor is " << delayFactor << endl;
	step(numberOfSteps*delayFactor);
}

EasyDriver::~EasyDriver() {
	gpio_unexport(this->gpio_coil1);
	gpio_unexport(this->gpio_coil2);
	gpio_unexport(this->gpio_coil3);
	gpio_unexport(this->gpio_coil4);
}

