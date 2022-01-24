#ifndef SURFACE_MEASUREMENT_H
#define SURFACE_MEASUREMENT_H
#include "point_cloud_generator.h"
#include "data_types.h"
class SurfaceMeasurement
{
public:

	void GeneratePointCloud(const GpuMat &input_depth_map,std::vector<PointXyz> &output_point_cloud);

	void Init(std::shared_ptr<StellarParams> stellar_params_,std::shared_ptr<CameraParamsPyramid> camera_params_pyramid_);

	void Run(const cv::Mat &input_depth_map, const cv::Mat &input_rgb_map);

private:
	std::shared_ptr<CameraParamsPyramid> camera_params_pyramid;
	std::shared_ptr<StellarParams> stellar_params;
};


#endif
