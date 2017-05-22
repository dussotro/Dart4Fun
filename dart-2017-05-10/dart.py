#!/usr/bin/python
# -*- coding: utf-8 -*-

# Second Year ENSTA Bretagne SPID Project
#    D : Brian Detourbet
#    A : Elouan Autret
#    A : Fahad Al Shaik
#    R : Corentin Rifflart
#    R : Clément Rodde
#    T : Rémi Terrien

# Code modified in May 2016, by BenBlop (small changes to conform with
#  new DART)

# Code modified in May 2017, by BenBlop (big changes to adapt to Irvin's
# drivers and to communicate with V-REP using sockets

# student starting code

import os
import time
import math
import struct
import sys
from threading import Thread


def high_low_int(high_byte, low_byte):
    '''
    Convert low and low and high byte to int
    '''
    return (high_byte << 8) + low_byte

def high_byte(integer):
    '''
    Get the high byte from a int
    '''
    return integer >> 8


def low_byte(integer):
    '''
    Get the low byte from a int
    '''
    return integer & 0xFF

class Dart():
    def __init__(self):

        
        # test if on real robot, if yes load the drivers
        # if os.access("/var/www/daarrt.conf", os.F_OK) :
        if os.access("/sys/class/gpio/gpio266", os.F_OK) :
            print ("Real DART is being created")

            # Import modules
            from drivers.trex import TrexIO
            from drivers.sonars import SonarsIO
            from drivers.razor import RazorIO
            from drivers.rear_odo import RearOdos

            self.__trex = TrexIO()
            self.__sonars = SonarsIO()
            self.__razor = RazorIO()
            self.__rear_odos = RearOdos()
            self.__trex.command["use_pid"] = 0 # 1

        # if not create virtual drivers for the robot running in V-REP
        else :
            print ("Virtual DART is being created")

            import threading

            import socket
            import sys
            import struct
            import time
 
            # socket connection to V-REP
            self.__HOST = 'localhost'  # IP of the sockect
            self.__PORT = 30100 # port (set similarly in v-rep)

            self.__s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            print ('Socket created')

            # bind socket to local host and port
            try:
                # prevent to wait for  timeout for reusing the socket after crash
                # from :  http://stackoverflow.com/questions/29217502/socket-error-address-already-in-use
                self.__s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
                self.__s.bind((self.__HOST, self.__PORT))
            except socket.error as msg:
                print (msg)
                sys.exit()
            print ('Socket bind completed')
             
            # start listening on socket
            self.__s.listen(10)
            print ('Socket now listening')

            # reset variables 
            self.__vMotorLeft =  0.0
            self.__vMotorRight = 0.0
            self.__vEncoderLeft = 0
            self.__vEncoderRight = 0
            self.__vSonarLeft = 0.0
            self.__vSonarRight = 0.0
            self.__vSonarFront = 0.0
            self.__vSonarRear = 0.0
            self.__vHeading =  0.0

            # initiate communication thread with V-Rep
            self.__simulation_alive = True
            a = self.__s
            vrep = threading.Thread(target=self.vrep_com_socket,args=(a,))
            vrep.start()

            # start virtual drivers 
            import vDaarrt.modules.vTrex as vTrex
            import vDaarrt.modules.vSonar as vSonar
            import vDaarrt.modules.vRazor as vRazor

            self.__trex = vTrex.vTrex()
            self.__razor = vRazor.vRazorIO()
            self.__sonars = vSonar.vSonar(self)



    @property
    def s(self):
        return self.__s

    @property
    def vMotorLeft(self):
        return self.__vMotorLeft

    @property
    def vMotorRight(self):
        return self.__vMotorRight

    @property
    def vSonarFront(self):
        return self.__vSonarFront

    @property
    def vSonarRear(self):
        return self.__vSonarRear

    @property
    def vSonarLeft(self):
        return self.__vSonarLeft

    @property
    def vSonarRight(self):
        return self.__vSonarRight

    @property
    def vEncoderLeft(self):
        return self.__vEncoderLeft

    @property
    def vEncoderRight(self):
        return self.__vEncoderRight

    @property
    def simulation_alive(self):
        return self.__simulation_alive

    @property
    def vHeading(self):
        return self.__vHeading

    @property
    def angles(self):
        return self.__razor.angles 
    
    def vrep_com_socket(vdart,s):
        print (s)
        RECV_BUFFER = 4096 # buffer size 
        while True:
            #wait to accept a connection - blocking call
            conn, addr =  s.accept()
            print ('Connected with ' + addr[0] + ':' + str(addr[1]))
            #print (conn)

            while True:
                #print ("socket read",conn)
                data = conn.recv(RECV_BUFFER)
                #print (len(data))
                hd0,hd1,sz,lft,vSonarFront, vSonarRear,vSonarLeft, vSonarRight, vEncoderLeft, vEncoderRight, vHeading, simulationTime = struct.unpack('<ccHHffffffff',data)
                #print (hd0,hd1,sz,lft,vSonarFront, vSonarRear,vSonarLeft, vSonarRight, vEncoderLeft, vEncoderRight, vHeading, simulationTime)

                #print (vEncoderLeft, vEncoderRight, vHeading)

                vdart.vrep_update_sim_param (vEncoderLeft,vEncoderRight,vSonarLeft,vSonarRight,vSonarFront,vSonarRear,vHeading)

                vMotorLeft = vdart.vMotorLeft
                vMotorRight = vdart.vMotorRight

                strSend = struct.pack('<BBHHff',data[0],data[1],8,0,vMotorLeft,vMotorRight)
                conn.send(strSend)
                if not vdart.simulation_alive:
                    break
                time.sleep(0.010)

            if not vdart.simulation_alive:
                break



    def vrep_update_sim_param (self,vEncoderLeft,vEncoderRight,vSonarLeft,vSonarRight,vSonarFront,vSonarRear,vHeading):
        self.__vEncoderLeft = vEncoderLeft
        self.__vEncoderRight = vEncoderRight
        self.__vSonarLeft = vSonarLeft
        self.__vSonarRight = vSonarRight
        self.__vSonarFront = vSonarFront
        self.__vSonarRear = vSonarRear
        self.__trex.status["left_encoder"] = vEncoderLeft
        self.__trex.status["right_encoder"] = vEncoderRight
        self.__vMotorLeft = self.__trex.command["left_motor_speed"]
        self.__vMotorRight = self.__trex.command["right_motor_speed"]
        self.__vHeading = vHeading

    # insert here your functions to control the robot using motors, sonars
    # encoders and heading

    def stop(self):
        print ("Game Over")
        # add a command to stop the motors
        self.set_speed(0,0)
        self.__trex.i2c_write()
        # stop the connection to the simulator    
        self.__simulation_alive = False
   
    def set_speed(self, speed_left, speed_right):
        self.__trex.command["left_motor_speed"] = speed_left
        self.__trex.command["right_motor_speed"] = speed_right
        self.__trex.i2c_write() 
    
    def get_odometers(self):
        vLeft = self.__trex.status ['left_encoder']
        vRight = self.__trex.status ['right_encoder']
        return vLeft, vRight  
        
    def get_distance(self, direction):
        return(self.__sonars.get_distance(direction))
    
    def get_angles(self):
        return(self.__razor.angles[0])
        #return(self.__vHeading)

    def goCap(self, trigo):
        self.set_speed(50,-50)
        while(self.get_angles()-trigo > 2 or self.get_angles()-trigo < -2):
            continue
        self.set_speed(0,0)
 
    def center(self, a,b,s):
        
        if s<=-180:
            s = s + 360
        elif s > 180:
            s = s - 360
        #a entre -180 et 180
        #b entre -180 et 180
        return(s)


    def setHeading(self, head):
        #head entre 0 et 360
        headErrMax = 1
        headOK = False
        while not headOK :
            headMes = self.get_angles()
            headErr = head - headMes
            headErr = self.center(head, headMes, headErr)
            vit = abs(headErr)/4 + 30
            if headErr >=0 :
                self.set_speed(vit,-vit)
            else :
                self.set_speed(-vit,vit)

            if abs(headErr) < headErrMax:
                print("ca marche Michel")
                headOK = True
                self.set_speed(0,0)
            else:
                #print(self.__vHeading)
                #print(abs(headErr) - headErrMax)
                time.sleep(0.1)

    def goLineHeading (self,head,speed, duration):
        self.setHeading(head)
        time.sleep(0.1)
        capInitial=head
        t0=time.time()
        t1=time.time()
        while t1-t0 < duration:
            t1=time.time()
            capFinal=self.get_angles()
            diff = capInitial-capFinal
            diff = self.center(capInitial, capFinal, diff)
            #print(capInitial-capFinal)
            if capInitial-capFinal>0:
                self.set_speed(speed+3,speed)
            else:
                self.set_speed(speed, speed+3)
        self.set_speed(0,0)

    def goLineOdo (self,speed, duration):
        self.setHeading(50)
        t0=time.time()
        t1=time.time()
        gauche0, droite0=self.get_odometers()
        while t1-t0 < duration:
            t1=time.time()
            gauche1, droite1=self.get_odometers()
            time.sleep(0.1)
            #print((gauche1 - gauche0) - (droite1-droite0) )
            if (gauche1 - gauche0) - (droite1-droite0) > 1:
                self.set_speed(speed, speed + 3)
            elif (gauche1 - gauche0) - (droite1-droite0) < -1:
                self.set_speed(speed + 3, speed)
            gauche0, droite0 = gauche1, droite1

            
    def obstacleAvoid(self):
        self.set_speed(0,0)
        self.setHeading(self.get_angles()+90)
        """ A perfectionner plus tard """

    def goCurveOdo (self,speedTan, radius, sign, duration):

        t0=time.time()
        t1=time.time()
        while t1-t0 < duration:
            if sign==1:
                self.goLineHeading (self.setHeading(1,1),(50,-50), 0.1)
            else:
                self.goLineHeading (self.setHeading(1,1),(-50,50), 0.1)


STATE_FORWARD = 1
STATE_TURN_LEFT = 2
STATE_TURN_RIGHT = 3
STATE_STOP = 0
             
                
class FSMfacile():
    """FSM basique du robot, où les avancées sont pré-programmées, et les rotations aussi (90°)"""
    
    def __init__(self,robot):

        self.state = 0
        self.nxtState = 0
        self.robot = robot
        self.dMax = 1
        
    def arret(self,robot):
       robot.set_speed(0,0)
   
    def avancer(self,robot):
        
        d = robot.get_distance("front")
        if d<=0.005:
            d = 1000
        print(d)
        if d < self.dMax :
            robot.obstacleAvoid()
            print("manoeuvre evitement")
        else:
            robot.goLineHeading(robot.get_angles(),60,0.2)
        
    def rotationDroite(self,robot):
        robot.setHeading(robot.get_angles()+90)
        self.nxtState = 0
        
    def rotationGauche(self,robot):
        robot.setHeading(robot.get_angles()-90)
        self.nxtState = 0
    
        
    def global_next_state(self, key):
        if key == 'a':
            self.nxtState = STATE_FORWARD
        elif key == 'g':
            self.nxtState = STATE_TURN_LEFT
        elif key == 'd':
            self.nxtState = STATE_TURN_RIGHT
        elif key == 's':
            self.nxtState = STATE_STOP

    
    def run(self):        
        if self.nxtState == STATE_FORWARD:
            self.state = 1
            print("Avancer")
            self.avancer(self.robot)
            

        elif self.nxtState == STATE_TURN_LEFT:
            self.state = 2
            print("Rotation gauche")
            self.rotationGauche(self.robot)
            
        elif self.nxtState == STATE_TURN_RIGHT:
            self.state == 3
            print("Rotation Droite")
            self.rotationDroite(self.robot)
            
        elif self.nxtState == STATE_STOP:
            self.state = 0
            self.arret(self.robot)
            
            
class Key_listener(Thread):
    def __init__(self, fsm):
        Thread.__init__(self)
        self.fsm = fsm
    
    def run(self):
        while True:
            l = input("fsm : ")
            self.fsm.global_next_state(l)


if __name__ == "__main__":
    myDart = Dart()
#    myDart.obstacleAvoid()
#   arrêt
#    myDart.stop()

    fsm = FSMfacile(myDart)
    kl = Key_listener(fsm)
    kl.start()
    print("en avant Michel")
    while True:
        fsm.run()

