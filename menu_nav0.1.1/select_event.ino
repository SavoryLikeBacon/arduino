
void select_event(){
  
  if(numeric_flag){  
    lcd.setCursor ( 13, 1 );
    lcd.print("   ");
    numeric_flag = false;
  }else{
  
  
 
    if(yes_no_flag){   
      
      if(current_yesno){
      
        if (submenu2_flag){
          if (submain2_menu_state == st_save){
             save_current();
             submenu2_flag = false;
             menu_flag = true;
             main_menu_state = 1;
          }
          if (submain2_menu_state == st_restore){
             save_defaults();
             submenu2_flag = false;
             menu_flag = true;
             main_menu_state = 1;
          }
            
        }  
      }    
      
      //Serial.println("in yes/no event");
      lcd.setCursor ( 11, 1 );
      lcd.print("     ");
      yes_no_flag = false;
    
    }else{  
      if (menu_flag){
    //    #define st_intensity 1
    //    #define st_color 2
    //    #define st_program 3
    	//Serial.println("Handling main menu click");
         switch (main_menu_state){
           case st_intensity:
    //       menu_flag =  false;
             numeric_flag = true; // turn on numeric display for user to select
             rotary_counter = current_intensity;
      	 break;
           case st_color:
             menu_flag =  false;
             submenu1_flag = true;
             submain1_menu_state=1;
    	 break;	
           case st_program:
             menu_flag =  false;
             submenu2_flag = true;   
             submain2_menu_state=1; 
    	 break;
           
           default:   
             delay(1);    
          }      
        }else{
      
          if (submenu1_flag){  
    //    #define st_color_red 1
    //    #define st_color_green 2
    //    #define st_color_blue 3
    //    #define st_color_back 4
          // set current color
         // Serial.println("Handling submenu 1 menu click");
          switch (submain1_menu_state){
            case st_color_red:
               numeric_flag = true; // turn on numeric display for user to select
               rotary_counter = current_red;
               break;
            case st_color_green:
               numeric_flag = true; // turn on numeric display for user to select
               rotary_counter = current_green;
    	   break;	
            case st_color_blue:
               numeric_flag = true; // turn on numeric display for user to select
               rotary_counter = current_blue;
    	   break;
            case st_color_back:
               menu_flag =  true;
               submenu1_flag = false;
               main_menu_state = st_color;
               break;          
            default:   
               delay(1);    
           }    
        
        }else{
      
          if (submenu2_flag){             
            
    //        #define st_dflt_intensity 1
    //        #define st_dflt_color 2
    //        #define st_save 3
    //        #define st_restore 4
    //        #define st_program_back 5
            
            // set default current color
            //submenu2 is a child of submenu3
            //Serial.println("Handling submenu 2 menu click");
            switch (submain2_menu_state){
              case st_dflt_intensity:
                 numeric_flag = true; // turn on numeric display for user to select
                 break;
              case st_dflt_color:
                 //numeric_flag = true; // turn on numeric display for user to select
                 submenu2_flag = false;
                 submenu3_flag = true;
                 submain3_menu_state=1;
    	         break;	
              case st_save:
                 yes_no_flag = true;
    	         break;
              case st_restore:
                 yes_no_flag = true;
    	         break;
              case st_program_back:
               //  Serial.print("submenu2 back:  ");
               //  Serial.print(submain2_menu_state);
                 menu_flag =  true;
                 submenu2_flag = false;
                 submain2_menu_state = st_program;          
                 break;          
              default:   
              //   Serial.print("submenu2 back in delay   :");
              //   Serial.print(submain2_menu_state);
     
                 delay(1);    
            } 
    
    
           }else{
        
            if (submenu3_flag){
    
            //#define st_dflt_red 1
            //#define st_dflt_green 2
            //#define st_dflt_blue 3
            //#define st_dflt_back 4
              
               // Serial.println("Handling submenu 3 menu click");
                switch (submain3_menu_state){
                  case st_dflt_red:
                      numeric_flag = true; // turn on numeric display for user to select
                      break;
                  case st_dflt_green:
                      numeric_flag = true; // turn on numeric display for user to select
                      break;	
                  case st_dflt_blue:
                      numeric_flag = true; // turn on numeric display for user to select
                      break;
                  case st_dflt_back:
                      submenu2_flag =  true;
                      submenu3_flag = false;
                      main_menu_state = st_dflt_color;
                      break;          
                  default:   
                      delay(1);    
                }
    	
            }
          
          }
     
        }
      
      }
    }
  }
 
  //Serial.print("select  ");
  //Serial.println(millis());
//  button_service_waiting = false;
}

