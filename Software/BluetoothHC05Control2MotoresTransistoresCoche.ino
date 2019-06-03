
#include <SoftwareSerial.h>
#include <TimerOne.h>

#define rxPin 2
#define txPin 3

SoftwareSerial mySerial= SoftwareSerial(rxPin, txPin);

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int motor1 = 7;
int motor2 = 8;
int motor3 = 9;
int motor4 = 10;
// OPERADOR

byte var;

int securityStop = 0;

// the setup routine runs once when you press reset:
void setup() {
  // PUERTO SERIE BLUETOOTH

   mySerial.begin(9600);
   Serial.begin(9600);
   
  // make the pushbutton's pin an input:
  //pinMode(pushButton, INPUT);

    // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  //digitalWrite(motor1, HIGH);
  //digitalWrite(motor2, HIGH);
  //digitalWrite(motor3, HIGH);
  //digitalWrite(motor4, HIGH);
  
  
  Serial.println("Motor server running");
  Serial.println("0 forward");
  Serial.println("1 stop");
  Serial.println("2 left");
  Serial.println("3 right"); 
  
  Serial.println("Testing forward");
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, HIGH);
  delay(1000);
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  
  securityStop = 0;
}

// the loop routine runs over and over again forever:
void loop() {
  
   if(mySerial.available()){
    char var2 = mySerial.read();   
    Serial.print("Recibido comando:");
    Serial.println(var2);
    switch(var2){
      case '1': //forward
              Serial.println("Moving forward");
              digitalWrite(motor1, HIGH);
              digitalWrite(motor2, HIGH);
              mySerial.write(10);
              securityStop = 0;
              break;
      case '0': //stop
              Serial.println("Stop");
              digitalWrite(motor1, LOW);
              digitalWrite(motor2, LOW);
              mySerial.write(11);
              securityStop = 0;
              break;  
       case '2': //left
              Serial.println("Turning Left");
              digitalWrite(motor1, HIGH);
              digitalWrite(motor2, LOW);
              mySerial.write(12);
              securityStop = 0;
              break;
       case '3': //right
              Serial.println("Turning Right");
              digitalWrite(motor1, LOW);
              digitalWrite(motor2, HIGH);
              mySerial.write(13);
              securityStop = 0;
              break;               
    }
   delay(100);        // delay in between reads for stability
  }else if(Serial.available()){
    char var2 = Serial.read();   
    Serial.print("Recibido comando:");
    Serial.println(var2);
    switch(var2){
      case '1': //forward
              Serial.println("Moving forward");
              digitalWrite(motor1, HIGH);
              digitalWrite(motor2, HIGH);
              Serial.write(10);
              securityStop = 0;
              break;
      case '0': //stop
              Serial.println("Stop");
              digitalWrite(motor1, LOW);
              digitalWrite(motor2, LOW);
              Serial.write(11);
              securityStop = 0;
              break;  
       case '2': //left
              Serial.println("Turning Left");
              digitalWrite(motor1, HIGH);
              digitalWrite(motor2, LOW);
              Serial.write(12);
              securityStop = 0;
              break;
       case '3': //right
              Serial.println("Turning Right");
              digitalWrite(motor1, LOW);
              digitalWrite(motor2, HIGH);
              Serial.write(13);
              securityStop = 0;
              break;               
    }
   delay(100);        // delay in between reads for stability
  }else{
    delay(100);
    if (securityStop>50){
       digitalWrite(motor1, LOW);
       digitalWrite(motor2, LOW);
    }else{
       securityStop=securityStop+1;
       Serial.print("Security Stop="); Serial.println(securityStop);
    }
  }
  
  
}



