// Bounce.pde
// -*- mode: C++ -*-
//
// Make a single stepper bounce from one limit to another
//
// Copyright (C) 2012 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>
#include <ezButton.h>
#include <LiquidCrystal.h>



// Define a stepper and the pins it will use
AccelStepper stepper(1,7,6);

LiquidCrystal lcd(12, 11, 5, 4, 3, 13);


ezButton interButUp(10);


ezButton interButDown(2);

int buttonUp=0;

int buttonDown=0;

String fartPrint;

boolean nyrunde;

float fart=0.1;
float strek=0.968;
float om=0.2199;
const int button1Pin = 8;
const int button2Pin = 1;

int button1State = 0;
int button2State = 0;

boolean flag1 = 0;
boolean flag2 = 0;






float RotMove(float strek){
  float distance=(strek/om)*400;

 return distance;
}



void setup()
{
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  lcd.begin(20, 2);
  interButUp.setDebounceTime(50);
  interButDown.setDebounceTime(50);

  Serial.begin(9600);
}





float retFart (float fart){
  float r=0.035;
  float rpm=fart*60/om;
  float rotPerSec=rpm/60;
  float pulsPerSec=400*rotPerSec;
 
  return pulsPerSec;
 
}


float jusFart(){
  interButUp.loop();
  interButDown.loop();
 
  
  if(interButUp.isPressed()){
     fart+=0.5;
   
     return fart;
  }
  if(interButDown.isPressed()){
     fart-=0.5;
    
     
     if(fart>0){
     
         return fart;
     }
      
    
     return fart=+0.5;
     
   
  }
  
  
  return fart;
 
}


void kast(){
  
  if (button1State == HIGH)
  {

  stepper.setMaxSpeed(retFart(jusFart()));
  stepper.setSpeed(retFart(jusFart()));
  stepper.runSpeedToPosition();
  

  
  
  }
}

void loop(){
  
  jusFart();
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  
  stepper.moveTo(RotMove(strek));
  kast();





  
 
  if (button2State == LOW)
  {
    
    stepper.setSpeed(-100);
    stepper.runSpeed();

  }

  
}
