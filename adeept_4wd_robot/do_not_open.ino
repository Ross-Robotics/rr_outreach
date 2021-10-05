#include <Servo.h>
#include <Adafruit_NeoPixel.h>
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            8
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      3
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Motor control port
const int dirAPin = 7;    // define pin used to control rotational direction of motor A
const int pwmAPin = 6;    // define pin for PWM used to control rotational speed of motor A
const int dirBPin = 4;    // define pin used to control rotational direction of motor B
const int pwmBPin = 5;    // define pin for PWM used to control rotational speed of motor B

//Define motor control direction
#define FORWARD 1
#define BACKWARD 2
#define LEFT 3
#define RIGHT 4
#define STOP 5
#define MILD_RIGHT 6
#define MILD_LEFT 7
#define THRESH_H 1000
#define THRESH_L 100

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(dirAPin, OUTPUT);   // set dirAPin to output mode
  pinMode(pwmAPin, OUTPUT);   // set pwmAPin to output mode
  pinMode(dirBPin, OUTPUT);   // set dirBPin to output mode
  pinMode(pwmBPin, OUTPUT);   // set pwmBPin to output mode 
  ctrlCar(STOP,0);//A0, A1, A2 tracking does not detect black lines
  pinMode(13, OUTPUT);   // set dirAPin to output mode
  pinMode(8, OUTPUT);
  delay(50);
  for(int i=0;i<3;i++){
      pixels.setPixelColor(i,pixels.Color(100,50,150));
      pixels.show();    
      delay(50);       
  } 
  delay(500);   
  for(int i=0;i<3;i++){
      pixels.setPixelColor(i,pixels.Color(0,0,0));
      pixels.show();    
      delay(50);       
  } 
}
void loop() {
  Tracking();
  LedFeedback();  
  delay(50);
}
//Control motor motion direction and speed function
void ctrlCar( int motorDir, byte motorSpd) {
  byte motorSpdA;
  byte motorSpdB;
  switch(motorDir){
    case 1:digitalWrite(dirAPin, HIGH);
           digitalWrite(dirBPin, LOW);
           motorSpdA = motorSpd;
           motorSpdB = motorSpd;
           break;
    case 2:digitalWrite(dirAPin, LOW);
           digitalWrite(dirBPin, HIGH);
           motorSpdA = motorSpd;
           motorSpdB = motorSpd;
           break;
    case 3:digitalWrite(dirAPin, HIGH);
           digitalWrite(dirBPin, HIGH);
           motorSpdA = motorSpd;
           motorSpdB = motorSpd;
           break;
    case 4:digitalWrite(dirAPin, LOW);
           digitalWrite(dirBPin, LOW);
           motorSpdA = motorSpd;
           motorSpdB = motorSpd;
           break;    
    case 5:digitalWrite(dirAPin, LOW);
           digitalWrite(dirBPin, LOW);
           motorSpdA = 0;
           motorSpdB = 0;
           break;    
    case 6:digitalWrite(dirAPin, HIGH);
           digitalWrite(dirBPin, LOW);
           motorSpdA = motorSpd * 0.3;
           motorSpdB = motorSpd;
           break;    
    case 7:digitalWrite(dirAPin, HIGH);
           digitalWrite(dirBPin, LOW);
           motorSpdA = motorSpd;
           motorSpdB = motorSpd * 0.3;
           break;    
    default:digitalWrite(dirAPin, LOW);
           digitalWrite(dirBPin, LOW);
           motorSpdA = 0;
           motorSpdB = 0;
           break;     
  }
  analogWrite(pwmAPin, motorSpdA);
  analogWrite(pwmBPin, motorSpdB);
}
void LedFeedback(){
  if(analogRead(A0)>THRESH_H){
    pixels.setPixelColor(0,pixels.Color(100,100,100));
  }
  else{
    pixels.setPixelColor(0,pixels.Color(0,0,0));
  }
  if(analogRead(A1)>THRESH_H){
    pixels.setPixelColor(1,pixels.Color(100,100,100));
  }
  else{
    pixels.setPixelColor(1,pixels.Color(0,0,0));
  }
  if(analogRead(A2)>THRESH_H){
    pixels.setPixelColor(2,pixels.Color(100,100,100));
  }
  else{
    pixels.setPixelColor(2,pixels.Color(0,0,0));
  }
  pixels.show();
}
void Tracking(){
  int right_sensor = analogRead(A0);
  int centre_sensor = analogRead(A1);
  int left_sensor = analogRead(A2);
    
    if(right_sensor>THRESH_H&&centre_sensor>THRESH_H&&left_sensor>THRESH_H){
      ctrlCar(FORWARD,110);//Three tracking detections are black lines
    }
}
