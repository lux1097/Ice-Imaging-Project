/* This sketch below is for controlling Automated ice imager that is used to capture polarized pictures of thin section of ice. Once the start button is pressed the polarizer
 *  rotates 5 degress and the camera captures and then again the polarizer rotates and this sequence repeats until polarizer reaches 180 degree and then it will automatically 
 *  returns to the start position. 
 *  
 *  created 10th November 2023
 *  by Lakshminarayanan Kuruchi Venkatachalam (Lux)
 *  
 *  
 *  Ice Imager - Arduino code
 */
const int buttonPin = 2;
const int SHUTTER_PIN = 5;
bool sequenceRunning = false;
int buttonPressCount = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(buttonPin) == LOW) {
      buttonPressCount++;
      if (buttonPressCount % 2 == 1) {
        startSequence();
      } else {
        stopSequence();
      }
      while (digitalRead(buttonPin) == LOW) {
        // Wait for button release
      }
    }
  }
}

void startSequence() {
  sequenceRunning = true;
  Serial.println("Running Sequence");
  digitalWrite(4, LOW);
  while (sequenceRunning) {
    for (int y = 0; y < 10; y++) {
      for (int x = 0; x < 1422; x++) {
        digitalWrite(3, HIGH);
        delayMicroseconds(50);
        digitalWrite(3, LOW);
        delayMicroseconds(50);

        int buttonState = digitalRead(buttonPin);
        if (buttonState == LOW) {
          delay(50); // Debounce delay
          if (digitalRead(buttonPin) == LOW) {
            buttonPressCount++;
            if (buttonPressCount % 2 == 0) {
              stopSequence();
              return;
            }
            while (digitalRead(buttonPin) == LOW) {
              // Wait for button release
            }
          }
        }
      }
      Serial.print("y=");
      Serial.println(y);
      delay(1000);
      captureImage();
    }
  }
}

void stopSequence() {
  sequenceRunning = false;
  Serial.println("Stopped");
}

void captureImage() {
  Serial.println("Capturing image");
  pinMode(SHUTTER_PIN, OUTPUT);
  digitalWrite(SHUTTER_PIN, LOW);
  delay(200);
  digitalWrite(SHUTTER_PIN, HIGH);
  pinMode(SHUTTER_PIN, INPUT);
  delay(2000);
}
