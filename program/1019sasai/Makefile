
wait:wait.cpp auto.h controll.h data.h gps.h csm.h Makefile
	g++ -o wait wait.cpp  Connection_information.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv` `urg_cpp-config --cflags` `urg_cpp-config --libs`


main:main.cpp sfm.h Makefile
	g++ -o main main.cpp -Lurg_cpp.a `pkg-config --cflags opencv` `pkg-config --libs opencv` 

test:test.cpp camera.h camera.cpp Makefile
	g++ -o test test.cpp camera.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`


motor_test:motor_test.cpp motor.h motor.cpp joystick.h joystick.cpp Makefile
	g++ -o motor_test motor_test.cpp motor.cpp joystick.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`


camera_test:camera_test.cpp camera.h camera.cpp Makefile
	g++ -o camera_test camera_test.cpp camera.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`

joystick_test:joystick_test.cpp joystick.h joystick.cpp Makefile
	g++ -o joystick_test joystick_test.cpp joystick.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv`

