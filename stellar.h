#ifndef STELLAR_H
#define STELLAR_H

#include "data_types.h"
#include ""

enum StellarErrors
{


};
class Stellar
{
public:
	virtual ~Stellar() = default;

	virtual StellarErrors Initialize(const StellarParams &stellar_params)=0;

	virtual StellarErrors StartDevice()=0;

	virtual StellarErrors GetFrameData(uint16_t * output_depth_data,uint8_t *output_rgb_data)=0;

	virtual StellarErrors DestoryDevice() = 0;

	virtual StellarErrors StellarFusion() = 0;



};
#endif