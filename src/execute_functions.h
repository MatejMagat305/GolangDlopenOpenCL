/*
 *   this that dlsyms into actual library based on environment variable
 *   depending on correct given path
**/

#include <stdlib.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include "../include/store_loaded_functions.h"

/*#if defined(__APPLE__) || defined(__MACOSX)
static const char *default_so_paths[] = {
  "libOpenCL.so",
  "/System/Library/Frameworks/OpenCL.framework/OpenCL"
};
int u(){
    return 0;
};
#elif defined(__ANDROID__)
static const char *default_so_paths[] = {
  "/system/lib64/libOpenCL.so",
  "/system/vendor/lib64/libOpenCL.so",
  "/system/vendor/lib64/egl/libGLES_mali.so",
  "/system/vendor/lib64/libPVROCL.so",
  "/data/data/org.pocl.libs/files/lib64/libpocl.so",
  "/system/lib/libOpenCL.so",
  "/system/vendor/lib/libOpenCL.so",
  "/system/vendor/lib/egl/libGLES_mali.so",
  "/system/vendor/lib/libPVROCL.so",
  "/data/data/org.pocl.libs/files/lib/libpocl.so",
  "libOpenCL.so"
};

int u(){
    return 1;
};
#elif defined(_WIN32)
static const char *default_so_paths[] = {
  "OpenCL.dll"
};

int u(){
    return 2;
};
#elif defined(__linux__)
static const char *default_so_paths[] = {
        "/usr/lib/libOpenCL.so",
        "/usr/local/lib/libOpenCL.so",
        "/usr/local/lib/libpocl.so",
        "/usr/lib64/libOpenCL.so",
        "/usr/lib32/libOpenCL.so",
        "libOpenCL.so"
};

int u(){
    return 10;
};
#endif
*/
static void *so_handle = NULL;

static int access_file(const char *filename){
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}

static int open_libopencl_so_with_path(const char * path)
{
    if(path )
    {
        if ( access_file(path))
        {
            so_handle = dlopen(path, RTLD_LAZY);
            return 0;
        }
    }
    return -1;
}

static int open_libopencl_so_with_multiple_path(const char **path, const int length)
{
    for (int i = 0; i < length; ++i) {
        if (open_libopencl_so_with_path(path[i]) == 0)
        {
            return 0;
        }
    }
    return -1;
}

void stubOpenclReset() {
    if (so_handle)
    {
        dlclose(so_handle);
    }
    so_handle = NULL;
}

cl_int
clGetPlatformIDs(cl_uint          num_entries,
                 cl_platform_id * platforms,
                 cl_uint *        num_platforms)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clGetPlatformIDs == NULL || !fun_fake_clGetPlatformIDs)
        fun_fake_clGetPlatformIDs =(fake_clGetPlatformIDs) dlsym(so_handle, "clGetPlatformIDs");

    if(fun_fake_clGetPlatformIDs) {
        return fun_fake_clGetPlatformIDs(num_entries, platforms, num_platforms);
    }
    return CL_INVALID_PLATFORM;
}


cl_int
clGetPlatformInfo(cl_platform_id   platform,
                  cl_platform_info param_name,
                  size_t           param_value_size,
                  void *           param_value,
                  size_t *         param_value_size_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clGetPlatformInfo == NULL || !fun_fake_clGetPlatformInfo)
        fun_fake_clGetPlatformInfo =(fake_clGetPlatformInfo) dlsym(so_handle, "clGetPlatformInfo");

    if(fun_fake_clGetPlatformInfo) {
        return fun_fake_clGetPlatformInfo(platform, param_name, param_value_size, param_value, param_value_size_ret);
    }
    return CL_INVALID_PLATFORM;
}


cl_int
clGetDeviceIDs(cl_platform_id   platform,
               cl_device_type   device_type,
               cl_uint          num_entries,
               cl_device_id *   devices,
               cl_uint *        num_devices)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clGetDeviceIDs == NULL || !fun_fake_clGetDeviceIDs)
        fun_fake_clGetDeviceIDs =(fake_clGetDeviceIDs) dlsym(so_handle, "clGetDeviceIDs");

    if(fun_fake_clGetDeviceIDs) {
        return fun_fake_clGetDeviceIDs(platform, device_type, num_entries, devices, num_devices);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clGetDeviceInfo(cl_device_id    device,
                cl_device_info  param_name,
                size_t          param_value_size,
                void *          param_value,
                size_t *        param_value_size_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clGetDeviceInfo == NULL || !fun_fake_clGetDeviceInfo)
        fun_fake_clGetDeviceInfo =(fake_clGetDeviceInfo) dlsym(so_handle, "clGetDeviceInfo");

    if(fun_fake_clGetDeviceInfo) {
        return fun_fake_clGetDeviceInfo(device, param_name, param_value_size, param_value, param_value_size_ret);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clCreateSubDevices(cl_device_id                         in_device,
                   const cl_device_partition_property * properties,
                   cl_uint                              num_devices,
                   cl_device_id *                       out_devices,
                   cl_uint *                            num_devices_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clCreateSubDevices == NULL || !fun_fake_clCreateSubDevices)
        fun_fake_clCreateSubDevices =(fake_clCreateSubDevices) dlsym(so_handle, "clCreateSubDevices");

    if(fun_fake_clCreateSubDevices) {
        return fun_fake_clCreateSubDevices(in_device, properties, num_devices, out_devices, num_devices_ret);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clRetainDevice(cl_device_id device)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clRetainDevice == NULL || !fun_fake_clRetainDevice)
        fun_fake_clRetainDevice =(fake_clRetainDevice) dlsym(so_handle, "clRetainDevice");

    if(fun_fake_clRetainDevice) {
        return fun_fake_clRetainDevice(device);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clReleaseDevice(cl_device_id device)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clReleaseDevice == NULL || !fun_fake_clReleaseDevice)
        fun_fake_clReleaseDevice =(fake_clReleaseDevice) dlsym(so_handle, "clReleaseDevice");

    if(fun_fake_clReleaseDevice) {
        return fun_fake_clReleaseDevice(device);
    }
    return CL_INVALID_PLATFORM;
}


cl_context
clCreateContext(const cl_context_properties * properties,
                cl_uint                 num_devices,
                const cl_device_id *    devices,
                void (*pfn_notify)(const char *, const void *, size_t, void *),
                void *                  user_data,
                cl_int *                errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateContext == NULL || !fun_fake_clCreateContext)
        fun_fake_clCreateContext =(fake_clCreateContext) dlsym(so_handle, "clCreateContext");

    if(fun_fake_clCreateContext) {
        return fun_fake_clCreateContext(properties, num_devices, devices, pfn_notify, user_data, errcode_ret);
    }
    return NULL;
}

cl_context
clCreateContextFromType(const cl_context_properties * properties,
                        cl_device_type          device_type,
                        void (*pfn_notify )(const char *, const void *, size_t, void *),
                        void *                  user_data,
                        cl_int *                errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateContextFromType == NULL || !fun_fake_clCreateContextFromType)
        fun_fake_clCreateContextFromType =(fake_clCreateContextFromType) dlsym(so_handle, "clCreateContextFromType");

    if(fun_fake_clCreateContextFromType) {
        return fun_fake_clCreateContextFromType(properties, device_type, pfn_notify, user_data, errcode_ret);
    }
    return NULL;
}

cl_int
clRetainContext(cl_context context)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clRetainContext == NULL || !fun_fake_clRetainContext)
        fun_fake_clRetainContext =(fake_clRetainContext) dlsym(so_handle, "clRetainContext");

    if(fun_fake_clRetainContext) {
        return fun_fake_clRetainContext(context);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clReleaseContext(cl_context context)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clReleaseContext == NULL || !fun_fake_clReleaseContext)
        fun_fake_clReleaseContext =(fake_clReleaseContext) dlsym(so_handle, "clReleaseContext");

    if(fun_fake_clReleaseContext) {
        return fun_fake_clReleaseContext(context);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clGetContextInfo(cl_context         context,
                 cl_context_info    param_name,
                 size_t             param_value_size,
                 void *             param_value,
                 size_t *           param_value_size_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clGetContextInfo == NULL || !fun_fake_clGetContextInfo)
        fun_fake_clGetContextInfo =(fake_clGetContextInfo) dlsym(so_handle, "clGetContextInfo");
    if(fun_fake_clGetContextInfo) {
        return fun_fake_clGetContextInfo(context, param_name, param_value_size,
                                         param_value, param_value_size_ret);
    }
    return CL_INVALID_PLATFORM;
}


cl_command_queue
clCreateCommandQueue(cl_context                     context,
                     cl_device_id                   device,
                     cl_command_queue_properties    properties,
                     cl_int *                       errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateCommandQueue == NULL || !fun_fake_clCreateCommandQueue)
        fun_fake_clCreateCommandQueue =(fake_clCreateCommandQueue) dlsym(so_handle, "clCreateCommandQueue");

    if(fun_fake_clCreateCommandQueue) {
        return fun_fake_clCreateCommandQueue(context, device, properties, errcode_ret);
    }
    return NULL;
}

#ifdef CL_VERSION_2_0
cl_command_queue
clCreateCommandQueueWithProperties(cl_context                     context,
                                   cl_device_id                   device,
                     	             const cl_queue_properties *    properties,
                                   cl_int *                       errcode_ret)
{
  if(!so_handle)
      return NULL;
  if(fun_fake_clCreateCommandQueueWithProperties == NULL || !fun_fake_clCreateCommandQueueWithProperties)
      fun_fake_clCreateCommandQueueWithProperties=(fake_clCreateCommandQueueWithProperties) dlsym(so_handle, "clCreateCommandQueueWithProperties");

  if(fun_fake_clCreateCommandQueueWithProperties) {
    return fun_fake_clCreateCommandQueueWithProperties(context, device, properties, errcode_ret);
  }
  return NULL;
}
#endif

cl_int
clRetainCommandQueue(cl_command_queue command_queue)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clRetainCommandQueue == NULL || !fun_fake_clRetainCommandQueue)
        fun_fake_clRetainCommandQueue =(fake_clRetainCommandQueue) dlsym(so_handle, "clRetainCommandQueue");

    if(fun_fake_clRetainCommandQueue) {
        return fun_fake_clRetainCommandQueue(command_queue);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clReleaseCommandQueue(cl_command_queue command_queue)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clReleaseCommandQueue == NULL || !fun_fake_clReleaseCommandQueue)
        fun_fake_clReleaseCommandQueue =(fake_clReleaseCommandQueue) dlsym(so_handle, "clReleaseCommandQueue");

    if(fun_fake_clReleaseCommandQueue) {
        return fun_fake_clReleaseCommandQueue(command_queue);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clGetCommandQueueInfo(cl_command_queue      command_queue,
                      cl_command_queue_info param_name,
                      size_t                param_value_size,
                      void *                param_value,
                      size_t *              param_value_size_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clGetCommandQueueInfo == NULL || !fun_fake_clGetCommandQueueInfo)
        fun_fake_clGetCommandQueueInfo =(fake_clGetCommandQueueInfo) dlsym(so_handle, "clGetCommandQueueInfo");

    if(fun_fake_clGetCommandQueueInfo) {
        return fun_fake_clGetCommandQueueInfo(command_queue, param_name, param_value_size,
                                              param_value, param_value_size_ret);
    }
    return CL_INVALID_PLATFORM;
}


cl_mem
clCreateBuffer(cl_context   context,
               cl_mem_flags flags,
               size_t       size,
               void *       host_ptr,
               cl_int *     errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateBuffer == NULL || !fun_fake_clCreateBuffer)
        fun_fake_clCreateBuffer =(fake_clCreateBuffer) dlsym(so_handle, "clCreateBuffer");

    if(fun_fake_clCreateBuffer) {
        return fun_fake_clCreateBuffer(context, flags, size, host_ptr, errcode_ret);
    }
    return NULL;
}

cl_mem
clCreateSubBuffer(cl_mem                   buffer,
                  cl_mem_flags             flags,
                  cl_buffer_create_type    buffer_create_type,
                  const void *             buffer_create_info,
                  cl_int *                 errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateSubBuffer == NULL || !fun_fake_clCreateSubBuffer)
        fun_fake_clCreateSubBuffer =(fake_clCreateSubBuffer) dlsym(so_handle, "clCreateSubBuffer");

    if(fun_fake_clCreateSubBuffer) {
        return fun_fake_clCreateSubBuffer(buffer, flags, buffer_create_type,
                                          buffer_create_info, errcode_ret);
    }
    return NULL;
}

cl_mem
clCreateImage(cl_context              context,
              cl_mem_flags            flags,
              const cl_image_format * image_format,
              const cl_image_desc *   image_desc,
              void *                  host_ptr,
              cl_int *                errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateImage == NULL || !fun_fake_clCreateImage)
        fun_fake_clCreateImage =(fake_clCreateImage) dlsym(so_handle, "clCreateImage");

    if(fun_fake_clCreateImage) {
        return fun_fake_clCreateImage(context, flags, image_format, image_desc,
                                      host_ptr, errcode_ret);
    }
    return NULL;
}

cl_int
clRetainMemObject(cl_mem memobj)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clRetainMemObject == NULL || !fun_fake_clRetainMemObject)
        fun_fake_clRetainMemObject =(fake_clRetainMemObject) dlsym(so_handle, "clRetainMemObject");

    if(fun_fake_clRetainMemObject) {
        return fun_fake_clRetainMemObject(memobj);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clReleaseMemObject(cl_mem memobj)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clReleaseMemObject == NULL || !fun_fake_clReleaseMemObject)
        fun_fake_clReleaseMemObject =(fake_clReleaseMemObject) dlsym(so_handle, "clReleaseMemObject");

    if(fun_fake_clReleaseMemObject ) {
        return fun_fake_clReleaseMemObject(memobj);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clGetSupportedImageFormats(cl_context           context,
                           cl_mem_flags         flags,
                           cl_mem_object_type   image_type,
                           cl_uint              num_entries,
                           cl_image_format *    image_formats,
                           cl_uint *            num_image_formats)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clGetSupportedImageFormats == NULL || !fun_fake_clGetSupportedImageFormats)
        fun_fake_clGetSupportedImageFormats =(fake_clGetSupportedImageFormats) dlsym(so_handle, "clGetSupportedImageFormats");
    if(fun_fake_clGetSupportedImageFormats) {
        return fun_fake_clGetSupportedImageFormats(context, flags, image_type, num_entries,
                                                   image_formats, num_image_formats);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clGetMemObjectInfo(cl_mem           memobj,
                   cl_mem_info      param_name,
                   size_t           param_value_size,
                   void *           param_value,
                   size_t *         param_value_size_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clGetMemObjectInfo == NULL || !fun_fake_clGetMemObjectInfo)
        fun_fake_clGetMemObjectInfo =(fake_clGetMemObjectInfo) dlsym(so_handle, "clGetMemObjectInfo");
    if(fun_fake_clGetMemObjectInfo) {
        return fun_fake_clGetMemObjectInfo(memobj, param_name, param_value_size,
                                           param_value, param_value_size_ret);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clGetImageInfo(cl_mem           image,
               cl_image_info    param_name,
               size_t           param_value_size,
               void *           param_value,
               size_t *         param_value_size_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clGetImageInfo == NULL || !  fun_fake_clGetImageInfo)
        fun_fake_clGetImageInfo =(fake_clGetImageInfo) dlsym(so_handle, "clGetImageInfo");

    if(fun_fake_clGetImageInfo) {
        return fun_fake_clGetImageInfo(image, param_name, param_value_size,
                                       param_value, param_value_size_ret);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clSetMemObjectDestructorCallback(  cl_mem memobj,
                                   void (*pfn_notify)( cl_mem , void* ),
                                   void * user_data )
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clSetMemObjectDestructorCallback == NULL || !fun_fake_clSetMemObjectDestructorCallback)
        fun_fake_clSetMemObjectDestructorCallback =(fake_clSetMemObjectDestructorCallback) dlsym(so_handle, "clSetMemObjectDestructorCallback");

    if(fun_fake_clSetMemObjectDestructorCallback) {
        return fun_fake_clSetMemObjectDestructorCallback(memobj, pfn_notify, user_data);
    }
    return CL_INVALID_PLATFORM;
}

cl_sampler
clCreateSampler(cl_context          context,
                cl_bool             normalized_coords,
                cl_addressing_mode  addressing_mode,
                cl_filter_mode      filter_mode,
                cl_int *            errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateSampler == NULL || !fun_fake_clCreateSampler)
        fun_fake_clCreateSampler =(fake_clCreateSampler) dlsym(so_handle, "clCreateSampler");

    if(fun_fake_clCreateSampler) {
        return fun_fake_clCreateSampler(context, normalized_coords, addressing_mode, filter_mode, errcode_ret);
    }
    return NULL;
}

cl_int
clRetainSampler(cl_sampler sampler)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clRetainSampler == NULL || !fun_fake_clRetainSampler)
        fun_fake_clRetainSampler =(fake_clRetainSampler) dlsym(so_handle, "clRetainSampler");

    if(fun_fake_clRetainSampler) {
        return fun_fake_clRetainSampler(sampler);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clReleaseSampler(cl_sampler sampler)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clReleaseSampler == NULL || !fun_fake_clReleaseSampler)
        fun_fake_clReleaseSampler =(fake_clReleaseSampler) dlsym(so_handle, "clReleaseSampler");

    if(fun_fake_clReleaseSampler) {
        return fun_fake_clReleaseSampler(sampler);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clGetSamplerInfo(cl_sampler         sampler,
                 cl_sampler_info    param_name,
                 size_t             param_value_size,
                 void *             param_value,
                 size_t *           param_value_size_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clGetSamplerInfo == NULL || !fun_fake_clGetSamplerInfo)
        fun_fake_clGetSamplerInfo =(fake_clGetSamplerInfo) dlsym(so_handle, "clGetSamplerInfo");

    if(fun_fake_clGetSamplerInfo) {
        return fun_fake_clGetSamplerInfo(sampler, param_name, param_value_size, param_value, param_value_size_ret);
    }
    return CL_INVALID_PLATFORM;
}


cl_program
clCreateProgramWithSource(cl_context        context,
                          cl_uint           count,
                          const char **     strings,
                          const size_t *    lengths,
                          cl_int *          errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateProgramWithSource == NULL || !fun_fake_clCreateProgramWithSource)
        fun_fake_clCreateProgramWithSource =(fake_clCreateProgramWithSource) dlsym(so_handle, "clCreateProgramWithSource");

    if(fun_fake_clCreateProgramWithSource) {
        return fun_fake_clCreateProgramWithSource(context, count, strings, lengths, errcode_ret);
    }
    return NULL;
}



cl_program
clCreateProgramWithBinary(cl_context                     context,
                          cl_uint                        num_devices,
                          const cl_device_id *           device_list,
                          const size_t *                 lengths,
                          const unsigned char **         binaries,
                          cl_int *                       binary_status,
                          cl_int *                       errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateProgramWithBinary == NULL || !fun_fake_clCreateProgramWithBinary)
        fun_fake_clCreateProgramWithBinary =(fake_clCreateProgramWithBinary) dlsym(so_handle, "clCreateProgramWithBinary");

    if(fun_fake_clCreateProgramWithBinary) {
        return fun_fake_clCreateProgramWithBinary(context, num_devices, device_list,
                                                  lengths, binaries, binary_status, errcode_ret);
    }
    return NULL;
}

cl_program
clCreateProgramWithBuiltInKernels(cl_context            context,
                                  cl_uint               num_devices,
                                  const cl_device_id *  device_list,
                                  const char *          kernel_names,
                                  cl_int *              errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateProgramWithBuiltInKernels == NULL || !fun_fake_clCreateProgramWithBuiltInKernels)
        fun_fake_clCreateProgramWithBuiltInKernels =(fake_clCreateProgramWithBuiltInKernels) dlsym(so_handle, "clCreateProgramWithBuiltInKernels");

    if(fun_fake_clCreateProgramWithBuiltInKernels) {
        return fun_fake_clCreateProgramWithBuiltInKernels(context, num_devices, device_list, kernel_names, errcode_ret);
    }
    return NULL;
}

cl_int
clRetainProgram(cl_program program)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clRetainProgram == NULL || !fun_fake_clRetainProgram)
        fun_fake_clRetainProgram =(fake_clRetainProgram) dlsym(so_handle, "clRetainProgram");

    if(fun_fake_clRetainProgram) {
        return fun_fake_clRetainProgram(program);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clReleaseProgram(cl_program program)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clReleaseProgram == NULL || !fun_fake_clReleaseProgram)
        fun_fake_clReleaseProgram =(fake_clReleaseProgram) dlsym(so_handle, "clReleaseProgram");
    if(fun_fake_clReleaseProgram) {
        return fun_fake_clReleaseProgram(program);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clBuildProgram(cl_program           program,
               cl_uint              num_devices,
               const cl_device_id * device_list,
               const char *         options,
               void (*pfn_notify)(cl_program , void * ),
               void *               user_data)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clBuildProgram == NULL || !fun_fake_clBuildProgram)
        fun_fake_clBuildProgram =(fake_clBuildProgram) dlsym(so_handle, "clBuildProgram");

    if(fun_fake_clBuildProgram) {
        return fun_fake_clBuildProgram(program, num_devices, device_list, options, pfn_notify, user_data);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clCompileProgram(cl_program           program,
                 cl_uint              num_devices,
                 const cl_device_id * device_list,
                 const char *         options,
                 cl_uint              num_input_headers,
                 const cl_program *   input_headers,
                 const char **        header_include_names,
                 void (*pfn_notify)(cl_program , void * ),
                 void *               user_data)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clCompileProgram == NULL || !fun_fake_clCompileProgram)
        fun_fake_clCompileProgram =(fake_clCompileProgram) dlsym(so_handle, "clCompileProgram");
    if(fun_fake_clCompileProgram) {
        return fun_fake_clCompileProgram(program, num_devices, device_list, options, num_input_headers, input_headers,
                                         header_include_names, pfn_notify, user_data);
    }
    return CL_INVALID_PLATFORM;
}

cl_program
clLinkProgram(cl_context           context,
              cl_uint              num_devices,
              const cl_device_id * device_list,
              const char *         options,
              cl_uint              num_input_programs,
              const cl_program *   input_programs,
              void (*pfn_notify)(cl_program , void * ),
              void *               user_data,
              cl_int *             errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clLinkProgram == NULL || !fun_fake_clLinkProgram)
        fun_fake_clLinkProgram =(fake_clLinkProgram) dlsym(so_handle, "clLinkProgram");

    if(fun_fake_clLinkProgram) {
        return fun_fake_clLinkProgram(context, num_devices, device_list, options, num_input_programs,
                                      input_programs, pfn_notify, user_data, errcode_ret);
    }
    return NULL;
}


cl_int
clUnloadPlatformCompiler(cl_platform_id platform)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clUnloadPlatformCompiler == NULL || !fun_fake_clUnloadPlatformCompiler)
        fun_fake_clUnloadPlatformCompiler =(fake_clUnloadPlatformCompiler) dlsym(so_handle, "clUnloadPlatformCompiler");

    if(fun_fake_clUnloadPlatformCompiler) {
        return fun_fake_clUnloadPlatformCompiler(platform);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clGetProgramInfo(cl_program         program,
                 cl_program_info    param_name,
                 size_t             param_value_size,
                 void *             param_value,
                 size_t *           param_value_size_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clGetProgramInfo == NULL || !fun_fake_clGetProgramInfo)
        fun_fake_clGetProgramInfo =(fake_clGetProgramInfo) dlsym(so_handle, "clGetProgramInfo");
    if(fun_fake_clGetProgramInfo) {
        return fun_fake_clGetProgramInfo(program, param_name, param_value_size,
                                         param_value, param_value_size_ret);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clGetProgramBuildInfo(cl_program            program,
                      cl_device_id          device,
                      cl_program_build_info param_name,
                      size_t                param_value_size,
                      void *                param_value,
                      size_t *              param_value_size_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clGetProgramBuildInfo == NULL || !fun_fake_clGetProgramBuildInfo)
        fun_fake_clGetProgramBuildInfo=(fake_clGetProgramBuildInfo) dlsym(so_handle, "clGetProgramBuildInfo");

    if(fun_fake_clGetProgramBuildInfo) {
        return fun_fake_clGetProgramBuildInfo(program, device, param_name, param_value_size,
                                              param_value, param_value_size_ret);
    }
    return CL_INVALID_PLATFORM;
}


cl_kernel
clCreateKernel(cl_program      program,
               const char *    kernel_name,
               cl_int *        errcode_ret)
{
    if(!so_handle)
        return NULL;

    if(fun_fake_clCreateKernel == NULL || !fun_fake_clCreateKernel)
        fun_fake_clCreateKernel =(fake_clCreateKernel) dlsym(so_handle, "clCreateKernel");
    if(fun_fake_clCreateKernel) {
        return fun_fake_clCreateKernel(program, kernel_name, errcode_ret);
    }
    return NULL;
}

cl_int
clCreateKernelsInProgram(cl_program     program,
                         cl_uint        num_kernels,
                         cl_kernel *    kernels,
                         cl_uint *      num_kernels_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clCreateKernelsInProgram == NULL || !fun_fake_clCreateKernelsInProgram)
        fun_fake_clCreateKernelsInProgram=(fake_clCreateKernelsInProgram) dlsym(so_handle, "clCreateKernelsInProgram");
    if(fun_fake_clCreateKernelsInProgram) {
        return fun_fake_clCreateKernelsInProgram(program, num_kernels, kernels, num_kernels_ret);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clRetainKernel(cl_kernel kernel)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clRetainKernel == NULL || !fun_fake_clRetainKernel)
        fun_fake_clRetainKernel =(fake_clRetainKernel) dlsym(so_handle, "clRetainKernel");
    if(fun_fake_clRetainKernel) {
        return fun_fake_clRetainKernel(kernel);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clReleaseKernel(cl_kernel kernel)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clReleaseKernel == NULL || !fun_fake_clReleaseKernel)
        fun_fake_clReleaseKernel =(fake_clReleaseKernel) dlsym(so_handle, "clReleaseKernel");
    if(fun_fake_clReleaseKernel) {
        return fun_fake_clReleaseKernel(kernel);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clSetKernelArg(cl_kernel    kernel,
               cl_uint      arg_index,
               size_t       arg_size,
               const void * arg_value)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clSetKernelArg == NULL || !fun_fake_clSetKernelArg)
        fun_fake_clSetKernelArg =(fake_clSetKernelArg) dlsym(so_handle, "clSetKernelArg");

    if(fun_fake_clSetKernelArg) {
        return fun_fake_clSetKernelArg(kernel, arg_index, arg_size, arg_value);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clGetKernelInfo(cl_kernel       kernel,
                cl_kernel_info  param_name,
                size_t          param_value_size,
                void *          param_value,
                size_t *        param_value_size_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clGetKernelInfo == NULL || !fun_fake_clGetKernelInfo)
        fun_fake_clGetKernelInfo=(fake_clGetKernelInfo) dlsym(so_handle, "clGetKernelInfo");
    if(fun_fake_clGetKernelInfo) {
        return fun_fake_clGetKernelInfo(kernel, param_name, param_value_size, param_value, param_value_size_ret);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clGetKernelArgInfo(cl_kernel       kernel,
                   cl_uint         arg_indx,
                   cl_kernel_arg_info  param_name,
                   size_t          param_value_size,
                   void *          param_value,
                   size_t *        param_value_size_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clGetKernelArgInfo == NULL || !fun_fake_clGetKernelArgInfo)
        fun_fake_clGetKernelArgInfo=(fake_clGetKernelArgInfo) dlsym(so_handle, "clGetKernelArgInfo");

    if(fun_fake_clGetKernelArgInfo) {
        return fun_fake_clGetKernelArgInfo(kernel, arg_indx, param_name, param_value_size,
                                           param_value, param_value_size_ret);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clGetKernelWorkGroupInfo(cl_kernel                  kernel,
                         cl_device_id               device,
                         cl_kernel_work_group_info  param_name,
                         size_t                     param_value_size,
                         void *                     param_value,
                         size_t *                   param_value_size_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clGetKernelWorkGroupInfo == NULL || !fun_fake_clGetKernelWorkGroupInfo)
        fun_fake_clGetKernelWorkGroupInfo =(fake_clGetKernelWorkGroupInfo) dlsym(so_handle, "clGetKernelWorkGroupInfo");

    if(fun_fake_clGetKernelWorkGroupInfo) {
        return fun_fake_clGetKernelWorkGroupInfo(kernel, device, param_name, param_value_size, param_value, param_value_size_ret);
    }
    return CL_INVALID_PLATFORM;
}


cl_int
clWaitForEvents(cl_uint             num_events,
                const cl_event *    event_list)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clWaitForEvents == NULL || !fun_fake_clWaitForEvents)
        fun_fake_clWaitForEvents =(fake_clWaitForEvents) dlsym(so_handle, "clWaitForEvents");

    if(fun_fake_clWaitForEvents) {
        return fun_fake_clWaitForEvents(num_events, event_list);
    }
    return CL_INVALID_PLATFORM;
}


cl_int
clGetEventInfo(cl_event         event,
               cl_event_info    param_name,
               size_t           param_value_size,
               void *           param_value,
               size_t *         param_value_size_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clGetEventInfo == NULL || !fun_fake_clGetEventInfo)
        fun_fake_clGetEventInfo =(fake_clGetEventInfo) dlsym(so_handle, "clGetEventInfo");

    if(fun_fake_clGetEventInfo) {
        return fun_fake_clGetEventInfo(event, param_name, param_value_size, param_value, param_value_size_ret);
    }
    return CL_INVALID_PLATFORM;
}

cl_event
clCreateUserEvent(cl_context    context,
                  cl_int *      errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateUserEvent == NULL || !fun_fake_clCreateUserEvent)
        fun_fake_clCreateUserEvent =(fake_clCreateUserEvent) dlsym(so_handle, "clCreateUserEvent");

    if(fun_fake_clCreateUserEvent) {
        return fun_fake_clCreateUserEvent(context, errcode_ret);
    }
    return NULL;
}

cl_int
clRetainEvent(cl_event event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clRetainEvent == NULL || !fun_fake_clRetainEvent)
        fun_fake_clRetainEvent =(fake_clRetainEvent) dlsym(so_handle, "clRetainEvent");

    if(fun_fake_clRetainEvent) {
        return fun_fake_clRetainEvent(event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clReleaseEvent(cl_event event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clReleaseEvent == NULL || !fun_fake_clReleaseEvent)
        fun_fake_clReleaseEvent =(fake_clReleaseEvent) dlsym(so_handle, "clReleaseEvent");

    if(fun_fake_clReleaseEvent) {
        return fun_fake_clReleaseEvent(event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clSetUserEventStatus(cl_event   event,
                     cl_int     execution_status)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clSetUserEventStatus == NULL || !fun_fake_clSetUserEventStatus)
        fun_fake_clSetUserEventStatus=(fake_clSetUserEventStatus) dlsym(so_handle, "clSetUserEventStatus");

    if(fun_fake_clSetUserEventStatus) {
        return fun_fake_clSetUserEventStatus(event, execution_status);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clSetEventCallback( cl_event    event,
                    cl_int      command_exec_callback_type,
                    void (*pfn_notify)(cl_event, cl_int, void *),
                    void *      user_data)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clSetEventCallback == NULL || !fun_fake_clSetEventCallback)
        fun_fake_clSetEventCallback =(fake_clSetEventCallback) dlsym(so_handle, "clSetEventCallback");
    if(fun_fake_clSetEventCallback) {
        return fun_fake_clSetEventCallback(event, command_exec_callback_type, pfn_notify, user_data);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clGetEventProfilingInfo(cl_event            event,
                        cl_profiling_info   param_name,
                        size_t              param_value_size,
                        void *              param_value,
                        size_t *            param_value_size_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clGetEventProfilingInfo == NULL || !fun_fake_clGetEventProfilingInfo)
        fun_fake_clGetEventProfilingInfo =(fake_clGetEventProfilingInfo) dlsym(so_handle, "clGetEventProfilingInfo");
    if(fun_fake_clGetEventProfilingInfo) {
        return fun_fake_clGetEventProfilingInfo(event, param_name, param_value_size, param_value, param_value_size_ret);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clFlush(cl_command_queue command_queue)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clFlush == NULL || !fun_fake_clFlush)
        fun_fake_clFlush =(fake_clFlush) dlsym(so_handle, "clFlush");
    if(fun_fake_clFlush) {
        return fun_fake_clFlush(command_queue);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clFinish(cl_command_queue command_queue)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clFinish == NULL || !fun_fake_clFinish)
        fun_fake_clFinish =(fake_clFinish) dlsym(so_handle, "clFinish");

    if(fun_fake_clFinish) {
        return fun_fake_clFinish(command_queue);
    }
    return CL_INVALID_PLATFORM;
}


cl_int
clEnqueueReadBuffer(cl_command_queue    command_queue,
                    cl_mem              buffer,
                    cl_bool             blocking_read,
                    size_t              offset,
                    size_t              size,
                    void *              ptr,
                    cl_uint             num_events_in_wait_list,
                    const cl_event *    event_wait_list,
                    cl_event *          event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clEnqueueReadBuffer == NULL || !fun_fake_clEnqueueReadBuffer)
        fun_fake_clEnqueueReadBuffer =(fake_clEnqueueReadBuffer) dlsym(so_handle, "clEnqueueReadBuffer");
    if(fun_fake_clEnqueueReadBuffer) {
        return fun_fake_clEnqueueReadBuffer(command_queue, buffer, blocking_read, offset, size, ptr,
                                            num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueReadBufferRect(cl_command_queue    command_queue,
                        cl_mem              buffer,
                        cl_bool             blocking_read,
                        const size_t *      buffer_offset,
                        const size_t *      host_offset,
                        const size_t *      region,
                        size_t              buffer_row_pitch,
                        size_t              buffer_slice_pitch,
                        size_t              host_row_pitch,
                        size_t              host_slice_pitch,
                        void *              ptr,
                        cl_uint             num_events_in_wait_list,
                        const cl_event *    event_wait_list,
                        cl_event *          event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueReadBufferRect == NULL || !fun_fake_clEnqueueReadBufferRect)
        fun_fake_clEnqueueReadBufferRect =(fake_clEnqueueReadBufferRect) dlsym(so_handle, "clEnqueueReadBufferRect");

    if(fun_fake_clEnqueueReadBufferRect) {
        return fun_fake_clEnqueueReadBufferRect(command_queue, buffer, blocking_read, buffer_offset, host_offset, region,
                                                buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr,
                                                num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueWriteBuffer(cl_command_queue   command_queue,
                     cl_mem             buffer,
                     cl_bool            blocking_write,
                     size_t             offset,
                     size_t             size,
                     const void *       ptr,
                     cl_uint            num_events_in_wait_list,
                     const cl_event *   event_wait_list,
                     cl_event *         event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueWriteBuffer == NULL || !fun_fake_clEnqueueWriteBuffer)
        fun_fake_clEnqueueWriteBuffer =(fake_clEnqueueWriteBuffer) dlsym(so_handle, "clEnqueueWriteBuffer");

    if(fun_fake_clEnqueueWriteBuffer) {
        return fun_fake_clEnqueueWriteBuffer(command_queue, buffer, blocking_write, offset, size, ptr,
                                             num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}


cl_int
clEnqueueWriteBufferRect(cl_command_queue    command_queue,
                         cl_mem              buffer,
                         cl_bool             blocking_write,
                         const size_t *      buffer_offset,
                         const size_t *      host_offset,
                         const size_t *      region,
                         size_t              buffer_row_pitch,
                         size_t              buffer_slice_pitch,
                         size_t              host_row_pitch,
                         size_t              host_slice_pitch,
                         const void *        ptr,
                         cl_uint             num_events_in_wait_list,
                         const cl_event *    event_wait_list,
                         cl_event *          event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueWriteBufferRect == NULL || !fun_fake_clEnqueueWriteBufferRect)
        fun_fake_clEnqueueWriteBufferRect =(fake_clEnqueueWriteBufferRect) dlsym(so_handle, "clEnqueueWriteBufferRect");

    if(fun_fake_clEnqueueWriteBufferRect) {
        return fun_fake_clEnqueueWriteBufferRect(command_queue, buffer, blocking_write, buffer_offset, host_offset, region,
                                                 buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch,
                                                 ptr, num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}


cl_int
clEnqueueFillBuffer(cl_command_queue   command_queue,
                    cl_mem             buffer,
                    const void *       pattern,
                    size_t             pattern_size,
                    size_t             offset,
                    size_t             size,
                    cl_uint            num_events_in_wait_list,
                    const cl_event *   event_wait_list,
                    cl_event *         event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueFillBuffer == NULL || !fun_fake_clEnqueueFillBuffer)
        fun_fake_clEnqueueFillBuffer =(fake_clEnqueueFillBuffer) dlsym(so_handle, "clEnqueueFillBuffer");

    if(fun_fake_clEnqueueFillBuffer) {
        return fun_fake_clEnqueueFillBuffer(command_queue, buffer, pattern, pattern_size, offset, size,
                                            num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueCopyBuffer(cl_command_queue    command_queue,
                    cl_mem              src_buffer,
                    cl_mem              dst_buffer,
                    size_t              src_offset,
                    size_t              dst_offset,
                    size_t              size,
                    cl_uint             num_events_in_wait_list,
                    const cl_event *    event_wait_list,
                    cl_event *          event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueCopyBuffer == NULL || !fun_fake_clEnqueueCopyBuffer)
        fun_fake_clEnqueueCopyBuffer =(fake_clEnqueueCopyBuffer) dlsym(so_handle, "clEnqueueCopyBuffer");

    if(fun_fake_clEnqueueCopyBuffer) {
        return fun_fake_clEnqueueCopyBuffer(command_queue, src_buffer, dst_buffer, src_offset, dst_offset, size,
                                            num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}



cl_int
clEnqueueCopyBufferRect(cl_command_queue    command_queue,
                        cl_mem              src_buffer,
                        cl_mem              dst_buffer,
                        const size_t *      src_origin,
                        const size_t *      dst_origin,
                        const size_t *      region,
                        size_t              src_row_pitch,
                        size_t              src_slice_pitch,
                        size_t              dst_row_pitch,
                        size_t              dst_slice_pitch,
                        cl_uint             num_events_in_wait_list,
                        const cl_event *    event_wait_list,
                        cl_event *          event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueCopyBufferRect == NULL || !fun_fake_clEnqueueCopyBufferRect)
        fun_fake_clEnqueueCopyBufferRect =(fake_clEnqueueCopyBufferRect) dlsym(so_handle, "clEnqueueCopyBufferRect");

    if(fun_fake_clEnqueueCopyBufferRect) {
        return fun_fake_clEnqueueCopyBufferRect(command_queue, src_buffer, dst_buffer, src_origin, dst_origin, region, src_row_pitch,
                                                src_slice_pitch, dst_row_pitch, dst_slice_pitch, num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueReadImage(cl_command_queue     command_queue,
                   cl_mem               image,
                   cl_bool              blocking_read,
                   const size_t *       origin,
                   const size_t *       region,
                   size_t               row_pitch,
                   size_t               slice_pitch,
                   void *               ptr,
                   cl_uint              num_events_in_wait_list,
                   const cl_event *     event_wait_list,
                   cl_event *           event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueReadImage == NULL || !fun_fake_clEnqueueReadImage)
        fun_fake_clEnqueueReadImage =(fake_clEnqueueReadImage) dlsym(so_handle, "clEnqueueReadImage");

    if(fun_fake_clEnqueueReadImage) {
        return fun_fake_clEnqueueReadImage(command_queue, image, blocking_read, origin, region, row_pitch, slice_pitch,
                                           ptr, num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueWriteImage(cl_command_queue    command_queue,
                    cl_mem              image,
                    cl_bool             blocking_write,
                    const size_t *      origin,
                    const size_t *      region,
                    size_t              input_row_pitch,
                    size_t              input_slice_pitch,
                    const void *        ptr,
                    cl_uint             num_events_in_wait_list,
                    const cl_event *    event_wait_list,
                    cl_event *          event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueWriteImage == NULL || !fun_fake_clEnqueueWriteImage)
        fun_fake_clEnqueueWriteImage =(fake_clEnqueueWriteImage) dlsym(so_handle, "clEnqueueWriteImage");

    if(fun_fake_clEnqueueWriteImage) {
        return fun_fake_clEnqueueWriteImage(command_queue, image, blocking_write, origin, region, input_row_pitch, input_slice_pitch, ptr,
                                            num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}


cl_int
clEnqueueFillImage(cl_command_queue   command_queue,
                   cl_mem             image,
                   const void *       fill_color,
                   const size_t *     origin,
                   const size_t *     region,
                   cl_uint            num_events_in_wait_list,
                   const cl_event *   event_wait_list,
                   cl_event *         event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueFillImage == NULL || !fun_fake_clEnqueueFillImage)
        fun_fake_clEnqueueFillImage =(fake_clEnqueueFillImage) dlsym(so_handle, "clEnqueueFillImage");

    if(fun_fake_clEnqueueFillImage) {
        return fun_fake_clEnqueueFillImage(command_queue, image, fill_color, origin, region, num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueCopyImage(cl_command_queue     command_queue,
                   cl_mem               src_image,
                   cl_mem               dst_image,
                   const size_t *       src_origin,
                   const size_t *       dst_origin,
                   const size_t *       region,
                   cl_uint              num_events_in_wait_list,
                   const cl_event *     event_wait_list,
                   cl_event *           event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;

    if(fun_fake_clEnqueueCopyImage == NULL || !fun_fake_clEnqueueCopyImage)
        fun_fake_clEnqueueCopyImage =(fake_clEnqueueCopyImage) dlsym(so_handle, "clEnqueueCopyImage");
    if(fun_fake_clEnqueueCopyImage) {
        return fun_fake_clEnqueueCopyImage(command_queue, src_image, dst_image, src_origin, dst_origin, region,
                                           num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueCopyImageToBuffer(cl_command_queue command_queue,
                           cl_mem           src_image,
                           cl_mem           dst_buffer,
                           const size_t *   src_origin,
                           const size_t *   region,
                           size_t           dst_offset,
                           cl_uint          num_events_in_wait_list,
                           const cl_event * event_wait_list,
                           cl_event *       event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueCopyImageToBuffer == NULL || !fun_fake_clEnqueueCopyImageToBuffer)
        fun_fake_clEnqueueCopyImageToBuffer =(fake_clEnqueueCopyImageToBuffer) dlsym(so_handle, "clEnqueueCopyImageToBuffer");

    if(fun_fake_clEnqueueCopyImageToBuffer) {
        return fun_fake_clEnqueueCopyImageToBuffer(command_queue, src_image, dst_buffer, src_origin, region, dst_offset,
                                                   num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}


cl_int
clEnqueueCopyBufferToImage(cl_command_queue command_queue,
                           cl_mem           src_buffer,
                           cl_mem           dst_image,
                           size_t           src_offset,
                           const size_t *   dst_origin,
                           const size_t *   region,
                           cl_uint          num_events_in_wait_list,
                           const cl_event * event_wait_list,
                           cl_event *       event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueCopyBufferToImage == NULL || !fun_fake_clEnqueueCopyBufferToImage)
        fun_fake_clEnqueueCopyBufferToImage=(fake_clEnqueueCopyBufferToImage) dlsym(so_handle, "clEnqueueCopyBufferToImage");

    if(fun_fake_clEnqueueCopyBufferToImage) {
        return fun_fake_clEnqueueCopyBufferToImage(command_queue, src_buffer, dst_image, src_offset, dst_origin, region,
                                                   num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}

void *
clEnqueueMapBuffer(cl_command_queue command_queue,
                   cl_mem           buffer,
                   cl_bool          blocking_map,
                   cl_map_flags     map_flags,
                   size_t           offset,
                   size_t           size,
                   cl_uint          num_events_in_wait_list,
                   const cl_event * event_wait_list,
                   cl_event *       event,
                   cl_int *         errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clEnqueueMapBuffer == NULL || !fun_fake_clEnqueueMapBuffer)
        fun_fake_clEnqueueMapBuffer=(fake_clEnqueueMapBuffer) dlsym(so_handle, "clEnqueueMapBuffer");

    if(fun_fake_clEnqueueMapBuffer) {
        return fun_fake_clEnqueueMapBuffer(command_queue, buffer, blocking_map, map_flags, offset, size,
                                           num_events_in_wait_list, event_wait_list, event, errcode_ret);
    }
    return NULL;
}

void *
clEnqueueMapImage(cl_command_queue  command_queue,
                  cl_mem            image,
                  cl_bool           blocking_map,
                  cl_map_flags      map_flags,
                  const size_t *    origin,
                  const size_t *    region,
                  size_t *          image_row_pitch,
                  size_t *          image_slice_pitch,
                  cl_uint           num_events_in_wait_list,
                  const cl_event *  event_wait_list,
                  cl_event *        event,
                  cl_int *          errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clEnqueueMapImage == NULL || !fun_fake_clEnqueueMapImage)
        fun_fake_clEnqueueMapImage =(fake_clEnqueueMapImage) dlsym(so_handle, "clEnqueueMapImage");

    if(fun_fake_clEnqueueMapImage) {
        return fun_fake_clEnqueueMapImage(command_queue, image, blocking_map, map_flags, origin, region, image_row_pitch,
                                          image_slice_pitch, num_events_in_wait_list, event_wait_list, event, errcode_ret);
    }
    return NULL;
}

cl_int
clEnqueueUnmapMemObject(cl_command_queue command_queue,
                        cl_mem           memobj,
                        void *           mapped_ptr,
                        cl_uint          num_events_in_wait_list,
                        const cl_event *  event_wait_list,
                        cl_event *        event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueUnmapMemObject == NULL || !fun_fake_clEnqueueUnmapMemObject)
        fun_fake_clEnqueueUnmapMemObject =(fake_clEnqueueUnmapMemObject) dlsym(so_handle, "clEnqueueUnmapMemObject");
    if(fun_fake_clEnqueueUnmapMemObject) {
        return fun_fake_clEnqueueUnmapMemObject(command_queue, memobj, mapped_ptr, num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueMigrateMemObjects(cl_command_queue       command_queue,
                           cl_uint                num_mem_objects,
                           const cl_mem *         mem_objects,
                           cl_mem_migration_flags flags,
                           cl_uint                num_events_in_wait_list,
                           const cl_event *       event_wait_list,
                           cl_event *             event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueMigrateMemObjects == NULL || !fun_fake_clEnqueueMigrateMemObjects)
        fun_fake_clEnqueueMigrateMemObjects =(fake_clEnqueueMigrateMemObjects) dlsym(so_handle, "clEnqueueMigrateMemObjects");

    if(fun_fake_clEnqueueMigrateMemObjects) {
        return fun_fake_clEnqueueMigrateMemObjects(command_queue, num_mem_objects, mem_objects, flags, num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueNDRangeKernel(cl_command_queue command_queue,
                       cl_kernel        kernel,
                       cl_uint          work_dim,
                       const size_t *   global_work_offset,
                       const size_t *   global_work_size,
                       const size_t *   local_work_size,
                       cl_uint          num_events_in_wait_list,
                       const cl_event * event_wait_list,
                       cl_event *       event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueNDRangeKernel == NULL || !fun_fake_clEnqueueNDRangeKernel)
        fun_fake_clEnqueueNDRangeKernel=(fake_clEnqueueNDRangeKernel) dlsym(so_handle, "clEnqueueNDRangeKernel");

    if(fun_fake_clEnqueueNDRangeKernel) {
        return fun_fake_clEnqueueNDRangeKernel(command_queue, kernel, work_dim, global_work_offset, global_work_size, local_work_size,
                                               num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueTask(cl_command_queue  command_queue,
              cl_kernel         kernel,
              cl_uint           num_events_in_wait_list,
              const cl_event *  event_wait_list,
              cl_event *        event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueTask == NULL || !fun_fake_clEnqueueTask)
        fun_fake_clEnqueueTask =(fake_clEnqueueTask) dlsym(so_handle, "clEnqueueTask");

    if(fun_fake_clEnqueueTask) {
        return fun_fake_clEnqueueTask(command_queue, kernel, num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueNativeKernel(cl_command_queue  command_queue,
                      void (*user_fun_)(void *),
                      void *            args,
                      size_t            cb_args,
                      cl_uint           num_mem_objects,
                      const cl_mem *    mem_list,
                      const void **     args_mem_loc,
                      cl_uint           num_events_in_wait_list,
                      const cl_event *  event_wait_list,
                      cl_event *        event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueNativeKernel == NULL || !fun_fake_clEnqueueNativeKernel)
        fun_fake_clEnqueueNativeKernel =(fake_clEnqueueNativeKernel) dlsym(so_handle, "clEnqueueNativeKernel");

    if(fun_fake_clEnqueueNativeKernel) {
        return fun_fake_clEnqueueNativeKernel(command_queue, user_fun_, args, cb_args, num_mem_objects, mem_list,
                                              args_mem_loc, num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueMarkerWithWaitList(cl_command_queue command_queue,
                            cl_uint           num_events_in_wait_list,
                            const cl_event *  event_wait_list,
                            cl_event *        event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueMarkerWithWaitList == NULL || !fun_fake_clEnqueueMarkerWithWaitList)
        fun_fake_clEnqueueMarkerWithWaitList =(fake_clEnqueueMarkerWithWaitList) dlsym(so_handle, "clEnqueueMarkerWithWaitList");

    if(fun_fake_clEnqueueMarkerWithWaitList) {
        return fun_fake_clEnqueueMarkerWithWaitList(command_queue, num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueBarrierWithWaitList(cl_command_queue command_queue,
                             cl_uint           num_events_in_wait_list,
                             const cl_event *  event_wait_list,
                             cl_event *        event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueBarrierWithWaitList == NULL || !fun_fake_clEnqueueBarrierWithWaitList)
        fun_fake_clEnqueueBarrierWithWaitList =(fake_clEnqueueBarrierWithWaitList) dlsym(so_handle, "clEnqueueBarrierWithWaitList");

    if(fun_fake_clEnqueueBarrierWithWaitList) {
        return fun_fake_clEnqueueBarrierWithWaitList(command_queue, num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}


void *
clGetExtensionFunctionAddressForPlatform(cl_platform_id platform,
                                         const char *   fun__name)
{
    if(!so_handle)
        return NULL;
    if (fun_fake_clGetExtensionFunctionAddressForPlatform == NULL)
        fun_fake_clGetExtensionFunctionAddressForPlatform=(fake_clGetExtensionFunctionAddressForPlatform) dlsym(so_handle, " clGetExtensionFunctionAddressForPlatform");

    if(fun_fake_clGetExtensionFunctionAddressForPlatform) {
        return fun_fake_clGetExtensionFunctionAddressForPlatform(platform, fun__name);
    }
    return NULL;
}


cl_mem
clCreateImage2D(cl_context              context,
                cl_mem_flags            flags,
                const cl_image_format * image_format,
                size_t                  image_width,
                size_t                  image_height,
                size_t                  image_row_pitch,
                void *                  host_ptr,
                cl_int *                errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateImage2D == NULL || !fun_fake_clCreateImage2D)
        fun_fake_clCreateImage2D =(fake_clCreateImage2D) dlsym(so_handle, "clCreateImage2D");

    if(fun_fake_clCreateImage2D) {
        return fun_fake_clCreateImage2D(context, flags, image_format, image_width, image_height,
                                        image_row_pitch, host_ptr, errcode_ret);
    }
    return NULL;
}

cl_mem
clCreateImage3D(cl_context              context,
                cl_mem_flags            flags,
                const cl_image_format * image_format,
                size_t                  image_width,
                size_t                  image_height,
                size_t                  image_depth,
                size_t                  image_row_pitch,
                size_t                  image_slice_pitch,
                void *                  host_ptr,
                cl_int *                errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateImage3D == NULL || !fun_fake_clCreateImage3D)
        fun_fake_clCreateImage3D=(fake_clCreateImage3D) dlsym(so_handle, "clCreateImage3D");

    if(fun_fake_clCreateImage3D) {
        return fun_fake_clCreateImage3D(context, flags, image_format, image_width, image_height, image_depth,
                                        image_row_pitch, image_slice_pitch, host_ptr, errcode_ret);
    }
    return NULL;
}

cl_int
clEnqueueMarker(cl_command_queue    command_queue,
                cl_event *          event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueMarker == NULL || !fun_fake_clEnqueueMarker)
        fun_fake_clEnqueueMarker =(fake_clEnqueueMarker) dlsym(so_handle, "clEnqueueMarker");

    if(fun_fake_clEnqueueMarker) {
        return fun_fake_clEnqueueMarker(command_queue, event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueWaitForEvents(cl_command_queue command_queue,
                       cl_uint          num_events,
                       const cl_event * event_list)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueWaitForEvents == NULL || !fun_fake_clEnqueueWaitForEvents)
        fun_fake_clEnqueueWaitForEvents =(fake_clEnqueueWaitForEvents) dlsym(so_handle, "clEnqueueWaitForEvents");

    if(fun_fake_clEnqueueWaitForEvents) {
        return fun_fake_clEnqueueWaitForEvents(command_queue, num_events, event_list);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueBarrier(cl_command_queue command_queue)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueBarrier == NULL || !fun_fake_clEnqueueBarrier)
        fun_fake_clEnqueueBarrier =(fake_clEnqueueBarrier) dlsym(so_handle, "clEnqueueBarrier");

    if(fun_fake_clEnqueueBarrier) {
        return fun_fake_clEnqueueBarrier(command_queue);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clUnloadCompiler(void)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clUnloadCompiler == NULL || !fun_fake_clUnloadCompiler)
        fun_fake_clUnloadCompiler=(fake_clUnloadCompiler) dlsym(so_handle, "clUnloadCompiler");

    if(fun_fake_clUnloadCompiler) {
        return fun_fake_clUnloadCompiler();
    }
    return CL_INVALID_PLATFORM;
}

void *
clGetExtensionFunctionAddress(const char * fun__name)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clGetExtensionFunctionAddress == NULL || !fun_fake_clGetExtensionFunctionAddress)
        fun_fake_clGetExtensionFunctionAddress =(fake_clGetExtensionFunctionAddress) dlsym(so_handle, " clGetExtensionFunctionAddress");

    if(fun_fake_clGetExtensionFunctionAddress) {
        return fun_fake_clGetExtensionFunctionAddress(fun__name);
    }
    return NULL;
}


cl_mem
clCreateFromGLBuffer(cl_context     context,
                     cl_mem_flags   flags,
                     cl_GLuint      bufobj,
                     int *          errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateFromGLBuffer == NULL || !fun_fake_clCreateFromGLBuffer)
        fun_fake_clCreateFromGLBuffer =(fake_clCreateFromGLBuffer) dlsym(so_handle, "clCreateFromGLBuffer");

    if(fun_fake_clCreateFromGLBuffer) {
        return fun_fake_clCreateFromGLBuffer(context, flags, bufobj, errcode_ret);
    }
    return NULL;
}

cl_mem
clCreateFromGLTexture(cl_context      context,
                      cl_mem_flags    flags,
                      cl_GLenum       target,
                      cl_GLint        miplevel,
                      cl_GLuint       texture,
                      cl_int *        errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateFromGLTexture == NULL || !fun_fake_clCreateFromGLTexture)
        fun_fake_clCreateFromGLTexture =(fake_clCreateFromGLTexture) dlsym(so_handle, "clCreateFromGLTexture");

    if(fun_fake_clCreateFromGLTexture) {
        return fun_fake_clCreateFromGLTexture(context, flags, target, miplevel, texture, errcode_ret);
    }
    return NULL;
}

cl_mem
clCreateFromGLRenderbuffer(cl_context   context,
                           cl_mem_flags flags,
                           cl_GLuint    renderbuffer,
                           cl_int *     errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateFromGLRenderbuffer == NULL || !fun_fake_clCreateFromGLRenderbuffer)
        fun_fake_clCreateFromGLRenderbuffer=(fake_clCreateFromGLRenderbuffer) dlsym(so_handle, "clCreateFromGLRenderbuffer");

    if(fun_fake_clCreateFromGLRenderbuffer) {
        return fun_fake_clCreateFromGLRenderbuffer(context, flags, renderbuffer, errcode_ret);
    }
    return NULL;
}

cl_int
clGetGLObjectInfo(cl_mem                memobj,
                  cl_gl_object_type *   gl_object_type,
                  cl_GLuint *           gl_object_name)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clGetGLObjectInfo == NULL || !fun_fake_clGetGLObjectInfo)
        fun_fake_clGetGLObjectInfo =(fake_clGetGLObjectInfo) dlsym(so_handle, "clGetGLObjectInfo");

    if(fun_fake_clGetGLObjectInfo) {
        return fun_fake_clGetGLObjectInfo(memobj, gl_object_type, gl_object_name);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clGetGLTextureInfo(cl_mem               memobj,
                   cl_gl_texture_info   param_name,
                   size_t               param_value_size,
                   void *               param_value,
                   size_t *             param_value_size_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clGetGLTextureInfo == NULL || !fun_fake_clGetGLTextureInfo)
        fun_fake_clGetGLTextureInfo =(fake_clGetGLTextureInfo) dlsym(so_handle, "clGetGLTextureInfo");

    if(fun_fake_clGetGLTextureInfo) {
        return fun_fake_clGetGLTextureInfo(memobj, param_name, param_value_size, param_value, param_value_size_ret);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueAcquireGLObjects(cl_command_queue      command_queue,
                          cl_uint               num_objects,
                          const cl_mem *        mem_objects,
                          cl_uint               num_events_in_wait_list,
                          const cl_event *      event_wait_list,
                          cl_event *            event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueAcquireGLObjects == NULL || !fun_fake_clEnqueueAcquireGLObjects)
        fun_fake_clEnqueueAcquireGLObjects =(fake_clEnqueueAcquireGLObjects) dlsym(so_handle, "clEnqueueAcquireGLObjects");

    if(fun_fake_clEnqueueAcquireGLObjects) {
        return fun_fake_clEnqueueAcquireGLObjects(command_queue, num_objects, mem_objects, num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}

cl_int
clEnqueueReleaseGLObjects(cl_command_queue      command_queue,
                          cl_uint               num_objects,
                          const cl_mem *        mem_objects,
                          cl_uint               num_events_in_wait_list,
                          const cl_event *      event_wait_list,
                          cl_event *            event)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clEnqueueReleaseGLObjects == NULL || !fun_fake_clEnqueueReleaseGLObjects)
        fun_fake_clEnqueueReleaseGLObjects =(fake_clEnqueueReleaseGLObjects) dlsym(so_handle, "clEnqueueReleaseGLObjects");

    if(fun_fake_clEnqueueReleaseGLObjects) {
        return fun_fake_clEnqueueReleaseGLObjects(command_queue, num_objects, mem_objects, num_events_in_wait_list, event_wait_list, event);
    }
    return CL_INVALID_PLATFORM;
}


cl_mem
clCreateFromGLTexture2D(cl_context      context,
                        cl_mem_flags    flags,
                        cl_GLenum       target,
                        cl_GLint        miplevel,
                        cl_GLuint       texture,
                        cl_int *        errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateFromGLTexture2D == NULL || !fun_fake_clCreateFromGLTexture2D)
        fun_fake_clCreateFromGLTexture2D=(fake_clCreateFromGLTexture2D) dlsym(so_handle, "clCreateFromGLTexture2D");

    if(fun_fake_clCreateFromGLTexture2D) {
        return fun_fake_clCreateFromGLTexture2D(context, flags, target, miplevel, texture, errcode_ret);
    }
    return NULL;
}

cl_mem
clCreateFromGLTexture3D(cl_context      context,
                        cl_mem_flags    flags,
                        cl_GLenum       target,
                        cl_GLint        miplevel,
                        cl_GLuint       texture,
                        cl_int *        errcode_ret)
{
    if(!so_handle)
        return NULL;
    if(fun_fake_clCreateFromGLTexture3D == NULL || !fun_fake_clCreateFromGLTexture3D)
        fun_fake_clCreateFromGLTexture3D =(fake_clCreateFromGLTexture3D) dlsym(so_handle, "clCreateFromGLTexture3D");

    if(fun_fake_clCreateFromGLTexture3D) {
        return fun_fake_clCreateFromGLTexture3D(context, flags, target, miplevel, texture, errcode_ret);
    }
    return NULL;
}

cl_int
clGetGLContextInfoKHR(const cl_context_properties * properties,
                      cl_gl_context_info            param_name,
                      size_t                        param_value_size,
                      void *                        param_value,
                      size_t *                      param_value_size_ret)
{
    if(!so_handle)
        return CL_INVALID_PLATFORM;
    if(fun_fake_clGetGLContextInfoKHR == NULL || !fun_fake_clGetGLContextInfoKHR)
        fun_fake_clGetGLContextInfoKHR =(fake_clGetGLContextInfoKHR) dlsym(so_handle, "clGetGLContextInfoKHR");

    if(fun_fake_clGetGLContextInfoKHR) {
        return fun_fake_clGetGLContextInfoKHR(properties, param_name, param_value_size, param_value, param_value_size_ret);
    }
    return CL_INVALID_PLATFORM;
}
