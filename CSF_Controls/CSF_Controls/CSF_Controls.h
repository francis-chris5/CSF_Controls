

/**
 * @mainpage CSF_Controls
 * @section description Summary
 * CSF_Controls is a C++ library designed to consolidate the coding for some common components in Arduino projects. At least things I have found get used in a lot of projects and often get connected and coded the same way over and over again. Such as potentiometers (with a power-indicator LED) for input sensors, or tactile-momentary-switches and capacitive-touch sensors which wire up differently but are used in essentially the same way --for me typically an On/Off button for both.\n
 * Here is the schematic for my standard way of wiring up a potentiometer as an input sensor and a tactile-momentary-switch that the objects in this library are designed to go with. Everything else in the library \(thus far\) goes with a prebuilt sensor module of some sort.\n
 * <IMG src="../images/pot_circuit.png">
 * <IMG src="../images/tactile_button_circuit.png">
 * @section author Author
 * Developed By: Christopher S. Francis, 19 June 2020 to ...
 */


#ifndef CSF_Controls_h
#define CSF_Controls_h

#include "Arduino.h"





/**
 * @section description Description
 * ControlUnit is the parent class for sensor controls.\n
 * Each "Control" typically consists of a tactile-momentary-switch or capacitive touch-sensor for a power button, a power indicator LED, and a sensor to input the control data\n
 * <IMG src="../images/pot_circuit.png">
 * <IMG src="../images/tactile_button_circuit.png">
 */
class ControlUnit{
	public:
		/**
		 * The constructor for the sensor.\n
		 * With only three arguments it sets the reuired time interval that must pass between registering button clicks to 250 milliseconds\n
		 * @param but -the power button connected to the sensor
		 * @param lin -the power line coming from the Arduino
		 * @param sig -the Arduino pin the sensor signal will be sent to
		 */
		ControlUnit(int but, int lin, int sig);
		
		
		
		/**
		 * The constructor for the sensor.\n
		 * @param but -the power button connected to the sensor
		 * @param lin -the power line coming from the Arduino
		 * @param sig -the Arduino pin the sensor signal will be sent to
		 * @param val -the reuired time interval that must pass between registering button clicks -in milliseconds
		 */
		ControlUnit(int but, int lin, int sig, int val);
		
		
		
		/**
		 * Initializes all variables and assigns INPUT/OUTPUT to the connections on the scale controls, i.e. the pinMode\(i, m\) method for Arduino\n
		 * Call this method in the setup\(\) method in the .ino file
		 */
		virtual void begin(void) = 0;
		
		
		/**
		 * Gets the current value of this control's sensor, this method is called from the .ino file as an argument in Serial.println\(this\) to send the data to Blender
		 * 
		 * @return int
		 */
		virtual int getSensorValue(void) = 0;
		
		
		/**
		 * Toggles the On/Off state of this control
		 */
		void toggleIsSensorOn(void);
		
		
		/**
		 * Getter for the On/Off state data of this control
		 * @return bool
		 */
		bool getIsSensorOn(void);
		
		
		/**
		 * Activates the power to this control
		 */
		void activateControl(void);
		
		
		/**
		 * Deactivates the power to this control
		 */
		void deactivateControl(void);
		
		
		/**
		 * Called internally when the Activation Button for this control on the Main-Unit is pressed\n
		 * Place in loop\(\) somewhere to determine if the power button for this control is currently being pressed
		 */
		void isButtonPressed(void);
	protected:
		bool isSensorOn;			///<On/Off State of this control
		int powerButton;		///<Power button for this control
		int powerLine; 		///<Power Line for this control's sensor and power indicator LED
		int sensorLine;		///<Input line feeding back from the sesnsor in this control
		long interval;	///< The amount of time to wait between checking presses of buttons
		long previousTime;	///< The unix epoch timestamp on last pass of the program's main loop
};




/**
 * The Pot class is for potentiometer input to an arduino, I use it for both rotary and sliding potentiometers.\n
 * I also usually include a Power-Indicator-LED with each particular sensor, so the power-line variable actually activates a NPN transistor to supply the VCC voltage to both the LED and Potentiometer from the +5V or +3.3V rail.\n
 * <IMG src="../images/pot_circuit.png">
 */
class Pot: public ControlUnit{
	public:
		/**
		 * The constructor for the sensor.\n
		 * @param but -the power button connected to the sensor
		 * @param lin -the power line coming from the Arduino
		 * @param sig -the Arduino pin the sensor signal will be sent to
		 */
		Pot(int but, int lin, int sig): ControlUnit(but, lin, sig){};
		
		
		void begin(void);
		
		
		
		int getSensorValue(void);
		
		
		/**
		 * Remaps the potentiometer data to the desired values. \n
		 * 0 to 1024 is presumed here, as circuits grow more complicated and draw more current these values may change, expanding the range between min and max can adjust for such a drop in input.
		 * @param min -the minimum value the potentiometer input should be mapped to
		 * @param max -the maximum value the potentiometer input should be mapped to
		 * @return float -to five decimal places
		 */
		float mapData(float min, float max);
		
		
		
		/**
		 * Remaps the potentiometer data to the desired values. \n
		 * 0 to 1024 is presumed here, as circuits grow more complicated and draw more current these values may change, expanding the range between min and max can adjust for such a drop in input.
		 * @param min -the minimum value the potentiometer input should be mapped to
		 * @param max -the maximum value the potentiometer input should be mapped to
		 * @return int 
		 */
		int mapData(int min, int max);
};





#endif