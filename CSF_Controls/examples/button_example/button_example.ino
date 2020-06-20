/**
 * @file
 * @section desription Description
 * An example using the CSF_Controls library.\n
 * The circuit used for this is pictured below: \(see documentation for library for wiring schematic on sections\)\n
 * <IMG src="../images/example_circuit1.jpg" width="500" height="300">\n\n\n
 * <IMG src="../images/example_circuit2.jpg" width="500" height="300">\n
 */

#include <CSF_Controls.h>

using namespace Switches;


Momentary clicker = Momentary(2); ///< Object representing the tactile-momentary-switch circuit
Touch zone = Touch(5);  ///< Object representing the capacitive-touch-sensor-module

/**
 * The standard setup\(\) method for arduino\n
 * For this example it intializes the serial communication port and initializes the Button-Subclass objects
 */
void setup() {
  Serial.begin(9600);
  clicker.begin();
  zone.begin();
}





/**
 * The standard loop\(\) method for Arduinon
 * Here it checks if the sensor needs activated/deactivated and prints that to the serial port.\n
 */
void loop() {
  Serial.print("Button: ");
  clicker.toSerial();
  Serial.print("Touch: ");
  zone.toSerial();
}
