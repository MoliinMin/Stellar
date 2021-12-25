#include "deptrum_device.h"



extern "C" STELLAR_API void  __stdcall TestDevice()
{
	const int RANGE_MIN = 250;
	const int RANGE_MID = 950;
	const int RANGE_MAX = 3000;
	const int occlusion_factor = 80;
	const int light_type = 5;
	const int threash_hold = 1;

	int result = 0;
	int device_count = 0;
	std::vector<deptrum::DeviceInformation> device_list;
	   result = Device::GetDeviceList(device_list);
	   device_count = device_list.size();
	   if (device_count < 1) {
	     cout << "Do not find deptrum device, device count: " << device_count << endl;
	     //return result;
	   }
	   cout << "Device count: " << device_count << endl;
	 
	   Device* device{nullptr};
	   result = Device::Create(&device, device_list[DEFUALT_DEVICE_INDEX]);
	   if (result == 0) {
	     cout << "Create device: " << device_list[DEFUALT_DEVICE_INDEX].model << endl;
	   }
	 
	   result = device->Open();
	   if (result != 0) {
	     cout << "Open devic failed, error info: " << aurora::GetErrorInfo(result) << endl;
	     //return result;
	   }
	   cout << "Open device succeed." << endl;
	 
	   result = device->SetMode(deptrum::FrameMode::kInvalid,
	                            deptrum::FrameMode::kInvalid,
	                            deptrum::FrameMode::kRes400x640Depth16Bit);
	   if (result != 0) {
	     cout << "Open deivce failed, error info: " << aurora::GetErrorInfo(result) << endl;
	   //  return result;
	   }
	 
	   Intrinsic ir_intri, rgb_intri;
	   Extrinsic ext;
	   result = device->GetCameraParameters(ir_intri, rgb_intri, ext);
	   if (result != 0) {
	     cout << "Get camera parameters failed: %x %s\n"
	          << result << aurora::GetErrorInfo(result) << endl;
	   //  return result;
	   }
	 
	   Stream* depth_stream{nullptr};
	   result = device->CreateStream(&depth_stream, deptrum::kDepth);
	   if (result != 0) {
	     cout << "Create stream failed, error info: " << aurora::GetErrorInfo(result) << endl;
	     getchar();
	   //  return result;
	   }
	 
	   Frame depth_frame;
	   depth_stream->AllocateFrame(depth_frame);
	   uint8_t* color = new uint8_t[depth_frame.rows * depth_frame.cols * 3];
	   depth_stream->SetConcurrency(4, 1);
	   depth_stream->Start();
	   cout << "Stream start getting frames" << endl << endl;
	 
	   cout << "--press 'f'/'F' to print fps--" << endl;
	   cout << "--press 'q'/'Q' to quit--" << endl;
	 
	   bool print_fps = false;
	 
	   while (1) {
	     result = depth_stream->GetFrame(depth_frame, 2000);
	     if (result != 0) {
	       if (result == 0x42005) {
	         cout << "Get frames timeout" << endl;
	         continue;
	       } else {
	         cout << "Get frames error: " << aurora::GetErrorInfo(result) << endl;
	         break;
	       }
	     }
	     // Draw depthmap in color
	     Visualizer::DrawDepthMapInColorByHist(color,
	                                           (uint16_t*) depth_frame.data,
	                                           depth_frame.rows,
	                                           depth_frame.cols);
	 
	     cv::Mat shadowed_depth_map(depth_frame.rows, depth_frame.cols, CV_8UC3, color);
	     cv::imshow("Depth", shadowed_depth_map);
		 cv::waitKey(20);
	 	//cv::Mat depth_map(depth_frame.rows, depth_frame.cols, CV_16UC1, depth_frame.data);
	 //     if (print_fps) {
	 //       static int count = 0;
	 //       static TimePoint start = TIMESTART;
	 //       count++;
	 //       if (count > 20) {
	 //         cout << "fps: " << count * 1000 / TIMEELAPSED(start) << endl;
	 //         start = TIMESTART;
	 //         count = 0;
	 //       }
	 //     }
	 
	 //     char key = cv::waitKey(1);
	 //     if (key == 'f' || key == 'F') {
	 //       print_fps = !print_fps;
	 //       cv::imwrite("test.png", depth_map);
	 // 	  GenerateAndSavePointCloudFromDepthMap(ir_intri, depth_map);
	 //     }
	 //     if (key == 'q' || key == 'Q') {
	 //       break;
	 //     }
	 // 	if (key == 's' || key == 'S')
	 // 	{
	 // 		GenerateAndSavePointCloudFromDepthMap(ir_intri,depth_map);
	 // 	}
	   }
	   cv::destroyAllWindows();
	   delete[] color;
	   Stream::ReleaseFrame(depth_frame);
	   depth_stream->Stop();
	   device->DestroyStream(&depth_stream);
	   device->Close();
	   Device::Destroy(&device);


}
