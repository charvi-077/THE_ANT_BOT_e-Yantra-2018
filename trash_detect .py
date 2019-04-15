'''
 * Team Id:2683

 * Author List: Dhawal
         
 * Filename: trash_detect.py
 * Theme: Ant Bot
 * Functions: trash_detect
 * Global variables: None
 '''
import time
from picamera import PiCamera
from picamera.array import PiRGBArray
import numpy as np
import cv2


""" 
* Function Name: trash_detect
* Input: None
* Output: returns 4 if the trash is detected else returns 0 
* Logic:    captures a image as an OpenCV Image with PiCam
                  |
                  V
            Apply Perspective transform to see it from top view
                  |
                  V
            Convert the image into HSV format
                  |
                  V
            Applying erosion over the image with rectangular kernel of 5*5 pixel
                  |
                  V
            Apply masking over the eroded image
                  |
                  V
            Detect the contours
                  |
                  V
            If contours detected then returns 4 otherwise 0 
                 
* Example Call: trash_detect()
"""


def trash_detect():
    low_param = [0, 245, 120]
    high_param = [30, 255, 230]

    with PiCamera() as camera:
        camera.resolution = (320, 240)
        camera.framerate = 24
        time.sleep(2)
        image = np.empty((240 * 320 * 3,), dtype=np.uint8)
        camera.capture(image, 'bgr')
        image = image.reshape((240, 320, 3))
        pts1 = np.float32([[50, 126], [30, 171], [300, 111], [300, 168]])
        pts2 = np.float32([[0, 0], [0, 240], [320, 0], [320, 240]])
        N = cv2.getPerspectiveTransform(pts1, pts2)
        dst = cv2.warpPerspective(image, N, (320, 240))
        lower = np.array(low_param)                                                                                                                                                                                       
        upper = np.array(high_param)
        hsv = cv2.cvtColor(dst, cv2.COLOR_BGR2HSV)
        kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5,5))
        ero = cv2.erode(hsv, kernel, iterations=2)      # removing noise from image
        mask = cv2.inRange(ero, lower, upper)
        _, contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        if len(contours) != 0:
            return 4
            
    return 0





