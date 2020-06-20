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

String pcCommand = "";  //< The string holding the serial communication input coming from the computer
Pot rotary = Pot(2, 3, A0); ///< Object representing the rotary potentiometer and associated components\n This will be used to control the x value of the mouse
Pot slider = Pot(5, 6, A2); ///< Object representing the slide potentiometer and associated components\n This will be used to control the y value of the mouse
int firstPass = 1;

/**
 * The standard setup\(\) method for arduino\n
 * For this example it intializes the serial communication port and initializes the Pot objects
 */
void setup() {
  Serial.begin(9600);
  rotary.begin();
  slider.begin();
}//end setup()





/**
 * The standard loop\(\) method for Arduinon
 * On the first pass through the loop it maps the potentiometers to values in the range a mouse would move\n
 * Then it checks for serial commands coming from the computer
 */
void loop() {
  activateSensors();
  if(firstPass == 1){
    slider.mapData(-200, 200);
    rotary.mapData(200, -200);
    firstPass = 0;
  }
  checkSerial();
}//end loop()



/**
 * Checks if the power buttons are currently being pressed and activates/deactivates the sensors as needed
 */
void activateSensors(){
  slider.isButtonPressed();
  rotary.isButtonPressed();
  if(slider.getIsSensorOn()){
    slider.activateControl();
  }
  else{
    slider.deactivateControl();
  }
  if(rotary.getIsSensorOn()){
    rotary.activateControl();
  }
  else{
    rotary.deactivateControl();
  }
}//end activateSensors()



/**
 * Monitors the communication coming in on the serial port and responds accordingly.\n
 *
 */
void checkSerial(){
  if(Serial.available() > 0){
     pcCommand = Serial.readStringUntil('\n');
    if(pcCommand == "Slide"){
      if(slider.getIsSensorOn()){
        slider.toSerial();  
      }
      else{
        Serial.println(0);
      }
    }
    else if(pcCommand == "Spin"){
      if(rotary.getIsSensorOn()){
        rotary.toSerial();  
      }
      else{
        Serial.println(0);
      }
    }
	else{
		Serial.println("\n");//avoid waiting for a timeout on computer
	}
  }//end serial is available
}//end checkSerial()
