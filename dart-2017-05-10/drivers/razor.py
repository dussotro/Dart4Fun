#!/usr/bin/python
# -*- coding: utf-8 -*-

import serial
import struct
import os

VALID_STATES = [b"#o0", b"#o1", b"#ob", b"#ot", b"#oc", b"#on", b"#osct", b"#osrt", b"#osbt", b"#oscb", b"#osrb", b"#osbb", b"#oe0", b"#oe1", b"#f", b"#s<xy>"]

class RazorIO():
    def __init__(self):

        self.bus = serial.Serial('/dev/ttyS1', 57600, timeout = 10)
        self.state = b"#o0"
        self.bus.write(self.state) # Output on demand
        self.state = b"#ob"
        self.bus.write(self.state) # Setting default state to binary angle output

    @property
    def angles(self):

        """
            Output angles in BINARY format (yaw/pitch/roll as binary float, so one output frame
            is 3x4 = 12 bytes long)

            yaw angle is used as robot heading
        """

        # in next line replace ???? with the right command and uncomment  
        # self.state = ?????
        self.bus.write(self.state)

        try:
            # get the 12 bytes of data with bus.read
            # ????
            #  and decode it with struct unpack
            #  output must be a list with 3 values
            # output = ???
        except:
            output = None
            pass
        return output

if __name__ == "__main__":
    razor = RazorIO()
    print(razor.angles)
