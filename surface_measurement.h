#ifndef SURFACE_MEASUREMENT_H
#define SURFACE_MEASUREMENT_H
#include "point_cloud_generator.h"
#include "data_types.h"
class SurfaceMeasurement
{
public:

	void GeneratePointCloud(const GpuMat &input_depth_map,std::vector<PointXyz> &output_point_cloud);

private:
	CameraParams camera_params;
};


#endif
