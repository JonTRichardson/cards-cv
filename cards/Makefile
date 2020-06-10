

CFLAGS=-I/home/pi/proj/opencv/opencv-3.4.1/include \
       -I/home/pi/proj/opencv/opencv-3.4.1/build \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/core/include \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/calib3d/include/ \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/features2d/include \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/flann/include \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/dnn/include \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/highgui/include \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/imgcodecs/include \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/videoio/include \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/imgproc/include \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/ml/include \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/objdetect/include \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/photo/include \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/shape/include \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/stitching/include \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/superres/include \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/video/include \
       -I/home/pi/proj/opencv/opencv-3.4.1/modules/videostab/include

LFLAGS= -L/home/pi/proj/opencv/opencv-3.4.1/build/lib/ \
        -lopencv_calib3d \
        -lopencv_dnn     \
        -lopencv_imgproc \
        -lopencv_core    \
        -lopencv_highgui \
        -lopencv_imgcodecs \
        -lopencv_features2d \
        -lopencv_photo

# terminate gcc so we can see the first error which probably caused the others
CFLAGS+=-fmax-errors=2

all : search display matchdemo jmatch

clean :
	rm -f a.out display matchdemo
	rm -f jmatch
	rm -f search
	rm -f search-nonface

display : DisplayImage.cpp
	g++ DisplayImage.cpp -o display $(CFLAGS) $(LFLAGS)

matchdemo : matchdemo.cpp
	g++ matchdemo.cpp -o matchdemo $(CFLAGS) $(LFLAGS)

jmatch : jmatch.cpp jutils.cpp jutils.hpp
	g++ jmatch.cpp jutils.cpp -o jmatch $(CFLAGS) $(LFLAGS)

search : search.cpp
	g++ search.cpp -o search $(CFLAGS) $(LFLAGS)

###########################################
# instructions for running:

# make

# set this variable to where the *.so files are:
# LD_LIBRARY_PATH=/home/pi/proj/opencv/opencv-3.4.1/build/lib ; export LD_LIBRARY_PATH

# run a specific file, for example:
# ./search data/nicubunu-Ornamental-deck-Queen-of-diamonds-300px.png 

# To run all of a rank:
# for i in data/nicubunu-Ornamental-deck-Queen-of-*-300px.png ; do echo $i ; ./search $i ; done

# To run all the cards of a particular suit:
# for i in data/nicubunu-Ornamental-deck-*-of-clubs-300px.png ; do echo $i ; ./search $i ; done

# To run all of them:
# for i in data/nicubunu-Ornamental-deck-*-300px.png ; do echo $i ; ./search $i ; done

# To display a specific file, along with the result image and best match area:
# ./matchdemo data/nicubunu-Ornamental-deck-Queen-of-diamonds-300px.png templates/patt-jr-alt-nicu.png

