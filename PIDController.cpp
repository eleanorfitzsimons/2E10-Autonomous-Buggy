#include "PIDController.h"
#include "Wifi.h"
#include "WheelEncoder.h"
// Define PID parameters

unsigned long prev_time_dist = 0;
unsigned long prev_time_ref = 0;

double integral_dist = 0, integral_ref = 0;
double derivative_dist = 0, derivative_ref = 0;
double error_dist =  0, error_ref = 0;
double last_error_dist = 0, last_error_ref = 0;
double current_speed = 0;

extern double prevTracking = 0, prevRefSpeed = 110;

double PIDTracking(double object_distance){
  unsigned long current_time_dist = millis();
  double diff_time_dist = (current_time_dist - prev_time_dist)/1000.0;
  //Serial.println(diff_time_dist);
  if (diff_time_dist >= 0.01){
    error_dist = object_distance - TRACKING_DIST;
    integral_dist += error_dist * diff_time_dist;
    integral_dist = constrain(integral_dist, -255 / Ki_dist, 255 / Ki_dist);
    //integral_dist = constrain(integral_dist, (-255/Ki_dist), (255/Ki_dist));
    derivative_dist = (error_dist- last_error_dist)/diff_time_dist;

    double PIDTracking = Kp_dist*error_dist + Ki_dist*integral_dist + Kd_dist*derivative_dist;

    
    last_error_dist = error_dist;
    prev_time_dist = current_time_dist;
    double output = PIDTracking + 100;
    prevTracking = output;
    Serial.print("Tracking mode speed: ");
    Serial.println(output);

    return output;
  }
  else
    Serial.println("previous");
    return prevTracking;
}

///if the speed is the same keep the speed
double PIDRefSpeed(double ref_speed){
  unsigned long current_time_ref = millis();
  double  diff_time_ref = (current_time_ref - prev_time_ref)/1000.0; //current time in seconds
 // Serial.print("Time difference: ");
  
  if(diff_time_ref >= 0.03){ 
    current_speed = getCurrentSpeed(diff_time_ref);
     Serial.print("Speed found in pid: "); Serial.println(current_speed);
   // Serial.print("Current speed");
  //  Serial.println(current_speed);
  //Serial.print("Ref Speed is ");
  //Serial.println(ref_speed);
  error_ref = ref_speed - current_speed;

    integral_ref += error_ref * diff_time_ref;
    //integral_ref = constrain(integral_ref,(-255/Ki_ref), (255/Ki_ref);
   // integral_ref = constrain(integral_ref, -255 / Ki_ref, 255 / Ki_ref);
    derivative_ref = (error_ref -last_error_ref)/diff_time_ref;

    double PIDRefSpeed = Kp_ref*error_ref + Ki_ref*integral_ref + Kd_ref*derivative_ref;
      
    last_error_ref = error_ref;
    prev_time_ref = current_time_ref;

    if (error_ref == 0){
      return prevRefSpeed;
    }
    else{
      double output = base_pwm + PIDRefSpeed;
      output = constrain(output, 0 ,255);
      prevRefSpeed = output;
      //Serial.print("PID speed ");
      //Serial.println(output);
      return output;
    }
  }
  else{
  // Serial.println("prev");
    return prevRefSpeed;
  } 
}
///functions are built in 

//double Kp_distance = 5.0, Ki_distance = 0.5, Kd_distance = 1.0;
//double Kp_speed = 2.0, Ki_speed = 1.0, Kd_speed = 0.5;
