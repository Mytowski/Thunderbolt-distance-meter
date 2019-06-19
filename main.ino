#include <LiquidCrystal.h>

//CONFIG 

const static int PIN_LIGHT_SENSOR = 18; // interrupt pin
const static int PIN_SOUND_SENSOR = 19; // interrupt pin
const static int PIN_BUTTON       = 20;

//

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); 

//PROGRAM

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Thunderb. meter");
  lcd.setCursor(0, 1);
  lcd.print("Press button");
}

void loop() {


}
