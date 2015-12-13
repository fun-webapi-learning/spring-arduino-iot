#define NUM_LEDS 8

int ledPins[] = {13, 12, 11, 10, 9, 8, 7, 6};

int number = 0;

void setup() {
  Serial.begin(9600);
  for (int i=0; i<NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  randomSeed(analogRead(A0)); 
}

void loop() {
  number = random(256); 
  for (int i=7; i >= 0; i--) {
    if ((number & (1 << i)) != 0) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
  
  
  delay(random(analogRead(A1)));
}
