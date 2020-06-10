

CFLAGS=-I/home/pi/proj/opencv/opencv-3.4.1/include -I/home/pi/proj/opencv/opencv-3.4.1/build -I/home/pi/proj/opencv/opencv-3.4.1/modules/core/include -I/home/pi/proj/opencv/opencv-3.4.1/modules/calib3d/include/ -I/home/pi/proj/opencv/opencv-3.4.1/modules/features2d/include -I/home/pi/proj/opencv/opencv-3.4.1/modules/flann/include -I/home/pi/proj/opencv/opencv-3.4.1/modules/dnn/include -I/home/pi/proj/opencv/opencv-3.4.1/modules/highgui/include  -I/home/pi/proj/opencv/opencv-3.4.1/modules/imgcodecs/include  -I/home/pi/proj/opencv/opencv-3.4.1/modules/videoio/include -I/home/pi/proj/opencv/opencv-3.4.1/modules/imgproc/include -I/home/pi/proj/opencv/opencv-3.4.1/modules/ml/include  -I/home/pi/proj/opencv/opencv-3.4.1/modules/objdetect/include  -I/home/pi/proj/opencv/opencv-3.4.1/modules/photo/include -I/home/pi/proj/opencv/opencv-3.4.1/modules/shape/include -I/home/pi/proj/opencv/opencv-3.4.1/modules/stitching/include -I/home/pi/proj/opencv/opencv-3.4.1/modules/superres/include -I/home/pi/proj/opencv/opencv-3.4.1/modules/video/include -I/home/pi/proj/opencv/opencv-3.4.1/modules/videostab/include

LFLAGS= -L/home/pi/proj/opencv/opencv-3.4.1/build/lib/ \
-lopencv_calib3d \
-lopencv_dnn     \
-lopencv_imgproc \
-lopencv_core    \
-lopencv_highgui \
-lopencv_imgcodecs \
-lopencv_features2d \
-lopencv_photo

CFLAGS+=-fmax-errors=3

all : jmatch

clean :
	rm -f a.out display matchdemo
	rm -f jmatch

DisplayImage : DisplayImage.cpp
	g++ DisplayImage.cpp -o display $(CFLAGS) $(LFLAGS)

matchdemo : matchdemo.cpp
	g++ matchdemo.cpp -o matchdemo $(CFLAGS) $(LFLAGS)

jmatch : jmatch.cpp jutils.cpp jutils.hpp
	g++ jmatch.cpp jutils.cpp -o jmatch $(CFLAGS) $(LFLAGS)
