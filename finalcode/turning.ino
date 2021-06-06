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
