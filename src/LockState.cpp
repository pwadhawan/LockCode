/*
 * LockState.cpp
 *
 *
 */

#include "LockState.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

LockState::LockState(int gpio_lock){

	this->gpio_lock = gpio_lock;
	this->lockstate = 0; // Def value of lockstate = 0,  0:UNLOCK,  1:LOCK

    cout << "The value of Lockstate  = "<< this->lockstate << endl;

    cout << "exporting GPIO Number "<< this->gpio_lock << endl;
	gpio_export(this->gpio_lock);
    cout << "Setting the direction of Lock control GPIO to input" << endl;
	gpio_set_dir(this->gpio_lock, INPUT_PIN);

}

void LockState::samplelockcontrolvalue(){
	if ((gpio_get_value(this->gpio_lock, &(this->lockstate)) == 0))
			perror("Reading Lock Control GPIO state");

	cout<<"The value of control is "<< this->lockstate << endl;
}

LockState::~LockState() {
	gpio_unexport(this->gpio_lock);
}

