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
