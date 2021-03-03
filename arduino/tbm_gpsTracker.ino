
// importing libraries for TinyGPS and SoftwareSerial
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// define RX & TX pins, and GPS Baud Rate w/ initial set values according to our Arduino 
static const int RXPin = 4, TXPin = 3;
//baud rate serial data out of TX 
static const uint32_t GPSBaud = 9600; 


// defining TinyGPS++ object
TinyGPSPlus gps;

// starting serial connection to the GPS device using pins defined above
SoftwareSerial ss(RXPin, TXPin);

// arduino basic setup function will run code once 
void setup() {
  
  // initialize serial communication w/ GPS module
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

// ardunio basic loop function will run repeatedly 
void loop() {
  
  // this will display information every time a new sentence is correctly encoded 
  while (ss.available() > 0) {
    gps.encode(ss.read());

    // retrieval of the longitude and latitude communicated from the GPS module 
    if (gps.location.isUpdated()) {
   
      // getting the latitude values 
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      
      // getting the longitude values 
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
      
      // getting the speed in km/h
      Serial.print("Speed in km/h = "); 
      Serial.println(gps.speed.kmph());
      
      // getting the altitude in meters 
      Serial.print("Altitude in meters = "); 
      Serial.println(gps.altitude.meters()); 
    }
  }
}
