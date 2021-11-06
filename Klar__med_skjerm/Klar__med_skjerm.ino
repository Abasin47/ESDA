#include <AccelStepper.h>
#include <ezButton.h>
#include <LiquidCrystal.h>

//----- DEFINING PERMANENT VALUES -----
#define microPin 9
const unsigned short StepsPerRev = 400;
const float circ = 0.2199; //In meters
const float dist = 1.5; //In meters
const float calibrationFactor = 1.031; //Used to compensate for some mechanical elasticity
const float extraAcceleration = 500;
const float backwardSpeed = 150;
//----- SETTING PINS -----
AccelStepper stepper(1,7,6); //Defines stepper pins
ezButton interButGo(8); //Sends stone
ezButton interButRet(9); //Goes back after throw
ezButton interButStop(11); //Microswitch for setting 0 position

LiquidCrystal lcd(12, 11, 5, 4, 3, 12); //LCD-display
ezButton interButUp(10); //Fart++
ezButton interButDown(2);//Fart--


//----- DEFINING GLOBAL VARIABLES -----
bool forward = false;
bool forwardSet = false;
bool backward = true;
float fart; //Fart variabel

//----- DEFINING FUNCTIONS -----
float calcStepDist(float l, unsigned short SPR, float circumference){ //l in meters
  return (l*SPR/circumference);
}

float calcStepSpeed(float v, float circumference, unsigned short SPR){
  float rps = v/circumference;
  return (SPR*rps);
}

float calcStepAccelration(float stepSpeed, float stepDist){
  return (stepSpeed*stepSpeed/(2*stepDist));
}

void driveWithConstSpeed(){
  
}

const float distInSteps = calcStepDist(dist, StepsPerRev, circ*calibrationFactor); //defining number of steps to reach a distance
const float stepVelocity = calcStepSpeed(2.5, circ*calibrationFactor, StepsPerRev);
const float stepAccelration = calcStepAccelration(stepVelocity, distInSteps);

void setThrowAcc(float aStep, float vStep, float lStep){
 interButGo.loop();
  if(interButGo.isPressed()){
      stepper.setAcceleration(aStep+extraAcceleration);
      stepper.setMaxSpeed(vStep);
      stepper.moveTo(lStep);
      forwardSet = true;
  }
}
void returnStone(float backSpeed){
  stepper.setSpeed(-backSpeed);
  stepper.runSpeed();
}



//Fart++ , fart-- funksjon
float jusFart(){
  interButUp.loop();
  interButDown.loop();
 
  if(interButUp.isPressed()){
     fart+=0.5;
     lcd.clear();
     lcd.setCursor(5,0)
     lcd.print(fart);
     lcd.print("m/s");
     
     
     return fart;
  }
  if(interButDown.isPressed()){
     fart-=0.5;
      lcd.clear();
      lcd.setCursor(5,0)
      lcd.print(fart);
      lcd.print("m/s");
     
     if(fart>0){
     
         return fart;
     }
      lcd.clear();
      lcd.setCursor(5,0)
      lcd.print(fart);
      lcd.print("m/s");
     return fart=+0.5; 
  }
  return fart;
}










//----- SETUP FUNCTION -----

void setup() {
  pinMode(microPin, INPUT);
  interButGo.setDebounceTime(50);
  interButRet.setDebounceTime(50);
  stepper.setCurrentPosition(0);
  stepper.setMaxSpeed(1000);
  ///Skjerm setUp
  lcd.begin(16,2);
  lcd.setCursor(5, 0);
  lcd.print("Fart: ");
  lcd.setCursor(5,1);
  lcd.print(fart);
  lcd.print("m/s");
  
}


//----- MAIN LOOP -----

void loop() {
  if(forward){
    if(!forwardSet){
      setThrowAcc(stepAccelration, stepVelocity, distInSteps);
    }else{
      stepper.run();
    }
    if(stepper.distanceToGo()==1){
      backward = true;
      stepper.setCurrentPosition(distInSteps);
      forward = false;
      delay(1000);
    }
  }
  if (backward){
    if(digitalRead(microPin) == HIGH){
      returnStone(backwardSpeed);
    }else{
      stepper.setCurrentPosition(0);
      backward = false;
      forward = true;
      forwardSet = false;
    }
  }
}
