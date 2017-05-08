#include <LiquidCrystal.h>

const uint8_t RIGHT_BUTTON = 0;
const uint8_t LEFT_BUTTON = 1;
const uint8_t UP_BUTTON = 2;
const uint8_t DOWN_BUTTON = 3;
const uint8_t SELECT_BUTTON = 4;
const uint8_t NONE_BUTTON = -1;


int8_t buttons_key(int value) {
  if (value < 10)   return RIGHT_BUTTON;
  if (value < 140)   return UP_BUTTON;
  if (value < 320)   return DOWN_BUTTON;
  if (value < 490)   return LEFT_BUTTON;
  if (value < 730)   return SELECT_BUTTON; 
  return NONE_BUTTON; 
}


const LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


void setup() {
  //уменьшить яркость lcd, 10 порт
  analogWrite(10, 50);
  lcd.begin(16, 2);
  lcd.clear();
}



int pinIn     = A0;
int keyValue  =  0; 

void loop() {
  uint16_t newKeyValue = GetKeyValue(); // Получаем актуальное состояние кнопок с коррекцией дребезга

  if (keyValue != newKeyValue) {  // Если новое значение не совпадает со старым - реагируем на него
    keyValue = newKeyValue;       // Актуализируем переменную хранения состояния
    if (keyValue < 1010) {           // Если значение больше 0, значит кнопка нажата
//      Serial.println("Key pressed: " + String(keyValue));   
      lcd.clear();   
      lcd.setCursor(0, 0);
      lcd.print(keyValue);
    }else {                        // Если 0, то состояние покоя
      lcd.setCursor(0, 1);
      lcd.print(" no          ");
    }
  }
}

uint16_t GetKeyValue() {         // Функция устраняющая дребезг
  static uint16_t oldKeyValue; // Переменная для хранения предыдущего значения состояния кнопок
  static long  lastChange;  // Переменная для хранения времени последнего изменения состояния
  int actualKeyValue = analogRead(pinIn);  // Получаем актуальное состояние

  if ((actualKeyValue != oldKeyValue) && (millis() - lastChange > 200)) { // Пришло новое значение, и с последнего изменения прошло достаточно времени
    oldKeyValue = actualKeyValue; // Запоминаем новое значение
    lastChange = millis();        // Обнуляем таймер
  }
  return oldKeyValue;          // Отправляем старое, либо уже модифицированное новое значение

}

//void loop() {
//  lcd.clear();
//  lcd.setCursor(0, 0);
//  lcd.print("KEY ");
//
//  uint16_t k = buttons_key(analogRead(A0));
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

