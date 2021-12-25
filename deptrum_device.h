#ifndef DEPTRUM_DEVICE_H
#define DEPTRUM_DEVICE_H
//#include "include/opencv/opencv"
#include "opencv2/opencv.hpp"
#include "deptrum/deptrum.h"


#if defined(_MSC_VER)||defined(_WIN32)||defined(_WIN64)
#ifdef STELLAR_EXPORTS
#define STELLAR_API _declspec(dllexport)
#else
#define STELLAR_API _declspec(dllimport)
#endif
#else
#define STELLAR_API
#endif

#define DEFUALT_DEVICE_INDEX 0
 using namespace std;
 using namespace deptrum;
 using namespace deptrum::aurora;

extern "C" STELLAR_API void  __stdcall TestDevice();





#endif
