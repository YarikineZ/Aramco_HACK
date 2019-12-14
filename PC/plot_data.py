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

    while((datetime.now() - init_time).seconds < 3):
        data = np.append(data, GetData(ser), axis=0)
        print(len(data), (datetime.now() - init_time).seconds)


    data1 = data[data[:, 0] == 1]
    data2 = data[data[:, 0] == 2]
    data3 = data[data[:, 0] == 3]
    data4 = data[data[:, 0] == 4]


    fig, ax = plt.subplots(2, 2, figsize=(8, 8))
    ax[0, 0].plot(data1[:, 1], data1[:, 2])
    ax[0, 1].plot(data2[:, 1], data2[:, 2])
    ax[1, 0].plot(data3[:, 1], data3[:, 2])
    ax[1, 1].plot(data4[:, 1], data4[:, 2])

    ax[0, 0].set_title("MSU 1")
    ax[0, 1].set_title("MSU 2")
    ax[1, 0].set_title("MSU 3")
    ax[1, 1].set_title("MSU 4")

    plt.show()
