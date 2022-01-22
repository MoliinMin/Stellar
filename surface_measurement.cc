
#include "surface_measurement.h"
void SurfaceMeasurement::GeneratePointCloud(const GpuMat &input_depth_map, std::vector<PointXyz> &output_point_cloud)
{


// 	GpuMat output_vertex_map;
 	float cutoff_val = 500.0f;
// 	ComputeVertexMap<< <blocks,threads> >>(input_depth_map, output_vertex_map, cutoff_val,camera_params);
	GpuMat output_vertex_map;
	//ComputeVertexMap(output_vertex_map, input_depth_map, cutoff_val, camera_params);
}

void SurfaceMeasurement::Init(std::shared_ptr<CameraParams> camera_params_)
{
	camera_params = camera_params_;
}

