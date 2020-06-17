/*
 * lineFollower
 * Copyright (c) 2020 Maxim Verhoef
*/

#include <Servo.h> 
  Servo rightServo;
  Servo leftServo;
  
int out1 = 10;                    // infra red out1 = links
int out2 = 2;                     // infra red out2 = lm
int out3 = 3;                     // infra red out3 = midden
int out4 = 4;                     // infra red out4 = rm
int out5 = 5;                     // infra red out5 = rechts

int out1Value;                    // out1 value
int out2Value;                    // out2 value
int out3Value;                    // out3 value
int out4Value;                    // out4 value
int out5Value;                    // out5 value

int const startUpLed = 11;        // Pin connected to the start up LED

//-------------
//Servo forward
//-------------
int const rsff =  0;              // Right Servo Forward Fast
int const lsff = 180;             // Left Servo Forward Fast

int const rsfs = 85;              // Right Servo Forward Slow
int const lsfs = 126;             // Left Servo Forward Slow was 118

//-------------
//Servo reverse
//-------------
int const rsrf = 180;             //Right Servo Reverse Fast
int const lsrf = 0;               //Left Servo Reverse Fast

//-----
//Break
//-----
int const rsbr = 90;              // Right Servo Break
int const lsbr = 90;              // Left Servo Break

//Starting up
void setup() 
{ 

   Serial.begin(9600);                   

  while(!Serial);                 //Wait for serial connection
  Serial.println("setup():        Hello there. ");
  //Define servos
  rightServo.attach(8);   
  leftServo.attach(9);

  pinMode(startUpLed, OUTPUT);    // Startup LED
  startFlash();                   // Flashing signal
}

void loop() {
  //Read the value from the sensor:
  out1Value = digitalRead(out1);
  out2Value = digitalRead(out2);
  out3Value = digitalRead(out3);
  out4Value = digitalRead(out4);
  out5Value = digitalRead(out5);
  Serial.println();                    
  Serial.print("out1: "); Serial.print(out1Value);
  Serial.print("  out2: "); Serial.print(out2Value); 
  Serial.print("  out3: "); Serial.print(out3Value);
  Serial.print("  out4: "); Serial.print(out4Value);
  Serial.print("  out5: "); Serial.print(out5Value);
  delay(10); 
                           
//-------
//Forward
//-------
  if((out1Value == 1) && (out2Value == 1) && (out3Value == 0) && (out4Value == 1) && (out5Value == 1)){
    forwardSlow();
    delay(20);
     //If robot loses track
    if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
      searchTrack();
      delay(20);
    }
  }
  //---------
  //Turn Left
  //---------
    if((out1Value == 0) && (out2Value == 0) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
    turnLeftSlow();
    delay(100);
    //If robot loses track
    if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
      turnLeftSlow();
      delay(500);
    }
  }
  if((out1Value == 0) && (out2Value == 0) && (out3Value == 0) && (out4Value == 1) && (out5Value == 1)){
    turnLeftSlow();
    delay(100);
    //If robot loses track
    if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
      turnLeftSlow();
      delay(500);
    }
  }
  if((out1Value == 0) && (out2Value == 0) && (out3Value == 0) && (out4Value == 0) && (out5Value == 1)){
    turnLeftSlow();
    delay(100);
    //If robot loses track
    if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
      turnLeftSlow();
      delay(500);
    }
  }
//----------
//Turn Right
//----------
  if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 0) && (out5Value == 0)){
    turnRightSlow();
    delay(100);
    //If robot loses track
    if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
      turnRightSlow();
      delay(500);
    }
  }
  if((out1Value == 1) && (out2Value == 1) && (out3Value == 0) && (out4Value == 0) && (out5Value == 0)){
    turnRightSlow();
    delay(100);
    //If robot loses track
    if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
      turnRightSlow();
      delay(500);
    }
  }
  if((out1Value == 1) && (out2Value == 0) && (out3Value == 0) && (out4Value == 0) && (out5Value == 0)){
    turnRightSlow();
    delay(100);
    //If robot loses track
    if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
      turnRightSlow();
      delay(500);
    }
  }
//----------
//Correction
//----------
//To Left
  if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 0) && (out5Value == 1)){
    correctionToLeft();
    delay(20);
    //If robot loses track
    if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
      turnRightSlow();
      delay(20);
    }
  }
  if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 1) && (out5Value == 0)){
    correctionToLeft();
    delay(20);
    //If robot loses track
    if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
      turnRightSlow();
      delay(20);
    }
  }
 if((out1Value == 1) && (out2Value == 1) && (out3Value == 0) && (out4Value == 0) && (out5Value == 1)){
    correctionToLeft();
    delay(20);
    //If robot loses track
    if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
      turnRightSlow();
      delay(20);
    }
  }
//To Right
  if((out1Value == 1) && (out2Value == 0) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
    correctionToRight();
    delay(20);
    //If robot loses track
    if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
      turnLeftSlow();
      delay(20);
    }
  }
  if((out1Value == 0) && (out2Value == 1) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
    correctionToRight();
    delay(20);
    //If robot loses track
    if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
      turnLeftSlow();
      delay(20);
    }
  }
  if((out1Value == 1) && (out2Value == 0) && (out3Value == 0) && (out4Value == 1) && (out5Value == 1)){
    correctionToRight();
    delay(20);
    //If robot loses track
    if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
      turnLeftSlow();
      delay(20);
    }
  }
//-----
//Break
//-----
  if((out1Value == 0) && (out2Value == 0) && (out3Value == 0) && (out4Value == 0) && (out5Value == 0)){
    hitBreaks();
    delay(20);
    //If robot loses track
    if((out1Value == 1) && (out2Value == 1) && (out3Value == 1) && (out4Value == 1) && (out5Value == 1)){
      hitBreaks();
      delay(20);
    }
  }
}
//-----------------
//Starting up flash
//-----------------
void startFlash(){    
  Serial.println("startFlash():   flash 3 times.");
  digitalWrite(startUpLed, HIGH);
  delay(100);
  digitalWrite(startUpLed, LOW);
  delay(500);
  digitalWrite(startUpLed, HIGH);
  delay(100);
  digitalWrite(startUpLed, LOW);
  delay(500);
  digitalWrite(startUpLed, HIGH);
  delay(100);
  digitalWrite(startUpLed, LOW);
  delay(500);
}
void forwardSlow(){       
  Serial.println("setup():        Going forward. "); 
  rightServo.write(rsfs);     
  leftServo.write(lsfs); 
}
void turnLeftSlow(){
  Serial.println("setup():        Turning left. ");
  rightServo.write(rsfs);     
  leftServo.write(lsbr);   
}
void turnRightSlow(){
  Serial.println("setup():        Turning right. ");
  rightServo.write(rsbr);     
  leftServo.write(lsfs); 
}
void correctionToLeft(){
  Serial.println("setup():        Correcting to the left. ");
  rightServo.write(rsfs);     
  leftServo.write(lsff); 
}
void correctionToRight(){
  Serial.println("setup():        Correcting to the right. ");
  rightServo.write(rsff);     
  leftServo.write(lsfs); 
}
void hitBreaks(){
  Serial.println("setup():        Hitting the breaks. ");
  rightServo.write(rsbr);     
  leftServo.write(lsbr); 
}
void searchTrack(){
  Serial.println("setup():        I've lost track. ");
  rightServo.write(rsff);     
  leftServo.write(lsfs); 
}
