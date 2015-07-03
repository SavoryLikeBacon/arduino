void button_check(){
  if (digitalRead(encoder_switch_pin) == HIGH){
    //Serial.println("before select_event function");
    select_event(); 
    
    while(digitalRead(encoder_switch_pin) == HIGH){
        delay(1);
    }
    
  }
}



void write_number(){
  lcd.setCursor ( 13, 1 );
  if ((rotary_counter >= 0) && (rotary_counter <= 9)){
    lcd.print("  ");
    lcd.print(rotary_counter);
  }
  if ((rotary_counter >= 10) && (rotary_counter <= 99)){
    lcd.print(" ");
    lcd.print(rotary_counter);
  }
  if (rotary_counter >= 100){
    lcd.print(rotary_counter);
  }
  
  //Serial.println(rotary_counter); 
}

void handle_encoder(){
    
    if (position_delta > 0)
      up_event();
    if (position_delta < 0)      
      down_event();
    
    if (rotary_counter > 255)
      rotary_counter= 255;
    if (rotary_counter < 0)
      rotary_counter= 0;
        
      
    //read select and back switch
//    if (inChar == 's')
//      select_event();
//    if (inChar ==  'b')        
//      back_event();
}

void get_position(){
  newPosition = (int )(myEnc.read()/4);


    position_delta =  (newPosition - oldPosition);
    rotary_counter += position_delta;
    if (position_delta > 0)
      up_event();
    if (position_delta < 0)
      down_event();
    position_delta=0;
    oldPosition = newPosition;
 
  
//  Serial.print("new: ");
//  Serial.print(newPosition);
//  Serial.print("      old: ");
//  Serial.print(oldPosition);
//  Serial.print("      delta: ");
//  Serial.print(position_delta);
  //Serial.print("      counter: ");
  //Serial.println(rotary_counter);
}


void lcd_yesno_update(){
//this function show the yes or no options when the user is going to select a boolean selector
  lcd.setCursor ( 7 , 1 );
  lcd.print("Save? ");
  if (oldPosition & 1){
    lcd.print("Yes");
    current_yesno = true;
    Serial.println("Yes");
  }else{
    lcd.print(" No");
    current_yesno = false;
    Serial.println(" No");
  }
}


