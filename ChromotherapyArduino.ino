#include <SoftwareSerial.h>

//Variables
const byte rxPin = 11;
const byte txPin = 10;
const int GREEN_pin = 9;  
const int BLUE_pin = 13;  
const int RED_pin = 12;  
String RGBColor = ""; 
String RGBColor_previous = "255.255.255"; // inicializacion a blanco
boolean RGBRead_Completed = false;
long bps = 9600; //bytes por seg

SoftwareSerial myConnect(txPin, rxPin); // RX, TX recordar que se cruzan

void setup()
{
  pinMode(GREEN_pin, OUTPUT);  
  pinMode(BLUE_pin, OUTPUT);  
  pinMode(RED_pin, OUTPUT);  
  
  Serial.begin(bps);
  myConnect.begin(bps);  
}

void loop()
{
    while(myConnect.available())
    {
      char ReadChar = (char)myConnect.read();
   
      if(ReadChar == ')')
      {
        RGBRead_Completed = true;
      }
      else
      {
         RGBColor += ReadChar;
      }
    }

    if(RGBRead_Completed)
    {
      if(RGBColor == "ON")
      {
          RGBColor = RGBColor_previous; 
          Control_RGB_StripLed();
      }
      else if(RGBColor == "OFF")
      {
          RGBColor = "0.0.0"; 
          Control_RGB_StripLed();
      }
      else
      {
          Control_RGB_StripLed();   
          RGBColor_previous = RGBColor;     
      }
      
      RGBColor = "";
      RGBRead_Completed = false;    
    }
}

void Control_RGB_StripLed() {
    // get finish position of colors
    int position1RGBColor = RGBColor.indexOf(' ');
    int position2RGBColor = RGBColor.indexOf(' ', position1RGBColor + 1);
    int position3RGBColor = RGBColor.indexOf(' ', position2RGBColor + 1);

    // get colors from string RGBColor with previous positions
    String RedColor = RGBColor.substring(0, position1RGBColor);
    String GreenColor = RGBColor.substring(position1RGBColor + 1, position2RGBColor);
    String BlueColor = RGBColor.substring(position2RGBColor + 1, position3RGBColor);

    //Pass string colors to int and get color variety between 0 - 255
    digitalWrite(GREEN_pin, (GreenColor.toInt()));// you can use de analogWrite if you use this arduino's conections
    digitalWrite(BLUE_pin, (BlueColor.toInt()));
    digitalWrite(RED_pin, (RedColor.toInt()));

    // If you need to invert colors, you could change GreenColor.toInt() by (255 - GreenColor.toInt())
}
