#define COMMAND 0xFE
#define SUPER   0x7C
#define NORMAL  0x00

#define LCD_BACKLIGHT           0x80
#define LCD_WIDTH_SETTING       1
#define LCD_LINE_SETTING        2

#define LINE1_START             5
#define LINE2_START             25

#define BAUD_RATE               45


static uint8_t LCD_Width = 16;
static uint8_t LCD_Lines = 2;

void lcd_init() {
  // set up the LCD's number of columns and rows:
  pinMode(LIGHT, OUTPUT);
  digitalWrite(LIGHT, LOW);
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

/*
    // TODO: save settings to EEPROM
    switch (letter) {
      case 1:
        // turn on backlight
        digitalWrite(LIGHT, HIGH);
        break;
      case 2:
        // turn off backlight
        digitalWrite(LIGHT, LOW);
        break;
      case 3:
        LCD_Width = 20; // TODO: test
        break;
      case 4:
        LCD_Width = 16; // TODO: test
        break;
      case 5:
        LCD_Lines = 4; // TODO: test
        break;
      case 6:
        LCD_Lines = 2; // TODO: test
        break;
      case 7:
        LCD_Lines = 1; // TODO: test
        break;
        break;
      default:
        break;
    }
    */

    if ((letter & 0xf0) == LCD_BACKLIGHT) {
      uint8_t brightness = letter & 0x0f;
      if (brightness == 0) {
        digitalWrite(LIGHT, LOW);
      } else {
        // TODO -- vary brightness levels, 1-29
        digitalWrite(LIGHT, HIGH);
      }
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

