#include "opencv2/opencv.hpp"
#include "stellar.h"
#include "data_types.h"

int main()
{

	StellarParams stellar_params;
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

	return 0;
}
