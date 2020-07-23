#!/usr/bin/python
# -*- coding: utf-8 -*-

# Initial release 12/05/2016, rewrite of DART/Trex interface
# © I. Probst, ENSTA-Bretagne, WTFPL


import struct
from collections import OrderedDict
import fcntl
import time

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
        'i2c_address'                   I2C subordinate address
        'i2c_clock'                     I2C clock frequency
        
    """
#    __command_dict_strings = (
#                'start_byte', 'pwm_freq', 'lm_speed_high_byte',
#                'lm_speed_low_byte', 'lm_brake', 'rm_speed_high_byte', 
#                'rm_speed_low_byte', 'rm_brake', 'servo_1_high_byte', 
#                'servo_1_low_byte', 'servo_2_high_byte', 'servo_2_low_byte', 
#                'servo_3_high_byte', 'servo_3_low_byte', 'servo_4_high_byte',
#                'servo_4_low_byte', 'servo_5_high_byte', 'servo_5_low_byte',
#                'servo_6_high_byte', 'servo_6_low_byte', 'devibrate', 
#                'impact_sensitivity_high_byte', 'impact_sensitivity_low_byte',
#                'battery_high_byte', 'battery_low_byte', 'i2c_address',
#                'i2c_clock'
#                )

#    __nb_command_bytes = 27

         
    __command_dict_strings = ('lm_speed', 'rm_speed', 'use_pîd', 'crc')
                )
 
    __nb_command_bytes = 6
        
    
#    __status_dict_strings = (           
#                'start_byte', 'error_flag', 'battery', 'lm_current', 'lm_enc',
#                'rm_current', 'rm_enc', 'acc_x', 'acc_y', 'acc_z',
#                'impact_x', 'impact_y', 'impact_z'
#                )
#                
#    __nb_status_bytes = 24
                
                
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
                        
        self.__reset_bytes = (15,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                              50,4,156,addr,0)

        # this list will be used as a "pointer of pointers" to speed up
        # the dict updates

                    

                    
        self.__status = dict(
                    zip(
                        TrexIO.__status_dict_strings, 
                        [0]*len(TrexIO.__status_dict_strings)
                        )
                    )
        self.reset()
        
    @property
    def status(self):
        raw_status = self.i2c_read()
        # I found no way to get around this as dicts are built with copies
        # of the values...
        self.__status.update(
                    zip(
                        TrexIO.__status_dict_strings, 
                        struct.unpack(">BBHHHHHhhhhhh", raw_status)
                        )
                    )
        return self.__status
    
    def reset(self):
        self.command = OrderedDict(
                zip(
                TrexIO.__command_dict_strings,
                self.__reset_bytes)
                )
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

        data_packet = struct.pack(
                                ">"+"B"*TrexIO.__nb_command_bytes,
                                *list(self.command.values())
                                )
        self.__i2c_fd["out"].write(data_packet)
        
        # nb_bytes_out = self.__i2c_fd["out"].write(data_packet)
        # give Trex board some time to process data, the delay is on the trex
        # side, there is no fancy trick to improve this from the CPU board side
        # without this delay the Trex board sometimes fails to answer when
        # a read order is sent on the I2C line.   
        time.sleep(1e-3)
        
        # for some reason nb_bytes_out il always set to None
        #if  nb_bytes_out != TrexIO.__nb_command_bytes:
        #    raise IOError("I2C write to T-rex failed %d %d"%(TrexIO.__nb_command_bytes, nb_bytes_out))
            
if __name__ == "__main__":
    trex = TrexIO()
    print(trex.status)
    trex.command["lm_speed_low_byte"]=50
    trex.i2c_write()
    time.sleep(2)
    trex.command["lm_speed_low_byte"]=0
    trex.i2c_write()
    print(trex.status)