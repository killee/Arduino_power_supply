
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
#define LIST_MAX 10
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'V'},
  {'4', '5', '6', 'A'},
  {'7', '8', '9', 'W'},
  {'.', '0', '#', 'M'}
};


//byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
//byte colPins[COLS] = {3, 2, 1, 0}; //connect to the column pinouts of the keypad
byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad
//byte rowPins[ROWS] = {22, 24, 26, 28}; //connect to the row pinouts of the keypad
//byte colPins[COLS] = {30, 32, 34, 36}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
String input_buffer_keypad = "";

void setup_keypad(void) {
  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad

}

char keypad_getKey(void) {
  return keypad.getKey();
}

void delete_input_buffer_keypad(void){
  input_buffer_keypad = "";
}

// Taking care of some special events.
void keypadEvent(KeypadEvent key) {
  for (int i = 0; i < LIST_MAX; i++) // Scan the whole key list.
  {
    if ( keypad.key[i].stateChanged )   // Only find keys that have changed state.
    {
      /*
      switch (keypad.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
        case PRESSED:
          msg = " PRESSED.";
          break;
        case HOLD:
          msg = " HOLD.";
          break;
        case RELEASED:
          msg = " RELEASED.";
          break;
        case IDLE:
          msg = " IDLE.";
      }
      Serial.print("Key ");
      Serial.print(keypad.key[i].kchar);
      Serial.println(msg);
      */
      if (keypad.key[i].kstate == PRESSED) {
        if (keypad.key[i].kchar == '#') {
          input_buffer_keypad = input_buffer_keypad.substring(0, (input_buffer_keypad.length() - 1));
        } else {
          input_buffer_keypad = input_buffer_keypad + keypad.key[i].kchar;
          input_buffer_keypad = manage_input(input_buffer_keypad);
        }
        print_display_input_buffer(input_buffer_keypad);
      }
    }
  }
}

