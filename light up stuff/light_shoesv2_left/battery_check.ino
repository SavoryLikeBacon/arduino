void battery_check(){
   //Serial.println("in batterycheck");
   int bat_level=750;
   int no_battery_connected = 400;
   int current_level = analogRead(battery_pin);
   Serial.print("current battery = ");
   Serial.println(current_level);
   if(current_level > no_battery_connected){
     if( current_level < bat_level ){
        colorWipe(0, 0);  // clear strip
        while(1){
           for(int i=0; i<5; i++){
              digitalWrite(ledPin, HIGH);
              strip.setPixelColor(0,strip.Color(10, 0, 0));
              strip.show();
              delay(500);
              digitalWrite(ledPin, LOW);
              strip.setPixelColor(0,strip.Color(0, 0, 0));
              strip.show();
              delay(500);
           }
           
           set_sleep_mode(SLEEP_MODE_PWR_DOWN);
           sleep_enable();
           sleep_cpu();
           sleep_mode();            // here the device is actually put to sleep!!
          
        }  
     }
    }else{
       Serial.print("Battery Bypass\t");
       Serial.println(current_level);
   }
}
