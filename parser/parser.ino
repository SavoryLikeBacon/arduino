/*
  Serial Event example
 
 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and 
 clears it.
 
 A good test for this is to try it with a GPS receiver 
 that sends out NMEA 0183 sentences. 
 
 Created 9 May 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/SerialEvent
 
 */
String command = "";
String inputString = "";         // a string to hold incoming data
String parsed_command="";
String parameter = "";
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
 
}

void loop() {
  // print the string when a newline arrives:
  //delay(2000);
  if (stringComplete) {
    //Serial.println(inputString); 
    //Serial.println(inputString.substring(0,inputString.indexOf('=')));
    
    Serial.println("-"+inputString);
    parsed_command = inputString.substring(0,inputString.indexOf('=')); // get what is before equals sign
    parameter = inputString.substring(inputString.indexOf('=')+1); // get what is after = sign
   // Serial.println("parameter => " + parameter);
    //Serial.println( String(parsed_command.length()) );
    if (inputString.length() == parsed_command.length()) // check if the command has a parameter
      parsed_command = parsed_command.substring(0, parsed_command.length() - 1);
    
    if (parsed_command.substring( parsed_command.length() - 1 ) == " ")//chop off space is there is one after the command
       parsed_command = parsed_command.substring(0, parsed_command.length() - 1);
    
    //Serial.println( String(parsed_command.length()) );
     
    
    
    //Serial.println( parsed_command );
    //Serial.println( String(parsed_command.length()) );
    int temp=0;
    
    if(parsed_command == "volt"){temp = 1;}
    if(parsed_command == "current"){temp = 2;}
    if(parsed_command == "help"){temp = 3;}
    
    
    char floatbuf[32]; // make this at least big enough for the whole string
    parameter.toCharArray(floatbuf, sizeof(floatbuf));
    float parameter_num = atof(floatbuf);
    
    //float parameter_num = atof(parameter);
    //Serial.println(parameter_num,3);
    switch( temp ){
     
     case 1:
      Serial.print("Voltage set to ");
      Serial.println(parameter_num,3);
      Serial.println("V");
      break;
      
     case 2:
     Serial.print("Current set to ");
      Serial.print(parameter_num,3);
      Serial.println("A");
      break; 
      
     case 3:
      Serial.println("This is the help command");
      Serial.println("Below is the command table:");
      Serial.println("volt=## to set voltage");
      Serial.println("volt=? to query voltage");
      Serial.println("current=## to set current");
      Serial.println("current= to query current");
      break; 
      
     default:
      Serial.println("ERROR");
      break;
      
    }
    
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    
    if ((inChar == '\r') && (inputString.length() != 1)){
        stringComplete = true;
    }
    if ((inChar == '\r') && (inputString.length() == 1)){
        stringComplete = false;
        Serial.println("-");//print cariage return
        inputString = "";
    }    
    
  }  
  
  
  
}


