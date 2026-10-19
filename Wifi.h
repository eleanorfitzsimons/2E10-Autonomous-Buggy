#ifndef WIFI_H
#define WIFI_H
#include <WiFiS3.h>
#include "WifiPassword.h"

extern char ssid[];
extern char pass[];    
extern int keyIndex; 
extern bool client_connect;


///////////////////////////
extern bool stop_button;
extern bool distMode;
extern double ref_speed;
extern int motor_speed; //defined in ino file
///////////////////////////


extern WiFiServer server;
extern WiFiServer server2;

extern WiFiClient client;

void connectClient();
void sendObstacleDistance();
void sendTelemetry();


///////////////////////////
void sendTravelDistance();
float extractSpeed(String input);
///////////////////////////

#endif // WIFI_H
