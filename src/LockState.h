/*
 * LockState.h
 *
 */

#ifndef LOCKSTATE_H_
#define LOCKSTATE_H_

#include "SimpleGPIO.h"
#include <stdlib.h>

class LockState {

	private:
		int	gpio_lock;
		unsigned int lockstate;

	public:
		LockState(int gpio_lock);

		void samplelockcontrolvalue() ;
        unsigned int getlockstate () { return lockstate;}
        void setlockstate (unsigned int state) { lockstate = state; }

		virtual ~LockState();  // unexport the gpios
};

#endif /* LOCKSTATE_H_ */
