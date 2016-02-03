// Node.js/Express RGB LED
// Written by Andrew Fake
// 2/1/16

// Pin mapping declarations
const int RED = 6;
const int GREEN = 3;
const int BLUE = 5;
const int POWER = 11;
int voltage = LOW;

// Values for colors
int redValue = 255;
int greenValue= 0;
int blueValue = 255;

// Temp Variables
int tR;
int tG;
int tB;
int tV;

// Serial Byte
int incomingByte;

void setup () {
  // Configure Pins
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(POWER, OUTPUT);

  // Initialize serial connection
  Serial.begin(9600);
  Serial.setTimeout(2000);
}

void setColor(int r, int g, int b) {
  // Must invert values to match the color
  redValue = 255 - r;
  greenValue = 255 - g;
  blueValue = 255 - b;
}

void parseColors() {
  char hexstring[6];
  Serial.readBytes(hexstring, 6);
  long number = (long) strtol( &hexstring[0], NULL, 16);
  int r = number >> 16;
  int g = number >> 8 & 0xFF;
  int b = number & 0xFF;
  setColor(r, g, b);
  voltage = HIGH;
}

void settingsBackup() {
  tR = redValue;
  tG = greenValue;
  tB = blueValue;
  tV = digitalRead(POWER);
}

void settingsRestore() {
  redValue = tR;
  greenValue = tG;
  blueValue = tB;
  voltage = tV;
}

void executeAlert() {
  // 1. Backup Colors and Voltage
  settingsBackup();
  
  // 2. Parse out Number
  char c[1];
  Serial.readBytes(c, 1);
  int blinkAmount = c[0] - '0';

  // 3. Set LED to Color Pending (remove code from buffer)
  parseColors();
  writeColors();

  // 4. Blink Loop (voltage will start HIGH)
  for (int i = 0; i < blinkAmount; i++) {
    delay(230);
    digitalWrite(POWER, !tV);
    delay(230);
    digitalWrite(POWER, tV);
  }

  // 5. Restore settings
  settingsRestore();
  
}

void sendStatus() {
  // Send back information regarding LED state
  if (digitalRead(POWER) == HIGH) {
    Serial.write("LED is ON\n");
  } else {
    Serial.write("LED is OFF\n");
  }
}

void writeColors() {
  analogWrite(RED, redValue);
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);
}

void loop () {
  digitalWrite(POWER, voltage);  //Power LED
  writeColors(); // Write the RGB values to the pins
  
   // Detect serial communication
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    // If the incoming byte is 'H' turn on LED
    // Else if the byte is 'L' turn it off
    switch (incomingByte) {
      case 'H': // Turn on LED
        voltage = HIGH;
        break;
      case 'L': // Turn off LED
        voltage = LOW;
        break;
      case 'S': // Return status of LED
        sendStatus();
        break;
      case 'I': // Display flash alert. e.g. I500ff38
        executeAlert();
        break;
      case '#': // Pure color change e.g. #e45aa6
        parseColors();
        break;
    }
  }
}