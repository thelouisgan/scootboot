#include <SoftwareSerial.h>

const int MOTOR_PWM1_PIN = 7;
const int MOTOR_DIR1_PIN = 6;
const int MOTOR_PWM2_PIN = 4;
const int MOTOR_DIR2_PIN = 3;

// ELRS rx
SoftwareSerial elrsSerial(10, 9); // RX-D10   TX-D9

int throttleValue = 0;
int auxValue = 0;
bool motorsEnabled = false;

unsigned long lastRXUpdate = 0;
const unsigned long RX_TIMEOUT = 1000;

const int MIN_MOTOR_SPEED = 0;
const int MAX_MOTOR_SPEED = 180;  // max->255
const int DEADBAND = 50;

// CRSF protocol values
uint16_t channelData[16];

void setup() {
  Serial.begin(115200);
  elrsSerial.begin(420000);

  pinMode(MOTOR_PWM1_PIN, OUTPUT);
  pinMode(MOTOR_DIR1_PIN, OUTPUT);
  pinMode(MOTOR_PWM2_PIN, OUTPUT);
  pinMode(MOTOR_DIR2_PIN, OUTPUT);

  stopMotors();
  
  Serial.println("SCOOTBOOT active");
  Serial.println("Waiting for RC signal...");
}

void loop() {
  readCRSF();
  
  // Signal loss check
  if (millis() - lastRXUpdate > RX_TIMEOUT) {
    motorsEnabled = false;
    stopMotors();
    Serial.println("SIGNAL LOST, MOTORS DISABLED");
    delay(100);
    return;
  }
  
  if (motorsEnabled) {
    controlMotors();
  } else {
    stopMotors();
  }

  //debug
  if (millis() % 200 == 0) {
    Serial.print("Throttle: ");
    Serial.print(throttleValue);
    Serial.print(" | Aux: ");
    Serial.print(auxValue);
    Serial.print(" | Enabled: ");
    Serial.println(motorsEnabled ? "YES" : "NO");
  }
  
  delay(20);
}

void readCRSF() {
  static uint8_t buffer[64];
  static uint8_t bufferIndex = 0;
  
  while (elrsSerial.available()) {
    uint8_t byte = elrsSerial.read();
    
    if (bufferIndex == 0 && byte != 0xC8) {
      continue;
    }
    
    buffer[bufferIndex++] = byte;
    
    if (bufferIndex >= 2 && bufferIndex >= buffer[1] + 2) {
      if (buffer[2] == 0x16) { // RC channels frame
        parseCRSFChannels(&buffer[3], buffer[1] - 2);
        lastRXUpdate = millis();
      }
      bufferIndex = 0;
    }
    
    if (bufferIndex >= 64) {
      bufferIndex = 0;
    }
  }
}

void parseCRSFChannels(uint8_t* payload, uint8_t length) {
  if (length >= 22) {
    channelData[0] = ((payload[0] | payload[1] << 8) & 0x07FF);
    channelData[1] = ((payload[1] >> 3 | payload[2] << 5) & 0x07FF);
    channelData[2] = ((payload[2] >> 6 | payload[3] << 2 | payload[4] << 10) & 0x07FF);
    channelData[3] = ((payload[4] >> 1 | payload[5] << 7) & 0x07FF);
    
    throttleValue = map(channelData[0], 172, 1811, -255, 255);
    auxValue = map(channelData[1], 172, 1811, 1000, 2000);
    
    motorsEnabled = (auxValue > 1500);
  }
}

void controlMotors() {
  int motorSpeed = 0;
  bool forward = true;
  
  if (abs(throttleValue) < DEADBAND) {
    motorSpeed = 0;
  } else {
    if (throttleValue > 0) {
      forward = true;
      motorSpeed = map(throttleValue, DEADBAND, 255, MIN_MOTOR_SPEED, MAX_MOTOR_SPEED);
    } else {
      forward = false;
      motorSpeed = map(abs(throttleValue), DEADBAND, 255, MIN_MOTOR_SPEED, MAX_MOTOR_SPEED/2);
    }
  }
  
  digitalWrite(MOTOR_DIR1_PIN, forward ? HIGH : LOW);
  digitalWrite(MOTOR_DIR2_PIN, forward ? HIGH : LOW);
  
  analogWrite(MOTOR_PWM1_PIN, motorSpeed);
  analogWrite(MOTOR_PWM2_PIN, motorSpeed);
}

void stopMotors() {
  analogWrite(MOTOR_PWM1_PIN, 0);
  analogWrite(MOTOR_PWM2_PIN, 0);
  digitalWrite(MOTOR_DIR1_PIN, LOW);
  digitalWrite(MOTOR_DIR2_PIN, LOW);
}

void emergencyStop() {
  motorsEnabled = false;
  stopMotors();
  Serial.println("EMERGENCY STOP ACTIVATED");
  
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
}