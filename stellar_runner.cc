#include "opencv2/opencv.hpp"
#include "stellar.h"
#include "data_types.h"
#include "cuda.h"
#include <opencv2/cudaimgproc.hpp>
int main()
{

	StellarParams stellar_params;

	stellar_params.data_cutoff = 500;
	stellar_params.image_height = 640;
	stellar_params.image_width = 480;
	stellar_params.pyramid_levels = 3;
	stellar_params.kernel_size = 5;
	stellar_params.spatial_sigma = 1.0f;
	stellar_params.sigma = 1.0f;
	/*stellar_params.*/
	Stellar *stellar = Stellar::Create();
	stellar->Initialize(stellar_params); 
	stellar->StartDevice();
	while (1)
	{
		cv::Mat depth_image, rgb_image;
		stellar->GetFrames(depth_image, rgb_image);
		stellar->StellarFusion(depth_image,rgb_image);
		cv::waitKey(20);
	}
	stellar->DestoryDevice();
	Stellar::Destory(stellar);
	  


	cv::waitKey(0);

	return 0;
}
