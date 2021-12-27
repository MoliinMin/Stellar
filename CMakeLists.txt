cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(Stellar)


add_definitions(-DSTELLAR_EXPORTS)

set(THIRD_PARTY_PATH "D:/third party/deptrum")

include_directories(${THIRD_PARTY_PATH}/include)
message(WARNING ${THIRD_PARTY_PATH}/include)
link_directories(${THIRD_PARTY_PATH}/libs)

set(THIRD_PARTY_LIBS  deptrum_aurora
	                  opencv_world343
	                  libjasper
	                  libjpeg-turbo
	                  libwebp
	                  libpng
	                  zlib)
		


add_library(deptrum_device STATIC 
            deptrum_device.cc
            deptrum_device.h)
			
target_link_libraries(deptrum_device ${THIRD_PARTY_LIBS})