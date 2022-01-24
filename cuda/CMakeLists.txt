cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

cuda_add_library(utils STATIC utils.h 
                              utils.cu)

target_link_libraries(utils ${OPENCV_CUDA_LIBS})

cuda_add_library(point_cloud_generator STATIC  
                 point_cloud_generator.h
				 point_cloud_generator.cu)

target_link_libraries(point_cloud_generator ${OPENCV_CUDA_LIBS}
                                            utils)
											
cuda_add_library(pose_estimation STATIC pose_estimation.h
                                        pose_estimation.cu)
										
target_link_libraries(pose_estimation ${OPENCV_CUDA_LIBS})