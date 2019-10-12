OPENCV_FILE=opencv-3.4.1.zip
OPENCV_PATH=opencv-3.4.1

all:
	rm $(OPENCV_FILE)* -rf
	wget  https://codeload.github.com/opencv/opencv/zip/3.4.1 -O $(OPENCV_FILE)
	unzip -o $(OPENCV_FILE)
	-mkdir $(OPENCV_PATH)/build/
	cp script/Makefile $(OPENCV_PATH)/build/
	cd $(OPENCV_PATH)/build/ && make
