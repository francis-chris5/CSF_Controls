

##
# @file
# @section desctiption
# A stripped down example of what I typically find myself doing with Arduino projects.\n
# A device that sends real-world responsive data to the PC to override certain keyboard or mouse features for a certain piece of software



import serial
import pyautogui as gui
import time


##
# An example object to control the serial data flowing between the computer and the Arduino
class Controller:

    ##
    # The constructor for Controller\n
    # The serial communication is initiated followed by a three second delay to give the Arduino time to boot up\n
    def __init__(self):
        self.__ser = serial.Serial("COM7", "9600", timeout=1);
        time.sleep(3)




    ##
    # provides a string representation of the class
    def __str__(self):
        return "A stripped down example of serial communication with Arduino using two potentiometers to control the mouse movement"



    ##
    # get the value of the slide potentiometer from the Arduino
    def getSlider(self):
        self.__ser.write(b"Slide\n")
        res = int(self.__ser.readline())
        return res



    ##
    # get the value of the slide potentiometer from the Arduino
    def getRotary(self):
        self.__ser.write(b"Spin\n")
        res = int(self.__ser.readline())
        return res


    ##
    # Moves the mouse relative to it's current position based on the state of the Pots connected to the Arduino
    def moveMouse(self):
        deltaX = self.getSlider()
        deltaY = self.getRotary()
        gui.moveRel(deltaX, deltaY)



    ##
    # calls the move mouse function a hundred times with a breif delay between each call to allow the screen to update
    def mainloop(self):
        for counter in range(100):
            self.moveMouse()
            time.sleep(0.3)


    
        
