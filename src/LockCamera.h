/*
 * LockCamera.h
 *
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "SimpleGPIO.h"
#include <stdlib.h>

class LockCamera {

	private:
	public:
		LockCamera(); //Initialize the LockCamera in BBB
                void capture();//Capture the image using the camera in BB
                void switchon(); //Switching LockCamera ON
                void switchoff();//Switching LockCamera OFF

		virtual ~LockCamera();  // unexport the gpios
};

#endif /* CAMERA_H_ */
