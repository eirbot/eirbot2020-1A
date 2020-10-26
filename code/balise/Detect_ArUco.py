import RPi.GPIO as GPIO
import numpy as np
import cv2
import cv2.aruco as aruco

LED_NORD_PIN = 11
LED_SUD_PIN = 13
LED_NOCODE_PIN = 15
SIGNAL_NS_PIN = 16
SIGNAL_OK_PIN = 18

NB_CHECK_VALUE = 10
NORD = 1
SUD = 2
RIEN = 0

LED_Nord_State = GPIO.LOW
LED_Sus_State = GPIO.LOW
LED_NoCode_State = GPIO.LOW

SIGNAL_NS_State = GPIO.LOW
SIGNAL_OK_State = GPIO.LOW

cap = cv2.VideoCapture(0)

GPIO.setmode(GPIO.BOARD)
GPIO.setup(LED_NORD_PIN, GPIO.OUT)
GPIO.setup(LED_SUD_PIN, GPIO.OUT)
GPIO.setup(LED_NOCODE_PIN, GPIO.OUT)
GPIO.setup(SIGNAL_NS_PIN, GPIO.OUT)
GPIO.setup(SIGNAL_OK_PIN, GPIO.OUT)

aruco_dict = aruco.Dictionary_get(aruco.DICT_4X4_50)
parameters = aruco.DetectorParameters_create()

bousole = RIEN
check_bousole = 0

while(True):
    #Lecture d'une image 
    ret, frame = cap.read()
    tag17_find = 0
    old_bousole = bousole
    #Detection des tags
    corners, ids, rejectedImgPoints = aruco.detectMarkers(frame, aruco_dict, parameters=parameters)

    if corners:
    #Recherche du tag 17 parmit les tags trouvee
        nb_id = np.size(ids)
        for index_tag_17 in range(nb_id):
            if ids[index_tag_17] != 17:
                tag17_find = 0
                continue
            print("tag 17 detect")
            tag17_find = 1
            break

    if tag17_find == 1:
    #Calcul de l'orientation du tag
        haut = (corners[0][0][0][1] + corners[0][0][1][1])/2
        bas = (corners[0][0][2][1] + corners[0][0][3][1])/2
        if (haut < bas):
            bousole = NORD
            SIGNAL_NS_State = 0
            #LED Nord ON
            LED_Nord_State = GPIO.HIGH
            #LED Sud OFF
            LED_Sud_State = GPIO.LOW
            #LED NoCode OFF
            LED_NoCode_State = GPIO.LOW
            vision = 1
            print('Nord')
        else :
            bousole = SUD
            SIGNAL_NS_State = 1
            #LED Nord OFF
            LED_Nord_State = GPIO.LOW
            #LED Sud ON
            LED_Sud_State = GPIO.HIGH
            #LED NoCode OFF
            LED_NoCode_State = GPIO.LOW
            print('Sud')
            vision = 1
    else :
        bousole = bousole
        #LED Nord OFF
        LED_Nord_State = GPIO.LOW
        #LED Sud OFF
        LED_Sud_State = GPIO.LOW
        #LED NoCode ON
        LED_NoCode_State = GPIO.HIGH
        print('no ArUco detected')
        vision = 0

    if (vision == 1):
        if (bousole != old_bousole):
            check_bousole = 0
        else:
            check_bousole = check_bousole + 1 
    else:
        check_bousole = check_bousole
    
    if check_bousole > NB_CHECK_VALUE:
        SIGNAL_OK_State = 1
        print("Check_OK")
    else:
        SIGNAL_OK_State = 0
        print("Attente check")

    #Gestion output GPIO
    GPIO.output(LED_NORD_PIN, LED_Nord_State)
    GPIO.output(LED_SUD_PIN, LED_Sud_State)
    GPIO.output(LED_NOCODE_PIN, LED_NoCode_State)
    GPIO.output(SIGNAL_NS_PIN, SIGNAL_NS_State)
    GPIO.output(SIGNAL_OK_PIN, SIGNAL_OK_State)

    #cv2.imshow('frame_r',out)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
