// C++ code
int buttonPin = 7;
int pins[] = {13, 12, 11};
int counter;
//debouncing for button
int lastSteadyState = HIGH; // The previous steady state from the input pin
int lastFlickerableState = HIGH; // The previous temporary state from the input pin
unsigned long lastDebounceTime = 0;  // The last time the output pin was toggled
const unsigned long DEBOUNCE_DELAY = 50; // The debounce time in milliseconds


void setup()
{
  Serial.begin(9600);
  for (int p = 0; p < 3; p++) {
    pinMode(pins[p], OUTPUT);
  }
  pinMode(buttonPin, INPUT);
  counter = 0;
}


void loop()
{
   int currentState = digitalRead(buttonPin);
   if (currentState != lastFlickerableState) {
    lastDebounceTime = millis();
    lastFlickerableState = currentState;
  }


  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (lastSteadyState == LOW && currentState == HIGH) {
      for (int p = 0; p < 3; p++) {
          digitalWrite(pins[p], LOW);
      }
      
      if (counter == 3) {  
          counter = 0;
      } else {
          digitalWrite(pins[counter], HIGH);
          counter++;
      }
  	}  
    lastSteadyState = currentState;
  }
}
