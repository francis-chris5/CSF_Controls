


##
# @file
# This file is really just to make sure the shell is pulling from the correct directory\n
# run the test from this file, then wait for the prompt to reappear in the shell, make sure both controls are on and call con.mainloop\(\) to control the mouse for a few seconds.


from Controller import *



con = Controller()
con.getSlider()
con.getRotary()
