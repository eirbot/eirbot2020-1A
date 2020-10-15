# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)

project(project)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O3") # debug, no optimisation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") # enabling coverage
set(SRCS
   rasp/src/navigation/world.cpp
   rasp/src/navigation/navigation.cpp
   rasp/src/interactions/detection.cpp
   rasp/src/interactions/actionneur.cpp
   rasp/src/navigation/protocole.cpp
   rasp/src/navigation/asserv.cpp
   rasp/src/robot.cpp
   rasp/src/affichage.cpp
   rasp/src/interactions/ecocup_pdv.cpp
   rasp/src/interactions/ecocup.cpp
   rasp/src/main.cpp
    )

set(HEADERS
   rasp/src/navigation/world.hpp
   rasp/src/navigation/navigation.hpp
   rasp/src/interactions/detection.hpp
   rasp/src/interactions/actionneur.hpp
   rasp/src/navigation/protocole.hpp
   rasp/src/navigation/asserv.hpp
   rasp/src/robot.hpp
   rasp/src/affichage.hpp
   rasp/src/interactions/ecocup_pdv.hpp
   rasp/src/interactions/ecocup.hpp
   rasp/src/main.hpp
  )

set(TSTS
  rasp/tst/test_actionneur.cpp
  rasp/tst/test_actionneur.hpp
  rasp/tst/test_asserv.cpp
  rasp/tst/test_asserv.hpp
  rasp/tst/test.cpp
  rasp/tst/test_detection.cpp
  rasp/tst/test_detection.hpp
  rasp/tst/test_ecocup.cpp
  rasp/tst/test_ecocup.hpp
  rasp/tst/test.hpp
  rasp/tst/test_navigation.cpp
  rasp/tst/test_navigation.hpp
  rasp/tst/test_protocole.cpp
  rasp/tst/test_protocole.hpp
  rasp/tst/test_robot.cpp
  rasp/tst/test_robot.hpp

   rasp/src/navigation/world.cpp
   rasp/src/navigation/navigation.cpp
   rasp/src/interactions/detection.cpp
   rasp/src/interactions/actionneur.cpp
   rasp/src/navigation/protocole.cpp
   rasp/src/navigation/asserv.cpp
   rasp/src/robot.cpp
   rasp/src/affichage.cpp
   rasp/src/interactions/ecocup_pdv.cpp
   rasp/src/interactions/ecocup.cpp

   rasp/src/navigation/world.hpp
   rasp/src/navigation/navigation.hpp
   rasp/src/interactions/detection.hpp
   rasp/src/interactions/actionneur.hpp
   rasp/src/navigation/protocole.hpp
   rasp/src/navigation/asserv.hpp
   rasp/src/robot.hpp
   rasp/src/affichage.hpp
   rasp/src/interactions/ecocup_pdv.hpp
   rasp/src/interactions/ecocup.hpp
  )

add_executable(project ${SRCS} ${HEADERS})

add_executable(test ${TSTS})


###########
# Doxygen #
###########
# add a target to generate API documentation with Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    install(DIRECTORY ../doc/html DESTINATION share/doc)
  endif()

add_custom_target(upload
  COMMAND scp ${CMAKE_CURRENT_BINARY_DIR}/bin/test pi@eirboat:~
  #COMMAND ssh pi@eirboat ./test
  )

add_custom_target(final
  COMMAND scp ${CMAKE_CURRENT_BINARY_DIR}/bin/project pi@eirboat:~
  #COMMAND ssh pi@eirboat ./project
)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(tools ${CMAKE_CURRENT_SOURCE_DIR}/../tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64)
set(CMAKE_C_COMPILER ${tools}/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/arm-linux-gnueabihf-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
