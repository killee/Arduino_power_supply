#include <Wire.h>
#include <PWM.h>


#define PWM_FREQUENCY 480


void setup_analog_pins(void) {

  pinMode(CURRENT_SET, OUTPUT);
  pinMode(VOLTAGE_SET, OUTPUT);
  pinMode(STANDBY_RELAIS1, OUTPUT);
  pinMode(STANDBY_RELAIS2, OUTPUT);
  digitalWrite(STANDBY_RELAIS1, standby);
  digitalWrite(STANDBY_RELAIS2, standby);

  InitTimersSafe(); //initialize all timers except for 0, to save time keeping functions
  SetPinFrequency(CURRENT_SET, PWM_FREQUENCY);
  SetPinFrequency(VOLTAGE_SET, PWM_FREQUENCY);
  pwmWriteHR(CURRENT_SET, 0);
  pwmWriteHR(VOLTAGE_SET, 0);

}

void write_analog_signals(void) {

#define SET_UPPER_LIMIT_VOLTAGE_CALL 10
#define SET_LOWER_LIMIT_VOLTAGE_CALL 0

#define SET_UPPER_LIMIT_CURRENT_CALL 750
#define SET_LOWER_LIMIT_CURRENT_CALL -120

  if (standby) {
    digitalWrite(VOLTAGE_SET, LOW);
    digitalWrite(CURRENT_SET, LOW);
  } else {

    if ((power + set_power * 0.1) > set_power) {
      pwmWriteHR(VOLTAGE_SET, (int)((set_power / current) * (2560 + SET_UPPER_LIMIT_VOLTAGE_CALL)) + SET_LOWER_LIMIT_VOLTAGE_CALL);
    } else {
      if (set_voltage >= 25.49) {
        digitalWrite(VOLTAGE_SET, HIGH);
      } else {
        pwmWriteHR(VOLTAGE_SET, (int)(set_voltage * (2560 + SET_UPPER_LIMIT_VOLTAGE_CALL)));
      }
    }
    if (set_current >= 2.549) {
      digitalWrite(CURRENT_SET, HIGH);
    } else {
      pwmWriteHR(CURRENT_SET, (int)(set_current * (25600 + SET_UPPER_LIMIT_CURRENT_CALL)) + SET_LOWER_LIMIT_CURRENT_CALL);
    }
  }
}
void reade_analog_signals(void) {
#define DEFAULT_UPPER_LIMIT_VOLTAGE_CALL 4
#define DEFAULT_LOWER_LIMIT_VOLTAGE_CALL 4


#define INTERNAL_UPPER_LIMIT_VOLTAGE_CALL 45
#define INTERNAL_LOWER_LIMIT_VOLTAGE_CALL 7

  analogReference(DEFAULT);
  int analog = readADC12bit(VOLTAGE);
  if (analog < 4092 / 2) {
    analogReference(INTERNAL);
    analog = readADC12bit(VOLTAGE);
    analog = readADC12bit(VOLTAGE);
    analog = readADC12bit(VOLTAGE);
    voltage = ((float)(analog + INTERNAL_LOWER_LIMIT_VOLTAGE_CALL) / (float)(7992 + INTERNAL_UPPER_LIMIT_VOLTAGE_CALL)) * 25.5; //(float)map(readADC12bit(VOLTAGE), 0, 7992, 0, 25599) / (float)1000; //Leonardo müsste dann 7992 sein MEGA 18600
    analogReference(DEFAULT);
    analog = readADC12bit(CURRENT);
    analog = readADC12bit(CURRENT);
  } else {
    voltage = ((float)(analog + DEFAULT_LOWER_LIMIT_VOLTAGE_CALL) / (float)(4092 + DEFAULT_UPPER_LIMIT_VOLTAGE_CALL)) * 25.5; //map(analog, 0, 4092, 0, 25599) / (float)1000;
  }

  analog = readADC12bit(CURRENT);

#define DEFAULT_UPPER_LIMIT_CURRENT_CALL 97
#define DEFAULT_LOWER_LIMIT_CURRENT_CALL 0

#define INTERNAL_UPPER_LIMIT_CURRENT_CALL 250
#define INTERNAL_LOWER_LIMIT_CURRENT_CALL 18


  if (analog < 4095 / 2) {
    analogReference(INTERNAL); //Leonardo: INTERNAL  MEGA: INTERNAL1V1
    analog = readADC12bit(CURRENT);
    analog = readADC12bit(CURRENT);
    analog = readADC12bit(CURRENT);
    current = ((float)(analog + INTERNAL_LOWER_LIMIT_CURRENT_CALL) / (float)(7992 + INTERNAL_UPPER_LIMIT_CURRENT_CALL)) * 2.55; //(float)map(readADC12bit(CURRENT), 0, 7992, 0, 25599) / (float)10000; //Leonardo müsste dann 7992 sein MEGA 18600
    analogReference(DEFAULT);
  } else {
    current = ((float)(analog + DEFAULT_LOWER_LIMIT_CURRENT_CALL) / (float)(4092 + DEFAULT_UPPER_LIMIT_CURRENT_CALL)) * 2.55; //(float)map(analog, 0, 4092, 0, 25599) / (float)10000;
    analog = readADC12bit(CURRENT);
    analog = readADC12bit(CURRENT);
  }

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
