// RGB-LED Pins
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

// Button Pins
const int RED_BUTTON = 2;
const int GREEN_BUTTON = 3;
const int BLUE_BUTTON = 4;

// Variablen
int ledState = 0; // 0 = aus, 1 = rot, 2 = grün, 3 = blau
int lastButtonState[3] = {HIGH, HIGH, HIGH};
int currentButtonState[3] = {HIGH, HIGH, HIGH};
unsigned long debounceDelay = 50; // Entprellungszeit in ms
unsigned long lastDebounceTime[3] = {0, 0, 0};

void setup() {
  // RGB-LED Pins als OUTPUT
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  // Button Pins als INPUT_PULLUP
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);
  
  // LEDs ausschalten
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
}

void loop() {
  // Alle 3 Taster prüfen
  checkButton(0, RED_BUTTON, RED_PIN);
  checkButton(1, GREEN_BUTTON, GREEN_PIN);
  checkButton(2, BLUE_BUTTON, BLUE_PIN);
}

void checkButton(int buttonIndex, int buttonPin, int ledPin) {
  int reading = digitalRead(buttonPin);
  
  // Entprellung: Zustand hat sich geändert
  if (reading != lastButtonState[buttonIndex]) {
    lastDebounceTime[buttonIndex] = millis();
  }
  
  // Debounce-Zeit abgelaufen?
  if ((millis() - lastDebounceTime[buttonIndex]) > debounceDelay) {
    if (reading != currentButtonState[buttonIndex]) {
      currentButtonState[buttonIndex] = reading;
      
      // Nur bei Tastendruck (LOW) reagieren
      if (currentButtonState[buttonIndex] == LOW) {
        handleButtonPress(buttonIndex, ledPin);
      }
    }
  }
  
  lastButtonState[buttonIndex] = reading;
}

void handleButtonPress(int buttonIndex, int ledPin) {
  // Wenn die LED mit diesem Button bereits an ist
  if (ledState == (buttonIndex + 1)) {
    // LED ausschalten
    digitalWrite(ledPin, LOW);
    ledState = 0;
  } 
  // Wenn keine LED an ist
  else if (ledState == 0) {
    // Alle LEDs ausschalten
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    
    // Neue LED einschalten
    digitalWrite(ledPin, HIGH);
    ledState = (buttonIndex + 1);
  }
  // Wenn eine andere LED an ist: Zustand ändert sich nicht
}
