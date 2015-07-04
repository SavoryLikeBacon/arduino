void button_check(){
  if (digitalRead(encoder_switch_pin) == HIGH){
    //Serial.println("before select_event function");
    select_event(); 
    
    while(digitalRead(encoder_switch_pin) == HIGH){
        delay(1);
    }
    delay(50);
    
  }
}

//prepare the inputs and outputs
void prep_IO(){
  pinMode(red_led_pin, OUTPUT); // PWM ready
  pinMode(green_led_pin, OUTPUT); // PWM ready
  pinMode(blue_led_pin, OUTPUT); // PWM ready
  //encoder switch inputs are declared in the library
  pinMode(encoder_switch_pin, INPUT); // signal is highgoing to no need to enable pullup
  
  analogWrite(red_led_pin, 255);
  analogWrite(green_led_pin, 255);
  analogWrite(blue_led_pin, 255);
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
  
//current_red
//current_blue
//current_green


  if(menu_flag){
    switch (main_menu_state){
      case st_intensity:
	current_intensity = rotary_counter;
	break;	
      default:
        Serial.println("ERROR:1"); 
    }
    
    
  }




  if(submenu1_flag){
    switch (submain1_menu_state){
      case st_color_red:
	current_red = rotary_counter;
	break;	
      case st_color_green:
	current_green = rotary_counter;
	break;	
      case st_color_blue:
	current_blue = rotary_counter;
	break;
      default:
        Serial.println("ERROR:2"); 
    }
    
    
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
 
}


void lcd_yesno_update(){
//this function show the yes or no options when the user is going to select a boolean selector
  lcd.setCursor ( 10 , 1 );
  lcd.print("?");
  lcd.setCursor ( 13 , 1 );
  if (oldPosition & 1){
    lcd.print("Yes");
    current_yesno = true;
    //Serial.println("Yes");
  }else{
    lcd.print(" No");
    current_yesno = false;
    //Serial.println(" No");
  }
}

void update_button_color(){
  
  analogWrite(red_led_pin, 255-current_red);
  analogWrite(green_led_pin, 255-current_green);
  analogWrite(blue_led_pin, 255-current_blue);
  
}

