// Bounce.pde
// -*- mode: C++ -*-
//
// Make a single stepper bounce from one limit to another
//
// Copyright (C) 2012 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>
#include <ezButton.h>

// Define a stepper and the pins it will use
AccelStepper stepper(1,7,6);

ezButton interButGo(8);
int buttonGo=0;

ezButton interButRet(9);
int buttonRet=0;

float fart=10;
float om=0.2199;
float strek=1.5;

bool New;

float RotMove(float strek){
float distance=(strek/om)*400;

 return distance;
}




void setup()
{  
  // Change these to suit your stepper if you want

  Serial.begin(9600);
  interButGo.setDebounceTime(50);
  interButRet.setDebounceTime(50);
  stepper.setMaxSpeed(retFart(fart));
  stepper.setAcceleration(10000);
  stepper.setCurrentPosition(0);

 
 
}

float retFart (float fart){
  float r=0.035;
  float rpm=fart*60/om;
  float rotPerSec=rpm/60;
  float pulsPerSec=400*rotPerSec;
  
  return pulsPerSec;
 
}


bool kast(){
  bool klar=true;

 interButGo.loop();

if(interButGo.isPressed ()){
  buttonGo=+1;
  stepper.runToPosition();
  stepper.setCurrentPosition(RotMove(strek));
}

}

void retur(){
interButRet.loop();
if(interButRet.isPressed()){
    stepper.move(-RotMove(strek));
    stepper.runToPosition();
  
  }





}




void loop(){
  stepper.move(RotMove(strek));
  kast();
  retur();
 
 
}
