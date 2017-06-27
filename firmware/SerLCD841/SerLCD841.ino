/* Serial LCD ATTiny841
 * by Michael Shimniok (www.bot-thoughts.com)
 */

#include <LiquidCrystal.h>

#define RS    10 // PA0
#define EN     7 // PA3
#define DATA4  2 // PB2
#define DATA5  3 // PA7
#define DATA6  4 // PA6
#define DATA7  6 // PA4

#define LIGHT  5 // PA5

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(RS, EN, DATA4, DATA5, DATA6, DATA7);

void setup() {
//  uint8_t *phde = 0x6A;
//  *phde |= 0x01; // enable high sink on PA5

  PHDE |= PHDEA0; // enable high sink on PA5
  
  lcd_init();
  Serial.begin(9600);
}

void loop() {
  char buf[16];
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  while (Serial.available()) {
    process(Serial.read() & 0xff);
  }
}
