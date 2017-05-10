
typedef struct dda_Button {
  int8_t last;
  int8_t state;
  unsigned long ts;
} dda_Button;

bool is_update_button( struct dda_Button *b, int8_t value, unsigned long ts)
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

dda_Button button;


void setup() {
  Serial.begin(115200);
  pinMode(A1, INPUT);

}

void loop() {
  int8_t  value = digitalRead(A1);
  bool is_f = is_update_button(&button, value, millis());
  if (is_f && value == 0) {
    Serial.println("down");
  }

}
