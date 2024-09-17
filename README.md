
# Arduino Brushless Motor Control with Potentiometer

Control a brushless DC motor using an Arduino and an Electronic Speed Controller (ESC). This project utilizes a potentiometer to adjust motor speed and includes serial debugging for real-time monitoring of potentiometer values and motor performance. Ideal for robotics and DIY motor control applications.

## Table of Contents

- [Introduction](#introduction)
- [Hardware Required](#hardware-required)
- [Circuit Diagram](#circuit-diagram)
- [Getting Started](#getting-started)
- [Code Explanation](#code-explanation)
- [Usage](#usage)
- [Safety Precautions](#safety-precautions)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Introduction

This project demonstrates how to control a brushless DC motor using an Arduino and an Electronic Speed Controller (ESC). A potentiometer is used to vary the motor's speed, providing precise control. Serial debugging is implemented to monitor the potentiometer readings and motor speed in real-time, making it an excellent educational tool for those interested in robotics, electronics, or DIY motor control systems.

## Hardware Required

- **Arduino Board** (e.g., Arduino Uno, Nano)
- **Brushless DC Motor**
- **Electronic Speed Controller (ESC)**
- **Potentiometer** (10kΩ recommended)
- **Power Source** for the ESC and motor (e.g., LiPo battery matching the ESC's voltage requirements)
- **Connecting Wires**
- **USB Cable** for programming the Arduino
- **Optional:** Breadboard, safety gear (e.g., safety glasses)

## Circuit Diagram

### ESC to Motor

- Connect the three output wires of the ESC to the three input wires of the brushless motor. The order doesn't matter initially. If the motor spins in the wrong direction, swap any two wires.

### ESC to Power Source

- **Red Wire (+):** Connect to the positive terminal of the battery.
- **Black Wire (-):** Connect to the negative terminal of the battery.

### ESC to Arduino

- **Signal Wire** (usually white or yellow): Connect to Arduino digital pin **9**.
- **Ground Wire** (black or brown): Connect to Arduino **GND** pin.
- **Power Wire** (red):
  - **Note:** If the ESC provides a 5V BEC (Battery Eliminator Circuit) output, you can use it to power the Arduino. Otherwise, power the Arduino separately via USB or an external power source.

### Potentiometer to Arduino

- **Middle Pin (wiper):** Connect to Arduino analog pin **A0**.
- **One Side Pin:** Connect to **5V** on the Arduino.
- **Other Side Pin:** Connect to **GND** on the Arduino.

*Include a circuit diagram image here if available.*

## Getting Started

### Installation

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/Olivabot/arduino-brushless-potentiometer-control.git
   ```

2. **Open the Sketch:**

   - Launch the Arduino IDE.
   - Open the `brushless_control.ino` file from the cloned repository.

### Hardware Setup

- Assemble the circuit as described in the [Circuit Diagram](#circuit-diagram) section.
- Ensure all connections are secure and correct.

## Code Explanation

```cpp
/*
    Arduino Brushless Motor Control with Serial Debugging
    by Dejan, https://howtomechatronics.com
*/

#include <Servo.h>

Servo ESC;     // Create servo object to control the ESC

int potValue;      // Raw value from the potentiometer (0-1023)
int mappedValue;   // Mapped value for the ESC (0-180)

void setup() {
    // Initialize Serial communication at 9600 bits per second
    Serial.begin(9600);

    // Attach the ESC on pin 9
    ESC.attach(9, 1000, 2000); // (pin, min pulse width, max pulse width in microseconds)

    // Arm the ESC by sending a zero throttle signal
    ESC.write(0);   // Sends a 0-degree signal (corresponds to 1000 μs pulse width)
    delay(1000);    // Wait for a second to allow the ESC to arm
}

void loop() {
    // Read the potentiometer value (0-1023)
    potValue = analogRead(A0);

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
```

### Detailed Explanation

- **Include the Servo Library:**

  ```cpp
  #include <Servo.h>
  ```

  - The `Servo` library is used to generate the PWM signals required by the ESC.

- **Create Servo Object:**

  ```cpp
  Servo ESC;
  ```

  - An instance of the `Servo` class is created to control the ESC.

- **Variable Declarations:**

  ```cpp
  int potValue;
  int mappedValue;
  ```

  - `potValue` stores the raw analog value from the potentiometer.
  - `mappedValue` stores the value mapped to the range suitable for the ESC.

- **Setup Function:**

  ```cpp
  void setup() {
      Serial.begin(9600);
      ESC.attach(9, 1000, 2000);
      ESC.write(0);
      delay(1000);
  }
  ```

  - Initializes serial communication for debugging.
  - Attaches the ESC to pin 9 with specified pulse widths.
  - Arms the ESC by sending a zero-throttle signal.
  - Delays to give the ESC time to arm.

- **Loop Function:**

  ```cpp
  void loop() {
      potValue = analogRead(A0);
      mappedValue = map(potValue, 0, 1023, 0, 180);
      ESC.write(mappedValue);
      Serial.print("Potentiometer Value: ");
      Serial.print(potValue);
      Serial.print("  |  Mapped Value: ");
      Serial.println(mappedValue);
      delay(100);
  }
  ```

  - Reads the potentiometer value.
  - Maps the value to the ESC's control range.
  - Sends the mapped value to the ESC to control motor speed.
  - Prints debugging information to the Serial Monitor.
  - Delays to make the serial output readable.

## Usage

1. **Upload the Code:**

   - Connect your Arduino board to your computer using a USB cable.
   - In the Arduino IDE, select the correct board and port from the **Tools** menu.
   - Upload the sketch to the Arduino.

2. **Power the ESC and Motor:**

   - Connect the battery or power source to the ESC.
   - **Caution:** Ensure the motor is secured and no propellers or loads are attached during testing.

3. **Open the Serial Monitor:**

   - In the Arduino IDE, click on **Tools > Serial Monitor**.
   - Set the baud rate to **9600**.

4. **Operate the Potentiometer:**

   - Rotate the potentiometer knob.
   - Observe the motor speed change accordingly.
   - Monitor the serial output to see the potentiometer and mapped values.

## Safety Precautions

- **Remove Propellers:** If testing with a propeller or any load, remove it to prevent injury.
- **Secure the Motor:** Ensure the motor is firmly mounted to prevent movement during operation.
- **Check Connections:** Verify all connections before powering the system.
- **Use Proper Power Supply:** Ensure your power source matches the ESC's voltage requirements.
- **Avoid Short Circuits:** Be cautious to prevent any short circuits in the wiring.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- **Dejan Nedelkovski**, [HowToMechatronics](https://howtomechatronics.com) - Original project inspiration.
- **Arduino Community** - For extensive resources and support.

