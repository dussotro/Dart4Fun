#coding:utf-8

# FSM du robot DART

#importations
from dart import Dart
from threading import Thread

class FSMfacile():
    """FSM basique du robot, où les avancées sont pré-programmées, et les rotations aussi (90°)"""
    
    def __init__(self):

        self.state = "arret"
        self.nxtState = "arret"
        
    def arret(robot):
       robot.set_speed(0,0)
   
    def avancer(robot):
        robot.goLineHeading(robot.get_angles(),60,1)
        
    def rotationDroite(robot):
        robot.setHeading(robot.get_angles()+90)
        
    def rotationGauche(robot):
        robot.setHeading(robot.get_angles()-90)
    
    
    def run(self):        
        if self.nxtState == "avancer":
            self.state = "avancer"
            self.avancer(self.robot)
            

        elif self.nxtState == "gauche":
            self.state = "gauche"
            self.rotationGauche(self.robot)
            
        elif self.nxtState == "droite":
            self.state == "droite"
            self.rotationDroite(self.robot)
            
        elif self.nxtState == "arret":
            self.state = "arret"
            self.arret(self.robot)
            
            
class Key_listener(Thread):
	def __init__(self, fsm):
		Thread.__init__(self)
		self.fsm = FSMfacile()
	
	def run(self):
		while True:
			l = input("fsm : ")
			self.fsm.nxtState = l

if __name__== "__main__":
    fsm = FSMfacile()
    kl = Key_listener(fsm)
    kl.start()
    while True:
        fsm.run()
