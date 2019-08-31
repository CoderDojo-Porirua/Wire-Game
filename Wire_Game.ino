//WIRE TRACE GAME
//
//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 20 chars and 4 line display

int TStart = 2;
int Track = 0;
int TEnd = 0;
int Trip = 0;

long startTime ;                    // start time for stop watch
long elapsedTime ;                  // elapsed time for stop watch
float endTime;                       // End time for stop watch
float BestTime = 9999999;
float elapsedTimeLCD;

void setup()
{
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, OUTPUT);

  digitalWrite(2, 1); //Turns on Wire Ring

  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("WIRE OF DOOM");
  lcd.setCursor(0, 1);
  lcd.print("Best Time:");
  lcd.setCursor(0, 2);
  lcd.print("");
  lcd.setCursor(0, 3);
  lcd.print("Timer:0.00 secs     ");
  lcd.setCursor(19, 0);
  lcd.print(Trip);
  TStart = digitalRead(3);
  if (TStart == 0) { //Checks if game is in start position
    Trip = 1;
    lcd.setCursor(0,2);
    lcd.print("    Go to Start     ");
  }
}


void loop()
{
  TStart = digitalRead(3);
  Track = digitalRead(4);
  TEnd = digitalRead(5);

  lcd.setCursor(19, 0);
  lcd.print(Trip);

  if (TStart == 1) {
    Trip = 0;
   }

  if (Trip == 0) { // User has wire loop on start position
    if (TStart == 1) {
      lcd.setCursor(0, 2);
      lcd.print("     Ready Set      ");
      lcd.setCursor(0, 3);
      lcd.print("Timer:0.00 secs     ");
      startTime = millis();
    }

    if (TStart == 0 && Track == 1) {
      float FailTime = elapsedTimeLCD;
      lcd.setCursor(6, 3);
      lcd.print(FailTime);
      lcd.setCursor(0, 2);
      lcd.print("ALERT: Try Again!!! ");
      Trip = 1;
    } else if (TStart == 0 && TEnd == 0) { // User moves off start and timer starts
      lcd.setCursor(0, 2);
      lcd.print("        GO!!!       ");
      lcd.setCursor(6, 3);
      lcd.print("          ");
      lcd.setCursor(6, 3);
      elapsedTime = millis() - startTime;
      elapsedTimeLCD = elapsedTime;
      elapsedTimeLCD = elapsedTimeLCD / 1000;
      lcd.print(elapsedTimeLCD);
    } else if (TStart == 0 && TEnd == 1) { // User completes wire without touching
      endTime = elapsedTimeLCD;
      lcd.setCursor(6, 3);
      lcd.print(endTime);
      Trip = 1;
    lcd.setCursor(0, 2);
      lcd.print("     Complete      ");
      if (endTime < BestTime) { // Stores the Best time since last reset
        BestTime = endTime;
        lcd.setCursor(10, 1);
        lcd.print("          ");
        lcd.setCursor(10, 1);
        lcd.print(BestTime);
        lcd.print("secs");
    lcd.setCursor(0, 2);
    lcd.print("   Best Score!!    ");
      }
    }
  }

  if (Track == 1) { //Buzzer and Light Trigger
    digitalWrite(6, 1);
  } else {
    digitalWrite(6, 0);
  }


  //LCD DEBUG AREA START
  lcd.setCursor(0, 0);
  lcd.print(TStart);
  lcd.setCursor(1, 0);
  lcd.print(Track);
  lcd.setCursor(2, 0);
  lcd.print(TEnd);
  lcd.setCursor(18, 0);



}
