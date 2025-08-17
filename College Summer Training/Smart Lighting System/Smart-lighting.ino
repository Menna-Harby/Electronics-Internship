#define ldrPin A0
#define ledPin 9
#define buttonPin 2

bool autoMode = true;
int manualLevel = 0;
const int levels[] = {0, 64, 128, 192, 255}; // 0%, 25%, 50%, 75%, 100%

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool lastButtonState = HIGH;
bool buttonState = HIGH;

unsigned long lastActivityTime = 0;
unsigned long timeoutDuration = 120000; // 2 minutes
bool isSystemActive = true;
int lastLDRValue = 0;
const int ldrChangeThreshold = 20;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Active LOW
  Serial.begin(9600);
  lastActivityTime = millis();
  lastLDRValue = analogRead(ldrPin);
}

void loop() {

// ---------------Button Press Detection with Debouncing------------------
  int reading = digitalRead(buttonPin);

  // Debounce logic
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        // Button press detected
        lastActivityTime = millis();
        isSystemActive = true;

        if (autoMode) {
          autoMode = false; // Switch to manual mode
          manualLevel = 1;  // Start at 25%
        } else {
          // Cycle through manual brightness levels
          manualLevel = (manualLevel + 1) % 5;
          if (manualLevel == 0) {
            autoMode = true; // If OFF (0%), return to auto mode
          }
        }
      }
    }
  }

  lastButtonState = reading;
  
  // ------------------Ambient Light Change Detection--------------------

  // Detect LDR changes only if system is active
  if (isSystemActive && autoMode) {
    int ldrValue = analogRead(ldrPin);
    if (abs(ldrValue - lastLDRValue) > ldrChangeThreshold) {
      lastActivityTime = millis(); // Significant ambient change
      lastLDRValue = ldrValue;
    }
  }

  // -------------------------Inactivity Timeout Check---------------
  if (isSystemActive && (millis() - lastActivityTime > timeoutDuration)) {
    analogWrite(ledPin, 0); // Turn off LED
    isSystemActive = false;
    Serial.println("System timed out. LED off.");
  }
  
  // --------------------------Brightness Control-----------------------

  if (isSystemActive) {
    if (autoMode) {
      int ldrValue = analogRead(ldrPin); // 0 (bright) to 1023 (dark)
      int brightness = map(ldrValue, 1023, 0, 0, 255); // Invert mapping
      analogWrite(ledPin, brightness);
      Serial.print("Auto Brightness: ");
      Serial.println(brightness);
    } else {
      analogWrite(ledPin, levels[manualLevel]);
      Serial.print("Manual Brightness: ");
      Serial.println(levels[manualLevel]);
    }
  }

  delay(50);
}