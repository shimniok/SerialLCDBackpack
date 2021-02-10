#define COMMAND 0xFE
#define SUPER   0x7C
#define NORMAL  0x00

#define LCD_BACKLIGHT           0x80
#define LCD_WIDTH_SETTING       1
#define LCD_LINE_SETTING        2

static uint8_t LCD_Width = 16;
static uint8_t LCD_Lines = 2;

void lcd_init() {
  // set up the LCD's number of columns and rows:
  pinMode(LIGHT, OUTPUT);
  digitalWrite(LIGHT, LOW);
  //setBrightness( EEPROM.read(addr) );
  //_cols = EEPROM.read(addr);
  //_rows = EEPROM.read(addr);
  //lcd.begin(_cols, _rows);
  lcd.begin(16, 2);
  lcd.clear();
}

void process(uint8_t letter) {
  static uint8_t state = NORMAL;

  if (state == NORMAL) {

    if (letter == COMMAND) {
      state = COMMAND;
    } else if (letter == SUPER) {
      state = SUPER;
    } else {
      lcd.print((char) letter);
    }
    
  } else if (state == COMMAND) {

    // Ignore 0b001100XX, the 8-bit mode command
    // because we're not wired for that
    if ((letter & 0xf0) != 0x30) {
      lcd.command(letter);
    }
    
    state = NORMAL;
    
  } else if (state == SUPER) {

    // TODO: save settings to EEPROM
    // TODO: lines, width
    
    // First 3 bits indicate command, remaining 5 bits are value
    if ((letter & 0xE0) == LCD_BACKLIGHT) {
      const uint8_t brightness[32] = { 
        0, 9, 17, 25, 33, 42, 50, 58, 66, 74, 83, 91, 99, 
        107, 116, 124, 132, 140, 148, 157, 165, 173, 181,
        190, 198, 206, 214, 222, 231, 239, 247, 255
      };
      uint8_t b = (letter & 0x1f);

      if (b >= 31) {
        digitalWrite(LIGHT, HIGH);
      } else {
        analogWrite(LIGHT, brightness[b]);
      }

      //EEPROM.write(addr, brightness);

    }

    /*
    if (letter >= 3 && letter <= 8) {
        lcd.begin(LCD_Width, LCD_Lines); // TODO: test
    }
    */

    state = NORMAL;   
    
  } else {
    // Shouldn't ever get here but...
    state = NORMAL;
  }
  
} //process

