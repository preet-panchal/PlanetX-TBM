
#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>
#include <TinyGPS.h>


TinyGPS gps;
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress remoteIp(192, 168, 0, 108);  // <- EDIT!!!!
unsigned short remotePort = 8888;
unsigned short localPort = 8888;
EthernetUDP udp;

void setup() {
  // Initialize serial port
  Serial.begin(9600);
  while (!Serial) continue;

  // Initialize Ethernet libary
  if (!Ethernet.begin(mac)) {
    Serial.println(F("Failed to initialize Ethernet library"));
    return;
  }

  // Enable UDP
  udp.begin(localPort);
}

void loop() {
  float speeding = 0;
  float tim = 0;
  float latitude, longitude; //stores values for longitude and latitude
  float dir = 90.0;
  float depth = 1.2;
  float len = speeding*tim;

  while(serialgps.available()) 
{
int c = serialgps.read(); 
if(gps.encode(c)) 
{
gps.f_get_position(&latitude, &longitude);
delay(2000);
}
}

  // Allocate JsonBuffer
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonBuffer<500> jsonBuffer;

  // Create the root object
  JsonObject& root = jsonBuffer.createObject();


  JsonArray& locationvalues = root.createNestedArray("location values");
  locationvalues.add("team: " + "Gary the Snail");
  locationvalues.add("latitude: " + latitude);
  locationvalues.add("longitude: " + longitude);
  locationvalues.add("heading: " + dir);
  locationvalues.add("depth: " + depth);
  locationvalues.add("len: " + len);


  // Log
  Serial.print(F("Sending to "));
  Serial.print(remoteIp);
  Serial.print(F(" on port "));
  Serial.println(remotePort);
  root.printTo(Serial);

  // Send UDP packet
  udp.beginPacket(remoteIp, remotePort);
  root.printTo(udp);
  udp.println();
  udp.endPacket();

  // Wait
  delay(10000);
}
