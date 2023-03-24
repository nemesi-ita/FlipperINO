#include <flipperpiGUI.h>

void setup(){
  lcd.init(); // initialize the lcd
  lcd.backlight();
}

void loop(){
  setGui("a");
}
