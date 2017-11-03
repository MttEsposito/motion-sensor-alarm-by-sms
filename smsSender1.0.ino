//**********************************************************************
//          WELCOME THANK YOU FOR DOWNLOAD THE CODE                    *
//          MADE BY MATTIA ESPOSITO                                    *
//          https://github.com/MttEsposito                             *
//          https://www.youtube.com/channel/UCPTNOyJNd_I3DN77ojzRrug   *
//          HAVE A NICE CODING                                         *
//**********************************************************************


#include <SoftwareSerial.h>
 
//SIM800 TX is connected to Arduino D8
#define SIM800_TX_PIN 8
 
//SIM800 RX is connected to Arduino D7
#define SIM800_RX_PIN 7
 
//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);
unsigned long time;
unsigned long time2;
unsigned long time3;
unsigned long time4;
const long interval = 15000; //15 sec
int sensor = 10;             
int val = LOW;  
int contatore= 0;
void setup()
{
  Serial.begin(9600);
  Serial.println("Alarm system ON....");
  Serial.println("Setup Complete!");
  Serial.println("Ready to sending SMS...");
  delay(60000);
}
 
void loop()
{
   val = digitalRead(sensor);   // read sensor value
  time = millis();
  //prints time since program started
  if(val== HIGH && contatore==0){
    time2=time;
    Serial.println("Time2 e: ");
    Serial.println(time2);
    contatore++;
    Serial.println(contatore);
    delay(1000);
  }
  if(val==HIGH){
    contatore++;
    Serial.println("contatore ");
    Serial.println( contatore);
    delay(3000);
  }
  if(contatore==4){
    time3=time;
    time4=time3-time2;
     Serial.println("Time3 e: ");
    Serial.println(time3);
    Serial.println("Time4 e: ");
    Serial.println(time4);
     Serial.println("interval e: ");
    Serial.println(interval);
    if(time4 <= interval){
       while(!Serial);
        serialSIM800.begin(9600);
      delay(2000);
       //Set SMS format to ASCII
      serialSIM800.write("AT+CMGF=1\r\n");
      delay(2000);
 
  //Send new SMS command and message number
      serialSIM800.write("AT+CMGS=\"3333333333\"\r\n");
      delay(2000);
   
  //Send SMS content
      serialSIM800.write("Allarme Scattato rilevata intrusione , F.R.I.D.A.Y ");
      delay(2000);
   
  //Send Ctrl+Z / ESC to denote SMS message is complete
      serialSIM800.write((char)26);
      delay(2000);
     
      Serial.println("SMS Sent!");
      delay(10000);
      time2=0;
      time3=0;
      contatore=0;
    }else{
      time2=0;
      time3=0;
      contatore=0;
       Serial.println("scatti al di sopra dei 10 secondi");
       delay(10000);
    }
    
  }
 
}
