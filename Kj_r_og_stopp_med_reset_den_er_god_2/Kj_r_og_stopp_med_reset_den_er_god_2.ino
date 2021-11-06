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


ezButton interButRet(9);


float fart=2;
const int stepsPerRevolution = 400;
const float omn= 0.2199;
const float strek = 1.4;
const float endAccStrek = strek+0.1;
const float kalib = 0.968;



bool New;

float RotMove(float strek){
  float distance=(strek*stepsPerRevolution/om);
  return distance;
}

float strekning;
float retFart (float fart){
  float r=0.035;
  float rpm=fart*60/om;
  float rotPerSec=rpm/60;
  float pulsPerSec=stepsPerRevolution*rotPerSec;
  return pulsPerSec;
}
float setAccelration(float v, float s){
  float vel = retFart(v);
  float dist = RotMove(s);
  float acc = (vel*vel)/(2*dist);
  return acc;
}
void drive(float v, float a, float s){
  stepper.setAcceleration(a); //2425.347
  stepper.setMaxSpeed(v);
  stepper.move(s);
  stepper.runToPosition();
  stepper.setCurrentPosition(s);
}

void setup(){  
  // Change these to suit your stepper if you want
  Serial.begin(9600);
  interButGo.setDebounceTime(50);
  interButRet.setDebounceTime(50);
  stepper.setCurrentPosition(0);
}

bool kast(){

 interButGo.loop();

if(interButGo.isPressed ()){
  drive(

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
  

  kast();
  retur();
 
 
}
