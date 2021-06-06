#include <IRremote.h> //including infrared remote header file
#include <Adafruit_NeoPixel.h>

int RECV_PIN = 2; // the pin where you connect the output pin of IR sensor
IRrecv irrecv(RECV_PIN);
decode_results results;

#define ledPin4 3
#define ledCount4 14 //turning
Adafruit_NeoPixel strip4 (ledCount4, ledPin4, NEO_GRB + NEO_KHZ800);

#define ledPin2 4
#define ledCount2 6  //front
Adafruit_NeoPixel strip2 (ledCount2, ledPin2, NEO_GRB + NEO_KHZ800);

#define ledPin3 5
#define ledCount3 29  //heartbeat
Adafruit_NeoPixel strip3 (ledCount3, ledPin3, NEO_GRB + NEO_KHZ800);

#define ledPin1 6
#define ledCount1 15  //calorie
Adafruit_NeoPixel strip1 (ledCount1, ledPin1, NEO_GRB + NEO_KHZ800);



void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  
  strip1.begin();           
  strip1.show();           
  strip1.setBrightness(50); 

  strip2.begin();           
  strip2.show();           
  strip2.setBrightness(50); 

  strip3.begin();           
  strip3.show();           
  strip3.setBrightness(50); 

  strip4.begin();           
  strip4.show();           
  strip4.setBrightness(50); 

}

void loop() {
  if (irrecv.decode(&results)){
    int readResults = results.value;
    Serial.println(" ");
    Serial.print("Code: ");
    Serial.println(results.value); 
    Serial.println(" ");

    //pin1
    if(results.value == 16582903){
      for (int i = 0; i < 2; i++) { 
         strip4.fill(strip4.Color(255,215,0), 0, 7);
         strip4.show();
         delay(300);
         
         strip4.fill(strip4.Color(0,0,0),0, 7);
         strip4.show();
         delay(300);
      }
     }

    //pin off
//    if(results.value == 16580863){
//        strip1.fill(strip1.Color(0,0,0), 7, ledCount1);
//        strip1.show();
//      }

    //pin2
     if(results.value == 16615543){
        for (int i = 0; i < 2; i++) { 
         strip4.fill(strip4.Color(255,215,0), 7, ledCount4);
         strip4.show();
         delay(300);
         
         strip4.fill(strip4.Color(0,0,0),7, ledCount4);
         strip4.show();
         delay(300);
      }
      }

     //pin3
     if(results.value == 16599223){
        theaterChase(strip2.Color(255,0,0), 500);
        strip2.show();

        theaterChase(strip3.Color(255,0,0), 500);
        strip3.show();
      }
    irrecv.resume(); 
    
   }

}

void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip2.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip2.numPixels(); c += 3) {
        strip2.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip2.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

//void CalorieStrip(){
//  strip2.clear();
//  strip2.setPixelColor(14, strip1.Color(0, 255, 0));
//  strip2.setPixelColor(13, strip1.Color(0, 255, 0));
//  strip2.setPixelColor(12, strip1.Color(0, 255, 0));
//  strip2.setPixelColor(11, strip1.Color(128, 255, 0));
//  strip2.setPixelColor(10, strip1.Color(128, 255, 0));
//  strip2.setPixelColor(9, strip1.Color(128, 255, 0));
//  strip2.setPixelColor(8, strip1.Color(255, 255, 0));
//  strip2.setPixelColor(7, strip1.Color(255, 255, 0));
//  strip2.setPixelColor(6, strip1.Color(255, 255, 0));
//  strip2.setPixelColor(5, strip1.Color(255, 64, 0));
//  strip2.setPixelColor(4, strip1.Color(255, 64, 0));
//  strip2.setPixelColor(3, strip1.Color(255, 64, 0));
//  strip2.setPixelColor(2, strip1.Color(255, 0, 0));
//  strip2.setPixelColor(1, strip1.Color(255, 0, 0));
//  strip2.setPixelColor(0, strip1.Color(255, 0, 0));
//
//  if (abs(v) > 5){  //改变if中的值来使卡路里灯在合适的速度下才开始消失
//    moveTime = moveTime + 1;
//    if (moveTime > 50000){
//      moveTime = 50001;
//      strip2.setPixelColor(14, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(13, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(12, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(11, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(10, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(9, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(8, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(7, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(6, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
//    }else if (moveTime > 40000){
//      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(11, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(10, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(9, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(8, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(7, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(6, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
//    }else if (moveTime > 30000){
//      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(11, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(10, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(9, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(8, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(7, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(6, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
//    }else if (moveTime > 20000){
//      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(11, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(10, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(9, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(8, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(7, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(6, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
//    }else if (moveTime > 10000){
//      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(11, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(10, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(9, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(8, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(7, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(6, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(5, strip1.Color(255, 64, 0));
//      strip2.setPixelColor(4, strip1.Color(255, 64, 0));
//      strip2.setPixelColor(3, strip1.Color(255, 64, 0));
//      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
//    }else{
//      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(11, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(10, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(9, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(8, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(7, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(6, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(5, strip1.Color(255, 64, 0));
//      strip2.setPixelColor(4, strip1.Color(255, 64, 0));
//      strip2.setPixelColor(3, strip1.Color(255, 64, 0));
//      strip2.setPixelColor(2, strip1.Color(255, 0, 0));
//      strip2.setPixelColor(1, strip1.Color(255, 0, 0));
//      strip2.setPixelColor(0, strip1.Color(255, 0, 0));
//    }
//  }else{
//    moveTime = moveTime;
//    if (moveTime > 50000){
//      strip2.setPixelColor(14, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(13, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(12, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(11, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(10, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(9, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(8, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(7, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(6, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
//    }else if (moveTime > 40000){
//      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(11, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(10, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(9, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(8, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(7, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(6, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
//    }else if (moveTime > 30000){
//      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(11, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(10, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(9, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(8, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(7, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(6, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
//    }else if (moveTime > 20000){
//      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(11, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(10, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(9, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(8, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(7, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(6, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
//    }else if (moveTime > 10000){
//      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(11, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(10, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(9, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(8, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(7, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(6, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(5, strip1.Color(255, 64, 0));
//      strip2.setPixelColor(4, strip1.Color(255, 64, 0));
//      strip2.setPixelColor(3, strip1.Color(255, 64, 0));
//      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
//      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
//    }else{
//      strip2.setPixelColor(14, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(13, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(12, strip1.Color(0, 255, 0));
//      strip2.setPixelColor(11, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(10, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(9, strip1.Color(128, 255, 0));
//      strip2.setPixelColor(8, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(7, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(6, strip1.Color(255, 255, 0));
//      strip2.setPixelColor(5, strip1.Color(255, 64, 0));
//      strip2.setPixelColor(4, strip1.Color(255, 64, 0));
//      strip2.setPixelColor(3, strip1.Color(255, 64, 0));
//      strip2.setPixelColor(2, strip1.Color(255, 0, 0));
//      strip2.setPixelColor(1, strip1.Color(255, 0, 0));
//      strip2.setPixelColor(0, strip1.Color(255, 0, 0));
//    }
//  }
//  strip2.show();
//}
