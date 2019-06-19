#include <LiquidCrystal.h>

//CONFIG

const static int PIN_LIGHT_SENSOR = 18; // interrupt pin
const static int PIN_SOUND_SENSOR = 19; // interrupt pin
const static int PIN_BUTTON       = 20;

//

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
long int button_millis = 0;
long int timeThunder = 0;
int measure = 0;
//PROGRAM

void buttonHandler() {
  if ((digitalRead(PIN_BUTTON) == 0) && (millis() - button_millis) > 50) {
    button_millis = millis();
    measure = 0;
    displayWaiting();
    while (digitalRead(PIN_BUTTON) == 0) {}
  }
}

void interruptLight() {
  if (measure == 1) {
    timeThunder = millis();
    displayMeasure();
    measure = 2;
  }
  lcd.display();
}

void interruptSound() {
  if (measure == 2) {
    long int timeBolt = millis();
    float distance = (343.3 * (timeBolt - timeThunder)) / 1000;
    measure = 0 ;
    displayResult(distance);
  }
  lcd.display();
}


void displayResult(float distance) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("dist. from tb.");
  lcd.setCursor(0, 1);
  if (distance > 1000) {
    lcd.print(distance / 1000, 3);
    lcd.print(" km.     ");
  }
  else  {
    lcd.print(distance, 0);
    lcd.print(" m.      ");
  }
}

void displayMeasure() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Measuring...  ");
}

void displayWaiting() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("waiting... ");
}

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Thunderb. meter");
  lcd.setCursor(0, 1);
  lcd.print("Press button");


  pinMode(PIN_LIGHT_SENSOR, INPUT_PULLUP);
  pinMode(PIN_SOUND_SENSOR, INPUT_PULLUP);
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(PIN_SOUND_SENSOR), interruptSound, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_LIGHT_SENSOR), interruptLight, FALLING);
}

void loop() {
  buttonHandler();


}
