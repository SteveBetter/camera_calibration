test:
	g++  calibrate.cpp -o calibrate `pkg-config opencv --cflags --libs`
	g++  calibrate2.cpp -o calibrate2 `pkg-config opencv --cflags --libs`
