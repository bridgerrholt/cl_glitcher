//
// Created by bridg on 3/5/2021.
//

#include <gpu_util/init.h>

#include <vector>
#include <exception>

namespace clglitch::gpu_util {

GpuHandle::GpuHandle(cl::Device device) :
  device {device},
  context {{device}}
{

}


GpuHandle init()
{
  std::vector<cl::Platform> platforms;
  cl::Platform::get(&platforms);

  if (platforms.empty())
  {
    throw std::runtime_error("No platforms found. Check OpenCL installation");
  }

  cl::Platform defaultPlatform = platforms[0];

  // get default device (CPUs, GPUs) of the default platform
	cl::Device device;

  std::vector<cl::Device> gpuDevices;
	defaultPlatform.getDevices(CL_DEVICE_TYPE_GPU, &gpuDevices);
	if (gpuDevices.size() > 0)
	{
		device = gpuDevices[0];
	}
	else
	{
		std::vector<cl::Device> allDevices;
		defaultPlatform.getDevices(CL_DEVICE_TYPE_ALL, &allDevices);

		if (allDevices.empty())
		{
			throw std::runtime_error("No devices found. Check OpenCL installation!");
		}

		device = allDevices[0];
	}

  // a context is like a "runtime link" to the device and platform;
  // i.e. communication is possible
  return GpuHandle {device};
}

}