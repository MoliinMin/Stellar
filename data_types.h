#ifndef DATA_TYPE_H
#define DATA_TYPE_H
#include "cuda_runtime.h"

#include <opencv2/core/cuda.hpp>
#include <opencv2/core/cuda_types.hpp>

 
struct StellarParams
{
	int pyramid_levels;
	int image_height;
	int image_width;


};

#endif
