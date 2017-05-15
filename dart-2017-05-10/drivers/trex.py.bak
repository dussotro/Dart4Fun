#!/usr/bin/python
# -*- coding: utf-8 -*-

'''
Controll the Trex robot controller
http://www.dagurobot.com/goods.php?id=135
 - Control CD motors
 - Control Servos
 - Read impact and accelerometer
 - Read Battery voltage
 - Read DC motor current draw

I use both quick2wire and smbus.
smbus to send command
quick2wire to read status
I can not get both functions operate on one of the librarys.
Smbus can not read multipple bytes from the bus without sending a register command.
And I did not get quick2wire to work when write to the slave.

Dependencies
------------
1. Enable I2C on the Raspberry PI
The file /etc/modules shall have the following lines
i2c-bcm2708
i2c-dev

2. Change the baudrate on The Raspberry Pi
Create a new file: /etc/modprobe.d/i2c.conf
And add:
options i2c_bcm2708 baudrate=9600

3. Install smbus:
sudo apt-get install python-smbus

4. Install quick2wire:
Add the following to /etc/apt/sources.list
deb http://dist.quick2wire.com/raspbian wheezy main
deb-src http://dist.quick2wire.com/raspbian wheezy main

sudo apt-get update
sudo apt-get install install quick2wire-gpio-admin quick2wire-python3-api
sed -i '/^assert sys.version_info.major/d' /usr/lib/python3/dist-packages/quick2wire/i2c.py

5. If you use python2 add the following to /etc/profile.d/pythonpath.sh
export PYTHONPATH=/usr/lib/python3/dist-packages

NOTE! When you execute this from the command line it execute outside of steelsquid daemon, and may interrupt for example the LCD, DAC, ADC or extra GPIO.
It is meant to be used inside the steelsquid daemon (see http://www.steelsquid.org/steelsquid-kiss-os-development)

@organization: Steelsquid
@author: Andreas Nilsson
@contact: steelsquid@gmail.com
@license: GNU Lesser General Public License v2.1
@change: 2014-11-23 Created
'''

from time import sleep
import os
import sys
import smbus
import ctypes
import struct
import threading
import ConfigParser

# If the python3 packages not is in path (quick2wire)
sys.path.append("/usr/lib/python3/dist-packages")
import quick2wire.i2c as i2c
from quick2wire.i2c import I2CMaster, writing_bytes, reading

MAX_BATTERY = 1270.0
MIN_BATTERY = 1180.0

class TrexIO():
    def __init__(self, addr = 0x07):
        self.battery = 0
        self.i2c_write_bus = smbus.SMBus(2)
        self.i2c_read_bus = i2c.I2CMaster(2)

        self.ADDRESS = addr

        self.lock = threading.Lock()
        self.package = {}
        self.__byte_package = [None] * 26
        self.reset()

    def __trex_reset(self):
        '''
        Reset the trex controller byte array
        '''
        self.package = {
        	'start_byte' : 15,                     # Start byte
        	'pwm_freq' : 6,                        # PWMfreq
        	'lm_speed_high_byte' : 0,              # Left speed high byte
        	'lm_speed_low_byte' : 0,               # Left Speed low byte
        	'lm_brake' : 0,                        # Left brake
        	'rm_speed_high_byte' : 0,              # Right Speed high byte
        	'rm_speed_low_byte' : 0,               # Right Speed low byte
        	'rm_brake' : 0,                        # Right brake
        	'servo_1_high_byte' : 0,               # Servo 1 high byte
        	'servo_1_low_byte' : 0,                # Servo 1 low byte
        	'servo_2_high_byte' : 0,               # Servo 2 high byte
        	'servo_2_low_byte' : 0,                # Servo 2 low byte
        	'servo_3_high_byte' : 0,               # Servo 3 high byte
        	'servo_3_low_byte' : 0,                # Servo 3 low byte
        	'servo_4_high_byte' : 0,               # Servo 4 high byte
        	'servo_4_low_byte' : 0,                # Servo 4 low byte
        	'servo_5_high_byte' : 0,               # Servo 5 high byte
        	'servo_5_low_byte' : 0,                # Servo 5 low byte
        	'servo_6_high_byte' : 0,               # Servo 6 high byte
        	'servo_6_low_byte' : 0,                # Servo 6 low byte
        	'devibrate' : 50,                      # Devibrate
        	'impact_sensitivity_high_byte' : 0,    # Impact sensitivity high byte
        	'impact_sensitivity_low_byte' : 50,    # Impact sensitivity low byte
        	'battery_high_byte' : 4,               # Battery voltage high byte (when motors are off)
        	'battery_low_byte' : 156,              # Battery voltage low byte (when motors are off)
        	'i2c_address' : 7,                     # I2C slave address
        	'i2c_clock' : 1                        # I2C clock frequency
        }
        self.__map()

    def __map(self):
        self.start_byte = self.package['start_byte']

        self.__byte_package[0] = self.package['pwm_freq']
        self.__byte_package[1] = self.package['lm_speed_high_byte']
        self.__byte_package[2] = self.package['lm_speed_low_byte']
        self.__byte_package[3] = self.package['lm_brake']
        self.__byte_package[4] = self.package['rm_speed_high_byte']
        self.__byte_package[5] = self.package['rm_speed_low_byte']
        self.__byte_package[6] = self.package['rm_brake']
        self.__byte_package[7] = self.package['servo_1_high_byte']
        self.__byte_package[8] = self.package['servo_1_low_byte']
        self.__byte_package[9] = self.package['servo_2_high_byte']
        self.__byte_package[10] = self.package['servo_2_low_byte']
        self.__byte_package[11] = self.package['servo_3_high_byte']
        self.__byte_package[12] = self.package['servo_3_low_byte']
        self.__byte_package[13] = self.package['servo_4_high_byte']
        self.__byte_package[14] = self.package['servo_4_low_byte']
        self.__byte_package[15] = self.package['servo_5_high_byte']
        self.__byte_package[16] = self.package['servo_5_low_byte']
        self.__byte_package[17] = self.package['servo_6_high_byte']
        self.__byte_package[18] = self.package['servo_6_low_byte']
        self.__byte_package[19] = self.package['devibrate']
        self.__byte_package[20] = self.package['impact_sensitivity_high_byte']
        self.__byte_package[21] = self.package['impact_sensitivity_low_byte']
        self.__byte_package[22] = self.package['battery_high_byte']
        self.__byte_package[23] = self.package['battery_low_byte']
        self.__byte_package[24] = self.package['i2c_address']
        self.__byte_package[25] = self.package['i2c_clock']

    def __updateStatus(self, raw_status):
        conf = ConfigParser.ConfigParser()
        conf.read("/var/www/daarrt.conf")

        status = struct.unpack(">cchhHhHhhhhhh", raw_status)

        if not conf.has_section("trex") : conf.add_section("trex")

        conf.set("trex", "battery", status[2])
        self.battery = min([(int(status[2]) - MIN_BATTERY) / (MAX_BATTERY - MIN_BATTERY) * 100, 100.0])
        conf.set("trex", "battery_level", self.battery)

        conf.set("trex", "left_motor", status[3])
        conf.set("trex", "left_encoder", status[4])

        conf.set("trex", "right_motor", status[5])
        conf.set("trex", "right_encoder", status[6])

        conf.set("trex", "accelerometer_x", status[7])
        conf.set("trex", "accelerometer_y", status[8])
        conf.set("trex", "accelerometer_z", status[9])

        fd = open("/var/www/daarrt.conf", 'w')
        conf.write(fd)
        fd.close()

    def i2cRead(self):
        '''
        Read status from trex
        Return as a byte array
        '''
        try :
            status = self.i2c_read_bus.transaction(i2c.reading(self.ADDRESS, 24))[0]
            self.__updateStatus(status)
            return status
        except :
            return -1

    def i2cWrite(self):
        '''
        Write I2C data to T-Rex
        '''
        self.__map()
        self.lock.acquire()
        try:
            self.i2c_write_bus.write_i2c_block_data(self.ADDRESS, self.start_byte, self.__byte_package)
        except:
            print "Erreur d'accès au bus I2C"
        finally:
            self.lock.release()

    def getBattery(self):
        self.i2cRead()
        print "Niveau de batterie : %.2f" % (self.battery) , "%"
        return self.battery

    def reset(self):
        '''
        Reset the trex controller to default
        Stop dc motors...
        '''
        self.lock.acquire()
        try:
            self.__trex_reset()
            self.i2c_write_bus.write_i2c_block_data(self.ADDRESS, self.start_byte, self.__byte_package)
            self.lock.release()

            sleep(.1)
            self.i2cRead()
            self.getBattery()
            return 0
        except:
            self.lock.release()
            print "Erreur d'accès au bus I2C"
            print "Pensez à vérifier la charge de la batterie !"
            return -1
