#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include "Wifi.h"

// PID Variables
extern double setpoint, measured_value, output;
//const double Kp_dist = 13, Ki_dist = 0.03, Kd_dist = 1;

const double Kp_dist = 3, Ki_dist = 0.05, Kd_dist  = 0;
//was 6, .5 and 1
//const float Kp_distance = 3, Ki_distance = 0.05, Kd_distance = 2;
const double Kp_ref = 1.2, Ki_ref = 0, Kd_ref = 0;
extern unsigned long current_time_dist, prev_time_dist, diff_time_dist;
extern unsigned long current_time_ref, prev_time_ref, diff_time_ref;
//const double base_pwm = (ref_speed/ max_speed) * 255;
const double base_pwm = (ref_speed/ 100) * 255;
const double max_speed = 70;
extern double current_speed;
//these are the setpoints
const double TRACKING_DIST = 15;

extern double prevTracking, prevRefSpeed;


extern double integral_dist, integral_ref;
extern double derivative_dist, derivative_ref;
extern double error_dist, error_ref;
extern double last_error_dist, last_error_ref;



double PIDTracking(double object_distance);
double PIDRefSpeed(double ref_speed);




#endif
