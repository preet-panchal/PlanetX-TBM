#include <SoftwareSerial.h> //module use to set up the bluetooth device

int rxPin = 3;
int txPin = 2;
SoftwareSerial bluetooth(rxPin, txPin); //used for setting up the bluetooth

float value=0;
float rev=0;
int rpm;
int oldtime=0;
int time;
 
void isr() //interrupt service routine
{
rev++;
}
 
void setup()
{
  attachInterrupt(0,isr,RISING); //attaching the interrupt
  Serial.begin(9600); //used to set up the bluetooth
  bluetooth.begin(9600); //set baud rate
}
 
void loop()
{
delay(1000);
detachInterrupt(0); //detaches the interrupt
time=millis()-oldtime; //finds the time
rpm=(rev/time)*60000*3; //calculates rpm for blades
bluetooth.print(rpm);
oldtime=millis(); //saves the current time
rev=0; //resets the rev cycle
attachInterrupt(0,isr,RISING);
}
