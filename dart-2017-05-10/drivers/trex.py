#!/usr/bin/python
# -*- coding: utf-8 -*-

# Initial release 12/05/2016, rewrite of DART/Trex interface
# © I. Probst, ENSTA-Bretagne, WTFPL


import struct
from collections import OrderedDict
import fcntl
import time
import crcmod

# from stackoverflow, it's safer to proxy dict rather than subclassing it
# this way we are sure to give access to methods we know we want to provide
# rather than falling back to parent class' methods

# provide a student-proof dictionary with immutable keys 
class FixedDict():
        def __init__(self, dictionary):
            self._dictionary = dictionary
        def __setitem__(self, key, item):
                if key not in self._dictionary:
                    raise KeyError("The key {} is not defined.".format(key))
                self._dictionary[key] = item
        def __getitem__(self, key):
            return self._dictionary[key]
        def values(self):
            return self._dictionary.values()

class TrexIO():
    """
    Handles communications with Trex power board.
    This class exports two dict called: ``command`` and ``status`` (see below)
    mapped to the corresponding bytes in the binary packet used for I/O with
    the Trex board.
    
    Parameters
    ----------
    bus_nb : integer, optionnal, defaults to 2
        I2C bus to use
    addr : integer, optionnal, defaults to 0x7
        I2C address of the Trex Board
        
    Notes
    -----

    ``status`` is mapped as follows:
        'start_byte'                    Start byte – will be 0xF0 (240 decimal)
        'error_flag'                    Error flag – 0 = ok
        'battery'                       Battery voltage 
        'lm_current'                    Left motor current
        'lm_enc'                        Left encoder count
        'rm_current'                    Right motor current
        'rm_enc'                        Right motor encoder
        'acc_x'                         Accelerometer X-axis
        'acc_y'                         Accelerometer Y-axis
        'acc_z'                         Accelerometer Z-axis
        'impact_x'                      Impact X-axis
        'impact_y'                      Impact Y-axis
        'impact_z'                      Impact Z-axis

    ``status`` is mapped as follows:
        'start_byte'                    Start byte - must be 0x0F (15 decimal)
        'pwm_freq'                      PWMfreq
        'lm_speed_high_byte'            Left speed high byte
        'lm_speed_low_byte'             Left Speed low byte
        'lm_brake'                      Left brake
        'rm_speed_high_byte'            Right Speed high byte
        'rm_speed_low_byte'             Right Speed low byte
        'rm_brake'                      Right brake
        'servo_1_high_byte'             Servo 1 high byte
        'servo_1_low_byte'              Servo 1 low byte
        'servo_2_high_byte'             Servo 2 high byte
        'servo_2_low_byte'              Servo 2 low byte
        'servo_3_high_byte'             Servo 3 high byte
        'servo_3_low_byte'              Servo 3 low byte
        'servo_4_high_byte'             Servo 4 high byte
        'servo_4_low_byte'              Servo 4 low byte
        'servo_5_high_byte'             Servo 5 high byte
        'servo_5_low_byte'              Servo 5 low byte
        'servo_6_high_byte'             Servo 6 high byte
        'servo_6_low_byte'              Servo 6 low byte
        'devibrate'                     Devibrate
        'impact_sensitivity_high_byte'  Impact sensitivity high byte
        'impact_sensitivity_low_byte'   Impact sensitivity low byte
        'battery_high_byte'             Battery voltage high byte (motors off)
        'battery_low_byte'              Battery voltage low byte (motors off)
        'i2c_address'                   I2C slave address
        'i2c_clock'                     I2C clock frequency
        
    """
     
    __command_dict_strings = ('left_motor_speed', 
                              'right_motor_speed', 'use_pid', 'crc')
                
 
    __nb_command_bytes = 6
        
    __status_dict_strings = (           
                'left_encoder', 'right_encoder',
                '__dont_use_this_padding_byte', 'crc'
                )
                
    __nb_status_bytes = 6
    
    __I2C_SLAVE=0x0703
    __I2C_TENBIT=0x0704


    def __init__(self, bus_nb = 2, addr = 0x07):
        self.__i2c_fd ={
                    "in": open("/dev/i2c-"+str(bus_nb), 'rb', buffering=0),
                    "out": open("/dev/i2c-"+str(bus_nb), 'wb', buffering=0)
                    }
        for fd in self.__i2c_fd.values():
            fcntl.ioctl(fd, TrexIO.__I2C_TENBIT, 0)
            if fcntl.ioctl(fd, TrexIO.__I2C_SLAVE, 7) < 0:
                raise IOError(
                    "Can not find a T-rex at address %d on bus %d"%(addr, bus_nb)
                            )
                        
        self.__reset_bytes = (0,0,0,0)

        # this list will be used as a "pointer of pointers" to speed up
        # the dict updates

                    

                    
        self.__status = dict(
                    zip(
                        TrexIO.__status_dict_strings, 
                        [0]*len(TrexIO.__status_dict_strings)
                        )
                    )
                    
        self.compute_crc = crcmod.mkCrcFun(0x131, initCrc=0) #Dallas polynom
        self.reset()
        
    @property
    def status(self):
        raw_status = self.i2c_read()
        # I found no way to get around this as dicts are built with copies
        # of the values...
        
        data = struct.unpack("<hhBB", raw_status)
        crc = self.compute_crc(raw_status[:-1], 0)
        if data[-1] != crc:
            self.reset()
            raise ValueError(
                "Expected crc %d got %d.\n Trying to stop motors"%
                (data[-1], crc)
                )

        self.__status.update(
                    zip(
                        TrexIO.__status_dict_strings, 
                        data
                        )
                    )

        return self.__status
    
    def reset(self):
        self.command = FixedDict(OrderedDict(
                zip(
                TrexIO.__command_dict_strings,
                self.__reset_bytes)
                ))
        self.i2c_write()

    def i2c_read(self):
        '''
        Read status from Trex board.
        Warning, this function does not perform any sanity check on the values
        got from the board.

        Parameters
        ----------
        None

        Return values
        -------------
        data_packet: bytes
            Raw data packet read from i2c        
        '''
        
        data_packet = self.__i2c_fd["in"].read(TrexIO.__nb_status_bytes)
        return data_packet
        
    def i2c_write(self):
        '''
        Write bytes from ``command`` to the Trex board.
        Warning, this function does not perform any sanity check on the values
        sent to the board. .
        Parameters
        ----------
        None

        Return values
        -------------
        None
        
        '''

        # extract all data from command dict, ignore crc which should not
        # be modified by the user anyway
        data_packet = struct.pack(
                                "<hhB",
                                *list(self.command.values())[:-1]
                                )

        crc = self.compute_crc(data_packet, 0)
        self.__i2c_fd["out"].write(data_packet+struct.pack("B", crc))
        self.__i2c_fd["out"].flush()
        # throttle down students...
        # time.sleep(1e-3)

if __name__ == "__main__":
    import sys
    import time
    
    val_left = int(sys.argv[1])
    val_right = int(sys.argv[2])
    print("Testing motors")
    trex = TrexIO()
    print(trex.status)
    time.sleep(1e-3)
    trex.command["left_motor_speed"] = val_left
    trex.command["right_motor_speed"]= val_right
    trex.i2c_write()
    time.sleep(2)
    trex.command["left_motor_speed"]= 0
    trex.command["right_motor_speed"]= 0
    trex.i2c_write()
    print(trex.status)
    
    print("Flooding I2C bus")
    trex.command["left_motor_speed"] = val_left
    trex.command["right_motor_speed"]= val_right
    
    ts = time.time()
    for i in range(1000):
        trex.i2c_write()
        #trex.status
    print("Sent/got 1000 packets in %f seconds"%(time.time()-ts))
    print("Testing stop/reset")        
    trex.reset()
    
    print("Testing immutable dictionary keys")
    trex.command["grumpf"]= "pouet"
