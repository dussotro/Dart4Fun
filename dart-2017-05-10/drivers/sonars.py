#!/usr/bin/env python
# -*- coding: utf8 -*-

import os
import time
from math import inf

class GPIO():
    
    __HIGH = "1"
    __LOW = "0"
    __PIN_PATH = os.path.normpath('/sys/class/gpio/gpio')

    def __init__(self, id) :
        # check if the pin has been set as input or output
        mode_fd = open(GPIO.__PIN_PATH + str(id) + "/direction", "r")
        if "in" in mode_fd.read():
            self.__is_input = True
            self.__pin_fd = open(GPIO.__PIN_PATH + str(id) + "/value", "r")
        else:
            self.__is_input = False
            self.__pin_fd = open(GPIO.__PIN_PATH + str(id) + "/value", "w")

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
        return self.__pin_fd.read(1)==GPIO.__HIGH

    def set_high(self) :
            if self.is_input:
                raise IOError("Pin number %d is an input pin"%self.id)
            #self.__pin_fd.seek(0)
            self.__pin_fd.write(GPIO.__HIGH)
            self.__pin_fd.flush()

    def set_low(self) :
            if self.is_input:
                raise IOError("Pin number %d is an input pin"%self.id)
            #self.__pin_fd.seek(0)
            self.__pin_fd.write(GPIO.__LOW)
            self.__pin_fd.flush()

class SonarsIO():
    # Ensure we don't have a zillion fd on the GPIO pins if the students 
    # call this class' __init__ several times
    __PIN_MAP = {"rear": (GPIO(231),GPIO(230)),
                 "left": (GPIO(232),GPIO(34)), 
                 "front": (GPIO(259),GPIO(233)), 
                 "right": (GPIO(234),GPIO(229))}

    __MAX_DIST = 10 # maximum distance
    __SPEED_OF_SOUND = 340.0 # meters/sec
    
    def __init__(self):
        for pin_in, pin_out in SonarsIO.__PIN_MAP.values():
            pin_out.set_low()
            
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
            pin_in, pin_out = SonarsIO.__PIN_MAP[sonar_key]
        except KeyError:
            print("There is no such key as: "+sonar_key)
            return -1
            
        
        pin_out.set_low()
        pin_out.set_high()
        time.sleep(1e-5)
        pin_out.set_low()


        # Sometimes the answer is too fast so it isn't caught, sometimes the 10us pulse is not caught by the PCDuino (python not much precise with time.sleep())
        start = time.time()
        while not pin_in.is_high():
            if time.time()- start > 1e-3:
                print("No answer from sonar: "+sonar_key)
                return -1

        start = time.time()   
        # sometimes there are fake detections faster than the time elapsed 
        # between these two loops
        stop = start      
        while pin_in.is_high():
            stop = time.time()
            if (stop - start > SonarsIO.__MAX_DIST/SonarsIO.__SPEED_OF_SOUND):
                return inf

        return (stop-start)*SonarsIO.__SPEED_OF_SOUND/2

class SonarFilter():
    def __init__(self, dart, sonar_key, filter_len = 3):
        self.filter_len = filter_len
        self.sonar_key = sonar_key
        self.dist_array = np.array([dart.get_distance(sonar_key) for _ in range(filter_len)])
        self.dist_idx = 0

    def update(self):
        self.dist_array[self.dist_idx] = dart.get_distance(self.sonar_key)
        self.dist_idx = (self.dist_idx + 1)%self.filter_len

    @property
    def distance(self):
        # filter_len shouldn't be too big anyway so we don't need to be smart
        # with this moving average
        return np.mean(self.dist_array)



if __name__ == "__main__":
    sonars=SonarsIO()
    print(sonars.get_distance("left"))