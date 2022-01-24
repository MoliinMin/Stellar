cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(Stellar)


add_definitions(-DSTELLAR_EXPORTS)


find_package(CUDA 10.0 REQUIRED)
IF (CUDA_FOUND)
    include_directories("${CUDA_INCLUDE_DIRS}")
	 message(WARNING "find cuda")
    # Optional: Specify the arch of your CUDA hardware here
    SET(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-O3;-std=c++11 -gencode arch=compute_61,code=sm_61)
ENDIF ()

set(THIRD_PARTY_PATH "E:/third party/windows-amd64")

include_directories(${THIRD_PARTY_PATH}/deptrum/include)
message(WARNING ${THIRD_PARTY_PATH}/deptrum/include)
link_directories(${THIRD_PARTY_PATH}/deptrum/libs)

set(THIRD_PARTY_LIBS  deptrum_aurora
	                  opencv_world343
	                  libjasper
	                  libjpeg-turbo
	                  libwebp
	                  libpng
	                  zlib)
		

include_directories(${THIRD_PARTY_PATH}/opencv_cuda/include)
link_directories(${THIRD_PARTY_PATH}/opencv_cuda/static_lib)

set(OPENCV_CUDA_LIBS opencv_core3414
                     opencv_cudaarithm3414
					 opencv_cudabgsegm3414
					 opencv_cudacodec3414
					 opencv_cudafeatures2d3414
					 opencv_cudafilters3414
					 opencv_cudaimgproc3414
					 opencv_cudalegacy3414
					 opencv_cudaobjdetect3414
					 opencv_cudastereo3414
					 opencv_cudawarping3414
					 opencv_cudev3414
					 opencv_features2d3414
					 opencv_flann3414
					 opencv_highgui3414
					 opencv_imgcodecs3414
					 opencv_imgproc3414
					 opencv_objdetect3414
					 opencv_photo3414
					 opencv_shape3414
					 opencv_stitching3414
					 opencv_ts3414)

include_directories(${THIRD_PARTY_PATH}/pcl/3rdParty/Eigen)





add_library(deptrum_device STATIC 
            deptrum_device.h
            deptrum_device.cc
           )
			
target_link_libraries(deptrum_device ${THIRD_PARTY_LIBS})




add_library(surface_measurement STATIC 
            surface_measurement.h
			surface_measurement.cc)
			
target_link_libraries(surface_measurement ${THIRD_PARTY_LIBS}
                                          ${OPENCV_CUDA_LIBS}
                                           point_cloud_generator)


add_executable(deptrum_runner deptrum_runner.cc)

target_link_libraries(deptrum_runner deptrum_device
                                     ${THIRD_PARTY_LIBS})


add_library(Stellar STATIC stellar_impl.h
                           stellar.h
						   data_types.h
						   global.h
						   stellar_impl.cc)

target_link_libraries(Stellar surface_measurement
                              point_cloud_generator
							  deptrum_device
                              ${THIRD_PARTY_LIBS}
							  ${OPENCV_CUDA_LIBS})
					
add_executable(stellar_runner stellar_runner.cc)

target_link_libraries(stellar_runner Stellar
                                     ${OPENCV_CUDA_LIBS})
					

add_subdirectory(cuda)
