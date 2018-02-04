#include "PlarformEx.h"

using namespace std;
using namespace cl;

vector<Platform> PlarformEx::GetPlatforms()
{
	auto platforms = vector<Platform>();
	Platform::get(&platforms);
	return platforms;
}

vector<Device> PlarformEx::GetDevices(const Platform& platform)
{
	auto devices = vector<Device>();
	platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
	return devices;
}