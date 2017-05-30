#include <Wire.h>
#include "LiquidCrystal_I2C.h"
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

const uint8_t details_count = 7;

const uint8_t END = 255;

const detail details[] =  {
  { //уголок
    {0, 0, 90, END},
    "ygolok"
  },
  { //конек
    {0, 0, 120, END},
    "konek"
  },
  { //ветровик
    {0, 0, 120, 120, 90, END},
    "vetrovaya"
  },
  { //снегозадержатель
    {0, 0, 120, 90, 0, END},
    "snegozadergatel"
  },
  { //капельник
    {0, 120, END},
    "karnizka"
  },
   { //лобовая
    {0, 90, END},
    "Lobovaya"
  },
  { //парапет
    {0, 0, 120, 120, 90, 90, END},
    "Parapet"
  }
};

State state;

Analog_Button keypad;
Analog_Button endstop_button;

const uint8_t KEYPAD_PIN = A0;
const uint8_t ENDSTOP_PIN = A2;

const uint8_t RELAY_90_PIN = 3;
const uint8_t RELAY_120_PIN = 4;

LiquidCrystal_I2C lcd(0x3F, 16, 2);

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

uint8_t next_angle(uint8_t angle) {
  switch (angle) {
    case 0:
      return 90;
    case 90:
      return 120;
    case 120:
      return END;
    case END:
      return 0;
  }
  return 0;
}

void on_select(State& state) {
  uint8_t old = state.steps[state.step];
  uint8_t new_angle = next_angle(old);
  state.steps[state.step] = new_angle;
  state.text = "Custom";
}

void on_up(State& state) {
  state.step = 0;
  state.detail_n = inc(state.detail_n, details_count - 1);
  state.text = details[state.detail_n].text;
  memcpy(state.steps, details[state.detail_n].steps, 8);
}

void on_down(State& state) {
  state.step = 0;
  state.detail_n = dec(state.detail_n, details_count - 1);
  state.text = details[state.detail_n].text;
  memcpy(state.steps, details[state.detail_n].steps, 8);
}

void on_right(State& state) {
  state.step = inc(state.step, 8 - 1);
}

void on_left(State& state) {
  state.step = dec(state.step, 8 - 1);
}

void on_step(State& state) {
  uint8_t angle = state.steps[state.step];

  if (angle == 0) {
    relays_off();
  } else if (angle == 90) {
    relays_on_90();
  } else if (angle == 120) {
    relays_on_120();
  }

  state.step = inc(state.step, 8 - 1);
  angle = state.steps[state.step];
  if (angle == END) {
    state.step = 0;
  }
}

void printSteps(LiquidCrystal_I2C& lcd, uint8_t steps[]) {
  for (uint8_t i = 0; i < 8; i++) {
    uint8_t angle = steps[i];
    if (angle == 0) {
      lcd.print("0");
    } else  if (angle == 90) {
      lcd.print("1");
    } else  if (angle == 120) {
      lcd.print("2");
    } else if (angle == END) {
      return;
    }
  }
}

void relays_off() {
  digitalWrite(RELAY_90_PIN, HIGH);
  digitalWrite(RELAY_120_PIN, HIGH);
}

void relays_on_90() {
  digitalWrite(RELAY_90_PIN, LOW);
  digitalWrite(RELAY_120_PIN, HIGH);
}

void relays_on_120() {
  digitalWrite(RELAY_90_PIN, HIGH);
  digitalWrite(RELAY_120_PIN, LOW);
}


void refresh(LiquidCrystal_I2C& lcd, State& state) {
  lcd.clear();
  lcd.noBlink();
  printSteps(lcd, state.steps);
  lcd.setCursor(0, 1);
  lcd.print(state.text);
  lcd.setCursor(state.step, 0);
  lcd.blink();
}


void setup() {
  pinMode(RELAY_90_PIN, OUTPUT);
  pinMode(RELAY_120_PIN, OUTPUT);

  relays_off();

  pinMode(KEYPAD_PIN, INPUT);
  pinMode(ENDSTOP_PIN, INPUT);

  state.text = details[state.detail_n].text;
  memcpy(state.steps, details[state.detail_n].steps, 8);

  lcd.begin();
  refresh(lcd, state);
}

void loop() {

  int8_t end_value = digitalRead(ENDSTOP_PIN);
  bool is_f = is_update_button(endstop_button, end_value, millis());
  if (is_f && end_value == 0) {
    on_step(state);
    lcd.setCursor(state.step, 0);
    return;
  }

  if (is_f && end_value == 1) {
    relays_off();
    return;
  }

  int8_t value = buttons_key_keyes(analogRead(KEYPAD_PIN));

  if (is_update_button(keypad, value, millis())) {
    switch (value) {
      case NONE_BUTTON:
        break;
      case RIGHT_BUTTON:
        on_right(state);
        lcd.setCursor(state.step, 0);
        break;
      case LEFT_BUTTON:
        on_left(state);
        lcd.setCursor(state.step, 0);
        break;
      case UP_BUTTON:
        on_up(state);
        refresh(lcd, state);
        break;
      case DOWN_BUTTON:
        on_down(state);
        refresh(lcd, state);
        break;
      case SELECT_BUTTON:
        on_select(state);
        refresh(lcd, state);
        break;
    }

  }

}

