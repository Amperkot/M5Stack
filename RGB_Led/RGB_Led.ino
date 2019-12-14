#include <M5Stack.h>

#define G 22
#define R 23
#define B 21

uint8_t flag = 0;

void setup() {

  M5.begin(true, false, true);
  M5.Lcd.clear(BLACK);
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);
  off_led();
}

void loop() {
 M5.update();
  if (M5.BtnA.wasReleased()) {
    off_led();
    enable_led(R);
    M5.Lcd.clear(RED);
  } 
  else if (M5.BtnB.wasReleased()) {
    off_led();
    enable_led(G);
    M5.Lcd.clear(GREEN);
  } 
  else if (M5.BtnC.wasReleased()) {
    off_led();
   enable_led(B);
   M5.Lcd.clear(BLUE);
  }
  else if (M5.BtnC.wasReleasefor(300))
  {
    flag = 0;
    while (flag < 10) {rainbow() ;flag+=1;}
  }

}

void rainbow()
{
  enable_led(R);
  delay(1000);
  enable_led(G);
  delay(1000);
  enable_led(B);
  delay(1000);
  off_led();
  enable_led(G);
  enable_led(B);
  delay(1000);
  off_led();
  enable_led(G);
  enable_led(R);
  delay(1000);
}

void off_led()
{
  digitalWrite(R,LOW);
  digitalWrite(G,LOW);
  digitalWrite(B,LOW);
}

void enable_led(uint8_t pin)
{
  digitalWrite(pin,HIGH);
}
