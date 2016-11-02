tsukuba2016:main.o navigation.o avoid.o localization.o camera.o joystick.o motor.o tsukuba_time.o tsukuba_tkk.o tsukuba_urg.o  Makefile
	g++ -o tsukuba2016 main.o navigation.o avoid.o localization.o camera.o joystick.o motor.o tsukuba_time.o tsukuba_tkk.o tsukuba_urg.o `pkg-config --libs opencv`  `urg_cpp-config --libs` `urg_cpp-config --libs` 

main.o:main.cpp tsukuba_def.h

navigation.o:navigation.cpp navigation.h

avoid.o:avoid.cpp avoid.h

localization.o:localization.cpp localization.h

camera.o:camera.cpp camera.h

joystick.o:joystick.cpp joystick.h

motor.o:motor.cpp motor.h

tsukuba_time.o:tsukuba_time.cpp tsukuba_time.h

tsukuba_tkk.o:tsukuba_tkk.cpp tsukuba_tkk.h

tsukuba_urg.o:tsukuba_urg.cpp tsukuba_urg.h
	g++ -c -o tsukuba_urg.o tsukuba_urg.cpp `urg_cpp-config --cflags`



clean:
	rm *.o tsukuba2016

#main.cpp navigation.h navigation.cpp avoid.h avoid.cpp localization.h localization.cpp camera.h camera.cpp joystick.h joystick.cpp motor.h motor.cpp tsukuba_time.h tsukuba_time.cpp tsukuba_tkk.h tsukuba_tkk.cpp tsukuba_urg.cpp Makefile
#	g++ -o tsukuba2016 main.cpp navigation.cpp avoid.cpp localization.cpp camera.cpp motor.cpp joystick.cpp tsukuba_time.cpp tsukuba_tkk.cpp tsukuba_urg.cpp `pkg-config --libs opencv` `urg_cpp-config --cflags` `urg_cpp-config --libs` `pkg-config --cflags opencv` `pkg-config --libs opencv`

