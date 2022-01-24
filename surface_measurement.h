#ifndef SURFACE_MEASUREMENT_H
#define SURFACE_MEASUREMENT_H
#include "point_cloud_generator.h"
#include "data_types.h"
#include <opencv2/cudaarithm.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudafilters.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
class SurfaceMeasurement
{
public:

	void Init(std::shared_ptr<StellarParams> stellar_params_,std::shared_ptr<CameraParamsPyramid> camera_params_pyramid_);

	void Run(FrameData &output_frame_data, cv::Mat &input_depth_map, const cv::Mat &input_rgb_map);

private:
	std::shared_ptr<CameraParamsPyramid> camera_params_pyramid;
	std::shared_ptr<StellarParams> stellar_params;
};


#endif
