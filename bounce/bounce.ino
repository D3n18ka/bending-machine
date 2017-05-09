
const int8_t NONE_BUTTON = -1;
const int8_t RIGHT_BUTTON = 0;
const int8_t LEFT_BUTTON = 1;
const int8_t UP_BUTTON = 2;
const int8_t DOWN_BUTTON = 3;
const int8_t SELECT_BUTTON = 4;


const uint8_t NONE_B = 0;
const uint8_t CHANGED_B = 1;

int8_t buttons_key(uint16_t value) {
  if (value < 10)   return RIGHT_BUTTON;
  if (value < 140)   return UP_BUTTON;
  if (value < 320)   return DOWN_BUTTON;
  if (value < 490)   return LEFT_BUTTON;
  if (value < 730)   return SELECT_BUTTON;
  return NONE_BUTTON;
}

const char* key_text(int8_t value) {
  if (value == RIGHT_BUTTON)   return "right";
  if (value == LEFT_BUTTON)   return "left";
  if (value == UP_BUTTON)   return "up";
  if (value == DOWN_BUTTON)   return "down";
  if (value == SELECT_BUTTON)   return "select";
  return "";
}

typedef struct Analog_Button {
  int8_t last_button;
  int8_t button_state;
  unsigned long lastDebounceTime;
} Analog_Button;


Analog_Button a_button;



int8_t update_button( struct Analog_Button *b, int8_t value, unsigned long ts)
{
  if (b->last_button != value) {
    b->lastDebounceTime = ts;
  }
  b->last_button = value;


  if ((ts - b->lastDebounceTime) < 10) {
    return;
  }

  if (value != b->button_state) {
    b->button_state = value;
    Serial.println(key_text(value));
  }

}

int8_t is_update_button( struct Analog_Button *b, int8_t value, unsigned long ts)
{
  if (b->last_button != value) {
    b->lastDebounceTime = ts;
  }

  b->last_button = value;

  if ((ts - b->lastDebounceTime) < 10) {
    return NONE_B;
  }

  if (b->button_state != value) {
    b->button_state = value;
    return CHANGED_B;
  }

  return NONE_B;
}




void setup() {
  Serial.begin(115200);
}


void loop() {
  int8_t value = buttons_key(analogRead(A0));
  if(is_update_button(&a_button, value, millis())==CHANGED_B){
    Serial.println(key_text(value));
   }
}


