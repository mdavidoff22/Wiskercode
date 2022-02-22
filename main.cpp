#include <Arduino.h>
#include <Servo.h>
//import the arduino and servo libraries

//Methodology: I deleted the conditional for when both sensors are activtaed ~ at the same time, as it would only allow the robot to turn one direction (I had is as turn left) when this happened. Including this conditional worked for most of the course, as the robot often had the sensors activated at the same time and only had left turn for like 80% of the course. However there was one turn at the end where the robot had to turn right, and both sensors where activated there. There was no good way to differentiate the direction the robot was to turn when both sensors were activated, so I deleted the conditional, only running the ones for the left and right sensors individually being activated. This allowed for more specific turns based on the angles the robot aproached the walls, and allowed for the robot to complete the course. The sensitivity of the sensors were not equal, so I had to attach them at different vertical and horizontal angles so that the detection would be accurate.  

Servo servoLeft;
Servo servoRight;
//declare the servos

void setup()
{ pinMode(10, INPUT);  pinMode(9, OUTPUT);
  pinMode(3, INPUT);  pinMode(2, OUTPUT);
  servoLeft.attach(13);
  servoRight.attach(12);
}
//a function that associates the signals from pins 10 and 3 as input functions from the two receivors and 9 and 2 for the output
//and associate the servos with their pins

int irDetect(int irLedPin, int irReceiverPin, long frequency)
{ tone(irLedPin, frequency, 8); // IRLED 38 kHz for at least 1 ms
  delay(1); // Wait 1 ms
  int ir = digitalRead(irReceiverPin); // IR receiver -> ir variable
  delay(1); // Down time before recheck
  return ir; // Return 1 as the value for no detection and 0 as detection
}

void forward(int time)
{ servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(time);
}
//a function to move the wheels in the microseconds directions to move forward for a passed in time value

void turnLeft(int time)
{ servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(time);
}
//turn the robot left

void turnRight(int time)
{ servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(time);
}
//turn the robot left

void backward(int time)
{ servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
  delay(time);
}
//move the robot backwards

//a loop to run the code
void loop()
{ int irLeft = irDetect(9, 10, 38000);
  int irRight = irDetect(2, 3, 38000);

  if(irLeft == 0)
  { 
    backward(500);
    turnRight(400);
  }
  else if(irRight == 0)
  { 
    backward(500);
    turnLeft(200);
  }
  else {forward(20); }
}
//contains detection conditionals for if the right and left signals detect something and if so turn the oppositve way. If nothing is detected, then keep moving forwards. Note, there is no conditional for when both sensors are activated simultaneously.
