import time
import os
import sys
import math as mt

class vGPIO():
    """
    vGPIO simulation PCDUINO GPIO ports (in and out)
    also simulate the sonar by combining in and out ports and
    using the distance received from v-rep (in vdart)
    """

    __HIGH = "1"
    __LOW = "0"
    __TRIG_PULSE_MIN = 1e-5
    __SPEED_OF_SOUND = 340.0 # meters/sec

    def __init__(self, id) :
        # value file of GPIO
        self.__value = vGPIO.__LOW         
        self.__id = id
        self.__pulse_trig = False
        self.__pulse_cnt = 0.0
        self.__t_rise = 0.0
        self.__t_fall = 0.0
        self.__t_last = 0.0
        self.__vdart = None
    
    @property
    def id(self):
        return self.__id

    @property
    def t_fall(self):
        return self.__t_fall

    @property
    def t_rise(self):
        return self.__t_rise

    @property
    def pulse_trig(self):
        return self.__pulse_trig

    def set_id_in(self,gpio_in):
        self.__gpio_in = gpio_in

    def set_t_fall(self,val):
        self.__t_fall = val

    def set_t_rise(self,val):
        self.__t_rise = val

    def set_pulse_trig(self,val):
        self.__pulse_trig = val

    def set_vdart(self,val):
        self.__vdart = val

    def sonar_time_of_flight(self):
        dist = 10.0+0.1
        # get distance from the appropriate sonar
        # using GPIO in port 
        if self.__id == 231:
            dist = self.__vdart.vSonarRear
        if self.__id == 232:
            dist = self.__vdart.vSonarLeft
        if self.__id == 259:
            dist = self.__vdart.vSonarFront
        if self.__id == 234:
            dist = self.__vdart.vSonarRight
        return 2.0*dist/340.

    def is_high(self) :

        if self.__gpio_in.pulse_trig:
            self.__pulse_trig = True
            self.__pulse_cnt = self.sonar_time_of_flight()
            self.__gpio_in.set_t_fall(0.0)
            self.__gpio_in.set_t_rise(0.0)
            self.__gpio_in.set_pulse_trig(False)
            self.__t_last = time.time()
            #print ("Tx detected, cnt=",self.__pulse_cnt)
            return  True

        if self.__pulse_trig:
            if (time.time()-self.__t_last) < self.__pulse_cnt:
                #print (time.time()-self.__t_last)
                return True
            else:
                #print ("End of pulse")
                self.__pulse_trig = False
                self.__pulse_cnt = 0.0
                return False
        return False



    def set_high(self) :
        if self.__value!=vGPIO.__HIGH:
            self.__t_rise = time.time()
            #print (self.__id," set high")
        self.__value=vGPIO.__HIGH

    def set_low(self) :
        if self.__value==vGPIO.__HIGH:
            self.__t_fall = time.time()
            self.__pulse_trig=False
            if (self.__t_fall - self.__t_rise) >  vGPIO.__TRIG_PULSE_MIN:
                self.__pulse_trig=True
                #print (self.__id," set low",self.__t_fall-self.__t_rise,self.__pulse_trig)
        self.__value=vGPIO.__LOW

    

class vSonar():
    # Ensure we don't have a zillion fd on the vGPIO pins if the students 
    # call this class' __init__ several times
    __PIN_MAP = {"rear": (vGPIO(231),vGPIO(230)),
                 "left": (vGPIO(232),vGPIO(34)), 
                 "front": (vGPIO(259),vGPIO(233)), 
                 "right": (vGPIO(234),vGPIO(229))}

    __MAX_DIST = 10 # maximum distance
    __SPEED_OF_SOUND = 340.0 # meters/sec

    def __init__(self,vdart):
        self.__vDart = vdart
        self.all_pin_in=[]
        self.all_pin_out=[]
        for pin_in, pin_out in vSonar.__PIN_MAP.values():
            pin_out.set_low()
            pin_in.set_id_in(pin_out)
            pin_in.set_vdart(vdart)
            pin_out.set_vdart(vdart)

    def get_distance(self, sonar_key):
        """
        Triggers the sonar referenced by ''sonar_key'' and returns the one-way
        travel time to the nearest obstacle.
        
        Parameters:
            sonar_key: string, one of ''front'', ''rear'', ''left'', ''right''
            
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

        distance = -1
        Tmax = 2*self.__MAX_DIST/self.__SPEED_OF_SOUND
	
        #impulsion de 10micros
        pin_out.set_high()
        time.sleep(1e-5)
        pin_out.set_low()

        #reception    
        pin_in.set_high()
        t0 = time.time()
        t1 = 0
        while(pin_in.is_high() and t1-t0 < Tmax):
            t1 = time.time()	
        pin_in.set_low()

        if (t1-t0) >= Tmax:
            distance = 1000
        else:
            distance = self.__SPEED_OF_SOUND * (t1-t0) / 2

        if distance < 0.001:
            distance = 1000

        return distance


