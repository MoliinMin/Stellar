#ifndef DEPTRUM_DEVICE_H
#define DEPTRUM_DEVICE_H
//#include "include/opencv/opencv"
#include "opencv2/opencv.hpp"
#include "deptrum/deptrum.h"

 using namespace deptrum;
 using namespace deptrum::aurora;
#define DEFAULT_DEVICE_INDEX 0

 class DeptrumDevice
 {
 public:
	 DeptrumDevice();
	 ~DeptrumDevice();
	 bool CreateDevice();

	 bool OpenDevice();

	 void CreateStream();



      




 private:
	 Device *global_device;


 };






#endif
