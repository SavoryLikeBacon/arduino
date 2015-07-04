void up_event(){

if (!(numeric_flag || yes_no_flag)){
//do not change sub menu when the above flags are set
    if (menu_flag){
      main_menu_state++;
      if (main_menu_state== (main_menu_size+1) )
         main_menu_state = 1;
    }
  
    if (submenu1_flag){
      submain1_menu_state++;
      if (submain1_menu_state== (submenu1_size+1) )
         submain1_menu_state = 1;
    }  
  
    if (submenu2_flag){
      submain2_menu_state++;
      if (submain2_menu_state== (submenu2_size+1) )
         submain2_menu_state = 1;
    } 
 
    if (submenu3_flag){
      submain3_menu_state++;
      if (submain3_menu_state== (submenu3_size+1) )
         submain3_menu_state = 1;
    }  
  }
//  Serial.print("up ");
//  Serial.print(millis());
//  Serial.print("    ");
//  Serial.println(rotary_counter);
}

void down_event(){
//    if (rotary_counter <= 0){
//     rotary_counter = 0;
//  }else{
//     rotary_counter--;
//  }

  
  if (!(numeric_flag || yes_no_flag)){
   //stop changing the sub menu when the y/n flag is set or if the numeric flag is set

  //increment the main menu
    if (menu_flag){
      main_menu_state--;
      if (main_menu_state==0)
         main_menu_state = main_menu_size;
    }  
  
    if (submenu1_flag){
      submain1_menu_state--;
      if (submain1_menu_state==0)
         submain1_menu_state = submenu1_size;
    }  
  
    if (submenu2_flag){
      submain2_menu_state--;
      if (submain2_menu_state==0)
         submain2_menu_state = submenu2_size;
    }  

    if (submenu3_flag){
      submain3_menu_state--;
      if (submain3_menu_state==0)
         submain3_menu_state = submenu3_size;
    }  
  }
    
//  Serial.print("down ");
//  Serial.print(millis());
//  Serial.print("    ");
//  Serial.println(rotary_counter);

}
