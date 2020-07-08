

/**
 * @mainpage CSF_Controls
 * @section description Summary
 * CSF_Controls is a C++ library designed to consolidate the coding for some common components in Arduino projects. At least things I have found get used in a lot of projects and often get connected and coded the same way over and over again. Such as potentiometers (with a power-indicator LED) for input sensors, or tactile-momentary-switches and capacitive-touch sensors which wire up differently but are used in essentially the same way --for me typically an On/Off button for both with code to prevent spamming the button.\n
 * While the library is currently pretty small, I do have a number of things in mind to include here, hence the need to organize the library into namespaces, for example there are other common ways that I set up Pots as output level control or adjusting input thresholds and I'd like to use the name Pot to indicate it goes with a potentiometer there too.\n
 * @section author Author
 * Developed By: Christopher S. Francis, 19 June 2020 to ...
 */


#ifndef CSF_Controls_h
#define CSF_Controls_h

#include "Arduino.h"



/**
 * The Sensors namespace is for circuits normally used as primary inputs to a project
 */
namespace Sensors{


	/**
	 * @section description Description
	 * ControlUnit is the parent class for sensor controls.\n
	 * Each "Control" typically consists of a tactile-momentary-switch or capacitive touch-sensor for a power button, a power indicator LED, and a sensor to input the control data\n
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
			 * @param val -the required time interval that must pass between registering button clicks -in milliseconds
			 */
			ControlUnit(int but, int lin, int sig, int val);
			
			
			
			/**
			 * Initializes all variables and assigns INPUT/OUTPUT to the connections on the scale controls, i.e. the pinMode\(i, m\) method for Arduino\n
			 * Call this method in the setup\(\) method in the .ino file
			 */
			virtual void begin(void) = 0;
			
			
			/**
			 * Gets the current value of this control's sensor
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
			 * Called when ready to check if the Activation Button for this control is currently being pressed \(I chose not to put interupts in this library\)\n
			 * Place in loop\(\) somewhere to determine if the power button for this control is currently being pressed
			 */
			void isButtonPressed(void);
			
			
			/**
			 * I often find my ideas for Arduino projects are input devices (essentially a customized keyboard or mouse override) for software running on my PC. This is typically handled with bits of code written in python making use of the libraries pyserial and pyautogui.\n
			 * This method is encapsulates sending the sensor data to the serial port for that purpose.\n
			 */
			virtual void toSerial(void) = 0;
		protected:
			bool isSensorOn;			///<On/Off State of this control
			int powerButton;		///<Power button for this control
			int powerLine; 		///<Power Line for this control's sensor and power indicator LED
			int sensorLine;		///<Input line feeding back from the sesnsor in this control
			long interval;	///< The amount of time to wait between checking presses of buttons
			long previousTime;	///< The unix epoch timestamp on last pass of the program's main loop
	};




	/**
	 * The Pot class is for potentiometer input to an Arduino, I use it for both rotary and sliding potentiometers.\n
	 * I also usually include a Power-Indicator-LED with each particular sensor, so the power-line variable actually activates a NPN transistor to supply the VCC voltage to both the LED and Potentiometer from the +5V or +3.3V rail.\n
	 * The extra pin on there is a supplemental power In/Out to bypass the button and LED. For example a recent project I put together contained two pots wired up in this fashion, originally one sent values ranging from -5.12 to +5.12 to the computer and the other sent the range -3.14 to +3.14. By connecting their supplemental pins I was able to use the other as a strength control \(without the LED confusing which sensor was active\) so that the values sent to the computer could be refined from \(+-\)0.0512 to \(+-\)512.0 and \(+-\)0.0314 to \(+-\)314. 0, allowing for much finer or broader control with ease.
	 * Here are the prototypes of the Rotary-Pot-Module and Slider-Pot-Module to go with classes in this library. The thought of smaller and smaller electronics is nice, but I like the size of these controls with my chubby-stubby-northern-european-ancestory fingers when mocking up ideas so the Pot-Module-R and Pot-Module-S Gerber files don't include components, just holes for them to go in and I plan to solder the full size components in myself, but might as well share those here too, if you want to update a copy of the gerber file most any factory wouldn't have any trouble stamping these common parts on there for you \(that may not be the case with the dual output slide pots I use, but everything else... definitely\).\n
	 * <IMG src="../images/pot_circuit.PNG">
	 * <IMG src="../images/tactile_button_circuit.PNG">\n
	 * <IMG src="../images/Pot_Module-R.jpg" width="500">
	 * <A href="../pcb/Gerber_Rotary Pot Module.zip"> Download Gerber Files for Pot-Module-R</A>\n\n
	 * <IMG src="../images/Pot_Module-S.jpg" width="500">
	 * <A href="../pcb/Gerber_Slider Pot Module.zip"> Download Gerber Files for Pot-Module-S</A>\n
	 * @htmlonly
	 * <iframe src="../pcb/pcb_rotary.html" width="900" height="700">
	 * </iframe>
	 <iframe src="../pcb/pcb_slider.html" width="900" height="700">
	 * </iframe>
	 * @endhtmlonly
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
			
			
			
			/**
			 * The constructor for the sensor.\n
			 * @param but -the power button connected to the sensor
			 * @param lin -the power line coming from the Arduino
			 * @param sig -the Arduino pin the sensor signal will be sent to
			 * @param val -the reuired time interval that must pass between registering button clicks -in milliseconds
			 */
			Pot(int but, int lin, int sig, int val): ControlUnit(but, lin, sig, val){};
			
			
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
			
			
			
			void toSerial(void);
		protected:
			int mappingMode; ///< If the mapData\(\) function has been called this will be track whether it should be an int or a float for toSerial\(\) with the same range.\n 0 is unmapped, 1 is int, 2 is float.
			int minValueInt;	///< hold the mapped data from the sensor
			int maxValueInt;	///< hold the mapped data from the sensor
			float minValueFloat;	///< hold the mapped data from the sensor
			float maxValueFloat;	///< hold the mapped data from the sensor
	};


}











/**
 * The Switches namesapce is for activation/deactivation controls which typically require more than merely reading the level coming to an Arduino pin
 */
namespace Switches{
	
	
	/**
	 * This is the parent object for tactile switches and touch sensors which will essentially be used as On/Off switches.\n
	 * Essentially this just returns the On/Off state of the switch/sensor as an int \(1 when pressed, 0 otherwise\).
	 */
	class Button{
		public:
			/**
			 * The constructor for ControlButton class
			 * @param p -The Arduino pin the momentary-switch/touch-sensor is connected to
			 */
			Button(int p);
			
			
			/**
			 * Initializes all variables and assigns INPUT/OUTPUT to the connections on the scale controls, i.e. the pinMode\(i, m\) method for Arduino\n
			 * Call this method in the setup\(\) method in the .ino file
			 */
			void begin(void);
			
			
			
			/**
			 * gets the current state of the button 
			 * @return int -a 1 if currently being pressed/touched, and 0 otherwise
			 */
			int getState();
			
			
			
			/**
			 * gets the current state of the button 
			 * @param condition -a boolean approving the activation of this button \(for example, I often combine features to a common potentiometer, and want to be certain that the other use of the sensor is not running before I turn this one on\). In most cases just pass in the word true though.
			 * @return int -a 1 if currently being pressed/touched, and 0 otherwise
			 */
			int getState(bool condition);
			
			
			/**
			 * I often find my ideas for Arduino projects are input devices (essentially a customized keyboard or mouse override) for software running on my PC. This is typically handled with bits of code written in python making use of the libraries pyserial and pyautogui.\n
			 * This method is encapsulates sending the data to the serial port for that purpose, in this case it sends a true/false value to represent whether the button is currently activated \(pressed or touched, etc.\) or not.\n
			 * see getState\(\) about the overloading
			 */
			void toSerial(void);
			
			
			/**
			 * I often find my ideas for Arduino projects are input devices (essentially a customized keyboard or mouse override) for software running on my PC. This is typically handled with bits of code written in python making use of the libraries pyserial and pyautogui.\n
			 * This method is encapsulates sending the data to the serial port for that purpose, in this case it sends a true/false value to represent whether the button is currently activated \(pressed or touched, etc.\) or not.\n
			 * see getState\(\) about the overloading
			 */
			void toSerial(bool condition);
		protected:
			int pin;	///<The arduino pin the button/touch-sensor is connected to
	};










	/**
	 * The subclass of Button specialized for Taactile-Momentary-Switches. If such a setup is used as a regular "Button" make sure to include a timer to avoid spamming the On/Off states at every pulse of the processor's clock.\n
	 * <IMG src="../images/tactile_button_circuit.png">
	 */
	class Momentary: public Button{
		public:
			/**
			 * The constructor for Momentary objects.
			 * @param p -the Arduino pin the signal from the tactile-momentary-switch will be received on
			 */
			Momentary(int p): Button(p){};
			
			
			/**
			 * The constructor for Momentary objects.
			 * @param p -the Arduino pin the signal from the tactile-momentary-switch will be received on
			 * @param val -the time interval in milliseconds that must pass between reading the state of the button
			 */
			Momentary(int p, int val): Button(p){interval = val;};
			
			
			
			/**
			 * Overrides getState\(\) from Button class with a timer to avoid spamming the tactile momentary switch and toggling the On/Off state with every pusle of the processor's clock the button is held down for.
			 * @return int -a 1 if currently being pressed/touched, and 0 otherwise
			 */
			 int getState();
			
			
			
			/**
			 * Overrides getState\(\) from Button class with a timer to avoid spamming the tactile momentary switch with every pusle of the processor's clock the button is held down for.
			 * @param condition -a boolean approving the activation of this button \(for example, I often combine features to a common sensor when they won't overlap, and want to be certain that the other use of the sensor is not running before I turn this one on\). In most cases just pass in the word true though.
			 * @return int -a 1 if currently being pressed/touched, and 0 otherwise
			 */
			 int getState(bool condition);
			 
			 
	

		protected:
			int interval;	///< The amount of time to wait between checking presses of buttons
			long previousTime;	///< The unix epoch timestamp on last pass of the program's main loop
	};


	/**
	 * The subclass of Button specialized for Capacitive-Touch-Sensor-Modules. If such a setup is used as a regular "Button" make sure to include a timer to avoid spamming the On/Off states at every pulse of the processor's clock.\n
	 * This is what I use this with the prebuilt capacitive touch sensor modules, and not a custom capacitive touch sensor
	 */
	class Touch: public Button{
		public:
			/**
			 * The constructor for Touch objects.
			 * @param p -the Arduino pin the signal from the capacitive-touch-sensor-module will be received on
			 */
			Touch(int p): Button(p){};
			
			
			
			/**
			 * The constructor for Touch objects.
			 * @param p -the Arduino pin the signal from the tactile-momentary-switch will be received on
			 * @param val -the time interval in milliseconds that must pass between reading the state of the tuch sensor
			 */
			Touch(int p, int val): Button(p){interval = val;};
			
			
			/**
			 * Overrides getState\(\) from Button class with a timer to avoid spamming the touch sensor and toggling the On/Off state with every pusle of the processor's clock the button is held down for.
			 * @return int -a 1 if currently being pressed/touched, and 0 otherwise
			 */
			 int getState();
			
			
			
			/**
			 * Overrides getState\(\) from Button class with a timer to avoid spamming the tactile momentary switch with every pusle of the processor's clock the button is held down for.
			 * @param condition -a boolean approving the activation of this button \(for example, I often combine features to a common sensor when they shouldn't overlap, and want to be certain that the other use of the sensor is not running before I turn this one on\). In most cases just pass in the word true though.
			 * @return int -a 1 if currently being pressed/touched, and 0 otherwise
			 */
			 int getState(bool condition);

		protected:
			int interval;	///< The amount of time to wait between checking presses of buttons
			long previousTime;	///< The unix epoch timestamp on last pass of the program's main loop
	};

	
	
	
}

#endif