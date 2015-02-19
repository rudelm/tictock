#include <DS1307RTC.h>
#include <Time.h>
#include <LiquidCrystal.h>
#include <Wire.h>


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(17, OUTPUT);
  pinMode(16, OUTPUT);
  digitalWrite(17, HIGH);
  digitalWrite(16, LOW);
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  Serial.begin(57600);
  Wire.begin();

  if (!RTC.chipPresent())
  {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    //RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  time_t time = RTC.get();

  Serial.println(now());
  setTime(time);
  Serial.println(now());


  // Print a message to the LCD.
  lcd.print("tickclock");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print((now() / 60) % 1440);
  
  
}
