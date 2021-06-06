#include "Timer.h"
#include <Adafruit_NeoPixel.h>
Timer t;

unsigned int buzzTime = 1000; //ms

const int trigPin = 7; //set pin variables
const int echoPin = 6;

int trigState = LOW; //state of trigPin
int interval = 1; // interval in milliseconds at which trigPin turns on
int interval2 = 1000; //time in milliseconds at which the distance is printed in serial monitors
int printState = LOW; //whether or not to print distance
unsigned long previousMillis = 0; //microsecond at which the pin was last writen

byte buzzer = A0; //vibration module

unsigned long previous = 0;

//LED for turning lights
#define ledPin 4
#define ledCount 14
Adafruit_NeoPixel strip (ledCount, ledPin, NEO_GRB + NEO_KHZ800);

//lED for ultrasonic
#define ledPinU 5
#define ledCountU 4
Adafruit_NeoPixel stripU (ledCountU, ledPinU, NEO_GRB + NEO_KHZ800);

//cap
#define ctsPin_left 2
#define ctsPin_right 3
unsigned long capprevious = 0;
bool start_left = false;
bool start_right = false;
int count = 0;

//mpu
#include <Wire.h>

int brightness = 255;

#define FRONT_PIN        8   //胸前灯条输出接口
#define FRONT_COUNT      6
#define HEARTBEAT_PIN    9   //心电图灯条输出接口
#define HEARTBEAT_COUNT  29
#define CALORIE_PIN      10   //卡路里灯条输出接口
#define CALORIE_COUNT    15

const int MPU_ADDR = 0x68;
float AccX, AccY, AccZ;
float elapsedTime, currentTime, previousTime;
float v = 0.0;
float sqrv;
int j = 0;
int i = 0;
long moveTime = 0;
unsigned long nextTimer = 0;
unsigned long animTime;

Adafruit_NeoPixel strip1 (HEARTBEAT_COUNT, HEARTBEAT_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 (CALORIE_COUNT, CALORIE_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 (FRONT_COUNT, FRONT_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600); //begin serial communication
  pinMode(trigPin,OUTPUT); //set pinmodes
  pinMode(echoPin,INPUT);
  
  pinMode(buzzer, OUTPUT);

  strip.begin();
  strip.show();
  strip.setBrightness(255);

  stripU.begin();
  stripU.show();
  stripU.setBrightness(255);

  pinMode(ctsPin_left, INPUT);
  pinMode(ctsPin_right, INPUT);

  //mpu
  strip1.begin();
  strip1.show();
  strip1.setBrightness(brightness);
  strip2.begin();
  strip2.show();
  strip2.setBrightness(brightness);
  strip3.begin();
  strip3.show();
  strip3.setBrightness(brightness);
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  nextTimer = millis();
  strip1.setPixelColor(i, strip1.Color(255, 0, 0));
  strip1.show();
  strip3.setPixelColor(j, strip1.Color(255, 0, 0));
  strip3.show();
}

void loop()
{
  unsigned long currentMillis = millis(); //time in milliseconds from which the code was started
  if (currentMillis-previousMillis >= interval) { //check "blink without delay" code
    previousMillis = currentMillis;
    if (trigState == LOW){
      (trigState = HIGH);
    }
    else {
      (trigState = LOW);
    }
  }
  // printing if statement
  if (currentMillis-previousMillis >= interval2) { //check "blink without delay" code
    previousMillis = currentMillis;
    if (printState == LOW){
      (printState = HIGH);
    }
    else {
      (printState = LOW);
    }
  }
  digitalWrite(trigPin,trigState);
  int duration, distance; //variables
  duration = pulseIn(echoPin,HIGH, 5000);
  distance = (duration/2) / 29.1;
//  if (printState = HIGH){
//  Serial.print(distance);
//  Serial.println("cm");}
  
  if (distance <= 100 && distance != 0){
    Serial.print(distance);
    Serial.println("cm");
    unsigned long current = millis();
    if (current - previous >= 0 && current - previous <= 500) {
      stripU.fill(stripU.Color(0,0,255), 0, stripU.numPixels());
      stripU.show();
      strip.fill(strip.Color(0,0,255), 0, strip.numPixels());
      strip.show();
    } else if(current - previous >= 500 && current - previous <= 1000){
      stripU.fill(stripU.Color(0,0,255), 0, stripU.numPixels());
      stripU.show();
      strip.fill(strip.Color(0,0,255), 0, strip.numPixels());
      strip.show();
    }
    if(current - previous >= 900){
      previous = current;
    }
    t.pulseImmediate(buzzer,buzzTime,HIGH);
    t.update();
  } else {
    // turn off 
    stripU.fill(stripU.Color(0,0,0), 0, stripU.numPixels());
    stripU.show();
    strip.fill(strip.Color(0,0,0), 0, strip.numPixels());
    strip.show();
    }

//  if (distance > 100 && distance <=150) {
//    t.pulseImmediate(buzzer,buzzTime - 500, HIGH);
//    t.update();
//  }

  //cap for turning
  int ctsValue_left = digitalRead(ctsPin_left);

  if (start_left && !start_right) {
    unsigned long current = millis();
    if (current - capprevious >= 0 && current -capprevious <= 500) {
      strip.fill(strip.Color(0,0,0), 0, 7);
      strip.show();
    } else if(current - capprevious >= 500 && current - capprevious <= 1000){
      strip.fill(strip.Color(255,215,0), 0, 7);
      strip.show();
    }
    if(current - capprevious >= 900){
      capprevious = current;
      count++;
//      Serial.println(count);
      if (count == 3) {
        start_left = false;
        count = 0;
        strip.fill(strip.Color(0,0,0),0,7);
        strip.show();
      }
    }
  }
  

  if (ctsValue_left == HIGH) {
    start_left = true;
    Serial.println("LEFT");
  }

  if (start_right) {
    unsigned long current = millis();
    if (current - capprevious >= 0 && current - capprevious <= 500) {
      strip.fill(strip.Color(0,0,0), 7, strip.numPixels());
      strip.show();
    } else if(current - capprevious >= 500 && current - capprevious <= 1000){
      strip.fill(strip.Color(255,215,0), 7, strip.numPixels());
      strip.show();
    }
    if(current - capprevious >= 900){
      capprevious = current;
      count++;
//      Serial.println(count);
      if (count == 3) {
        start_right = false;
        count = 0;
        strip.fill(strip.Color(0,0,0),7,strip.numPixels());
        strip.show();
      }
    }
  }
  int ctsValue_right = digitalRead(ctsPin_right);

  if (ctsValue_right == HIGH) {
    start_right = true;
    Serial.println("RIGHT");
  }

  //mpu
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  AccX = Wire.read()<<8 | Wire.read();
  AccY = Wire.read()<<8 | Wire.read();
  AccZ = Wire.read()<<8 | Wire.read();
  AccZ = AccZ / 1638.4;

  previousTime = currentTime;
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000;

  if (abs(AccZ) < 1){AccZ = 0;}  //改变if条件里的值来确保传感器稍有倾斜也不会让Z轴数据受到重力加速度影响
  v = v + AccZ * elapsedTime;
  
  if (v == 0){v = 0.01;}
  if(v > 100){v = 100;}
  if (v < -100){v = -100;}
  sqrv = sqrt(abs(v));
  animTime = 200 / sqrv;
 // Serial.println(moveTime);  //在串口监视器里监视Z轴加速度
  
  HeartbeatStrip();
  
  CalorieStrip();
  
}

void HeartbeatStrip(){
  if(nextTimer + animTime < millis()){
    strip1.clear();
    strip3.clear();
    strip1.setPixelColor(i, strip1.Color(255, 0, 0));
    strip3.setPixelColor(j, strip1.Color(255, 0, 0));
    strip1.show();
    strip3.show();
    i++; j++;
    if(i>28){i=0;}
    if(j>11){j=0;}
    nextTimer = millis();
  }
}

void CalorieStrip(){
  strip2.clear();
  strip2.setPixelColor(14, strip1.Color(0, 255, 0));
  strip2.setPixelColor(13, strip1.Color(0, 255, 0));
  strip2.setPixelColor(12, strip1.Color(0, 255, 0));
  strip2.setPixelColor(11, strip1.Color(128, 255, 0));
  strip2.setPixelColor(10, strip1.Color(128, 255, 0));
  strip2.setPixelColor(9, strip1.Color(128, 255, 0));
  strip2.setPixelColor(8, strip1.Color(255, 255, 0));
  strip2.setPixelColor(7, strip1.Color(255, 255, 0));
  strip2.setPixelColor(6, strip1.Color(255, 255, 0));
  strip2.setPixelColor(5, strip1.Color(255, 64, 0));
  strip2.setPixelColor(4, strip1.Color(255, 64, 0));
  strip2.setPixelColor(3, strip1.Color(255, 64, 0));
  strip2.setPixelColor(2, strip1.Color(255, 0, 0));
  strip2.setPixelColor(1, strip1.Color(255, 0, 0));
  strip2.setPixelColor(0, strip1.Color(255, 0, 0));

  if (abs(v) > 5){  //改变if中的值来使卡路里灯在合适的速度下才开始消失
    moveTime = moveTime + 1;
    if (moveTime > 5000){
      moveTime = 5001;
      strip2.setPixelColor(14, strip1.Color(0, 0, 0));
      strip2.setPixelColor(13, strip1.Color(0, 0, 0));
      strip2.setPixelColor(12, strip1.Color(0, 0, 0));
      strip2.setPixelColor(11, strip1.Color(0, 0, 0));
      strip2.setPixelColor(10, strip1.Color(0, 0, 0));
      strip2.setPixelColor(9, strip1.Color(0, 0, 0));
      strip2.setPixelColor(8, strip1.Color(0, 0, 0));
      strip2.setPixelColor(7, strip1.Color(0, 0, 0));
      strip2.setPixelColor(6, strip1.Color(0, 0, 0));
      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
    }else if (moveTime > 4000){
      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
      strip2.setPixelColor(11, strip1.Color(0, 0, 0));
      strip2.setPixelColor(10, strip1.Color(0, 0, 0));
      strip2.setPixelColor(9, strip1.Color(0, 0, 0));
      strip2.setPixelColor(8, strip1.Color(0, 0, 0));
      strip2.setPixelColor(7, strip1.Color(0, 0, 0));
      strip2.setPixelColor(6, strip1.Color(0, 0, 0));
      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
    }else if (moveTime > 3000){
      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
      strip2.setPixelColor(11, strip1.Color(128, 255, 0));
      strip2.setPixelColor(10, strip1.Color(128, 255, 0));
      strip2.setPixelColor(9, strip1.Color(128, 255, 0));
      strip2.setPixelColor(8, strip1.Color(0, 0, 0));
      strip2.setPixelColor(7, strip1.Color(0, 0, 0));
      strip2.setPixelColor(6, strip1.Color(0, 0, 0));
      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
    }else if (moveTime > 2000){
      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
      strip2.setPixelColor(11, strip1.Color(128, 255, 0));
      strip2.setPixelColor(10, strip1.Color(128, 255, 0));
      strip2.setPixelColor(9, strip1.Color(128, 255, 0));
      strip2.setPixelColor(8, strip1.Color(255, 255, 0));
      strip2.setPixelColor(7, strip1.Color(255, 255, 0));
      strip2.setPixelColor(6, strip1.Color(255, 255, 0));
      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
    }else if (moveTime > 1000){
      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
      strip2.setPixelColor(11, strip1.Color(128, 255, 0));
      strip2.setPixelColor(10, strip1.Color(128, 255, 0));
      strip2.setPixelColor(9, strip1.Color(128, 255, 0));
      strip2.setPixelColor(8, strip1.Color(255, 255, 0));
      strip2.setPixelColor(7, strip1.Color(255, 255, 0));
      strip2.setPixelColor(6, strip1.Color(255, 255, 0));
      strip2.setPixelColor(5, strip1.Color(255, 64, 0));
      strip2.setPixelColor(4, strip1.Color(255, 64, 0));
      strip2.setPixelColor(3, strip1.Color(255, 64, 0));
      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
    }else{
      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
      strip2.setPixelColor(11, strip1.Color(128, 255, 0));
      strip2.setPixelColor(10, strip1.Color(128, 255, 0));
      strip2.setPixelColor(9, strip1.Color(128, 255, 0));
      strip2.setPixelColor(8, strip1.Color(255, 255, 0));
      strip2.setPixelColor(7, strip1.Color(255, 255, 0));
      strip2.setPixelColor(6, strip1.Color(255, 255, 0));
      strip2.setPixelColor(5, strip1.Color(255, 64, 0));
      strip2.setPixelColor(4, strip1.Color(255, 64, 0));
      strip2.setPixelColor(3, strip1.Color(255, 64, 0));
      strip2.setPixelColor(2, strip1.Color(255, 0, 0));
      strip2.setPixelColor(1, strip1.Color(255, 0, 0));
      strip2.setPixelColor(0, strip1.Color(255, 0, 0));
    }
  }else{
    moveTime = moveTime;
    if (moveTime > 5000){
      strip2.setPixelColor(14, strip1.Color(0, 0, 0));
      strip2.setPixelColor(13, strip1.Color(0, 0, 0));
      strip2.setPixelColor(12, strip1.Color(0, 0, 0));
      strip2.setPixelColor(11, strip1.Color(0, 0, 0));
      strip2.setPixelColor(10, strip1.Color(0, 0, 0));
      strip2.setPixelColor(9, strip1.Color(0, 0, 0));
      strip2.setPixelColor(8, strip1.Color(0, 0, 0));
      strip2.setPixelColor(7, strip1.Color(0, 0, 0));
      strip2.setPixelColor(6, strip1.Color(0, 0, 0));
      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
    }else if (moveTime > 4000){
      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
      strip2.setPixelColor(11, strip1.Color(0, 0, 0));
      strip2.setPixelColor(10, strip1.Color(0, 0, 0));
      strip2.setPixelColor(9, strip1.Color(0, 0, 0));
      strip2.setPixelColor(8, strip1.Color(0, 0, 0));
      strip2.setPixelColor(7, strip1.Color(0, 0, 0));
      strip2.setPixelColor(6, strip1.Color(0, 0, 0));
      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
    }else if (moveTime > 3000){
      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
      strip2.setPixelColor(11, strip1.Color(128, 255, 0));
      strip2.setPixelColor(10, strip1.Color(128, 255, 0));
      strip2.setPixelColor(9, strip1.Color(128, 255, 0));
      strip2.setPixelColor(8, strip1.Color(0, 0, 0));
      strip2.setPixelColor(7, strip1.Color(0, 0, 0));
      strip2.setPixelColor(6, strip1.Color(0, 0, 0));
      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
    }else if (moveTime > 2000){
      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
      strip2.setPixelColor(11, strip1.Color(128, 255, 0));
      strip2.setPixelColor(10, strip1.Color(128, 255, 0));
      strip2.setPixelColor(9, strip1.Color(128, 255, 0));
      strip2.setPixelColor(8, strip1.Color(255, 255, 0));
      strip2.setPixelColor(7, strip1.Color(255, 255, 0));
      strip2.setPixelColor(6, strip1.Color(255, 255, 0));
      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
    }else if (moveTime > 1000){
      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
      strip2.setPixelColor(11, strip1.Color(128, 255, 0));
      strip2.setPixelColor(10, strip1.Color(128, 255, 0));
      strip2.setPixelColor(9, strip1.Color(128, 255, 0));
      strip2.setPixelColor(8, strip1.Color(255, 255, 0));
      strip2.setPixelColor(7, strip1.Color(255, 255, 0));
      strip2.setPixelColor(6, strip1.Color(255, 255, 0));
      strip2.setPixelColor(5, strip1.Color(255, 64, 0));
      strip2.setPixelColor(4, strip1.Color(255, 64, 0));
      strip2.setPixelColor(3, strip1.Color(255, 64, 0));
      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
    }else{
      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
      strip2.setPixelColor(11, strip1.Color(128, 255, 0));
      strip2.setPixelColor(10, strip1.Color(128, 255, 0));
      strip2.setPixelColor(9, strip1.Color(128, 255, 0));
      strip2.setPixelColor(8, strip1.Color(255, 255, 0));
      strip2.setPixelColor(7, strip1.Color(255, 255, 0));
      strip2.setPixelColor(6, strip1.Color(255, 255, 0));
      strip2.setPixelColor(5, strip1.Color(255, 64, 0));
      strip2.setPixelColor(4, strip1.Color(255, 64, 0));
      strip2.setPixelColor(3, strip1.Color(255, 64, 0));
      strip2.setPixelColor(2, strip1.Color(255, 0, 0));
      strip2.setPixelColor(1, strip1.Color(255, 0, 0));
      strip2.setPixelColor(0, strip1.Color(255, 0, 0));
    }
  }
  strip2.show();
}
