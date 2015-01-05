/*
 * LockCamera.cpp
 *
 *
 */
#include "LockCamera.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

LockCamera::LockCamera(){
    cout << "Initalizing LockCamera...." << endl;
    system("v4l2-ctl --set-fmt-video=width=320,height=240,pixelformat=0");

//Build the grabber file on the BBB using the folloing command
//echo "Building the Video4Linux frame capture program"
//gcc -O2 -Wall `pkg-config --cflags --libs libv4l2` grabber.c -o lockgrabber

//Place the "lockgrabber" file in the directory /root/camera/bonecv/

}
void LockCamera::switchon(){
    cout << "Switching LockCamera ON...." << endl;
    system("/root/devmem2 0x47401c60 b 0x00");
    system("sleep 1");
    system("echo "usb1" > /sys/bus/usb/drivers/usb/unbind");
}

void LockCamera::switchoff(){
    cout << "Switching LockCamera OFF...." << endl;
    system("/root/devmem2 0x47401c60 b 0x00");
    system("sleep 1");
    system("echo "usb1" > /sys/bus/usb/drivers/usb/unbind");
}

void LockCamera::capture(){
   	cout<<"Capturing the image..... " << endl;
   	cout<<"Captured images would be saved in /root/camera/lockimages..... " << endl;
        system("/root/camera/bonecv/lockgrabber /root/camera/lockimages/");
        //system("scp /root/camera/bonecv/grabber000.ppm smartenlivez@192.168.0.101:/home/smartenlivez/Desktop/");
}

LockCamera::~LockCamera() {
    cout << "Resetting the LockCamera...." << endl;
}

