#include <M5Stack.h>

void setup(void) {
  M5.begin();
  M5.Lcd.setBrightness(200);
  M5.Lcd.setTextSize(5);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.printf("HELLO\nAMPERKOT!");
 M5.Lcd.drawJpgFile(SD, "/ak.jpg",0,80); 
}

void loop() {
}
