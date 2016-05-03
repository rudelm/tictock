/*
 * SyncProvider.ino
 * example code illustrating time synced from a DCF77 receiver
 * Thijs Elenbaas, 2012
 * This example code is in the public domain.
 
 This example shows how to fetch a DCF77 time and synchronize
 the internal clock. In order for this example to give clear output,
 make sure that you disable logging  from the DCF library. You can 
 do this by commenting out   #define VERBOSE_DEBUG 1   in Utils.cpp. 
 */

#include <DCF77.h>       //https://github.com/thijse/Arduino-Libraries/downloads
#include <Time.h>        //http://www.arduino.cc/playground/Code/Time
#include <Wire.h>
#include <DS1307RTC.h>

#define DCF_PIN 2	         // Connection pin to DCF 77 device
#define DCF_INTERRUPT 0		 // Interrupt number associated with pin

time_t prevDisplay = 0;          // when the digital clock was displayed
time_t time;
DCF77 DCF = DCF77(DCF_PIN,DCF_INTERRUPT);

struct word_t
{
  int index;
  int length;
};

int words(int minutesOfDay, word_t* buffer);


const word_t WORT_ES = {0, 2};
 const word_t WORT_IST = {3, 3};
 const word_t MINUTE_FUENF = {7, 4};
 const word_t MINUTE_ZEHN = {11, 4};
 const word_t MINUTE_FUENFZEHN = {7, 8};
 const word_t MINUTE_ZWANZIG = {15, 7};
 const word_t MINUTE_DREIVIERTEL = {22, 11};
 const word_t MINUTE_VIERTEL = {26, 7};
 const word_t WORT_NACH = {35, 4};
 const word_t WORT_VOR = {39, 3};
 const word_t MINUTE_HALB = {44, 4};
 const word_t STUNDE_ZWOELF = {49, 5};
 const word_t STUNDE_ZWEI = {55, 4};
 const word_t STUNDE_EIN = {57, 3};
 const word_t STUNDE_EINS = {57, 4};
 const word_t STUNDE_SIEBEN = {60, 6};
 const word_t STUNDE_DREI = {67, 4};
 const word_t STUNDE_FUENF = {73, 4};
 const word_t STUNDE_ELF = {77, 3};
 const word_t STUNDE_NEUN = {80, 4};
 const word_t STUNDE_VIER = {84, 4};
 const word_t STUNDE_ACHT = {89, 4};
 const word_t STUNDE_ZEHN = {93, 4};
 const word_t STUNDE_SECHS = {100, 5};
 const word_t WORT_UHR = {107, 3};
 
const word_t* MINUTE_WORDS[] = {
 0, &MINUTE_FUENF,
 &MINUTE_ZEHN, &MINUTE_VIERTEL, &MINUTE_ZWANZIG,
 &MINUTE_FUENF, &MINUTE_HALB, &MINUTE_FUENF,
 &MINUTE_ZWANZIG, &MINUTE_VIERTEL, &MINUTE_ZEHN,
 &MINUTE_FUENF
 };
 
 const word_t* CONNECTOR_WORDS[] = {
 0, &WORT_NACH,
 &WORT_NACH, &WORT_NACH, &WORT_NACH, &WORT_VOR,
 0, &WORT_NACH, &WORT_VOR, &WORT_VOR, &WORT_VOR, 
 &WORT_VOR
 };
 
 const word_t* HOUR_WORDS[] = {
 &STUNDE_ZWOELF,
 &STUNDE_EINS, &STUNDE_ZWEI, &STUNDE_DREI,
 &STUNDE_VIER, &STUNDE_FUENF, &STUNDE_SECHS,
 &STUNDE_SIEBEN, &STUNDE_ACHT, &STUNDE_NEUN,
 &STUNDE_ZEHN, &STUNDE_ELF
 };

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Serial.println("Setting system clock from RTC module");
  setSyncProvider(RTC.get); 
  //DCF.Start();
  //setSyncInterval(30);
  //setSyncProvider(getDCFTime);
  // It is also possible to directly use DCF.getTime, but this function gives a bit of feedback
  //setSyncProvider(DCF.getTime);

//  Serial.println("Waiting for DCF77 time ... ");
//  Serial.println("It will take at least 2 minutes until a first update can be processed.");
//  while(timeStatus()== timeNotSet) { 
//    // wait until the time is set by the sync provider     
//    Serial.print("RTC: ");
//    digitalClockDisplay();
//    delay(2000);
//  }
}


void loop()
{  
  digitalClockDisplay();
  delay(1000);
}

int words(int minutesOfDay, word_t* buffer)
{
 int bufferIndex = 0;
  /*
  int hours = (minutesOfDay + 2) / 60;
 int minutes = (minutesOfDay + 2) % 60;
 int minuteIndex = minutes / 5;
 int hourIndex = hours % 12;
 
 buffer[bufferIndex++] = &WORT_ES;
 buffer[bufferIndex++] = &WORD_IST;
 
 buffer[bufferIndex++] = MINUTE_WORDS[minuteIndex];
 buffer[bufferIndex++] = CONNECTOR_WORDS[minuteIndex];
 
 if (minuteIndex == 5 || minuteIndex == 7)
 {
 buffer[bufferIndex++] = &MINUTE_HALB;
 }
 
 if (minuteIndex == 0 && hourIndex == 1)
 {
 buffer[bufferIndex++] = &STUNDE_EIN;
 }
 else
 {
 if (minuteIndex > 4)
 {
 hourIndex = (hourIndex + 1) % 12;
 }
 buffer[bufferIndex++] = HOUR_WORDS[hourIndex];
 }
 
 if (minuteIndex == 0)
 {
 buffer[bufferIndex++] = WORT_UHR;
 }
 */
 return bufferIndex;
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

unsigned long getDCFTime()
{ 
  time_t DCFtime = DCF.getTime();
  // Indicator that a time check is done
  if (DCFtime!=0) {
    Serial.println("Reiceived DCF77 time signal, updating RTC...");
    void digitalClockDisplay();
    // set the RTC
    RTC.set(DCFtime);  
  }
  return DCFtime;
}


