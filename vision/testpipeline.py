import numpy as np
import cv2
import stickynote

cap = cv2.VideoCapture(1)
grip = stickynote.GripPipeline()

while(True):
    # Capture frame-by-fram
    ret, frame = cap.read() #Begin capturing images from the camera

    # Our operations on the frame come here

    grip.process(frame)
    cv2.drawContours(frame, grip.filter_contours_output, -1, (0,255,0), 3)

    # Display the resulting frame
    cv2.imshow('frame',frame) #Display what the camera sees
    if cv2.waitKey(1) & 0xFF == ord('q'): #Close when q is pressed
        break

    

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()