test_time:test_time.cpp tsukuba_time.h tsukuba_time.cpp Makefile
	g++ -o test_time test_time.cpp  tsukuba_time.cpp

test_tkk:test_tkk.cpp tsukuba_tkk.h tsukuba_tkk.cpp Makefile
	g++ -o test_tkk test_tkk.cpp  tsukuba_tkk.cpp

test_urg:test_urg.cpp tsukuba_urg.h tsukuba_urg.cpp  Makefile
	g++ -o test_urg test_urg.cpp tsukuba_urg.cpp Connection_information.cpp `pkg-config --libs opencv` `urg_cpp-config --cflags` `urg_cpp-config --libs`
