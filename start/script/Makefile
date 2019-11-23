all:
	-mkdir build_main
	cd build_main && cmake -DCPU_DISPATCH= -D WITH_CUDA=OFF -D CMAKE_BUILD_TYPE=Release -D WITH_QT=ON -D  CMAKE_INSTALL_PREFIX=`pwd`/../../../lib/opencv-3.4.1 -G "Unix Makefiles" ../..
	cd build_main && make -j 4 && make -j 4 install
