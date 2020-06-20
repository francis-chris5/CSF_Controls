

 
 
#include "CSF_Controls.h"
#include "Arduino.h"


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
	pinMode(powerButton, INPUT);
	pinMode(powerLine, OUTPUT);
	pinMode(sensorLine, INPUT);
}//end begin()


int Pot::getSensorValue(){
	int reading = analogRead(sensorLine);
	return reading;
}


float Pot::mapData(float min, float max){
	int signal = getSensorValue();
	signal = map(signal, 0, 1024, (int)(min * 10000), (int)(max * 10000));
	float fSignal = signal / 10000.0;
	return fSignal;
}//end mapData(floats)


int Pot::mapData(int min, int max){
	int signal = getSensorValue();
	signal = map(signal, 0, 1024, min, max);
	return signal;
}//end mapData(ints)





























