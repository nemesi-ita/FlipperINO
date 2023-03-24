#include <flipperpiGUI.h>

#define bzr 9 // Buzzer
#define dim 6
int B[dim] = {2, 3, 4, 5, 6, 7}; // Buttons
int RGB[3] = {10, 11, 12};       // RGBs

int exeFlag = 0; // Flag per capire stato di esecuzione

// Program Fuctionality
int flag = 0;

void defRGB() {
  // Default active color (Blue)
  analogWrite(RGB[0], 0);
  analogWrite(RGB[1], 112);
  analogWrite(RGB[2], 255);
}

void setup() {
  lcd.init(); // initialize the lcd
  lcd.backlight();
  Serial.begin(9600);

  // Set RGBs LED mode
  for (int i = 0; i < 3; i++) {
    pinMode(RGB[i], OUTPUT);
  }

  // Set Buttons mode
  for (int i = 0; i < dim; i++) {
    pinMode(B[i], INPUT);
  }
  pinMode(bzr, OUTPUT);

  defRGB();
  // Benvenuto
  setGui("B");
}

void buzz(int modType) {
  switch (modType) {
  case -1:
    tone(bzr, 900);
    delay(10);
    noTone(bzr);
    delay(200);
  case 1: // Executing
    tone(bzr, 1000);
    delay(10);
    noTone(bzr);
    delay(200);
  case 2: // Error
    tone(bzr, 1200);
    delay(10);
    noTone(bzr);
    delay(1500);
  }
}

void setColor(unsigned char red, unsigned char green, unsigned char blue) {
  analogWrite(RGB[0], red);
  analogWrite(RGB[1], green);
  analogWrite(RGB[2], blue);
}

void blink() {
  for (int i = 0; i < 2; i++) {
    analogWrite(RGB[0], 0);
    analogWrite(RGB[1], 0);
    analogWrite(RGB[2], 0);
    delay(25);
    analogWrite(RGB[0], 0);
    analogWrite(RGB[1], 112);
    analogWrite(RGB[2], 255);
    delay(25);
  }
}

void status(int modType) {
  switch (modType) {

  case 0: // Green
    setColor(0, 255, 0);
    break;

  case 1: // Yellow
    setColor(255, 215, 0);
    buzz(modType);
    //setGui("X");
    break;

  case 2: // Red
    setColor(255, 0, 252);
    buzz(modType);
    //setGui("E");
    // Wait for an input
    int OKbtn = digitalRead(B[4]); // OK
    int RSbtn = digitalRead(B[5]); // back

    if (OKbtn == HIGH) {
      // RERUN
    }
    if (RSbtn == HIGH) {
      //setGui("H");
    }
    break;

  case -1:
    blink();
    buzz(modType);
    break;
  default:
    defRGB();
    break;
  }
  defRGB();
}

void loop() {
  int B1State = digitalRead(B[0]); // up
  int B2State = digitalRead(B[1]); // down
  int B3State = digitalRead(B[2]); // left
  int B4State = digitalRead(B[3]); // right
  int B5State = digitalRead(B[4]); // OK
  int B6State = digitalRead(B[5]); // back

  int modType = NULL; // Mod type (Err, OK, Executing, ...) for buzz & status
  /*
  Description of states:
      - 0  |  Green: OK
      - 1  |  Yellow: EXECUTING
      - 2  |  Red: ERROR
      - -1 |  Blink: Moving trough the Iface
  */

  if (B1State == HIGH && flag == 0) {
    Serial.println("Click1");
    delay(600);
    modType = -1;
    status(modType);
    flag = 1;
  } else if (B1State == LOW && flag == 1) {
    flag = 0;
  }

  if (B2State == HIGH && flag == 0) {
    Serial.println("Click2");
    delay(600);
    modType = -1;
    status(modType);
    flag = 1;
  } else if (B2State == LOW && flag == 1) {
    flag = 0;
  }

  if (B3State == HIGH && flag == 0) {
    Serial.println("Click3");
    delay(600);
    modType = -1;
    status(modType);
    flag = 1;
  } else if (B3State == LOW && flag == 1) {
    flag = 0;
  }

  if (B4State == HIGH && flag == 0) {
    Serial.println("Click4");
    delay(600);
    modType = -1;
    status(modType);
    flag = 1;
  } else if (B4State == LOW && flag == 1) {
    flag = 0;
  }

  if (B5State == HIGH && flag == 0) {
    Serial.println("Ok");
    delay(600);
    modType = -1;
    status(modType);
    flag = 1;
  } 
  else if (B5State == LOW && flag == 1) {
    flag = 0;
  }

  if (B6State == HIGH && flag == 0) {
    Serial.println("Back");
    delay(600);
    modType = -1;
    status(modType);
    flag = 1;
  } 
  else if (B6State == LOW && flag == 1) {
    flag = 0;
  }
}
