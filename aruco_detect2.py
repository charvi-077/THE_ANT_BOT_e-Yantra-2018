'''
 * Team Id:2683

 * Author List: Pranav, Charvi, Ankur
         
 * Filename: aruco_detect2.py
 * Theme: Ant Bot
 * Functions: cap_aruco_detect()
 * Global variables: None
 '''

import numpy as np
import cv2
import time
from aruco_lib import *
import os
from picamera import PiCamera
from picamera.array import PiRGBArray

""" * Function Name: cap_aruco_detect()
* Input: g (i2c received integer)
* Output: ID (the ID of the aruco detected)
* Logic:
            captures a image from picam
                  |
                  V
            Sets the image resolution to 320x240
                  |
                  V
            Detects the aruco of dictionary 7x7 in the image 
                  |
                  V
            Returns the ID measured

                  
* Example Call: cap_aruco_detect(g)
"""

def cap_aruco_detect(g) :
    ID = -1      #Initialize ID with an impossible
    
    cap = PiCamera()
    cap.resolution = (320,240)
    rawCapture = PiRGBArray(cap) # picamera object
    cap.capture(rawCapture, format = "bgr")
    image = rawCapture.array   #Convert the object to image array
    """if(g == 2):
        cv2.imshow("image", image)
        cv2.waitKey(0)"""
    det_aruco = detect_Aruco(image, aruco.DICT_7X7_1000)   # returns the dictionary with key as aruco id and value as the image array
    cap.close()
    #ID = list()
    #print("dictionary is ", det_aruco)
    if det_aruco :
        for key in det_aruco.keys():
            ID = key
        
        return ID #Returning back to file Receive_i2c.py to show that the image has been captured and aruco has been detected
    
"""if __name__ == "__main__":
    
    cap_aruco_detect()"""
    
    
    
                      
    

    

        

