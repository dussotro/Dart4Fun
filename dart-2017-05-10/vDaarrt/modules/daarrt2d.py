import time, math, sys,struct,random
import pygame,pylygon
from pygame.locals import *
from numpy import array
import math
import os
import geometry as geo

from constantes import *



def high_low_signed_int(high_byte, low_byte):
    '''
    Convert low and low and high byte to signed int
    '''

    return (high_byte << 8) + low_byte


class DAARRT2d:

    def __init__(self,daarrtpos):

        #variable values
        try :
            self.posX = daarrtpos[0]
            self.posY = daarrtpos[1]
        except :
            self.posX=  250.0
            self.posY = 250.0
        self.posXw=  50.0
        self.posYw = 380.0
        self.posX = self.posXw/elementScale
        self.posY = self.posYw/elementScale
        self.leftSpeed = 0.0
        self.rightSpeed = 0.0
        self.leftSpeedCmd = 0
        self.rightSpeedCmd = 0
        self.aLeftSpeed = 4.02
        self.bLeftSpeed = -3.0
        self.aRightSpeed = 3.98
        self.bRightSpeed = 4.0
        self.robotCapTrigo = 0.0
        self.robotCap = - self.robotCapTrigo # y axis upside down
        self.robotHead = (90. - self.robotCapTrigo + 360.) % 360.0 #angle between 0 and 360
        self.clawOpening = 0.0 #angle between 0 and 180 (0 close/180 open)
        self.clawHeight = 0.0 #angle between 0 and 180 (0 up/180 bottom)

        print "Robot start x,y,cap ",self.posX, self.posY, self.robotCap
        print "Robot start x,y,cap ",self.posXw, self.posYw, self.robotHead
        self.cmdClawOpening = 0.0
        self.cmdClawHeight = 0.0

        #geometry constant

        self.clawLenght = clawLenght
        self.clawWidthOpened = clawWidthOpened
        self.clawWidthClosed = clawWidthClosed
        self.clawBase=clawBase

        self.robotLenght = robotLenght
        self.robotWidth = robotWidth

        self.wheelLenght = wheelLenght
        self.wheelWidth = wheelWidth
        self.wheelRadius = wheelRadius

        self.sonarAngle= sonarAngle
        self.sonarLenght = sonarLenght

        self.nFrontSonar = nFrontSonar
        self.nLeftSonar = nLeftSonar
        self.nRightSonar = nRightSonar
        self.nBackSonar = nBackSonar

        #creating the robot

        self.daarrt = geo.createRobot(self)
        self.sonar = geo.createSonar(self,0)
        self.sonarLoc = geo.createSonar(self,1)
        #self.intersect = geo.createSonarIntersect(self)

        self.sonarDist=[0.0,0.0,0.0,0.0]

        self.leftEncoFloat=0.0
        self.rightEncoFloat=0.0
        self.leftEnco=0
        self.rightEnco=0

    def sonarCollide(self,world):
        #print "-------------------------------------------------"
        finalDist=[]
        j=0
        ib=0
        nsonar=len(self.sonar)
        for ison in range(nsonar):
            beam=self.sonar[ison]
            sonarLoc=self.sonarLoc[ison].P
            sonarLoc=sonarLoc[0]
            dist=None
            #self.intersect[ib][1] = self.intersect[ib][0] 
            #print "nb obstacles ",len(world.obstacle)
            iobs=0
            for obstacle in world.obstacle :
                intersect,xi,yi,di=geo.intersectpoly(beam,obstacle,sonarLoc)
                #print  ison,iobs,intersect,xi,yi,di
                if intersect:
                    if dist is None:
                        dist=di
                    else:
                        if di<dist:
                            dist=di
                iobs+=1
            if dist is None:
                finalDist.append(5000)
            else:                
                finalDist.append(dist)
            ib += 1
        # convert sonarDist to world coordinates
        #print finalDist
        
        for i in range(len(finalDist)):
            finalDist[i] *=  elementScale
            self.sonarDist[i]=finalDist[i]
        #print finalDist
        return finalDist

    def sonarCollideOld(self,world):
        finalDist=[]
        j=0
        ib=0
        for beam in self.sonar:
            dist=[]
            #self.intersect[ib][1] = self.intersect[ib][0] 
            #print "nb obstacles ",len(world.obstacle)
            iobs=0
            for obstacle in world.obstacle :
                if not beam.collidepoly(obstacle) is False :
                    print "------------------------------"
                    print iobs,ib
                    print beam.collidepoly(obstacle)
                    print obstacle
                    tmp=5000
                    i=0
                    for beamPoint in beam.P :
                        distance=(math.sqrt((beamPoint[0]-self.posX)*(beamPoint[0]-self.posX) + (beamPoint[1]-self.posY)*(beamPoint[1]-self.posY)))
                        if distance<tmp :
                            index=i
                            tmp=distance
                        i+=1
                    x0=beam.P[index][0]
                    y0=beam.P[index][1]
                    ply=pylygon.Polygon([(x0,y0)])
                    tmp1=ply.distance(obstacle)
                    print tmp
                    #print "[%d],dist %d = %f"%(ib,iobs,math.sqrt(tmp[0]*tmp[0] + tmp[1]*tmp[1]))
                    dist.append(math.sqrt(tmp1[0]*tmp1[0] + tmp1[1]*tmp1[1]))
                iobs+=1
            try :
                finalDist.append(min(dist))
                #finalDist.append(10*j)
                #j+=1
            except :
                finalDist.append(5000)
            ib += 1
        # convert sonarDist to world coordinates
        print finalDist
        
        for i in range(len(finalDist)):
            finalDist[i] *=  elementScale
            self.sonarDist[i]=finalDist[i]
        return finalDist
 
    def updateOdo(self,package) :
        # at 60 , 4 revol per seconds 220 tics 
        dt=0.1
        dB = self.leftSpeed*dt
        dA = self.rightSpeed*dt
        dLeftEnco =  nTicks*dB/(math.pi*wheelRadius*2)
        dRightEnco =  nTicks*dA/(math.pi*wheelRadius*2)
        #print "denco l,r",dLeftEnco,dRightEnco
        self.leftEncoFloat += dLeftEnco
        self.rightEncoFloat += dRightEnco
        self.leftEnco = int(self.leftEncoFloat+65536) % 65536
        self.rightEnco = int(self.rightEncoFloat+65536) % 65536
        
       

    def updateOdo1(self,package) :
        #motorLeftAngSpeed = 0
        #motorRightAngSpeed = 0

        dAG=math.sqrt(self.robotWidth**2 + self.robotLenght**2)/2
        dBG=dAG

        dTime = 1.0
        theta=self.robotCap*math.pi/180.0
        thetaPrime = (self.leftSpeed-self.rightSpeed)/self.robotWidth
        vGx =(((self.rightSpeed+self.leftSpeed)/self.robotWidth)*math.cos(theta))
        vGy = (((self.rightSpeed+self.leftSpeed)/self.robotWidth)*math.sin(theta))

        vAx = vGx + 0
        vAy = vGy + dAG * math.cos(theta)* thetaPrime
        vA=math.sqrt(vAx**2 + vAy**2)
        dA = vA*dTime

        vBx = vGx + 0
        vBy = vGy - dBG * math.cos(theta)* thetaPrime
        vB=math.sqrt(vBx**2 + vBy**2)
        dB = vB*dTime

        print vAx,vAy,vA,dA,(nTicks*dA/(math.pi*wheelRadius*2))
        print vBx,vBy,vB,dB,(nTicks*dB/(math.pi*wheelRadius*2))
#        try :
#            self.leftEnco += ((nTicks*dB/(math.pi*wheelRadius*2))*(thetaPrime/abs(thetaPrime)))
#            self.rightEnco += ((nTicks*dA/(math.pi*wheelRadius*2))*(thetaPrime/abs(thetaPrime)))
#        except :
#            self.leftEnco += (nTicks*dB/(math.pi*wheelRadius*2))
#            self.rightEnco += (nTicks*dA/(math.pi*wheelRadius*2))
        self.leftEnco += (nTicks*dB/(math.pi*wheelRadius*2))
        self.rightEnco += (nTicks*dA/(math.pi*wheelRadius*2))

        self.leftEnco = int(self.leftEnco) % 65335
        self.rightEnco = int(self.rightEnco) % 65335


    def update(self , package , world,changeCap):
        dt = 0.1
        self.updateSpeed(package)
        self.updateClaw(package)
        self.sonarCollide(world)
        self.updateOdo(package)
        theta=self.robotCap*math.pi/180.0
        self.posX += (((self.rightSpeed+self.leftSpeed)/self.robotWidth)*math.cos(theta))*dt
        self.posY += (((self.rightSpeed+self.leftSpeed)/self.robotWidth)*math.sin(theta))*dt
        self.robotCap += (self.leftSpeed-self.rightSpeed)*dt/self.robotWidth        
        self.robotCapMes = self.robotCap+(random.random()-0.5)*4.0
        self.robotCap = self.robotCap %360
        self.robotCapMes = float(round(self.robotCapMes %360))
        self.robotCapTrigo = -self.robotCap
        self.robotHead = 90.0 - self.robotCapTrigo
        if self.robotHead > 180.0:
            self.robotHead -= 360.0
        if self.robotHead <  -180.0:
            self.robotHead += 360.0
            
        self.daarrt = geo.createRobot(self)
        self.sonar=geo.createSonar(self,0)
        self.sonarLoc=geo.createSonar(self,1)

        try:
            while (len(changeCap)>0):
                try:
                    changeCap.pop()
                except : pass
            changeCap.append(self.robotCapMes)
        except:
            print ("Fail shared memory : heading")

        #if(self.collide(world)):
        #    print "Collision detectee"
        #    return False

        return True

    def updateClaw(self,package):
        cHeight=high_low_signed_int(package['servo_1_high_byte'],package['servo_1_low_byte'])
        cOpening=high_low_signed_int(package['servo_2_high_byte'],package['servo_2_low_byte'])
        if cHeight<=0:
            self.cmdClawHeight=0.0
        else :
            if cHeight>180 :
                self.cmdClawHeight=180.0
            else :
                self.cmdClawHeight=cHeight
        if cOpening<=0 :
            self.cmdClawOpening=0.0
        else :
            if cOpening>180 :
                self.cmdClawOpening=180.0
            else :
                self.cmdClawOpening=cOpening
        if self.clawHeight<self.cmdClawHeight-1 :
            self.clawHeight+=0.5
        elif self.clawHeight>self.cmdClawHeight+1:
            self.clawHeight-=0.5
        if self.clawOpening<self.cmdClawOpening-1 :
            self.clawOpening+=0.5
        elif self.clawOpening>self.cmdClawOpening-1 :
            self.clawOpening-=0.5

    def updateSpeed(self , package):
        lSpeed=high_low_signed_int(package['lm_speed_high_byte'],package['lm_speed_low_byte'])
        rSpeed=high_low_signed_int(package['rm_speed_high_byte'],package['rm_speed_low_byte'])
        self.leftSpeedCmd=lSpeed
        self.rightSpeedCmd=rSpeed
        lSpeed=-lSpeed
        rSpeed=-rSpeed
        #print lSpeed,rSpeed
        #st = "speed get: left=%d, right=%d, [%d,%d,%d,%d]"%(lSpeed,rSpeed,package['lm_speed_high_byte'],package['lm_speed_low_byte'],package['rm_speed_high_byte'],package['rm_speed_low_byte']) 
        #print st
        #os.system('echo "%s" >> sim.log'%(st))
        a=4.0 # should be -0.5 to be similar to real robot 
        b=0.0
        #print a,b
        if(lSpeed < 40 and lSpeed>-40):
            self.leftSpeed = 0.0
        elif(lSpeed>=0) :
            self.leftSpeed = self.aLeftSpeed*lSpeed + self.bLeftSpeed
        else :
            self.leftSpeed= self.aLeftSpeed*lSpeed - self.bLeftSpeed

        if(rSpeed < 40 and rSpeed>-40):
            self.rightSpeed=0.0
        elif(rSpeed>=0) :
            self.rightSpeed=self.aRightSpeed*rSpeed + self.bRightSpeed
        else :
            self.rightSpeed=self.aRightSpeed*rSpeed - self.bRightSpeed
        #os.system('echo "%d,%d,%f,%f" >> sim.log'%(lSpeed,rSpeed,self.leftSpeed,self.rightSpeed))
        


    def collide(self,world):
        for element in self.daarrt:
            for obstacle in world.obstacle :
                try :
                    (bool)(element.collidepoly(obstacle))
                except :
                    return 1
        return 0

    def draw(self,simulation):
        i=0
        for element in self.daarrt :
            if(i==6 or i==7):
                pygame.draw.polygon(simulation,(0,0,255),element.P,0)
            elif(i!=0):
                pygame.draw.polygon(simulation,(255,0,0),element.P,0)
            else:
                pygame.draw.polygon(simulation,(255,0,0),element.P,1)
            i+=1
        for sonar in self.sonar :
            pygame.draw.polygon(simulation,(40,100,83),sonar.P,1)
        #for its in self.intersect :
        #    pygame.draw.polygon(simulation,(0,255,127),its.P,1)
            # line(Surface, color, start_pos, end_pos, width=1)
        #    pygame.draw.line(simulation,(0,255,127),(its[0][0],its[0][1]),(its[1][0],its[1][1]),1)
