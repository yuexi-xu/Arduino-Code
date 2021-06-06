#include <IRremote.h> //including infrared remote header file
#include <Adafruit_NeoPixel.h>
int RECV_PIN = 2; // the pin where you connect the output pin of IR sensor
IRrecv irrecv(RECV_PIN);
decode_results results;

#define ledPin 6
#define ledCount 24
Adafruit_NeoPixel strip (ledCount, ledPin, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  
  strip.begin();
  strip.show();
  strip.setBrightness(255);
}
void loop() {

  if (irrecv.decode(&results)){
    int readResults = results.value;
    Serial.println(" ");
    Serial.print("Code: ");
    Serial.println(results.value); 
    Serial.println(" ");

    //pin7
    if(results.value == 16586983){
      
      theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness
//        strip.fill(strip.Color(0,255,0), 0, ledCount); 
//        delay(2000);
        strip.show();
          }

    //pin off
    if(results.value == 16580863){
        strip.fill(strip.Color(0,0,0), 0, ledCount);
        strip.show();
      }

    //pin8
     if(results.value == 16619623){
        theaterChase(strip.Color(222,184,135), 50); // Red, half brightness
        strip.show();
      }

     //pin9
     if(results.value == 16603303){
        theaterChaseRainbow(50);
        strip.show();
      }


//    switch(results.value){
//        case 0xFF18E7: //Keypad button "2"
//        digitalWrite(greenPin, HIGH);
//        delay(2000);
//        digitalWrite(greenPin, LOW);
//          }
    irrecv.resume(); 
    
   }

   
  
}

void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}

void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}
