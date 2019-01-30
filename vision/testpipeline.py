import numpy as np
import cv2
import stickynote

cap = cv2.VideoCapture(0)
grip = stickynote.GripPipeline()

while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()

    # Our operations on the frame come here

    grip.process(frame)
    print(grip.filter_contours_output)

    # Display the resulting frame
    cv2.imshow('frame',frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

    

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()