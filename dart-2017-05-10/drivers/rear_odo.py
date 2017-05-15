# -*- coding: utf-8 -*-
import time
from select import poll, POLLPRI, POLLIN

class RearOdos():
    __gpio_basename = "/sys/class/gpio/gpio"
    def __init__(self):
        self.input_gpios = [266,267,268,269]

    def acquire(self):
        
        pins_dict = {}
        monitor = poll()
            
        for gpio_id in self.input_gpios:
            
            fd = open(RearOdos.__gpio_basename+str(gpio_id)+"/edge", 'w')
            fd.write("rising")
            fd.close()
            
            fd = open(RearOdos.__gpio_basename+str(gpio_id)+"/value", 'r')

            monitor.register(fd, POLLPRI)
            print(fd.fileno())
            pins_dict[fd.fileno()] = [gpio_id, fd]

        t0 = time.time()
        timeOut = 0.1
        while True:
            for fd_ev, ev in monitor.poll(1e-3):
                gpio_id, fd = pins_dict[fd_ev]
                fd.seek(0)
                if ev & (POLLPRI):
                    print("Data on pin " + str(gpio_id)+": ", fd.read())
            if (time.time()-t0) > timeOut:
                break

if __name__ == "__main__":
    toto=RearOdos()
    toto.acquire()