#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

#include "EEPROMAnything.h"
#include <Keypad.h>
#include <PWM.h>
//#include <keypad.h>


/*Todo:   
          Ester Egg einbauen
          Ein schönes VI in LabView basteln
          Noch mal gscheit kalibrieren. Ev. eine Funktion einbauen! Noch sind nur 75% belegt! So schlecht ist es aber nicht!

Fixed:
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

*/
#define CURRENT_SET 10
#define VOLTAGE_SET 9
//#define CURRENT_SET 12   //Bei Mega

#define VOLTAGE A0
#define CURRENT A1
#define STANDBY_RELAIS1 A2
#define STANDBY_RELAIS2 A3
#define DISPLAY_POWER   A4


#define BEEPER 11
#define BEEP 125

#define PWM_FREQUENCY 480

#define CURR_CAL 97

float set_voltage = 0;
float set_current = 0;
float set_power = 0;
float voltage = 0;
float current = 0;
float power = 0;
int print_intervall = 500;
boolean standby = true;
extern LiquidCrystal_I2C lcd;


void setup() {
  setup_display();
  setup_serial();
  setup_keypad();
  EEPROM_readAnything(0, set_voltage);
  EEPROM_readAnything(20, set_current);
  EEPROM_readAnything(40, set_power);
  pinMode(CURRENT_SET, OUTPUT);
  pinMode(VOLTAGE_SET, OUTPUT);
  pinMode(BEEPER, OUTPUT);
  pinMode(STANDBY_RELAIS1, OUTPUT);
  pinMode(STANDBY_RELAIS2, OUTPUT);
  digitalWrite(STANDBY_RELAIS1, standby);
  digitalWrite(STANDBY_RELAIS2, standby);
  
  InitTimersSafe(); //initialize all timers except for 0, to save time keeping functions
  SetPinFrequency(CURRENT_SET, PWM_FREQUENCY);
  SetPinFrequency(VOLTAGE_SET, PWM_FREQUENCY);
  pwmWriteHR(CURRENT_SET, 0);
  pwmWriteHR(VOLTAGE_SET, 0);
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

void write_analog_signals(void) {
  
  
  if ((power + set_power * 0.1) > set_power) {
    pwmWriteHR(VOLTAGE_SET, (int)((set_power / current) * (2560+10)));
  } else {
    if (set_voltage >= 25.49) {
      digitalWrite(VOLTAGE_SET, HIGH);
    } else {
      pwmWriteHR(VOLTAGE_SET, (int)(set_voltage * (2560+10)));
    }
  }
    if (set_current >= 2.549) {
      digitalWrite(CURRENT_SET, HIGH);
    } else {
      pwmWriteHR(CURRENT_SET, (int)(set_current * (25600+750))-120); //26350 25600
    }
}

void reade_analog_signals(void) {
  analogReference(DEFAULT);
  int analog = readADC12bit(VOLTAGE);
  if (analog < 4092 / 2) {        //Leonardo: /2
    analogReference(INTERNAL);  //Leonardo: INTERNAL MEGA: INTERNAL1V1
    //Serial.print("switch internal");
    analog = readADC12bit(VOLTAGE);
    analog = readADC12bit(VOLTAGE);
    analog = readADC12bit(VOLTAGE);
    voltage = ((float)(analog+7) / (float)(7992+45)) * 25.5; //(float)map(readADC12bit(VOLTAGE), 0, 7992, 0, 25599) / (float)1000; //Leonardo müsste dann 7992 sein MEGA 18600
    analogReference(DEFAULT);
    analog = readADC12bit(CURRENT);
    analog = readADC12bit(CURRENT);
  } else {
    voltage = ((float)(analog+4) / (float)(4092+4)) * 25.5; //map(analog, 0, 4092, 0, 25599) / (float)1000;
  }

  analog = readADC12bit(CURRENT);

  if (analog < 4095 / 2) {
    analogReference(INTERNAL); //Leonardo: INTERNAL  MEGA: INTERNAL1V1
    analog = readADC12bit(CURRENT);
    analog = readADC12bit(CURRENT);
    analog = readADC12bit(CURRENT);
    //int analog=readADC12bit(VOLTAGE);
    current = ((float)(analog+18) / (float)(7992+250)) * 2.55; //(float)map(readADC12bit(CURRENT), 0, 7992, 0, 25599) / (float)10000; //Leonardo müsste dann 7992 sein MEGA 18600
    analogReference(DEFAULT);
  } else {
    current = ((float)(analog) / (float)(4092 + 97)) * 2.55; //(float)map(analog, 0, 4092, 0, 25599) / (float)10000;
    analog = readADC12bit(CURRENT);
    analog = readADC12bit(CURRENT);
  }

}

void beep(void) {
  analogWrite(BEEPER, BEEP);
  delay(100);
  analogWrite(BEEPER, 0);
}

unsigned int readADC12bit(int channel) // oversamples ADC to 12 bit
{
  byte i;
  unsigned int analogResult = 0;
  for (i = 0; i < 16; i++)
  {
    analogResult += analogRead(channel);
  }
  return (analogResult >> 2);
}
