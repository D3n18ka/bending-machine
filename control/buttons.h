#ifndef BUTTONS_H_
#define BUTTONS_H_

const int8_t NONE_BUTTON = -1;
const int8_t RIGHT_BUTTON = 0;
const int8_t LEFT_BUTTON = 1;
const int8_t UP_BUTTON = 2;
const int8_t DOWN_BUTTON = 3;
const int8_t SELECT_BUTTON = 4;


int8_t buttons_key(int value) {
  if (value < 10)   return RIGHT_BUTTON;
  if (value < 140)   return UP_BUTTON;
  if (value < 320)   return DOWN_BUTTON;
  if (value < 490)   return LEFT_BUTTON;
  if (value < 730)   return SELECT_BUTTON;
  return NONE_BUTTON;
}

int8_t buttons_key_robodyn(int value) {
  if (value < 10)   return RIGHT_BUTTON;
  if (value < 160)   return UP_BUTTON;
  if (value < 340)   return DOWN_BUTTON;
  if (value < 520)   return LEFT_BUTTON;
  if (value < 760)   return SELECT_BUTTON;
  return NONE_BUTTON;
}

int8_t buttons_key_keyes(int value) {
  if (value < 10)   return LEFT_BUTTON;
  if (value < 160)   return UP_BUTTON;
  if (value < 340)   return DOWN_BUTTON;
  if (value < 520)   return RIGHT_BUTTON;
  if (value < 760)   return SELECT_BUTTON;
  return NONE_BUTTON;
}

typedef struct Analog_Button {
  int8_t last;
  int8_t state;
  unsigned long ts;
} Analog_Button;

bool is_update_button( struct Analog_Button *b, int8_t value, unsigned long ts)
{
  if (b->last != value) {
    b->ts = ts;
  }

  b->last = value;

  if ((ts - b->ts) < 20) {
    return false;
  }

  if (b->state != value) {
    b->state = value;
    return true;
  }

  return false;
}




#endif
