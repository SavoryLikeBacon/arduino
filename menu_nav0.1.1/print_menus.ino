void print_submenu1(){
 //this function prints the top part of each menu  
  String temp_buffer;
  //submain_menu_state %= 3;
  switch (submain1_menu_state){
      case st_color_red:
	temp_buffer="  Red        ";
	break;
	
      case st_color_green:
	temp_buffer="  Green      ";
	break;
	
      case st_color_blue:
	temp_buffer="  Blue       ";
	break;

      case st_color_back:
	temp_buffer="  back       ";
	break;

      default:
        temp_buffer="Dflt SubMenu1   "; 
  }
    lcd.setCursor ( 0, 0 );
    lcd.print("Color           ");
    lcd.setCursor ( 0, 1 );
    lcd.print(temp_buffer);
    //Serial.println(temp_buffer);
}

void print_submenu2(){
 //this function prints the top part of each menu  
  String temp_buffer;
  //submain_menu_state %= 3;
  switch (submain2_menu_state){
      case st_dflt_intensity:
	temp_buffer="  Intensity  ";
	break;
	
      case st_dflt_color:
	temp_buffer="  Color      ";
	break;

      case st_save:
	temp_buffer="  Save       ";
	break;
	
      case st_restore:
	temp_buffer="  Restore    ";
	break;
      
      case st_program_back:
	temp_buffer="  back       ";
	break;

      default:
         temp_buffer="Dflt SubMenu2  "; 
  }
    lcd.setCursor ( 0, 0 );
    lcd.print("Program         ");
    lcd.setCursor ( 0, 1 );
    lcd.print(temp_buffer);
    //Serial.println(temp_buffer);
}

void print_submenu3(){
 //this function prints the top part of each menu  
  String temp_buffer;
  //submain_menu_state %= 3;
  switch (submain3_menu_state){
      case st_dflt_red:
	temp_buffer="  Red     ";
	break;
	
      case st_dflt_green:
	temp_buffer="  Green   ";
	break;
	
      case st_dflt_blue:
	temp_buffer="  Blue    ";
	break;
	     
      case st_dflt_back:
	temp_buffer="  back    ";
	break;
	
      default:
         temp_buffer="Dflt SubMenu3"; 
  }
    lcd.setCursor ( 0, 0 );
    lcd.print("Default Color   ");
    lcd.setCursor ( 0, 1 );
    lcd.print(temp_buffer);
    //Serial.println(temp_buffer);
}

void print_top_menu(){
 //this function prints the top part of each menu  
  String temp_buffer;
  switch (main_menu_state){
//      case st_main:
//        temp_buffer="Main Menu       ";
//        break;
      
      case st_intensity:
     	temp_buffer="  Intensity  ";
	break;
	
      case st_color:
	temp_buffer="  Color      ";
	break;
	
      case st_program:
	temp_buffer="  Program    ";
	break;
	
      default:
         temp_buffer="Default Menu"; 
  }
    lcd.setCursor ( 0, 0 );
    lcd.print("Main Menu       ");
    lcd.setCursor ( 0, 1 );
    lcd.print(temp_buffer);
    //Serial.println(temp_buffer);
}
