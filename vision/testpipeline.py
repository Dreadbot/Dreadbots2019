import numpy as np
import cv2
import deepspacepipeline

cap = cv2.VideoCapture(1) #This creates a variable for a path to the camera
grip = deepspacepipeline.GripPipeline() #Initializes the pipeline
"""Display is 650 by 500"""
while(True):
    # Capture frame-by-fram
    ret, frame = cap.read() #Begin capturing images from the camera

    # Our operations on the frame come here

    grip.process(frame) #Push given image through grip pipeline
    contour_arr = [] #Clear out array before inputing contour data
    lines = [] #Clear out array before inputing contour data
    contour_arr.append(grip.filter_contours_output) #Pull out the result and assign it to countour_arr
    contours = grip.filter_contours_output
    num_contours = len(contour_arr[0])
    
    cv2.drawContours(frame, contours, -1, (0,255,0), 3) #Color the contours on the camera output

    contours_xs = [] #Set empty array
    contours_ys = [] #Set empty array

    #lines_xs.append(grip.filter_contours_output[0])
    #lines_raw = (grip.filter_lines_output)
    
    
    try:
        for i in range(0, num_contours):
            contours_xs.append(contour_arr[0][0][0][i][0]) #Add i arrays x value to the arrays
            contours_ys.append(contour_arr[0][0][0][i][1]) #Add i arrays y value to the arrays
        contours_xs.sort() #Sort highest to lowest
        contours_ys.sort()

        cv2.line(frame, 
        (grip.filter_lines_output[0].x1, grip.filter_lines_output[0].y1), 
        (grip.filter_lines_output[0].x2, grip.filter_lines_output[0].y2), 
        (255,0,0), 
        5)

    except:
        pass
    try:
        cv2.circle(frame,(contours_xs[0], contours_ys[0]), 5, (0,0,255), -1)
    except:
        pass
    
#TODO:
#Find a way to link contours to their lines


    # Display the resulting frame
    cv2.imshow('frame',frame) #Display what the camera sees
    if cv2.waitKey(1) & 0xFF == ord('q'): #Close when q is pressed
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()