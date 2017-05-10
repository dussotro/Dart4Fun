import struct


class vRazorIO():
    def __init__(self):
        pass

    def angles(self):
        # get bearing angle from V-REP
        cap = 120.0
        capTrigo = -cap
        head = 90.0 - capTrigo
        if head > 180.0:
            head -= 360.0
        if head <  -180.0:
            head += 360.0

        output = [head,0.0,0.0]
        return output

    def raw_sensor_data(self):
        output=struct.pack("fffffffff",0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0)
        return output

    def calibrated_sensor_data(self):
        output=struct.pack("fffffffff",0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0)
        return output
