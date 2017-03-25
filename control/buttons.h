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



const byte angle_120_sprite[8] = {
  0b11110,
  0b11100,
  0b11000,
  0b10000,
  0b11000,
  0b11100,
  0b11110,
  0b11111
};

const byte angle_90_sprite[8] = {
  0b11111,
  0b11110,
  0b11100,
  0b11000,
  0b10000,
  0b11000,
  0b11100,
  0b11110
};



//const LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//void setup() {
//  //уменьшить яркость lcd, 10 порт
//  analogWrite(10, 50);
//
//  lcd.begin(16, 2);
//
//  lcd.createChar(1, angle_90_sprite);
//  lcd.createChar(2, angle_120_sprite);
//
//
//  lcd.clear();
//}
//
//
//
//
//void loop() {
//  lcd.clear();
//  lcd.setCursor(0, 0);
//  lcd.print("KEY ");
//
//  uint8_t k = buttons_key(analogRead(A0));
//  switch (k) {
//    case NONE_BUTTON:
//      break;
//    case RIGHT_BUTTON:
//      lcd.write(201);
//      break;
//    case UP_BUTTON:
//      lcd.write(202);
//      break;
//    case DOWN_BUTTON:
//      lcd.write(203);
//      break;
//    case LEFT_BUTTON:
//      lcd.write(204);
//      break;
//    case SELECT_BUTTON:
//      lcd.write(205);
//      break;
//
//  }
//  delay(125);
//}

#endif
