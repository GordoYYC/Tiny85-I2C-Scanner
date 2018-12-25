#include "TinyWireM.h"                  // I2C Master lib for ATTinys which use USI
#include "LiquidCrystal_I2C.h"          // for LCD w/ GPIO MODIFIED for the ATtiny85

#define LCDlines        4
#define LCDcols         20    // besides creating instance, these are also used throughout program 
#define GPIO_ADDR     0x38              // (PCA8574A A0-A2 @5V) typ. A0-A3 Gnd 0x20 / 0x38 for A
#define LED1_PIN        1               // ATtiny Chip Pin 6  / AT Tiny module P1 a.k.a. BuiltInLED
#define rescanPIN       3               // ATtiny Chip Pin 2  / AT Tiny module P3 pushbutton for More/Rescan

LiquidCrystal_I2C lcd(GPIO_ADDR, LCDcols, LCDlines); // set address & 16 chars / 2 lines

byte customChar[8] = {  // a superscript 2 (since my LCD has Asian chars and no built in SS2)
  0b01100,
  0b10010,
  0b00100,
  0b01000,
  0b11110,
  0b00000,
  0b00000,
  0b00000};

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(rescanPIN, INPUT_PULLUP); // used to reset / restart prg
  TinyWireM.begin();                // initialize I2C lib
  lcd.init();                       // initialize the lcd
  lcd.backlight();                  // on, noBackLight turns it off
  lcd.createChar(0, customChar);    // create a new custom character superscript 2 in CG0
  digitalWrite(LED1_PIN, HIGH); }   // copies backlight

void flashBackLight(int count2) {
  for (byte i = 0; i < count2; i++)  {
    lcd.noBacklight();
    digitalWrite(LED1_PIN, LOW);
    delay (500);
    lcd.backlight();
    digitalWrite(LED1_PIN, HIGH);
    delay (500);  }}

void loop() {       // ad infinitum
  lcd.clear();
  lcd.print ("I");                // Print a message to the LCD.
//  lcd.print((char)0xB2);          // crap, mine has asian 2nd character set, no superscript2  YDMD
  lcd.print((uint8_t)0);          // planB, draw a superscript 2 in custom char RAM, location 0 and display it with this line
//  lcd.print ("2");                // Print a regular 2 if nothing else works
  lcd.print ("C scanning ....");  // Print rest of message to the LCD.
  lcd.setCursor(0, 1);
  lcd.print ("0x08..0x78 7-bit"); // also mention mode and limits
  delay (4000);
  lcd.clear();
  byte count = 0;
  int lcdLine = 0;
  for (byte i = 0x08; i < 0x78; i++)  {           // test every possible I2C address
    TinyWireM.beginTransmission (i);
    if (TinyWireM.endTransmission () == 0)  {     // if it replies, it exists
      if (lcdLine == LCDlines) {                  // test which LCD line we are on
        lcd.setCursor(16, 0);
        lcd.print ("More");
        flashBackLight(3);
        lcdLine = lcdLine - LCDlines;             // subtract # of lines on LCD to reset next info to top line
        while (digitalRead(rescanPIN) == HIGH){ };//sit here until rescan goes low  a.k.a. 'Press any key to continue'
          lcd.clear();
          delay(2000);}               // couple extra secs to get finger off of 'key
      lcd.setCursor(0, lcdLine);
      if (LCDcols >=17 ) {            // if a narrow display (16 chars) don't print 'Adr: to clean up display
        lcd.print ("Adr: ");}  
      if (i < 100) lcd.print(' ');      // pad displayed number of found I2C
      if (i < 10) lcd.print(' ');      // pad displayed number of found I2C
      lcd.print (i, DEC);             // print responding I2C address in decimal ...
      lcd.print (" (0x");             // and hex
      lcd.print (i, HEX);
      lcd.print (")");
      count++;                        // next I2C address to test
      lcdLine++;    }                 // end of good response
  } // end of for every I2C address loop
  lcd.setCursor(17, 0);               // only get here after testing all possible I2C addresses
  if (count<100) lcd.print('0');      // pad displayed number of found I2C
  if (count<10) lcd.print('0');
  lcd.print (count, DEC);             // number of found I2C in decimal with leading 0's (might be able to right justify? (but that might shift existing text)
  lcd.setCursor(17, 1);
  lcd.print ("Dev");
  if (LCDlines >= 3) {                // if display has 4 lines, spell out (Dev) ice (s) just for looks
    lcd.setCursor(17, 2);
    lcd.print ("ice");
    lcd.setCursor(17, 3);
    lcd.print ("(s)");  }
  delay(2000);  // need at least a couple secs to read, but more importantly gives more secs to get finger off rescan button

  while (digitalRead(rescanPIN) == HIGH){}  //'Press any key to continue...'
}
