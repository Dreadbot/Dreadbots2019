import numpy as np
import cv2
import stickynote

<<<<<<< HEAD
cap = cv2.VideoCapture(0) #This creates a variable for a path to the camera
grip = stickynote.GripPipeline() #Initializes the pipeline
=======
cap = cv2.VideoCapture(1)
grip = stickynote.GripPipeline()
>>>>>>> d66b042923aeba4e30a6177e0c6b1989c258eb4f

while(True):
    # Capture frame-by-fram
    ret, frame = cap.read() #Begin capturing images from the camera

    # Our operations on the frame come here

<<<<<<< HEAD
    grip.process(frame) #Push given image through grip pipeline
    contour_arr = [] #Clear out array before inputing contour data
    contours = grip.find_contours_output #Pull out the result and assign it to countour_arr 
    cv2.drawContours(frame, contours, -1, (0,255,0), 3) #Color the contours on the camera output
    
    try: print(contours[0][0])
    except: print(0)
=======
    grip.process(frame)
    cv2.drawContours(frame, grip.filter_contours_output, -1, (0,255,0), 3)

>>>>>>> d66b042923aeba4e30a6177e0c6b1989c258eb4f
    # Display the resulting frame
    cv2.imshow('frame',frame) #Display what the camera sees
    if cv2.waitKey(1) & 0xFF == ord('q'): #Close when q is pressed
        break

    

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()