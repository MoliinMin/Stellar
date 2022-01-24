#ifndef STELLAR_H
#define STELLAR_H

#include "data_types.h"
#include "opencv2/opencv.hpp"

enum StellarErrors
{
	OK = 0

};
class Stellar
{
public:
	virtual ~Stellar() = default;

	virtual StellarErrors Initialize(const StellarParams &stellar_params)=0;

	virtual StellarErrors StartDevice()=0;

	virtual StellarErrors GetFrames(cv::Mat &output_depth_frame, cv::Mat &output_rgb_frame) = 0;

	virtual StellarErrors DestoryDevice() = 0;

	virtual StellarErrors StellarFusion(const cv::Mat &input_depth_mat,const cv::Mat &input_rgb_mat) = 0;

	static Stellar *Create();

	static void Destory(Stellar *stellar_object);


};
#endif
