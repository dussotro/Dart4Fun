'''
@auhtor : Corentin R
@date : February 2015

This file contains robot's constants. If any element of the robot is changed,
please modify here

CAREFUL : 1px=1cm
'''

scale = 1 # Multiplicative scale for the robot
elementSize = 5 #Each element is the same size in pixels
# panelsize  gives 1.5 m
panelSize = 200
elementScale = 150.0/float(panelSize)
#Sizes for the window
windowHeight = 0
windowWidth = 400

#Sizes for the robot
robotLenght = 23*scale
robotWidth = 12*scale
wheelLenght = 12.5*scale
wheelWidth = 10*scale
wheelRadius = 6.25*scale
clawLenght = 10*scale
clawWidthClosed = 2*scale
clawWidthOpened = 2*scale
clawBase = 10*scale
nTicks = 75*scale

#Sizes for sonar
sonarLenght = 250.0
sonarAngle = 20.0 #in degrees
nFrontSonar = 1#number
nLeftSonar = 1
nRightSonar = 1
nBackSonar = 1

#Elements for the simulation
speed=30

#Path to useful files and other stuff

titre = "Simulateur DAARRT Challenge 2016"
worldName="vDaarrt/data/World/worldChallenge.txt"
#worldName="vDaarrt/data/World/world1.txt"
mur = "vDaarrt/data/mur.png"
obstacle = "vDaarrt/data/obstacle.png"
nomRobot = "DAARRT"
background = "vDaarrt/data/background.jpg"
button ="vDaarrt/data/button.png"
logo = "vDaarrt/data/logo.png"
