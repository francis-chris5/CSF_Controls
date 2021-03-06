/**
 * @file
 * @section desription Description
 * An example using the CSF_Controls library.\n
 * The circuit used for this is pictured below: \(see documentation for library for wiring schematic on sections\)\n
 * <IMG src="../images/example_circuit1.jpg" width="500" height="300">\n\n\n
 * <IMG src="../images/example_circuit2.jpg" width="500" height="300">\n
 */

#include <CSF_Controls.h>

using namespace Sensors;


Pot rotary = Pot(2, 3, A0); ///<Object representing the rotary potentiometer and associated components
Pot slider = Pot(5, 6, A2); ///<Object representing the slide potentiometer and associated components


/**
 * The standard setup\(\) method for arduino\n
 * For this example it intializes the serial communication port and initializes the Pot objects
 */
void setup() {
  Serial.begin(9600);
  rotary.begin();
  slider.begin();
}





/**
 * The standard loop\(\) method for Arduino\n
 * Here it checks if the sensor needs activated/deactivated, and if it's on prints the values to the serial port and a couple blank lines.
 */
void loop() {

  rotary.isButtonPressed();
  slider.isButtonPressed();

  if(rotary.getIsSensorOn()){
    rotary.activateControl();
    Serial.print("rotary pot: ");
    //rotary.toSerial();  //uncomment this line and comment out next four to see unmapped data
    
    float negPI = -3.14;
    float posPI = 3.14;
    rotary.mapData(negPI, posPI);
    rotary.toSerial();
    
  }
  else{
    rotary.deactivateControl();
  }


  if(slider.getIsSensorOn()){
    slider.activateControl();
    Serial.print("slider pot: ");
    //slider.toSerial();  //uncomment this line and comment out the next two to see mapped data
    
    slider.mapData(24, 38);
    slider.toSerial();
    
  }
  else{
    slider.deactivateControl();
  }

  if(rotary.getIsSensorOn() || slider.getIsSensorOn()){
    Serial.println();
    Serial.println();
  }
  

}
