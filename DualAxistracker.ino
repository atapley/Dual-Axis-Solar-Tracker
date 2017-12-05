#include <Servo.h> 
const int sensorPinLB = 0; //white
const int sensorPinRB = 1; //red
const int sensorPinLT = 2; //green
const int sensorPinRT = 3; //orange
const int servoPinH = 3; //purple
const int servoPinV = 4; //blue
int lightLevelLB, lightLevelRB, lightLevelLT, lightLevelRT, avgLeft, avgRight, avgTop, avgBottom, 
diffHorizontal, diffVertical, tolerance, maxHorAng, maxVerAng, servoAngleH, servoAngleV, delayTime, nightTime;
Servo ServoH;
Servo ServoV;

//bottom servo, purple to brown, black to red, blue to yellow
//top servo, purple to yellow, green to red, yellow to brown

//LT = green+red to red+blue
//RT = yellow+blue to yellow+orange
//LB = purple+orange to white+black
//RB = white+white to purple+white

void setup()
{
  Serial.begin(9600);
  ServoH.attach(servoPinH); 
  ServoV.attach(servoPinV);
  ServoH.write(0);
  ServoV.write(0);
}

void loop()
{
  lightLevelLB = analogRead(sensorPinLB);
  lightLevelRB = analogRead(sensorPinRB);
  lightLevelLT = analogRead(sensorPinLT);
  lightLevelRT = analogRead(sensorPinRT);
  avgLeft = (lightLevelLB + lightLevelLT) / 2;
  avgRight = (lightLevelRB + lightLevelRT) / 2;
  avgTop = (lightLevelLT + lightLevelRT) / 2;
  avgBottom = (lightLevelRB + lightLevelLB) / 2;
  diffHorizontal = avgRight - avgLeft; //positive means sun is on Right, negative means sun is on left
  diffVertical = avgTop - avgBottom; //positive means sun is above, negative means sun is below
  tolerance = 50;
  maxHorAng = 180;
  maxVerAng = 170;
  delayTime = 10;
  nightTime = 40;
  manualTune();

  if(diffHorizontal > tolerance) {

    if(servoAngleH > maxHorAng) {
      servoAngleH = maxHorAng;
    }
    else {
      servoAngleH = ++servoAngleH;
      ServoH.write(servoAngleH);
    }
  }
  else if(diffHorizontal < -tolerance) {

    if(servoAngleH < -maxHorAng) {
      servoAngleH = -maxHorAng;
    }
    else {
      servoAngleH = --servoAngleH;
      ServoH.write(servoAngleH);
    }
  }
  else {
    //do nothing
  }

    if(diffVertical > tolerance) {

    if(servoAngleV > maxVerAng) {
      servoAngleV = maxVerAng;
    }
    else {
      servoAngleV = ++servoAngleV;
      ServoV.write(servoAngleV);
    }
  }
  else if(diffVertical < -tolerance) {

    if(servoAngleV < -maxVerAng) {
      servoAngleV = -maxVerAng;
    }
    else {
      servoAngleV = --servoAngleV;
      ServoV.write(servoAngleV);
    }
  }
  else {
    //do nothing
  }

  if(lightLevelLB < nightTime && lightLevelRB < nightTime && lightLevelLT < nightTime && lightLevelRT < nightTime) {
    while(servoAngleH > 0) {
      ServoH.write(--servoAngleH);
    }

    while(servoAngleV > 0) {
      ServoV.write(--servoAngleV);
    }
  }

  delay(delayTime);
}


void manualTune()
{
  
  lightLevelLB = map(lightLevelLB, 0, 1023, 0, 255);
  lightLevelLB = constrain(lightLevelLB, 0, 255);

  lightLevelRB = map(lightLevelRB, 0, 1023, 0, 255);
  lightLevelRB  = constrain(lightLevelRB, 0, 255);
  
  lightLevelLT = map(lightLevelLT, 0, 1023, 0, 255);
  lightLevelLT = constrain(lightLevelLT, 0, 255);
    
  lightLevelRT = map(lightLevelRT, 0, 1023, 0, 255);
  lightLevelRT = constrain(lightLevelRT, 0, 255);
} 



