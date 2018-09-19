test:
	g++ calibrate.cpp -o calibrate `pkg-config opencv --cflags --libs`
	g++ calibrate2.cpp -o calibrate2 `pkg-config opencv --cflags --libs`
	g++ test_after_calibration.cpp -o test_after_calibration `pkg-config opencv --cflags --libs`
	
.PHONY:clean
clean:
	rm -f calibrate calibrate2 test_after_calibration
