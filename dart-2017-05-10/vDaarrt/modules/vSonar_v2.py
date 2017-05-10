import time
import os
import threading
import sys

class vGPIO():
    
    __HIGH = "1"
    __LOW = "0"
    __PIN_PATH = os.path.normpath('./gpio/gpio')
    __TRIG_PULSE_MIN = 1e-5

    def __init__(self, id) :
        # value file of GPIO
        self.__value = vGPIO.__LOW         
        self.__id = id
        self.__pulse_trig = False
        self.__pulse_cnt = 0.0
        self.__t_rise = 0.0
        self.__t_fall = 0.0
        self.__t_last = 0.0
    
    @property
    def id(self):
        return self.__id
        
    def is_high(self) :
        ret_val = vGPIO.__LOW
        print (self.__pulse_cnt)
        if not self.__pulse_trig:
            ret_val = vGPIO.__LOW
        else:
            if self.__pulse_cnt > 0.0:
                t_cur = time.time()
                dt = self.__t_last - t_cur
                self.__pulse_cnt -= dt
                self.__t_last = t_cur
                ret_val = vGPIO.__HIGH
            else:
                self.__pulse_cnt = 0.0
                self.__pulse_trig = False
                ret_val = vGPIO.__LOW
            if (self.__t_fall-self.__t_rise) > vGPIO.__TRIG_PULSE_MIN:
                print ("Tx")
                self.__t_fall = 0.0
                self.__t_rise = 0.0
                self.__pulse_trig=True
                self.__t_last = time.time()
                self.__pulse_cnt = 2.0*range_sonar/340.0
                ret_val = vGPIO.__HIGH
        return ret_val ==  vGPIO.__HIGH

    def set_high(self) :
        if self.__value!=vGPIO.__HIGH:
            self.__t_rise = time.time()
        self.__value=vGPIO.__HIGH

    def set_low(self) :
        if self.__value==vGPIO.__HIGH:
            self.__t_fall = time.time()         
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

    def __init__(self):
        self.all_pin_in=[]
        self.all_pin_out=[]
        for pin_in, pin_out in vSonar.__PIN_MAP.values():
            pin_out.set_low()
            self.all_pin_in.append(pin_in)
            self.all_pin_out.append(pin_out)
        self.tx=[False,False,False,False]
        t = threading.Thread(target=vSonar.simPropag,args=(self.all_pin_in,self.all_pin_out,))
        t.start()


    def simPropag(all_pin_in,all_pin_out):

        n_pin=len(all_pin_in)
        val=[]
        for i in range (n_pin):
            val.append(all_pin_out[i].is_high())
            print ("val = ",val[i])

        sonarDist = [0.3,0.4,0.5,0.6]
        sonarDelay = [0.0,0.0,0.0,0.0]
        sonarTime = []
        for i in range(n_pin):
            sonarTime.append(sonarDist[i]*2.0/340.)
        dt = 0.00001
        pulse=[False,False,False,False]
        while True:
            for i in range(n_pin):
                valnew = all_pin_out[i].is_high()
                if valnew != val[i]:
                    #print (i,all_pin_out[i].id,valnew,pulse[i])
                    pass
                if valnew > val[i]:
                    all_pin_in[i].set_high()
                    time.sleep(0.05)
                    all_pin_in[i].set_low()
                """
                if pulse[i]:
                    sonarDelay[i] -= dt
                    if sonarDelay[i]<= 0.0:
                        pulse[i] = False
                        all_pin_in[i].set_low()
                        t1=time.time()
                        print ("end ping : ",i,all_pin_in[i].id,t1-t0)
                if (valnew > val[i]) and (not pulse[i]):
                    t0=time.time()
                    print ("start ping : ",i,all_pin_in[i].id)
                    all_pin_in[i].set_high()
                    sonarDelay[i] = sonarTime[i]
                    pulse[i] = True
                """
                val[i]=valnew
            time.sleep(dt)
                
    


            
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
        time.sleep(1e-3)
        pin_out.set_low()

        # Sometimes the answer is too fast so it isn't caught, sometimes the 10us pulse is not caught by the PCDuino (python not much precise with time.sleep())

        start = time.time()
        while not pin_in.is_high():
            if time.time()- start > 1e-3:
                print("No answer from sonar: "+sonar_key)
                return -1

        #print ("rd pin_in",pin_in.id,pin_in.is_high())
        # sometimes there are fake detections faster than the time elapsed 
        # between these two loops
        timeOut = 2.0*vSonar.__MAX_DIST/vSonar.__SPEED_OF_SOUND
        timeOut = 1.0
        start = time.time()   
        stop = start      
        while pin_in.is_high():
            #print ("rd pin_in",pin_in.id,pin_in.is_high())
            #sys.stdout.write(".")
            #sys.stdout.flush()
            stop = time.time()
            if (stop - start) > timeOut:
                print (stop-start,timeOut,sonarTimeOfFly)
                print ("rd pin_in",pin_in.id,pin_in.is_high())
                return 9999.99
                
        return (stop-start)*vSonar.__SPEED_OF_SOUND/2.0


