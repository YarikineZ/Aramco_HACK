import serial
import time
import re
import msvcrt
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
from datetime import datetime


def GetData(port):
    reading = ser.readline().decode('utf-8')

    if re.match(r'[0-9 ]+', reading):
        reading = re.split(r'\t', reading, maxsplit=2)
        id = int(reading[0])
        time = (int(reading[1]))
        noize = (int(re.sub(r'\r\n', '', reading[2])))

        data = np.array([id, time, noize]).reshape((1, 3))
        return data
    else:
        return 0
        #GetData(port)



if __name__ == '__main__':
    SERIAL_PORT = 'COM9'
    SERIAL_RATE = 115200
    ser = serial.Serial(SERIAL_PORT, SERIAL_RATE)

    data = np.zeros((0, 3))

    init_time = datetime.now()

    while((datetime.now() - init_time).seconds < 10):
        data = np.append(data, GetData(ser), axis=0)
        print(len(data), (datetime.now() - init_time).seconds)


    plt.plot(data[:, 1], data[:, 2])
    plt.show()
