**FOR HEART RATE SENSOR**

#include <Adafruit_SSD1306.h>
#define OLED_Address 0x3C // 0x3C device address of I2C OLED. Few other OLED has 0x3D
Adafruit_SSD1306 oled(128, 64); // create our screen object setting resolution to 128x64
int a=0;
int lasta=0;
int lastb=0;
int LastTime=0;
int ThisTime;
bool BPMTiming=false;
bool BeatComplete=false;
int BPM=0;
#define UpperThreshold 560
#define LowerThreshold 530
void setup() {
oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
oled.clearDisplay();
oled.setTextSize(2);
}
void loop()
{
if(a>127)
{
oled.clearDisplay();
a=0;
lasta=a;
}
ThisTime=millis();
int value=analogRead(0);
oled.setTextColor(WHITE);
int b=60-(value/16);
oled.writeLine(lasta,lastb,a,b,WHITE);
lastb=b;
lasta=a;
if(value>UpperThreshold)
{
if(BeatComplete)
{
BPM=ThisTime-LastTime;
BPM=int(60/(float(BPM)/1000));
BPMTiming=false;
BeatComplete=false;
tone(8,1000,250);
}
if(BPMTiming==false)
{
LastTime=millis();
BPMTiming=true;
}
}
if((value<LowerThreshold)&(BPMTiming))
BeatComplete=true;
oled.writeFillRect(0,50,128,16,BLACK);
oled.setCursor(0,50);
oled.print("BPM:");
oled.print(BPM);
oled.display();
a++;
}


**FOR PULSE SENSOR ONLY**

// Variables
int PulseSensorPurplePin = 0; // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED13 = 13; // The on-board Arduion LED
int Signal; // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550; // Determine which Signal to "count as a beat", and which to ingore.
// The SetUp Function:
void setup() {
pinMode(LED13,OUTPUT); // pin that will blink to your heartbeat!
Serial.begin(9600); // Set's up Serial Communication at certain speed.
}
// The Main Loop Function
void loop() {
Signal = analogRead(PulseSensorPurplePin); // Read the PulseSensor's value.
// Assign this value to the "Signal" variable.
Serial.println(Signal); // Send the Signal value to Serial Plotter.
if(Signal > Threshold){ // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
digitalWrite(LED13,HIGH);
} else {
digitalWrite(LED13,LOW); // Else, the sigal must be below "550", so "turn-off" this LED.
}
delay(10);
}
