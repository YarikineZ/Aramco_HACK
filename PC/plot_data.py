import serial
import time
import re
import msvcrt
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np



def GetData(port):
    reading = ser.readline().decode('utf-8')

    if re.match(r'[0-9 ]+', reading):
        reading = re.split(r'\t', reading, maxsplit=2)
        id = int(reading[0])
        time = (int(reading[1]))
        noize = (int(re.sub(r'\r\n', '', reading[2])))

        #data = np.append(data, [id, time, noize])
        data = np.array([id, time, noize]).reshape((1, 3))
        #print("Func", data.shape)
        return data
    else:
        return 0
        #GetData(port)

def myPlot(ser):
    speed = 0.0001
    fig, ax = plt.subplots(2, 2, figsize = (3, 3))
    plt.ion()
    #ax2 = plt.subplot(1, 2, 1)
    for i in range(100):

        #plt.axis([0, 7, 0, 20000])
        data = GetData(ser)
        print(data)
        #plt.clf()
        if(len(data)>3): ax[0, 0].plot(data[:, 2])
        #plt.grid(True)
        plt.show()
        #plt.pause(speed)

    ser.close()


if __name__ == '__main__':
    SERIAL_PORT = 'COM4'
    SERIAL_RATE = 115200
    ser = serial.Serial(SERIAL_PORT, SERIAL_RATE)

    data = np.zeros((0, 3))
    #print("Main", data.shape)
    while(len(data)<10):
        data = np.append(data, GetData(ser), axis=0)
        print(len(data))

    print(data)
    plt.scatter(data[2], data[1], s=1)
    plt.show()
    #myPlot(ser)