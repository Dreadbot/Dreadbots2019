#!/usr/bin/env python

from __future__ import print_function

import io
import time
#import picamera
import cv2
from imutils.video import VideoStream
import stickynote


"""
Demonstates continous image capture technique suggested here:
 - http://www.pyimagesearch.com/2015/03/30/accessing-the-raspberry-pi-camera-with-opencv-and-python/

"""

class Timer(object):
    def __init__(self, name):
        self.name = name
        self.t1 = time.time()
        pass

    def start(self):
        self.t1 = time.time()

    def stop(self):
        self.t2 = time.time()

    def elapsed(self):
        return self.t2-self.t1

    def show(self):
        print( "%s: %4.4f" % ( self.name, (self.t2-self.t1) ) )
#|

t = Timer( "Camera continous" )
idx=0
cam = VideoStream(src=1).start()

t.start()
#cam = cv2.VideoCapture(0)
#stream = io.BytesIO()

for idx in range(20):
    img = cam.read()

t.stop()

cv2.imshow( 'frame', img )
cv2.waitKey(0)


pipe = stickynote.GripPipeline()
pipe.process(img)

print(pipe.filter_contours_output())

print( "%s iterations of image captures" % idx )

secs = (t.t2 - t.t1)
fps = 1.0 * idx / secs

t.show()

print( "fps = %.2f" % (fps) )
