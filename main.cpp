#include <iostream>
#include <stdlib.h>
#include <CL/cl.h>
#include <vector>
#include <random>
#include <exception>

struct OpenClInformation
{


};


typedef cl_platform_id ClPlatId;
typedef cl_uint ClUInt;
typedef cl_int  ClInt;
typedef cl_device_id  ClDevId;
typedef cl_context  ClCont;


#define array_length 1024

auto PopulateVector(std::vector<int> &intVector) -> void
{
    for(auto &currentElement : intVector)
    {
        currentElement = 55;
    }
}

auto PrintVector(std::vector<int> &intVector) -> void
{
    for(auto &currentElement : intVector)
    {
        std::cout << currentElement;
    }
    std::cout << "\n";
}

auto GetOpenClContext() -> OpenClInformation*
{

}

auto Pause() -> void
{
    std::cout << "Press any key to continue...\n";
    std::cin.get();
}

auto MultipleTwoArrays() -> void
{
    auto arrayA = std::vector<int>();
    arrayA.reserve(array_length);
    PopulateVector(arrayA);

    auto arrayB= std::vector<int>();
    arrayB.reserve(array_length);
    PopulateVector(arrayB);

    auto arrayC = std::vector<int>();
    arrayC.reserve(array_length);
}

inline void CheckForErrorsOpenCL(ClInt status)
{
    if(status != CL_SUCCESS) {
        std::cout  << "An error occured !! " << __LINE__ << "\n";
        throw std::exception();
    }
}

inline void CheckForErrorsOpenCL(ClInt status, std::string error)
{
    if(status != CL_SUCCESS) {
        std::cout  << error << " " << __LINE__ << "\n";
        throw std::exception();
    }
}


void GetFullPlatformInformation(ClPlatId platformId)
{
    size_t size = 0;

    auto getPlatformInformation = [&](ClPlatId platformId, ClUInt infoType, std::string typeString)
    {
        std::vector<char> charArray(1024);
        CheckForErrorsOpenCL(clGetPlatformInfo(platformId, infoType, charArray.size(), charArray.data(), &size));
        std::cout << typeString << charArray.data()<< std::endl;
    };
    getPlatformInformation(platformId, CL_PLATFORM_NAME, "NAME:");
    getPlatformInformation(platformId, CL_PLATFORM_PROFILE, "PROFILE:");
    getPlatformInformation(platformId, CL_PLATFORM_VERSION, "VERSION:");
    getPlatformInformation(platformId, CL_PLATFORM_VENDOR, "VENDOR:");
    getPlatformInformation(platformId, CL_PLATFORM_EXTENSIONS, "EXTENSIONS:");
}


void PrintDeviceInformation(ClDevId deviceId)
{
    size_t size = 0;
    auto getDeviceInformation = [&](ClDevId deviceId, ClUInt infoType, std::string typeString)
    {
        std::vector<char> charArray(1024);
        CheckForErrorsOpenCL(clGetDeviceInfo(deviceId, infoType, charArray.size(), charArray.data(), &size));
        std::cout << charArray.data()<< std::endl;
    };

    getDeviceInformation(deviceId, CL_DEVICE_NAME, "DEVICE NAME:");
    getDeviceInformation(deviceId, CL_DEVICE_TYPE, "DEVICE TYPE:");
}

int main() {
    ClInt err;
    ClUInt numPlatforms;

    try
    {
        CheckForErrorsOpenCL(clGetPlatformIDs(0, nullptr, &numPlatforms));

        if(numPlatforms == 0)
            std::cout << "No platforms found on this machine" << "\n";

        std::vector<ClPlatId> platforms(numPlatforms);


        std::cout << numPlatforms << std::endl;

        // get the ids of the platforms
        CheckForErrorsOpenCL(clGetPlatformIDs(numPlatforms, platforms.data(), nullptr));

        ClUInt numDevices = 0;

        // get the number of gpu devices on platform 0
        CheckForErrorsOpenCL(clGetDeviceIDs(platforms[1], CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices));

        std::vector<ClDevId> deviceList(numDevices);
        CheckForErrorsOpenCL(clGetDeviceIDs(platforms[1], CL_DEVICE_TYPE_GPU, numDevices, deviceList.data(), nullptr));

        PrintDeviceInformation(deviceList[0]);

        ClCont context = clCreateContext(nullptr, numDevices, deviceList.data(), nullptr, nullptr, &err);
        cl_command_queue command_queue = clCreateCommandQueue(context, deviceList.data()[0], 0, &err);
        //std::cout << context << std::endl;
    }
    catch (std::exception &exception)
    {
        std::cout << exception.what() << "\n";
    }

    Pause();
    return 0;
}