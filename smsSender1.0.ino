#include <SoftwareSerial.h>
 
//SIM800 TX is connected to Arduino D8
#define SIM800_TX_PIN 8
 
//SIM800 RX is connected to Arduino D7
#define SIM800_RX_PIN 7
 
//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);

int led = 5;                // the pin that the LED is atteched to
int sensor = 4;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                // variable to store the sensor status (value)
int nmex = 0;

void setup() {
  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  
  Serial.begin(9600);
 
   
  //Being serial communication witj Arduino and SIM800
 
  Serial.println("Alarm system ON....");
  Serial.println("Setup Complete!");
  Serial.println("Ready to sending SMS...");
   
 
}
 
void loop() {
  
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);
    delay(4000);// turn LED ON
           
    
    if (state == LOW && nmex < 3 ) {
      
      Serial.println("Motion detected!");
      nmex++; 
       while(!Serial);
        serialSIM800.begin(9600);
      delay(1000);
       //Set SMS format to ASCII
      serialSIM800.write("AT+CMGF=1\r\n");
      delay(1000);
 
  //Send new SMS command and message number
      serialSIM800.write("AT+CMGS=\"3330000000\"\r\n");
      delay(1000);
   
  //Send SMS content
      serialSIM800.write("Allarme Scattato rilevata intrusione , F.R.I.D.A.Y ");
      delay(1000);
   
  //Send Ctrl+Z / ESC to denote SMS message is complete
      serialSIM800.write((char)26);
      delay(1000);
     
      Serial.println("SMS Sent!");
      state = HIGH;       // update variable state to HIGH
      delay(8000);
    }
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF
      delay(6000);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  }
}


