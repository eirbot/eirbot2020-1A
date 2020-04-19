import numpy as np
import cv2
import cv2.aruco as aruco

##@file Detect_ArUco.py
##@brief Permet de configurer la balise pour qu'elle détecte si la boussole est du côté nord ou sud
##@author Maxime

cap = cv2.VideoCapture(0)
 
while(True):
    #Lecture d'une image
    ret, frame = cap.read()

    aruco_dict = aruco.Dictionary_get(aruco.DICT_4X4_50)
    parameters =  aruco.DetectorParameters_create()

    #Detection des tags
    corners, ids, rejectedImgPoints = aruco.detectMarkers(frame, aruco_dict, parameters=parameters)

    #TODO
    #Fonction de descrimination des tag autre que le tag 17

    #Calcul de l'orientation du tag
    if corners :
        haut = (corners[0][0][0][1] + corners[0][0][1][1])/2
        bas = (corners[0][0][2][1] + corners[0][0][3][1])/2

        if (haut < bas):
            print('Nord')
        else :
            print('Sud')
    else :
        print('no ArUco detected')

    #Affichage des tag sur l'image de la caméra
    # /!\ DESACTIVER SUR VERSION FINAL /!\
    out = aruco.drawDetectedMarkers(frame, corners, ids)
    cv2.imshow('frame_r',out)
    #/!\ /!\

    if cv2.waitKey(1) & 0xFF == ord('q'):
        cap.release()
        break
 
# Fermeture de la webcam et fermeture des fenêtres
cv2.destroyAllWindows()
