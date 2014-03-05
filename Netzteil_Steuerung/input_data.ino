String manage_input(String inputString) {
  
  char char1[8];
  inputString.toCharArray(char1, 8);
  
  if (inputString.endsWith("V") ) {
    //      Serial.print(value);
    //set_voltage=inputString.toInt();
    set_voltage = abs(atof(char1));
    if (set_voltage > 25.500)
      set_voltage = 25.500;
    Serial.print("New Set Voltage: ");
    Serial.println(set_voltage);
    EEPROM_writeAnything(0, set_voltage);
    inputString="";
    beep();
  }
  if (inputString.endsWith("A") ) {
    set_current = abs(atof(char1));
    if (set_current > 2.5500)
      set_current = 2.55000;
    Serial.print("New Set Current: ");
    Serial.println(set_current);
    EEPROM_writeAnything(20, set_current);
    inputString="";
    beep();
  }
  if (inputString.endsWith("W") ) {
    set_power = abs(atof(char1));
        if (set_power > 99.99)
      set_power = 99.99;

    Serial.print("New Set Power: ");
    Serial.println(set_power);
    EEPROM_writeAnything(40, set_power);
    inputString="";
    beep();
  }
  if (inputString.endsWith("I") ) {
    print_intervall = abs(atof(char1));
    Serial.print("New Intervall: ");
    Serial.println(print_intervall);
    inputString="";
    beep();
  }
  if (inputString.endsWith("S") ) {
    standby = atof(char1);
    Serial.print("Standby ");
    Serial.println(standby);
    inputString="";
    beep();
  }
  if (inputString.endsWith("M") ) {
    standby = !standby;
    Serial.print("Standby ");
    Serial.println(standby);
    inputString="";
    beep();
  }

  //clear the string:
  return inputString;
}
