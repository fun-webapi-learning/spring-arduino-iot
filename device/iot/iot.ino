#define NUM_LEDS 8

#define TWINKLE_MODE 0
#define NUMBER_MODE 1
#define METER_MODE 2

#define TWINKLE_MAX 500
#define NUMBER_MAX 255
#define METER_MAX 7

char mode = 0;
int ledPins[] = {13, 12, 11, 10, 9, 8, 7, 6};


int num = 0;
int pos = 0;
int time = 500;

void setup() {
  Serial.begin(9600);
  for (int i=0; i<NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void serialEvent() {
  
  byte state = 0;
  int n = 0;
  while (Serial.available()) {
    char ch = Serial.read();
    switch (state) {
      
      case 0:
      if (ch == 'g') {
        state = 4;
      } else if (ch == 's') {
        state = 1;
      } else if (ch == 'm') {
        state = 3;
      }
      break;
      
      case 1:
      if (isDigit(ch)) {
        n *= 10;
        n += (int)(ch - '0');
      } else if (ch == ';') {
        if (n >=0 && n <= (mode == TWINKLE_MODE ? TWINKLE_MAX : (mode == NUMBER_MODE ? NUMBER_MAX : METER_MAX))) {
          num = n;
        }
        state = 2;
      }
      break;
      
      case 2:
      break;
      
      case 3:
      if (ch == 'm') {
        mode = METER_MODE;
      } else if (ch == 'n') {
        mode = NUMBER_MODE;
      } else if (ch == 't') {
        mode = TWINKLE_MODE;
      }
      state = 2;
      break;
      
      case 4:
      if (ch == 'v') {
        // output current value
        if (mode == TWINKLE_MODE) {
          Serial.println(time);
        } else if (mode == NUMBER_MODE) {
          Serial.println(num);
        } else if (mode == METER_MODE) {
          Serial.println(pos);
        }
        state = 2;
      } else if (ch == 'm') {
        // output current mode
        Serial.println((char)(mode + '0'));
        state = 2;
      }
      break;
      
      default:
      break;
    }
  }
}



void loop() {
  if (mode == TWINKLE_MODE) {
    int n = random(256);
    for (int i=NUM_LEDS-1; i >= 0; i--) {
      if ((n & (1 << i)) != 0) {
        digitalWrite(ledPins[i], HIGH);
      } else {
        digitalWrite(ledPins[i], LOW);
      }  
    }
    delay(time);    
  } else if (mode == NUMBER_MODE) {
    for (int i=NUM_LEDS-1; i >= 0; i--) {
      if ((num & (1 << i)) != 0) {
        digitalWrite(ledPins[i], HIGH);
      } else {
        digitalWrite(ledPins[i], LOW);
      }
    }
  } else if (mode == METER_MODE) {
    for (int i=0; i < NUM_LEDS; i++) {
      if (i == pos) {
        digitalWrite(ledPins[i], HIGH);
      } else {
        digitalWrite(ledPins[i], LOW);
      }
    }
  }
}
