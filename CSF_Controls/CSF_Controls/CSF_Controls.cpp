

 
 
#include "CSF_Controls.h"
#include "Arduino.h"
#include "HardwareSerial.h"


using namespace Sensors;

//ControlUnit

ControlUnit::ControlUnit(int but, int lin, int sig){
	isSensorOn = false;
	powerButton = but;
	powerLine = lin;
	sensorLine = sig;
	interval = 250;
	previousTime = millis();
}//end construtor

ControlUnit::ControlUnit(int but, int lin, int sig, int val){
	isSensorOn = false;
	powerButton = but;
	powerLine = lin;
	sensorLine = sig;
	interval = val;
	previousTime = millis();
}//end construtor


void ControlUnit::toggleIsSensorOn(){
	isSensorOn = !isSensorOn;
}//end toggleIsSensorOn()


bool ControlUnit::getIsSensorOn(){
	return isSensorOn;
}//end getIsSensorOn()


void ControlUnit::activateControl(){
	digitalWrite(powerLine, HIGH);
}//end activateControl()


void ControlUnit::deactivateControl(){
	digitalWrite(powerLine, LOW);
}//end deactivateControl()


void ControlUnit::isButtonPressed(){
	long currentTime = millis();
	if( (currentTime - previousTime) >= interval){
		int power = digitalRead(powerButton);
		if(power == HIGH){
			toggleIsSensorOn();
		}
		previousTime = millis();
	}
}//end isButtonPressed()







// Pot

void Pot::begin(){
	mappingMode = 0;
	minValueInt = 0;
	maxValueInt = 0;
	minValueFloat = 0.0;
	maxValueFloat = 0.0;
	pinMode(powerButton, INPUT);
	pinMode(powerLine, OUTPUT);
	pinMode(sensorLine, INPUT);
}//end begin()


int Pot::getSensorValue(){
	int reading = analogRead(sensorLine);
	return reading;
}


float Pot::mapData(float min, float max){
	mappingMode = 2;
	minValueFloat = min;
	maxValueFloat = max;
	int signal = getSensorValue();
	signal = map(signal, 0, 1024, (int)(min * 10000), (int)(max * 10000));
	float fSignal = signal / 10000.0;
	
	return fSignal;
}//end mapData(floats)


int Pot::mapData(int min, int max){
	mappingMode = 1;
	minValueInt = min;
	maxValueInt = max;
	int signal = getSensorValue();
	signal = map(signal, 0, 1024, min, max);
	return signal;
}//end mapData(ints)


void Pot::toSerial(){
		//check type of mapped data
	if(mappingMode == 0){
		Serial.println(getSensorValue());
	}
	else if(mappingMode == 1){
		//it's an integer
		int output = mapData(minValueInt, maxValueInt);
		Serial.println(output);
	}
	else if(mappingMode == 2){
		//it's a float
		float output = mapData(minValueFloat, maxValueFloat);
		Serial.println(output);
	}
}//end toSerial()

