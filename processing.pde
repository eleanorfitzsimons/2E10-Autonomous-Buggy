import processing.net.*;
import controlP5.*;

Client myClient;
String data;
float speed_out = 0, dist_travelled = 0, object_dist = -1;
boolean isDistanceMode = false;
float ref_speed = 35;
boolean goStatus = false;

ControlP5 cp5;
Button goButton, stopButton;
Toggle modeToggle;
Slider refSpeedSlider, speedOutSlider;
Textlabel distanceLabel, objectDistLabel;

void setup() {
  size(1600, 800);
  background(10, 10, 50);
  
  cp5 = new ControlP5(this);
  
  goButton = cp5.addButton("GO")
    .setPosition(100, 100)
    .setSize(100, 50)
    .setColorBackground(color(0, 200, 0))
    .setColorForeground(color(0, 255, 0))
    .onChange(new CallbackListener() {
      public void controlEvent(CallbackEvent event) {
        goStatus = true;
        sendGoStatus(); // ✅ Send GO command separately
      }
    });
  
  stopButton = cp5.addButton("STOP")
    .setPosition(250, 100)
    .setSize(100, 50)
    .setColorBackground(color(200, 0, 0))
    .setColorForeground(color(255, 0, 0))
    .onChange(new CallbackListener() {
      public void controlEvent(CallbackEvent event) {
        goStatus = false;
        sendGoStatus(); // ✅ Send STOP command separately
      }
    });
  
  modeToggle = cp5.addToggle("Mode")
    .setPosition(400, 100)
    .setSize(80, 40)
    .setValue(false)
    .setLabel("Speed Mode")
    .setLock(true);
  
  refSpeedSlider = cp5.addSlider("Reference Speed (cm/s)")
    .setPosition(100, 200)
    .setSize(300, 30)
    .setRange(0, 90)
    .setValue(ref_speed)
    .setColorBackground(color(50, 50, 150))
    .setColorForeground(color(100, 100, 255))
    .onChange(new CallbackListener(){
      public void controlEvent(CallbackEvent event) {
        ref_speed = event.getController().getValue();
        sendRefSpeed(); // ✅ Send REF_SPEED separately
      }
    });
  
  speedOutSlider = cp5.addSlider("Speed Output (cm/s)")
    .setPosition(100, 250)
    .setSize(300, 30)
    .setRange(0, 90)
    .setValue(0)
    .setColorBackground(color(50, 50, 150))
    .setColorForeground(color(100, 100, 255))
    .setLock(true);
  
  distanceLabel = cp5.addTextlabel("distanceTravelled")
    .setPosition(100, 350)
    .setText("Distance Travelled: 0 cm")
    .setColor(color(255, 255, 255));
  
  objectDistLabel = cp5.addTextlabel("objectDistance")
    .setPosition(100, 400)
    .setText("Object Distance: No obstacle detected")
    .setColor(color(255, 255, 255));

  myClient = new Client(this, "172.20.10.10", 5200); // IP and port of Arduino server
  if (myClient != null) {
    println("Attempting to connect...");
    if (myClient.active()) {
      println("Connected to Arduino.");
    } else {
      println("⚠️ Connection failed.");
    }
  }
}

void draw() {
  background(10, 10, 50);
  
  if (myClient != null && myClient.active()) {
    String incomingData = myClient.readStringUntil('\n');
    if (incomingData != null && incomingData.length() > 0) {
      parseData(incomingData);
    }
  }
}

// ✅ Sends GO/STOP command separately
void sendGoStatus() {
  if (myClient != null && myClient.active()) {
    String command = "GO_STATUS: " + (goStatus ? "GO" : "STOP");
    myClient.write(command + "\n"); 
    println("Sent: " + command);
  } else {
    println("⚠️ Connection lost. Cannot send data.");
  }
}

// ✅ Sends REF_SPEED command separately
void sendRefSpeed() {
  if (myClient != null && myClient.active()) {
    String command = "REF_SPEED: " + ref_speed;
    myClient.write(command + "\n");
    println("Sent: " + command);
  } else {
    println("⚠️ Connection lost. Cannot send data.");
  }
}

// ✅ Improved function to handle possible incomplete telemetry data
void parseData(String rawData) {
  println("Received: " + rawData.trim());
  
  String[] parts = rawData.split(" ");
  for (int i = 0; i < parts.length - 1; i++) {
    try {
      if (parts[i].equals("SPEED_OUT:")) {
        speed_out = float(parts[i + 1]);
      } else if (parts[i].equals("DIST_TRAVELLED:")) {
        dist_travelled = float(parts[i + 1]);
      } else if (parts[i].equals("OBJECT_DIST:")) {
        object_dist = float(parts[i + 1]);
      } else if (parts[i].equals("MODE:")) {
        String modeValue = parts[i + 1].trim();
        isDistanceMode = modeValue.equals("DIST");
        println("Parsed mode: " + modeValue);
      }
    } catch (Exception e) {
      println("Error parsing telemetry data: " + e.getMessage());
    }
  }
  
  speedOutSlider.setValue(speed_out);
  distanceLabel.setText("Distance Travelled: " + dist_travelled + " cm");

  if (object_dist == -1 || object_dist >= 100) {
    objectDistLabel.setText("Object Distance: No obstacle detected");
  } else {
    objectDistLabel.setText("Object Distance: " + object_dist + " cm");
  }

  modeToggle.setValue(isDistanceMode);
  modeToggle.setLabel(isDistanceMode ? "Distance Mode" : "Speed Mode");
}
