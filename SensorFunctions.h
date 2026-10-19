#ifndef SENSORFUNCTIONS_H
#define SENSORFUNCTIONS_H

#include <Arduino.h>
extern bool front_stop;
extern double obstacle_distance;
extern bool distMode;
extern int motor_speed;
//ir sensors
//bool poll_reye(bool &Rold_state);
//b vb ool poll_leye (bool &Lold_state);
//us sensor
void getObstacleDistance();


#endif // SENSORFUNCTIONS_H
