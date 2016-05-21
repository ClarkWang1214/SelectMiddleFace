CMake Project - Select Middle Face Based on CLM-framework (Now the project has moved to new repositories: OpenFace - https://github.com/TadasBaltrusaitis/OpenFace Created by TadasBaltrusaitis) 



This code has been tested on Ubuntu 14.04

This requires cmake, OpenCV 3.0.0 (or newer), tbb and boost.

Need to do the following:

1. Get newest GCC, done using:
	sudo apt-get update
	sudo apt-get install build-essential

2. Cmake: sudo apt-get install cmake

3. Get BLAS (for dlib)
	sudo apt-get install libopenblas-dev liblapack-dev 

4. OpenCV 3.0.0, Based on tutorial from http://docs.opencv.org/trunk/doc/tutorials/introduction/linux_install/linux_install.html
	4.1 Install OpenCV dependencies:
	sudo apt-get install git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
    	sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev checkinstall

	4.2 Download OpenCV 3.0.0 https://github.com/Itseez/opencv/archive/3.0.0-beta.zip

	4.3 Unzip it and create a build folder there:
	
		unzip 3.0.0-beta.zip
		cd opencv-3.0.0-beta
		mkdir build
		cd build

	4.4 Build it using: 
		cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_SHARED_LIBS=OFF ..
		make -j2
		sudo make install	
	
5. Get Boost: sudo apt-get install libboost1.55-all-dev
	alternatively: sudo apt-get install libboost-all-dev


6. Make the actual Glasses_PoseEstimation_SelectFrames and compile it using
	cd Glasses_PoseEstimation_SelectFrames_Use
	mkdir build
	cmake -D CMAKE_BUILD_TYPE=RELEASE .. 
	make -j2
	cd ..

7. a) Update your video path you want to store in the src/main.cpp text;
      For example, change the default directory "Video/". to the path you want to load;
   b) Then, the program will create two directoies: "Images" and "FaceImages", in the "bin" directory by the side of excutable file "Glasses_PoseEstimation_SelectFrames_Use";  
   c) Finally, the result of key images and face images will be saved  in the two directories "Images" and "FaceImages", respectively.

8. test it with 
	cd bin
	./Glasses_PoseEstimation_SelectFrames_Use

<img src="https://github.com/ClarkWang12/SelectMiddleFace/blob/master/SelectMiddleFace_Use/bin/FaceImages/6020535_4.jpg" height="100" width="100" >
<img src="https://github.com/ClarkWang12/SelectMiddleFace/blob/master/SelectMiddleFace_Use/bin/FaceImages/6020763_2.jpg" height="100" width="100" >
<img src="https://github.com/ClarkWang12/SelectMiddleFace/blob/master/SelectMiddleFace_Use/bin/FaceImages/6020426_4.jpg" height="100" width="100" >
<img src="https://github.com/ClarkWang12/SelectMiddleFace/blob/master/SelectMiddleFace_Use/bin/FaceImages/6020444_1.jpg" height="100" width="100" >
<img src="https://github.com/ClarkWang12/SelectMiddleFace/blob/master/SelectMiddleFace_Use/bin/FaceImages/5828767_4.jpg" height="100" width="100" >
<img src="https://github.com/ClarkWang12/SelectMiddleFace/blob/master/SelectMiddleFace_Use/bin/FaceImages/6020834_2.jpg" height="100" width="100" >
<img src="https://github.com/ClarkWang12/SelectMiddleFace/blob/master/SelectMiddleFace_Use/bin/FaceImages/6020627_4.jpg" height="100" width="100" >
<img src="https://github.com/ClarkWang12/SelectMiddleFace/blob/master/SelectMiddleFace_Use/bin/FaceImages/6020458_0.jpg" height="100" width="100" >







