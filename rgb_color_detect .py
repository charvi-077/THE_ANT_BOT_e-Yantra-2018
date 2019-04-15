'''
 * Team Id:2683

 * Author List: Dhawal
         
 * Filename: rgb_color_detect.py
 * Theme: Ant Bot
 * Functions: color_detect 
 * Global variables: None
 '''


import time
from picamera import PiCamera
from picamera.array import PiRGBArray
import numpy as np
import cv2

""" * Function Name: color_detect()
* Input: None
* Output: Outputs the number of the color detected as follows:--
            1 =====> Red
            2 =====> Green
            3 =====> Blue
            4 =====> Nothing is detected
* Logic:
            captures a image as an OpenCV Image with PiCam
                  |
                  V
            Apply Perspective transform to see it from top view
                  |
                  V
            loops over it maximum 3 times
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
            Caculate the centroid
                  |
                  V
            Take the mean of all the pixels with size of 6*6 around the centroid
                  |
                  V
            Find the index of the maximum value and accordingly announce color 
                  
* Example Call: color_detect()
"""


def color_detect():
    low_param = [[85, 120, 80], [40, 110, 55], [0, 120, 50]]          # Lower threshold parameters for masking of color boxes in [ B, G, R] format with ranges also first for Blue, Green and Red
    high_param = [[110, 255, 140], [80, 250, 125], [40, 240, 180]]    #  Higher threshold parameters for masking of color boxes in [ B, G, R] format with ranges also first for Blue, Green and Red

    color = 0                                                           # color variable to be returned from function this function
    with PiCamera() as camera:
        camera.resolution = (320, 240)
        camera.framerate = 24
        time.sleep(2)
        image = np.empty((240 * 320 * 3,), dtype=np.uint8)              #empty array for the image to be stored
        camera.capture(image, 'bgr')                                    # image should be stored in BGR format
        image = image.reshape((240, 320, 3))
        pts1 = np.float32([[3, 110], [0, 169], [290, 71], [290, 151]])         #  co-ordinate points for perspective transform in input image
        pts2 = np.float32([[0, 0], [0, 240], [320, 0], [320, 240]])            #  coordinate points for perspective transform in output image
        N = cv2.getPerspectiveTransform(pts1, pts2)
        dst = cv2.warpPerspective(image, N, (320, 240))
        for i in range(0, 3):                                            # check for all the colours and return when found the color
            crop_img = np.empty((6 * 6 * 3,), dtype=np.uint8)           # variable for cropping a small part around the centroid
            lower = np.array(low_param[i])                              # lower threshold
            upper = np.array(high_param[i])                             # higher threshold
            hsv = cv2.cvtColor(dst, cv2.COLOR_BGR2HSV)                  # convert the image from the BGR ----> HSV format
            kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5,5))   # rectangular kernel for removing noise
            ero = cv2.erode(hsv, kernel, iterations=2)                  # removing noise from image by erosion
            mask = cv2.inRange(ero, lower, upper)                       # masking the image
            _, contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE) # detecting the contours
            if len(contours) != 0:                                     # check if contours exist in image
                cnt = contours[0]                                       # using contour at index 0
                M = cv2.moments(cnt)                                    # calculating the Moment
                cx = int(M['m10'] / (M['m00'] + 1))
                cy = int(M['m01'] / (M['m00'] + 1))
                crop_img = dst[cy-3:cy+3, cx - 3:cx + 3, :]                # cropped image around centroid
                a = cv2.mean(crop_img)                                  # taking mean of all the pixel values
                a = a[:3]                                                # taking first three values
                result = np.argmax(a, axis=0)                           # detecting the index of highest value in the mean values
                if a[0] + a[1] + a[2] > 0:
                    if result == 2:
                        color = 1                                           # if the result == 2 ===> color = 1 or RED
                        return color
                    elif result == 1:
                        color = 2                                           # if the result == 1 ===> color = 2 or GREEN
                        return color
                    else:
                        color = 3                                           # else the result == 0 ===> color = 3 or BLUE
                        return color

    return 0                                                            #   return 0 if nothing is detected
