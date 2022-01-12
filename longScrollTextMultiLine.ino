/* https://stackoverflow.com/questions/40564050/scroll-long-text-on-oled-display */

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



   char message[]="297M LstWyPt, 345M StPt, rec#89";
   int x, minX;

  void setup(){
  Serial.begin(11200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setTextWrap(false);
  x = display.width();
  minX = -12 * strlen(message);  // 12 = 6 pixels/character * text size 2
  }

  void loop(){
       
   display.clearDisplay();
   display.setCursor(0,0);
   display.setTextSize(1);
   display.print("Sat:13  03:56:32  67%");// GPS # Satellites, Time, % Batt chg
   display.setTextSize(2);
   display.setCursor(x,10);
   display.print(message);
   display.setCursor(x,28);
   display.setTextSize(1);
   display.print("Press #1 New StPt, 2 RecWayPt, Cur 32.567, -102.456");
   display.setCursor(x,38);
   display.setTextSize(1);
   display.print("Press #1 New StPt, 2 RecWayPt, Cur 32.567, -102.456");
   display.setCursor(x,48);
   display.setTextSize(1);
   display.print("Press #1 New StPt, 2 RecWayPt, Cur 32.567, -102.456");
   display.display();
   x=x-8; // scroll speed, make more positive to slow down the scroll
   if(x < minX) x= display.width();
}
