#include "ArduinoPins.h"
#include "MotorFunctions.h"
#include <Arduino.h>
#include "SensorFunctions.h"

//WHEEL FUNCTIONS
void drive_forward(int speed){
  int left_speed = speed*1.1;
  right_forward();
  left_forward();
  analogWrite(RENABLE, left_speed); 
  analogWrite(LENABLE, speed);//were these backwards
  //one motor is weaker
}

void reverse(){
  right_backward();
  left_backward();
  analogWrite(RENABLE, 100);
  analogWrite(LENABLE, 100);
}
void stop_buggy (){
  digitalWrite (LMOTOR1,LOW);
  digitalWrite (LMOTOR2,LOW);
  digitalWrite (RMOTOR1, LOW);
  digitalWrite (RMOTOR2,LOW);
}


//are these necessary
void right_forward(){
  digitalWrite (RMOTOR1,HIGH);
  digitalWrite (RMOTOR2,LOW);
}
void left_forward(){
  digitalWrite (LMOTOR1,HIGH);
  digitalWrite (LMOTOR2,LOW);
}

void right_backward(){
  digitalWrite (RMOTOR1,LOW);
  digitalWrite (RMOTOR2, HIGH);
}
void left_backward(){
  digitalWrite (LMOTOR1,LOW);
  digitalWrite (LMOTOR2, HIGH);
}

void right_speed(int speed){
  analogWrite(RENABLE, 100);
}
void left_speed(int speed){
  analogWrite(LENABLE, 100);
}
void right_turn(int speed){
  int turn_speed = 115;

  right_forward();
  analogWrite(RENABLE, turn_speed);
  left_forward();
  analogWrite(LENABLE, 0);
  delay(50);
}
void left_turn(int speed){
  int turn_speed = 115;
  


  
  left_forward();
  analogWrite(LENABLE, turn_speed);
  right_forward();
  analogWrite(RENABLE, 0);
  delay(50); 
}


/*
void right_veer(){
  right_forward();
  analogWrite(RENABLE, 120);
  left_forward();
  analogWrite(LENABLE, 80);
}
void left_veer(){
  left_forward();
  analogWrite(LENABLE, 120);
  right_forward();
  analogWrite(RENABLE, 80);
}
*/
