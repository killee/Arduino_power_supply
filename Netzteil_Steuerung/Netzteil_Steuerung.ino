#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

#include "EEPROMAnything.h"
#include <Keypad.h>

/*Todo:
          Ein schönes VI in LabView basteln
          Serielle Ausgabe verbessern!
          Noch mal gscheit kalibrieren. Da müsste noch ein bissl etwas gehen!
          Ev. eine Kalibrier Funktion einbauen! Noch sind nur 75% belegt!
          Automatisches Abarbeiten von einer Kurfe einbauen

Erledigt:
          Auflösung der PWM verbessern
          Power regelung testen
          Ansteuerung für Relay Standby implementieren
          Beim Start mein Logo ausgeben!
          Tastatur anbindung müsste passen. Ausgabe erfolgt in input_buffer
          Display Anbindung

          ADC Referenz umschalten um bei nidrigen Strömen und Spannungen bessere ergebnisse zu erzielen
          Der leonardo wird so wie ich hier rumase ev. nicht reichen... Doch den Mega Bessere auflösung des ADCs durch 3 referenzspannungen!

          eine möglichkeit den ADC zu verbessern ist oversampling:
          Beim Strom ist genug rauschen da. Da sollte es eine Verbesserung bringen. Der ist aber eh nicht so der Bruller...
          Spannung ist recht gut
          Mit der erhöten PWM-Auflösung noch mal schauen
          Im Standby Spannung und Strom Sollwerte runterfahren
*/

#define CURRENT_SET 10
#define VOLTAGE_SET 9

#define VOLTAGE A0
#define CURRENT A1

#define STANDBY_RELAIS1 A2
#define STANDBY_RELAIS2 A3

#define DISPLAY_POWER   A4

#define BEEPER 11
#define BEEP 125

extern LiquidCrystal_I2C lcd;

float set_voltage = 0;
float set_current = 0;
float set_power = 0;
float voltage = 0;
float current = 0;
float power = 0;
int print_intervall = 500;
boolean standby = true;


void setup() {
  setup_display();
  setup_serial();
  setup_keypad();
  EEPROM_readAnything(0, set_voltage);
  EEPROM_readAnything(20, set_current);
  EEPROM_readAnything(40, set_power);
  setup_analog_pins();
  pinMode(BEEPER, OUTPUT);
  beep();
  lcd.clear();
}

uint8_t count = 100;

void loop() {

  digitalWrite(STANDBY_RELAIS1, standby);
  digitalWrite(STANDBY_RELAIS2, standby);
  keypad_getKey();
  power = voltage * current;
  read_String_serial();
  print_data_serial();
  print_data_display();
  reade_analog_signals();
  write_analog_signals();

}


void beep(void) {
  analogWrite(BEEPER, BEEP);
  delay(100);
  analogWrite(BEEPER, 0);
}


