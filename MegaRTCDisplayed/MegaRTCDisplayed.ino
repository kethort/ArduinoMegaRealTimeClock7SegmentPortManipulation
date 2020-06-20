#include <DS3231.h>

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

Time current;
byte lastSecond;
int lastMinute;
int lastHour;
char cstr[5];
volatile byte tickMod;

#define NUM_DIGITS 4

/* Arduino Mega PORTs Used
//-----------------------------------------------------------------   
// PORTF = {A0, A1, A2,  A3,  A4,  A5,  A6,  A7};     D1 - D4 & Dot
// PORTK = {A8, A9, A10, A11, A12, A13, A14, A15};    A - G       
//-----------------------------------------------------------------
*/
void setup() {
  Serial.begin(9600);

  DDRF = 0x1F;
  PORTF = ~0x1F;
    
  DDRK = 0x7F;
  PORTK = 0x7F;
  
  rtc.begin();

  current = rtc.getTime();
  lastSecond = current.sec;

  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(FRIDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(17, 49, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(19, 6, 2020);   // Set the date to January 1st, 2014
}

void loop() {  
  current = rtc.getTime();
  
  if (current.sec != lastSecond) {   
    lastSecond = current.sec;  

    // blink the dots to the second
    //PORTF = ((PINF >> PF4) & 0x01) ? PORTF & 0xEF : PORTF | 0x10;
  }

  if (current.min != lastMinute || current.hour != lastHour) {
    lastMinute = current.min;
    lastHour = current.hour;

    int output = 0;
    
    if (current.hour == 0)
      output = (current.hour + 12);
    else if (current.hour > 12)
      output = (current.hour - 12);
    else
      output = current.hour;
    
    output *= 100;
    output += current.min;
    memset(cstr, 0, sizeof(cstr));
    sprintf(cstr, "%4d", output);
  }

  writeChars(cstr);
}


// high selects the position of the digit
// low turns on the segments in the digit
void switchDigitPos(int digitPos) {
  PORTF = 0x10;
  PORTF |= (1 << digitPos);
}

byte aToFChars[] = {0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};
byte zeroThruNine[] = {0x40, 0xF9, 0xA4, 0x30, 0x19, 0x12, 0x02, 0xF8, 0x00, 0x10};

void displayNumber(char ch) {
  int number = ch - '0';
  
  PORTK = 0x7F;
  byte mask = zeroThruNine[number];
  PORTK &= mask;
}

void displayCharacter(char ch) {
  int number = ch - 'a';
  
  PORTK = 0x7F;
  byte mask = aToFChars[number];
  PORTK &= mask;
}

void writeChars(char str[]) {
  for (int i = 0; i < NUM_DIGITS; i++) {
    char ch = str[i];
    if (ch >= '0' && ch <= '9') {
      switchDigitPos(i);
      displayNumber(ch);
    } else if (ch >= 'a' && ch <= 'f') {
      switchDigitPos(i);
      displayCharacter(ch);
    }
    delay(5);
  }
}
