#include "deptrum_device.h"

DeptrumDevice::DeptrumDevice():global_device(nullptr)
{

}

DeptrumDevice::~DeptrumDevice()
{

}

bool DeptrumDevice::CreateDevice()
{
	std::vector<DeviceInformation> device_list;
	int result = 0;
	result = Device::GetDeviceList(device_list);
	size_t device_conut = device_list.size();
	if (device_conut<1)
	{
		return false;
	}
	result = Device::Create(&global_device, device_list[DEFAULT_DEVICE_INDEX]);
	if (result != 0)
	{
		return false;
	}
	return true;
}

bool DeptrumDevice::OpenDevice()
{
	int result=global_device->Open();
	if (result!=0)
	{
		return false;
	}
	result = global_device->SetMode(deptrum::FrameMode::kInvalid,
		                            deptrum::FrameMode::kRes480x640RgbJpeg,
		                            deptrum::FrameMode::kRes400x640Depth16Bit);
	if (result != 0)
	{
		return false;
	}
	return true;
}

void DeptrumDevice::CreateStream()
{
	
}

