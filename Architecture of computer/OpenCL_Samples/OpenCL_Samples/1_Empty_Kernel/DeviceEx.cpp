#include "DeviceEx.h"

using namespace std;
using namespace cl;

string DeviceEx::GetVendor(const Device& device)
{
	return string(device.getInfo<CL_DEVICE_VENDOR>());
}

string DeviceEx::GetName(const Device& device)
{
	return string(device.getInfo<CL_DEVICE_NAME>());
}