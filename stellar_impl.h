
#ifndef STELLAR_IMPL_H
#define STELLAR_IMPL_H
#include "stellar.h"
#include "deptrum_device.h"
#include "global.h"
class StellarImpl:public Stellar
{

public:
	StellarImpl() = default;
	~StellarImpl() = default;

	StellarErrors Initialize(const StellarParams &stellar_params) override;

	StellarErrors StartDevice() override;

	StellarErrors GetFrameData(uint16_t * output_depth_data, uint8_t *output_rgb_data) override;

	StellarErrors DestoryDevice() override;

	StellarErrors StellarFusion() override;
private:
	CameraParamsPyramid depth_camera_params_pyramid;
	
	DeptrumDevice deptrum_device;



};


#endif
