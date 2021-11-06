

#include <AccelStepper.h>
#include <ezButton.h>
#include <LiquidCrystal.h>
#include <Wire.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 13);
// Define Slave I2C Address
#define SLAVE_ADDR 9




// Define a stepper and the pins it will use
AccelStepper stepper(1,7,6);


ezButton interButUp(10);

ezButton interButDown(2);


int buttonUp=0;

int buttonDown=0;


int pinS=1;




float fart=1.0;
float strek=0.968;
float om=0.2199;
const int button1Pin = 8;
const int button2Pin = 9;

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
  pinMode(pinS,INPUT);
 
  interButUp.setDebounceTime(50);
  interButDown.setDebounceTime(50);

  
  lcd.begin(16,2);
  lcd.setCursor(5, 0);
  lcd.print("Fart: ");
  lcd.setCursor(0,5);
  lcd.print(fart);

 
  
  
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
     lcd.clear();
     lcd.print(fart);
     
     return fart;
  }
  if(interButDown.isPressed()){
     fart-=0.5;
      lcd.clear();
     lcd.print(fart);
     
     if(fart>0){
     
         return fart;
     }
     lcd.clear();
     lcd.print(fart);
     
 
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
  stepper.moveTo(RotMove(strek));
  
  
  
  
  }
}

void loop(){

  
  if(pinS==HIGH){
    lcd.print("HALLA");

    
    
  }
  
 
  
  jusFart();
  
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
 

  

  
  
  
  kast();
 
 
  if (button2State == HIGH)
  {
    stepper.setSpeed(-1000);
    stepper.runSpeed();
   

  }


 

}
