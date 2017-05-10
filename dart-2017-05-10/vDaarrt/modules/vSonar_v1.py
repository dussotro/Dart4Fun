import time
import os
import threading
import sys

class vGPIO():
    
    __HIGH = "1"
    __LOW = "0"
    __PIN_PATH = os.path.normpath('./gpio/gpio')

    def __init__(self, id) :
        # check if the pin has been set as input or output
        mode_fd = open(vGPIO.__PIN_PATH + str(id) + "/direction", "r")
        if "in" in mode_fd.read():
            self.__is_input = True
            # for simulation using r+ allows fro sim to modify the file
            self.__pin_fd = open(vGPIO.__PIN_PATH + str(id) + "/value", "r+")
        else:
            self.__is_input = False
            self.__pin_fd = open(vGPIO.__PIN_PATH + str(id) + "/value", "w")

        self.__id = id
        mode_fd.close()

    @property
    def is_input(self):
        return self.__is_input
    
    @property
    def id(self):
        return self.__id
        
    def is_high(self) :
        """
        Returns True if the input level is high, False otherwise.
        Will raise IOError if the pin has been set as output.
        """
        if not self.is_input:
            raise IOError("Pin number %d an output pin"%self.id)
        self.__pin_fd.seek(0)
        return self.__pin_fd.read(1)==vGPIO.__HIGH

    def set_high(self) :
        """
        In sim no errors raised with writing an input pin ...
        ... no other way to put V-REP sonar range in the sim sonar device
        """
        #if self.is_input:
        #   raise IOError("Pin number %d is an input pin"%self.id)
        #print ("set id=",self.__id,vGPIO.__HIGH)
        self.__pin_fd.seek(0)
        self.__pin_fd.write(vGPIO.__HIGH)
        self.__pin_fd.write('\n')
        self.__pin_fd.flush()

    def set_low(self) :
        """
        In sim no errors raised with writing an input pin ...
        ... no other way to put V-REP sonar range in the sim sonar device
        """
        #if self.is_input:
        #    raise IOError("Pin number %d is an input pin"%self.id)
        #print ("reset id=",self.__id,vGPIO.__LOW)
        self.__pin_fd.seek(0)
        self.__pin_fd.write(vGPIO.__LOW)
        self.__pin_fd.write('\n')
        self.__pin_fd.flush()


class vSonar():
    # Ensure we don't have a zillion fd on the vGPIO pins if the students 
    # call this class' __init__ several times
    __PIN_MAP = {"rear": (vGPIO(231),vGPIO(230)),
                 "left": (vGPIO(232),vGPIO(34)), 
                 "front": (vGPIO(259),vGPIO(233)), 
                 "right": (vGPIO(234),vGPIO(229))}

    __MAX_DIST = 10 # maximum distance
    __SPEED_OF_SOUND = 340.0 # meters/sec
    
    def __init__(self):
        for pin_in, pin_out in vSonar.__PIN_MAP.values():
            pin_out.set_low()

    def simEcho(gpioPinIn):
        gpioPinIn.set_low() # set pulse low at end of time of flight
        #sys.stdout.write("+")
        sys.stdout.flush()
            
    def get_distance(self, sonar_key):
        """
        Triggers the sonar referenced by ''sonar_key'' and returns the one-way
        travel time to the nearest obstacle.
        
        Parameters:
            sonar_key: string, one of ''front'', ''back'', ''left'', ''right''
            
        Return value:
            travel_time: float, -1 on error, ''math.inf'' if the sonar can't
                detect any obstacle or the one way travel time in seconds to
                the nearest obstacle.
        """
        try:
            pin_in, pin_out = vSonar.__PIN_MAP[sonar_key]
        except KeyError:
            print("There is no such key as: "+sonar_key)
            return -1

        # get the sonar distance from V-REP
        sonarRangeVrep = 0.8
        sonarTimeOfFly = (sonarRangeVrep*2.0)/vSonar.__SPEED_OF_SOUND
        
        pin_out.set_low()
        pin_out.set_high()
        time.sleep(1e-5)
        pin_out.set_low()
        t = threading.Timer(sonarTimeOfFly, vSonar.simEcho, [pin_in])

        # Sometimes the answer is too fast so it isn't caught, sometimes the 10us pulse is not caught by the PCDuino (python not much precise with time.sleep())
        start = time.time()
        pin_in.set_high()
        while not pin_in.is_high():
            if time.time()- start > 1e-3:
                print("No answer from sonar: "+sonar_key)
                return -1

        # sometimes there are fake detections faster than the time elapsed 
        # between these two loops
        timeOut = 2.0*vSonar.__MAX_DIST/vSonar.__SPEED_OF_SOUND
        start = time.time()   
        t.start()
        stop = start      
        while pin_in.is_high():
            #sys.stdout.write(".")
            sys.stdout.flush()
            stop = time.time()
            if (stop - start) > timeOut:
                #print (stop-start,timeOut,sonarTimeOfFly)
                return 9999.99
                
        return (stop-start)*vSonar.__SPEED_OF_SOUND/2.0


