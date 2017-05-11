/*
 *   DEFAULT PINOUT: 
 *        _____________________________
 *       |  ARDUINO UNO >>>   Sim800L  |
 *        -----------------------------
 *            GND      >>>   GND
 *        RX  10       >>>   TX    
 *        TX  11       >>>   RX
 *       RESET 2       >>>   RST               
 *   POWER SOURCE 4.2V >>> VCC
*/

#include <Sim800L.h>
#include <SoftwareSerial.h>               

#define RX  10
#define TX  11

Sim800L GSM(RX, TX);

char* text;
char* number;
bool error; 					        //to catch the response of sendSms
int led = 13;                // the pin that the LED is atteched to
int sensor = 2;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)


void setup(){
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  Serial.begin(9600);        // initialize serial
	GSM.begin(4800); 			
	text="Testing Sms";  		//text for the message. 
	number="2926451386"; 		//change to a valid number.
	
	
	// OR 
  //	Sim800L.sendSms("+540111111111","the text go here")

}

void loop(){
  
	val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
    error=GSM.sendSms(number,text);
    delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }
}

