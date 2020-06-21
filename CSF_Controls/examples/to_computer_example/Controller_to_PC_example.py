

##
# @file
# @section desctiption Description
# A stripped down example of what I typically find myself doing with Arduino projects.\n
# A device that sends real-world responsive data to the PC to override certain keyboard or mouse features for a particular piece of software\n
# To see this example run in a python shell run it and wait for the prompt to reapper \(those two lines at the bottom will throw a traceback if something goes wrong with the connection\), activate both pots, and enter con.mainloop\(\) in the prompt and adjust the two pots.



import serial
import pyautogui as gui
import time


##
# A stripped down example of what I typically find myself doing with Arduino projects.
# A device that sends real-world responsive data to the PC to override certain keyboard or mouse features for a particular piece of software\n
# To see this example run in a python shell run it and wait for the prompt to reapper \(those two lines at the bottom will throw a traceback if something goes wrong with the connection\), activate both pots, and enter con.mainloop\(\) in the prompt and adjust the two pots.\n
# The circuit used for this is pictured below: \(see documentation for library for wiring schematic on sections\)\n
# <IMG src="../images/example_circuit1.jpg" width="500" height="300">\n\n\n
# <IMG src="../images/example_circuit2.jpg" width="500" height="300">\n
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
        return "A stripped down example of serial communication with Arduino using two potentiometers to control the movement of the mouse"



    ##
    # gets the value of the slide potentiometer from the Arduino and strips away the extra bits from the binary string, e.g. "b'7\r\n'" is what the actual data stream from an Arduino looks like
    def getSlider(self):
        self.__ser.write(b"Slide\n")
        res = int(self.__ser.readline())
        return res



    ##
    # gets the value of the slide potentiometer from the Arduino and strips away the extra bits from the binary string, e.g. "b'7\r\n'" is what the actual data stream from an Arduino looks like
    def getRotary(self):
        self.__ser.write(b"Spin\n")
        res = int(self.__ser.readline())
        return res


    ##
    # Moves the mouse relative to it's current position based on the state of the two Pots connected to the Arduino
    def moveMouse(self):
        deltaX = self.getSlider()
        deltaY = self.getRotary()
        gui.moveRel(deltaX, deltaY)



    ##
    # calls the move mouse function a thousand times with a breif delay between each call to allow the screen to update
    def mainloop(self):
        for counter in range(1000):
            self.moveMouse()
            time.sleep(0.3)





con = Controller()
con.getSlider()
con.getRotary()
        
