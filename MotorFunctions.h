#ifndef MOTORFUNCTIONS_H
#define MOTORFUNCTIONS_H

#include <Arduino.h>
//wheel functions


void drive_forward(int speed);
void reverse();
void stop_buggy();


//are these necessary
void right_forward();
void left_forward();

void right_backward();
void left_backward();

void right_speed(int speed);
void left_speed(int speed);

void right_turn(int speed);
void left_turn(int speed);

/*
void right_veer();
void left_veer();
*/
#endif // MOTORFUNCTIONS_
