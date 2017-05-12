#coding:utf-8

# FSM du robot DART

#importations
from dart import Dart
from threading import Thread

class FSMfacile(Dart):
    """FSM basique du robot, où les avancées sont pré-programmées, et les rotations aussi (90°)"""
    
    def __init__(self):
        super(FSM,self).__init__()
        self.state = "arret"
        self.nxtState = "arret"
        
    def arret(self):
       self.set_speed(0,0)
   
    def avancer(self):
        self.goLineHeading(self.get_angles(),60,1)
        
    def rotationDroite(self):
        self.setHeading(self.get_angles()+90)
        
    def rotationGauche(self):
        self.setHeading(self.get_angles()-90)
    
    
    def run(self):        
        if self.nxtState == "avancer":
            self.state = "avancer"
            self.avancer()
            

        elif self.nxtState == "gauche":
            self.state = "gauche"
            self.rotationGauche()
            
        elif self.nxtState == "droite":
            self.state == "droite"
            self.rotationDroite()
            
        elif self.nxtState == "arret":
            self.state = "arret"
            self.arret()
            
            
class Key_listener(Thread):
	def __init__(self, fsm):
		Thread.__init__(self)
		self.fsm = FSMfacile()
	
	def run(self):
		while True:
			l = raw_input("fsm>")
			self.fsm.nxtState = l