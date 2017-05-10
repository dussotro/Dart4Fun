'''
@auhtor : Corentin R
@date : February 2015

This file contains the function called by the programm when running on simulation

'''


import pygame,pylygon,threading,sys,time
from pygame.locals import *

from modules.daarrt2d import *
from modules.world import *
from modules.constantes import *
from modules.info import *

HIGH    = "1"
LOW     = "0"
INPUT   = "0"
OUTPUT  = "1"

t0sim = time.time()


def simulate(ns,package,changeData,changeDataEnco,sonarLeft,sonarRight, sonarFront , sonarBack , changeCap):

    #creation of objects required
    myWorld=World(worldName)
    worldLenght=myWorld.generer()
    #print worldLenght
    pygame.init()
    simu=pygame.display.set_mode((worldLenght[0]+windowWidth,worldLenght[1]))
    info=Info(worldLenght)
    bg=pygame.image.load(background).convert()
    pygame.display.set_caption(titre)

    #first printingFront
    pos=myWorld.afficher(simu,True)
    daarrt2d=DAARRT2d(pos)


    #simulation loop
    pygame.key.set_repeat(400, 30)
    runSimu=True
    display=0

    while(runSimu==True) :
        #Limitation vitesse
        pygame.time.Clock().tick(speed)
        simu.blit(bg,(0,0))
        myWorld.afficher(simu,False)

        #package,changeData=cleanBus(package,changeData,changeDataEnco,daarrt2d)
        cleanBus(package,changeData,changeDataEnco,daarrt2d)
        runSimu=daarrt2d.update(package,myWorld,changeCap)
        info.afficher(simu,daarrt2d,display)
        daarrt2d.draw(simu)
        virtualSonar(ns,daarrt2d,myWorld,sonarLeft,sonarRight,sonarFront,sonarBack)
        pygame.display.flip()
        for event in pygame.event.get():
            if event.type == pygame.QUIT :
                runSimu = False
            if event.type == pygame.MOUSEBUTTONDOWN and event.pos[0]<worldLenght[0] + 40 and event.pos[0] > worldLenght[0] + 10 and event.pos[1] < worldLenght[1] - 30 and event.pos[1] > worldLenght[1] - 60 :
                display += 1
                if display >= 2 :
                    display = 0
            if event.type == KEYDOWN and event.key == K_l :

                if display == 2 :

                    display = 0

                else :

                    display = 2
        try:
            runSimu = ns.isAlive
        except:
            runSimu = False

    print "Ending Simulation..."
    pygame.quit()
    #ns.isAlive=False

def cleanBus1(package,changeData,changeDataEnco,daarrt):
    '''
    return the package updated and the element change Data cleaned

    args :
        package : dictionnary corresponding to the bus
        changeData : list of elements which changed since the last update
    '''

    while(len(changeData)>0):
        try :
            package[changeData[-1][0]]=changeData[-1][1]
            changeData.pop()
        except : pass
    while(len(changeDataEnco)>0):
        try :
            changeDataEnco.pop()
        except : pass
    changeDataEnco.append(["LeftEnco",daarrt.leftEnco])
    changeDataEnco.append(["RightEnco",daarrt.rightEnco])
    return package,changeData


def cleanBus(package,changeData,changeDataEnco,daarrt):
    '''
    return the package updated and the element change Data cleaned

    args :
        package : dictionnary corresponding to the bus
        changeData : list of elements which changed since the last update
    '''
    try:
        nchg=len(changeData)
    except:
        nchg=-1
        print "fail accessing changeData"

    if nchg > 0:
        updt=[]        
        while(len(changeData)>0):
            try :
                #print "change data : ",time.time()-t0sim,changeData[-1][0],changeData[-1][1]
                #package[changeData[-1][0]]=changeData[-1][1]
                updt.append([changeData[-1][0],changeData[-1][1]])
                changeData.pop()
            except : pass
        # cmd order is inverted should be FIFO but is actually FILO so correct it below
        for i in range(len(updt)):    
            ir = len(updt)-1-i
            package[updt[ir][0]]=updt[ir][1]
            #print "change data actual : ",time.time()-t0sim,updt[ir][0],updt[ir][1]
    
    try:
        nchg=len(changeDataEnco)
    except:
        nchg=-1
        print "fail accessing changeDataEnco"
   
    if nchg > 0:
        while(len(changeDataEnco)>0):
            try :
                changeDataEnco.pop()
            except : pass
                
    try:
        changeDataEnco.append(["LeftEnco",daarrt.leftEnco])
        changeDataEnco.append(["RightEnco",daarrt.rightEnco])
    except:
        print "Fail shared memory encoders"
        
    #return package,changeData

def virtualSonar(ns,daarrt2d,world,sonarLeft,sonarRight,sonarFront,sonarBack):
    changeSonarLeft = sonarLeft.changeSonarLeft
    changeSonarRight = sonarRight.changeSonarRight
    changeSonarFront = sonarFront.changeSonarFront
    changeSonarBack = sonarBack.changeSonarBack

    #print daarrt2d.sonarDist
    try:
        try :
            if(len(changeSonarLeft)>1):
                changeSonarLeft.pop()
        except :  print "Fail Sonar Left"
        try :
            changeSonarLeft.append(daarrt2d.sonarDist[2])
        except :  print "Fail Shared Memory Sonar Left"
    
    
        try :
            if(len(changeSonarRight)>1):
                changeSonarRight.pop()
        except : print "Fail Sonar Right"
        try :
            changeSonarRight.append(daarrt2d.sonarDist[3])
        except :  print "Fail Shared Memory Sonar Right"
    
    
        try :
            if(len(changeSonarFront)>1) :
                changeSonarFront.pop()
                #print changeSonarFront
        except : print "Fail Sonar Front"
        try :
            changeSonarFront.append(daarrt2d.sonarDist[0])
        except :  print "Fail Shared Memory Sonar Front"
        
        try :
            if(len (changeSonarBack)>1):
                changeSonarBack.pop()
        except : print "Fail Sonar Back"
        try :
            changeSonarBack.append(daarrt2d.sonarDist[1])
        except :  print "Fail Shared Memory Sonar Back"
    except:
        print "Namespace ns is down ..."
            
        #print daarrt2d.sonarDist


dtSonar = 0.00001
dtChange = 0.01

#dtSonar = 0.0000001
#dtChange = 0.25
        

def sonarFrontDeamon(ns,sonarFront,changeSonarFront):
    print "Starting Front Sonar Deamon..."
    simuOn=True
    tMax=5.0*2.0/3.4 # 5 meters max
    tFront=tMax
    tx = sonarFront.tx
    rx = sonarFront.rx
    t0=time.time()
    init=True
    while init:
        try:
            if len(changeSonarFront)>1:
                val=changeSonarFront.pop()
                tFront=2.0*val/34000.0
                changeSonarFront.append(val)
                init=False
        except:
            # can't get sonar
            #tFront = tMax
            pass
        time.sleep(dtSonar)      
    print "Front Sonar Ready ..."        
    while simuOn:
        if (time.time()-t0) > dtChange:
            t0=time.time()
            try:
                if len(changeSonarFront)>1:
                    val=changeSonarFront.pop()
                    tFront=2.0*val/34000.0
                    changeSonarFront.append(val)
            except:
                # can't get sonar
                #tFront = tMax
                pass
        if tx.read() == HIGH:
            time.sleep(sonarFront.txDuration)
            #while tx.read() == HIGH:
            #    time.sleep(dtSonar)
            #print "tx Front",tFront,val
            time.sleep(dtSonar)
            rx.write(HIGH)
            time.sleep(tFront)
            rx.write(LOW)
            #print "rx front",tFront,tFront*34000.0/2.0,val
        time.sleep(dtSonar)
        try:
            simuOn = ns.isAlive
        except:
            simuOn = False    
    print "Ending Front Sonar Deamon..."

def sonarBackDeamon(ns,sonarBack,changeSonarBack):
    print "Starting Back Sonar Deamon..."
    simuOn=True
    tMax=5.0*2.0/3.4 # 5 meters max
    tBack=tMax
    tx = sonarBack.tx
    rx = sonarBack.rx
    t0=time.time()
    init=True
    while init:
        try:
            if len(changeSonarBack)>1:
                val=changeSonarBack.pop()
                tBack=2.0*val/34000.0
                changeSonarBack.append(val)
                init=False
        except:
            # can't get sonar
            #tBack = tMax
            pass
        time.sleep(dtSonar)      
    print "Back Sonar Ready ..."        
    while simuOn:
        if (time.time()-t0) > dtChange:
            t0=time.time()
            try:
                if len(changeSonarBack)>1:
                    val=changeSonarBack.pop()
                    tBack=2.0*val/34000.0
                    changeSonarBack.append(val)
            except:
                # can't get sonar
                #tBack = tMax
                pass
        if tx.read() == HIGH:
            time.sleep(sonarBack.txDuration)
            #while tx.read() == HIGH:
            #    time.sleep(dtSonar)
            #print "tx Back",tBack,val
            time.sleep(dtSonar)
            rx.write(HIGH)
            time.sleep(tBack)
            rx.write(LOW)
            #print "rx Back",tBack,val
        time.sleep(dtSonar)
        try:
            simuOn = ns.isAlive
        except:
            simuOn = False    
    print "Ending Back Sonar Deamon..."


def sonarLeftDeamon(ns,sonarLeft,changeSonarLeft):
    print "Starting Left Sonar Deamon..."
    simuOn=True
    tMax=5.0*2.0/3.4 # 5 meters max
    tLeft=tMax
    tx = sonarLeft.tx
    rx = sonarLeft.rx
    t0=time.time()
    init=True
    while init:
        try:
            if len(changeSonarLeft)>1:
                val=changeSonarLeft.pop()
                tLeft=2.0*val/34000.0
                changeSonarLeft.append(val)
                init=False
        except:
            # can't get sonar
            #tLeft = tMax
            pass
        time.sleep(dtSonar)      
    print "Left Sonar Ready ..."        
    while simuOn:
        if (time.time()-t0) > dtChange:
            t0=time.time()
            try:
                if len(changeSonarLeft)>1:
                    val=changeSonarLeft.pop()
                    tLeft=2.0*val/34000.0
                    changeSonarLeft.append(val)
            except:
                # can't get sonar
                #tLeft = tMax
                pass
        if tx.read() == HIGH:
            time.sleep(sonarLeft.txDuration)
            #while tx.read() == HIGH:
            #    time.sleep(dtSonar)
            #print "tx Left",tLeft,val
            time.sleep(dtSonar)
            rx.write(HIGH)
            time.sleep(tLeft)
            rx.write(LOW)
            #print "rx Left",tLeft,val
        time.sleep(dtSonar)
        try:
            simuOn = ns.isAlive
        except:
            simuOn = False    
    print "Ending Left Sonar Deamon..."

def sonarRightDeamon(ns,sonarRight,changeSonarRight):
    print "Starting Right Sonar Deamon..."
    simuOn=True
    tMax=5.0*2.0/3.4 # 5 meters max
    tRight=tMax
    tx = sonarRight.tx
    rx = sonarRight.rx
    t0=time.time()
    init=True
    while init:
        try:
            if len(changeSonarRight)>1:
                val=changeSonarRight.pop()
                tRight=2.0*val/34000.0
                changeSonarRight.append(val)
                init=False
        except:
            # can't get sonar
            #tRight = tMax
            pass
        time.sleep(dtSonar)      
    print "Right Sonar Ready ..."        
    while simuOn:
        if (time.time()-t0) > dtChange:
            t0=time.time()
            try:
                if len(changeSonarRight)>1:
                    val=changeSonarRight.pop()
                    tRight=2.0*val/34000.0
                    changeSonarRight.append(val)
            except:
                # can't get sonar
                #tRight = tMax
                pass
        if tx.read() == HIGH:
            time.sleep(sonarRight.txDuration)
            #while tx.read() == HIGH:
            #    time.sleep(dtSonar)
            #print "tx Right",tRight,val
            time.sleep(dtSonar)
            rx.write(HIGH)
            time.sleep(tRight)
            rx.write(LOW)
            #print "rx Right",tRight,val
        time.sleep(dtSonar)
        try:
            simuOn = ns.isAlive
        except:
            simuOn = False    
    print "Ending Right Sonar Deamon..."


