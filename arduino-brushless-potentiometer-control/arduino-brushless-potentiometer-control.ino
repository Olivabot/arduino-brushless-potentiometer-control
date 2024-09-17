#include <Servo.h>

Servo ESC;     // create servo object to control the ESC

int potValue;  // value from the analog pin
int mappedValue;   // mapped value for the ESC

void setup() {

    // Initialize Serial communication at 9600 bits per second
  Serial.begin(9600);

  // Attach the ESC on pin 9
  ESC.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 

  // Optional: Give some time for the ESC to arm
  ESC.write(0);   // Send a 0 throttle signal to arm the ESC
  delay(1000);    // Wait for a second
}

void loop() {
  potValue = analogRead(A0);   // Read the potentiometer value (0-1023)
  
  // Map the potentiometer value to a value suitable for the ESC (0-180)
  mappedValue = map(potValue, 0, 1023, 0, 180);
  
  // Send the mapped value to the ESC
  ESC.write(mappedValue);
  
  // Debugging: Print the values to the Serial Monitor
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print("  |  Mapped Value: ");
  Serial.println(mappedValue);
  
  delay(100);  // Small delay to make the serial output readable
}