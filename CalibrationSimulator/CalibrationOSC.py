import OSC
import random
import sys
import RPi.GPIO as GPIO
from time import sleep

# Setup Button
buttonPin = 12
GPIO.setmode(GPIO.BCM)
GPIO.setup(buttonPin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

# Button Pushed Flag
buttonPushed = False

# Main Loop
def main_loop():
    while True:
        input_state = GPIO.input(buttonPin)
        if input_state == False:
            print('Button Pressed')
            oscmsg = OSC.OSCMessage()
            oscmsg.setAddress("/calibration/TX1_RSSI1")
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            c.send(oscmsg)

            oscmsg.setAddress("/calibration/TX2_RSSI2")
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            c.send(oscmsg)

            oscmsg.setAddress("/calibration/TX3_RSSI3")
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            oscmsg.append(random.random())
            c.send(oscmsg)

        sleep(0.5)


c = OSC.OSCClient()
c.connect(('127.0.0.1', 12345))   # connect to SuperCollider

try:
    main_loop()
except KeyboardInterrupt:
    GPIO.cleanup()
    print >> sys.stderr, '\nExiting by user request.\n'
    sys.exit(0)
