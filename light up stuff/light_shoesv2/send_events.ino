void toe_hit(){
    //send_ball( 0, 29, 59, 30, 6); // in pulse on full strip
    send_ball( 0, 21, 42, 22, 10); // in pulse on shoe
    
    //strip.setPixelColor(30,strip.Color(0, 0, 0));
    //strip.setPixelColor(29,strip.Color(0, 0, 0));
    strip.setPixelColor(22,strip.Color(0, 0, 0));
    strip.setPixelColor(21,strip.Color(0, 0, 0));
    strip.show();
    
    //Serial.print("toe hit | ");
    digitalWrite(ledPin, HIGH);
    armed = true;
    rearm();
}

void heel_hit(){
    //send_ball( 30, 60, 29, 0, 6); // out pulse on full strip
    send_ball( 22, 42, 21, 0, 6); // out pulse on shoe
    
    strip.setPixelColor(42,strip.Color(0, 0, 0));
    strip.setPixelColor(0,strip.Color(0, 0, 0));
    strip.show();
    
    //Serial.print("heel hit | ");
    digitalWrite(ledPin, HIGH);
    armed = true;
    rearm();
}

void back_and_forth(){
    //send_ball( 30, 60, 29, 0, 30); // out pulse
    send_ball( 22, 42, 21, 0, 6); // out pulse on shoe
    
    //Serial.print("heel hit | ");
    digitalWrite(ledPin, HIGH);
    
//    send_ball( 0, 29, 59, 30, 30); // in pulse
    send_ball( 0, 21, 42, 22, 6); // in pulse on shoe
    
    //Serial.print("toe hit | ");
    digitalWrite(ledPin, LOW);   
}
