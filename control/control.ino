//#include <LiquidCrystal.h>
#include <Wire.h>
#include "LiquidCrystal_I2C.h"

#include "buttons.h"

LiquidCrystal_I2C lcd(0x3F, 16, 2);

//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

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
    {0, 0, 120, 90, 0, END},
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
  state.detail_n = dec(state.detail_n, details_count - 1);
  state.text = details[state.detail_n].text;
  memcpy(state.steps, details[state.detail_n].steps, 8);
}

void onDown() {
  state.step = 0;
  state.detail_n = inc(state.detail_n, details_count - 1);
  state.text = details[state.detail_n].text;
  memcpy(state.steps, details[state.detail_n].steps, 8);
}


void onRight() {
  state.step = inc(state.step, 8 - 1);
}

void onLeft() {
  state.step = dec(state.step, 8 - 1);
}

void onStep() {
  uint8_t angel = state.steps[state.step];
  if (angel == 0) {
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  } else if (angel == 90) {
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  } else if (angel == 120) {
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
  }

  state.step = inc(state.step, 8 - 1);
  angel = state.steps[state.step];
  if (angel == 255) {
    state.step = 0;
  }
}



//void printSteps(LiquidCrystal lcd, uint8_t steps[]) {
void printSteps(LiquidCrystal_I2C& lcd, uint8_t steps[]) {
  lcd.setCursor(0, 0);
  for (uint8_t i = 0; i < 8; i++) {
    uint8_t angle = steps[i];
    if (angle == 0) {
      lcd.print("0");
    } else  if (angle == 90) {
      lcd.print("1");
    } else  if (angle == 120) {
      lcd.print("2");
    } else if (angle == 255) {
      return;
    }
  }
}

void onClear() {
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
}


//void refresh(LiquidCrystal lcd, State state) {
void refresh(LiquidCrystal_I2C& lcd, State state) {

  lcd.clear();
  lcd.noBlink();
  printSteps(lcd, state.steps);
  lcd.setCursor(0, 1);
  lcd.print(state.text);
  lcd.setCursor(state.step, 0);
  lcd.blink();
}

Analog_Button a_button;
Analog_Button end_button;

void setup() {
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

  pinMode(A2, INPUT);

  //  lcd.begin(16, 2);

  //  Serial.begin(115200);

  lcd.begin();

  state.text = details[state.detail_n].text;
  memcpy(state.steps, details[state.detail_n].steps, 8);
  lcd.setCursor(0, 0);
  printSteps(lcd, state.steps);
  lcd.setCursor(0, 1);
  lcd.print(state.text);
  lcd.setCursor(0, 0);
  lcd.blink();
}


void loop() {

  int8_t  end_value = digitalRead(A2);
  bool is_f = is_update_button(end_button, end_value, millis());
  if (is_f && end_value == 0) {
    onStep();
    lcd.setCursor(state.step, 0);
    return;
  }

  
  if (is_f && end_value == 1) {
    onClear();
    return;
  }


    int8_t value = buttons_key_keyes(analogRead(A0));
//  int8_t value = buttons_key_robodyn(analogRead(A0));

  if (!is_update_button(a_button, value, millis())) {
    return ;
  }

  switch (value) {
    case NONE_BUTTON:
      break;
    case RIGHT_BUTTON:
      onRight();
      lcd.setCursor(state.step, 0);

//      onStep();
//      lcd.setCursor(state.step, 0);

      break;
    case LEFT_BUTTON:
      onLeft();
      lcd.setCursor(state.step, 0);
      break;
    case UP_BUTTON:
      onUp();
      refresh(lcd, state);
      break;
    case DOWN_BUTTON:
      onDown();
      refresh(lcd, state);
      break;
    case SELECT_BUTTON:
      onSelect();
      refresh(lcd, state);
      break;
  }

}

