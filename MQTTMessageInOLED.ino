  #include <Adafruit_GFX.h>
   #include <Adafruit_SSD1306.h>

#include "EspMQTTClient.h"



EspMQTTClient client(
  "<wifi SSID(name)>",
  "<wifi password>",
  "<mqtt server URL>",  // MQTT Broker server ip - get a free account at https://www.emqx.com/en/cloud
  "testuser",   // Can be omitted if not needed
  "testpassword",   // Can be omitted if not needed
  "TestClient",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);
   

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



   char message[]="Initial Message";
   char submessage1[] = "Sub message 1";
   char submessage2[] = "Sub message 2";
   int x, minX;

  void setup(){
  Serial.begin(115200);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setTextWrap(false);
  x = display.width();
  minX = -12 * strlen(message);  // 12 = 6 pixels/character * text size 2
  }

  
// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{

  // Subscribe to "wildcardtest/#" and display received message to Serial
  client.subscribe("wildcardtest/#", [](const String & topic, const String & payload) {
    Serial.println("(From wildcard) topic: " + topic + ", payload: " + payload);
    payload.toCharArray(message, 50);
  });

    // Subscribe to "wildcardtest/#" and display received message to Serial
  client.subscribe("submessage1", [](const String & topic, const String & payload) {
    Serial.println("(From submessage1) topic: " + topic + ", payload: " + payload);
    payload.toCharArray(submessage1, 50);
  });

    // Subscribe to "wildcardtest/#" and display received message to Serial
  client.subscribe("submessage2", [](const String & topic, const String & payload) {
    Serial.println("(From submessage2) topic: " + topic + ", payload: " + payload);
    payload.toCharArray(submessage2, 50);
  });

}




  void loop(){
       
    client.loop();

    char str[80];

    
   display.clearDisplay();
   display.setCursor(0,0);
   display.setTextSize(1);
   display.print("Sat:13  03:56:32  67%");// Sample header text
   display.setTextSize(2);
   display.setCursor(x,10);  // Bold text as recieved from MQTT server
   display.print(message);
   display.setCursor(x,28);
   display.setTextSize(1);
   display.print("");
   display.setCursor(x,38);
   display.setTextSize(1);
      strcpy(str,"");
    strcat(str, "Message line1:");
    strcat(str,submessage1);
   display.print(str);
   display.setCursor(x,48);
   display.setTextSize(1);
    strcpy(str,"");
    strcat(str, "Message line2:");
    strcat(str,submessage2);
   display.print(str);
   display.display();
   x=x-2; // scroll speed, make more positive to slow down the scroll
   if(x < minX) x= display.width();
}



