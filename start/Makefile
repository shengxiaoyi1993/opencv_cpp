OPENCV_FILE=opencv-3.4.1.zip
OPENCV_PATH=opencv-3.4.1

all:
	rm $(OPENCV_FILE)* -rf
	wget  ftp://pub:9900@192.168.1.238/lib/opencv-3.4.1.zip -O $(OPENCV_FILE)
	unzip -o $(OPENCV_FILE)
	-mkdir $(OPENCV_PATH)/build/
	cp script/Makefile $(OPENCV_PATH)/build/
	cd $(OPENCV_PATH)/build/ && make
