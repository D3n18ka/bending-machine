#ifndef BUTTONS_H_
#define BUTTONS_H_

const uint8_t RIGHT_BUTTON = 0;
const uint8_t LEFT_BUTTON = 1;
const uint8_t UP_BUTTON = 2;
const uint8_t DOWN_BUTTON = 3;
const uint8_t SELECT_BUTTON = 4;
const uint8_t NONE_BUTTON = -1;


uint8_t buttons_key(int value) {
  if (value < 10)   return RIGHT_BUTTON;
  if (value < 140)   return UP_BUTTON;
  if (value < 320)   return DOWN_BUTTON;
  if (value < 490)   return LEFT_BUTTON;
  if (value < 730)   return SELECT_BUTTON; 
  return NONE_BUTTON; 
}

uint8_t buttons_key_robodyn(int value) {
  if (value < 10)   return RIGHT_BUTTON;
  if (value < 160)   return UP_BUTTON;
  if (value < 340)   return DOWN_BUTTON;
  if (value < 520)   return LEFT_BUTTON;
  if (value < 760)   return SELECT_BUTTON; 
  return NONE_BUTTON; 
}

uint8_t buttons_key_keyes(int value) {
  if (value < 10)   return LEFT_BUTTON;
  if (value < 160)   return UP_BUTTON;
  if (value < 340)   return DOWN_BUTTON;
  if (value < 520)   return RIGHT_BUTTON;
  if (value < 760)   return SELECT_BUTTON; 
  return NONE_BUTTON; 
}

#endif
