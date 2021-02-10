/********************************************************************/
// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 12 
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 

const int TEMP_THRESHOLD_UPPER = 37; // upper threshold of temperature, change to your desire value
const int TEMP_THRESHOLD_LOWER = 32; // lower threshold of temperature, change to your desire value
const int RELAY_FAN_PIN = A5; // Arduino pin connected to relay which connected to fan
#define control 8 // pin that controls the MOSFET

void setup(void) 
{ 
 // start serial port 
 Serial.begin(9600); 
 Serial.println("Dallas Temperature IC Control Library Demo"); 
 // Start up the library 
 sensors.begin();
 pinMode(control,OUTPUT);// define control pin as output 
} 
void loop(void) 
{ 
 // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus 
/********************************************************************/
 Serial.print(" Requesting temperatures..."); 
 sensors.requestTemperatures(); // Send the command to get temperature readings 
 Serial.println("DONE"); 
/********************************************************************/
 Serial.print("Temperature is: "); 
 Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?  
   // You can have more than one DS18B20 on the same bus.  
   // 0 refers to the first IC on the wire 
   delay(60000);
 
  if(sensors.getTempCByIndex(0) > TEMP_THRESHOLD_UPPER){
    Serial.println("The fan is turned on");
    digitalWrite(control,HIGH); // turn the MOSFET Switch ON
    digitalWrite(RELAY_FAN_PIN, HIGH); // turn on
  } else if(sensors.getTempCByIndex(0) < TEMP_THRESHOLD_LOWER){
    Serial.println("The fan is turned off");
    digitalWrite(RELAY_FAN_PIN, LOW); // turn on
    digitalWrite(control,LOW); // Turn the MOSFET Switch OFF
  }

} 
