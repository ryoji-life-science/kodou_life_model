#include <EEPROM.h>
#include <avr/sleep.h>

unsigned long tm;
int a = 0;
int b = 0;
int life = 30;

//  VARIABLES
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 12;                // pin to blink led at each beat
int fadePin = 9;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin

// these variables are volatile because they are used during the interrupt service routine!
volatile int BPM;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, the Inter-Beat Interval
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.



void setup(){
 digitalWrite(11,HIGH);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
  Serial.begin(115200);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
   // UN-COMMENT THE NEXT LINE IF YOU ARE POWERING The Pulse Sensor AT LOW VOLTAGE, 
   // AND APPLY THAT VOLTAGE TO THE A-REF PIN
   //analogReference(EXTERNAL);   
}



void loop(){


  sendDataToProcessing('S', Signal);     // send Processing the raw Pulse Sensor data
  if (QS == true){                       // Quantified Self flag is true when arduino finds a heartbeat
        fadeRate = 255;                  // Set 'fadeRate' Variable to 255 to fade LED with pulse
        sendDataToProcessing('B',BPM);   // send heart rate with a 'B' prefix
        sendDataToProcessing('Q',IBI);   // send time between beats with a 'Q' prefix
        QS = false;                      // reset the Quantified Self flag for next time    
        
  }
  ledFadeToBeat();
  delay(5);                             //  take a break
}


void ledFadeToBeat(){

    if(fadeRate > 200 ) { 
      fadeRate -= 20;
    } else if ( fadeRate > 150 ) { 
      fadeRate -= 10;
    } else if ( fadeRate > 100 ) { 
      fadeRate -= 5;
    } else if ( fadeRate > 50 ) { 
      fadeRate -= 2;
    } else if ( fadeRate > 0 ) { 
      fadeRate -= 1;
    }


    
  //  fadeRate -= 15;                         //  set LED fade value
    fadeRate = constrain(fadeRate,0,255);   //  keep LED fade value from going into negative numbers!
    analogWrite(fadePin,fadeRate);          //  fade LED
  }


void sendDataToProcessing(char symbol, int data ){
  int i[10];
  int value;
  int b[10];
  int wait = 0;
  int set_time;
    //Serial.print(symbol);                // symbol prefix tells Processing what type of data is coming
   //Serial.println(data);                // the data to send culminating in a carriage return
   //この↑のdataの記述のタイミングが使える
  }
