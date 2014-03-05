//LiquidCrystal_I2C lcd(0x38);  // Set the LCD I2C address
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

byte killeeins[8] = {
  B00010,
  B00100,
  B01000,
  B10011,
  B01010,
  B00110,
  B00010,
};
byte killezwei[8] = {
  B00000,
  B00000,
  B00000,
  B10000,
  B00000,
  B00000,
  B00000,
};

byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};



#define BACKLIGHT_PIN     13
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
//LiquidCrystal_I2C lcd(0x27, BACKLIGHT_PIN, POSITIVE);
//LiquidCrystal_I2C lcd(0x27);

void setup_display(void) {
  pinMode(DISPLAY_POWER, OUTPUT);
  digitalWrite(DISPLAY_POWER, HIGH);
  delay(10);
  //lcd.createChar(3, smiley);
  lcd.begin ( 20, 4 );
  lcd.createChar(0, killeeins);
  lcd.createChar(1, killezwei);
  lcd.clear();
  lcd.print("Starting up");
  //lcd.setCursor(0, 2);
  //lcd.write(byte(0));
  //lcd.write(byte(1));
  //delay(500);
  lcd.setCursor(0, 2);
  lcd.print("  Made by");
  lcd.setCursor(13, 3);
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.print("Kille");
  delay(1000);


}

void print_data_display(void) {
  static long print_millis = 0;
  if (millis() > print_millis) {
    print_millis = millis() + 500;
    lcd.setCursor ( 0, 0);
    if (voltage < 10)
      lcd.print(" ");
    lcd.print(voltage, 2);
    lcd.print("V ");
    lcd.print(current, 3);
    lcd.print("A ");
    if (power < 10)
      lcd.print(" ");
    lcd.print(power, 2);
    lcd.print("W ");

    lcd.setCursor ( 0, 1 );
    if (set_voltage < 10)
      lcd.print(" ");
    lcd.print(set_voltage, 2);
    lcd.print("V ");
    lcd.print(set_current, 3);
    lcd.print("A ");
    if (set_power < 10)
      lcd.print(" ");
    lcd.print(set_power, 2);
    lcd.print("W ");
    lcd.setCursor ( 0, 2);
    lcd.print("input:");

    lcd.setCursor ( 5, 3 );
    if (standby)
      lcd.print("Standby ");
    else
      lcd.print("Aktiv   ");

    lcd.setCursor(18, 3);
    lcd.write(byte(0));
    lcd.write(byte(1));

  }

}

void print_display_input_buffer(String input_buffer) {
  lcd.setCursor ( 7, 2);
  if (input_buffer.length() < 6) {
    lcd.print(input_buffer);
    lcd.print("       ");
  } else {
    lcd.setCursor ( 0, 2);
    lcd.print("input to long!");
    beep();
    delay(1000);
    lcd.setCursor ( 0, 2);
    lcd.print("               ");
    delete_input_buffer_keypad();
  }

}


void print_info_display(void) {
  lcd.clear();
  lcd.print("Info Page:   ");
  lcd.createChar(0, killeeins);
  lcd.createChar(1, killezwei);
  lcd.write((uint8_t)0);
  lcd.write((uint8_t)1);
  lcd.print("accuracy min. 20mV");
  lcd.setCursor ( 0, 2 );
  lcd.print("accuracy min 3mA");
  lcd.setCursor ( 0, 3 );
  lcd.print("Vmax25.6V Imax2.56A");
}



