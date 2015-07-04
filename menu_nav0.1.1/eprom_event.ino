
// this function will load the 4 bytes from memory. This runs on bootup and after restoring default values
void load_from_memory(){
////~~~~~~~~~~~~~~~~~~~~~~~~~`
////EEPROM address and default settings
//#define intensity_memory 0
//#define red_memory 1
//#define green_memory 2
//#define blue_memory 3
//
//#define default_intensity 100
//#define default_red 100
//#define default_green 100
//#define default_blue 100
//
//// varibales to hold the values of the RGB and intensity
////The initial restore function will load these with default values
//int current_red = 0;
//int current_blue = 0;
//int current_green = 0;
//int current_intensity = 0;
//
////~~~~~~~~~~~~~~~~~~~~~~~~~
  
  current_intensity = EEPROM.read(intensity_memory);
  current_red = EEPROM.read(red_memory);
  current_green = EEPROM.read(green_memory);
  current_blue = EEPROM.read(blue_memory); 
  
}


void save_defaults(){
  Serial.print("Restoring defaults....");
  EEPROM.write(intensity_memory, default_intensity);
  //Serial.print("....");
  EEPROM.write(red_memory, default_red);
  //Serial.print("....");
  EEPROM.write(green_memory, default_green);
  //Serial.print("....");
  EEPROM.write(blue_memory, default_blue);
  Serial.println("Complete");
  load_from_memory();
  
}

void save_current(){
  Serial.print("Saving current....");
  EEPROM.write(intensity_memory, current_intensity);
  //Serial.print("....");
  EEPROM.write(red_memory, current_red);
  //Serial.print("....");
  EEPROM.write(green_memory, current_green);
  //Serial.print("....");
  EEPROM.write(blue_memory, current_blue);
  Serial.println("Complete");
  
}


void print_loaded_memory(){
    
  Serial.print(current_intensity);
  Serial.print("\t");
  Serial.print(current_red);
  Serial.print("\t");
  Serial.print(current_green);
  Serial.print("\t");
  Serial.println(current_blue); 
}
