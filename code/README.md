# Cross compilation

cmake ./ -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake

# Eviter de se taper le mot de passe ssh à chaque fois

générer la clé : ssh-keygen
copier la clé sur la rasp: ssh-copy-id pi@eirboat
