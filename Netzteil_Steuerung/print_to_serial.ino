String inputString = "";         // a string to hold incoming data


void setup_serial(void) {
  Serial.begin(115200);
  inputString.reserve(200);
  Serial.println("Starting up");
  Serial.println("  Made by Kille ");
}

void read_String_serial(void) {

  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      inputString = manage_input(inputString.substring(0,(inputString.length()-2)));
    }
  }
}

void print_data_serial(void) {
  static long print_millis = 0;
  if (millis() > print_millis) {
    print_millis = millis() + print_intervall;
    Serial.print(voltage, 2);
    Serial.println("V");
    Serial.print(current, 3);
    Serial.println("A");
    Serial.print(power, 2);
    Serial.println("W");
    Serial.print(set_voltage, 2);
    Serial.println("v");
    Serial.print(set_current, 3);
    Serial.println("a");
    Serial.print(set_power, 2);
    Serial.println("w");
    if (standby)
      Serial.println("1S");
    else
      Serial.println("0S");
  }
}


