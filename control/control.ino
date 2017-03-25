#include <LiquidCrystal.h>

#include "buttons.h"

typedef struct {
  const uint8_t steps[8];
  const char* text;
} detail;


typedef struct {
  uint8_t detail_n;
  uint8_t step;
  uint8_t steps[8];
  const   char *text;
} State;


const uint8_t details_count = 5;

const uint8_t END = 255;


const detail details[] =  {
  { //уголок
    {0, 0, 90, END},
    "Angle"
  },
  { //конек
    {0, 0, 120, END},
    "Ridge"
  },
  { //ветровик
    {0, 0, 120, 120, 90, END},
    "Wind strip"
  },
  { //снегозадержатель
    {0, 0, 120, 90, END},
    "Snow barrier"
  },
  { //капельник
    {0, 120, END},
    "Eaves"
  }
};


State state;


uint8_t inc(uint8_t value, uint8_t max) {
  ++value;
  if (value > max) {
    return 0;
  } else {
    return value;
  }
}

uint8_t dec(uint8_t value, uint8_t max) {
  value--;
  if (value == 255) {
    return max;
  } else {
    return value;
  }
}

void onSelect() {
  uint8_t old = state.steps[state.step];

  uint8_t new_angle = 0;
  if (old == 0 ) {
    new_angle  = 90;
  } else if (old == 90) {
    new_angle = 120;
  } else if (old == 120) {
    new_angle  = END;
  } else if (old == END) {
    new_angle = 0;
  }

  state.steps[state.step] = new_angle;
  state.text = "Custom";
}


void onUp() {
  state.step = 0;
  state.detail_n = inc(state.detail_n, details_count - 1);
  state.text = details[state.detail_n].text;
  memcpy(state.steps, details[state.detail_n].steps, 8);
}

void onDown() {
  state.step = 0;
  state.detail_n = dec(state.detail_n, details_count - 1);
  state.text = details[state.detail_n].text;
  memcpy(state.steps, details[state.detail_n].steps, 8);
}


void onRight() {
  state.step = inc(state.step, 8 - 1) ;
}

void onLeft() {
  state.step = dec(state.step, 8 - 1) ;
}


void setup() {
  Serial.begin(115200);
  state.text = details[state.detail_n].text;
  memcpy(state.steps, details[state.detail_n].steps, 8);
}


void loop() {
  uint8_t k = buttons_key(analogRead(A0));
  switch (k) {
    case NONE_BUTTON:
      break;
    case RIGHT_BUTTON:
      onRight();
      break;
    case LEFT_BUTTON:
      onLeft();
      break;
    case UP_BUTTON:
      onUp();
      break;
    case DOWN_BUTTON:
      onDown();
      break;
    case SELECT_BUTTON:
      onSelect();
      break;
  }

  Serial.print(state.step);
  Serial.print(" ");

  Serial.println(state.detail_n);

  Serial.print("[");
  Serial.print(state.steps[0]);
  Serial.print(" ");
  Serial.print(state.steps[1]);
  Serial.print(" ");
  Serial.print(state.steps[2]);
  Serial.print(" ");
  Serial.print(state.steps[3]);
  Serial.print(" ");
  Serial.print(state.steps[4]);
  Serial.print(" ");
  Serial.print(state.steps[5]);
  Serial.print(" ");
  Serial.print(state.steps[6]);
  Serial.print(" ");
  Serial.print(state.steps[7]);
  Serial.println("]");

  Serial.println(state.text);
  delay(250);
}

