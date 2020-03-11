#!/usr/bin/env bash

cp .config buildroot/.config
pushd buildroot
	make olddefconfig && make sdk
	sudo cp output/images/arm-buildroot-linux-uclibcgnueabihf_sdk-buildroot.tar.gz /opt/
	
	pushd /opt
		sudo tar -xvf arm-buildroot-linux-uclibcgnueabihf_sdk-buildroot.tar.gz
		pushd arm-buildroot-linux-uclibcgnueabihf_sdk-buildroot
			sudo ./relocate-sdk.sh
		popd
		sudo rm arm-buildroot-linux-uclibcgnueabihf_sdk-buildroot.tar.gz
	popd
	
	echo "PATH=\"/opt/arm-buildroot-linux-uclibcgnueabihf_sdk-buildroot/bin:$PATH\"" >> ~/.profile
	source ~/.profile
popd

pushd lvgl_app/
	mkdir build && pushd build
		cmake -G "Ninja" -DCMAKE_CXX_COMPILER:FILEPATH=/opt/arm-buildroot-linux-uclibcgnueabihf_sdk-buildroot/bin/arm-buildroot-linux-uclibcgnueabihf-g++ -DCMAKE_C_COMPILER:FILEPATH=/opt/arm-buildroot-linux-uclibcgnueabihf_sdk-buildroot/bin/arm-buildroot-linux-uclibcgnueabihf-gcc -DCMAKE_BUILD_TYPE:STRING=Debug ..
		cmake --build .
	popd
popd
