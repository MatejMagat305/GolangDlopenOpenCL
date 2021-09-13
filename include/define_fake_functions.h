#ifndef LIBOPENCL_STUB_H
#define LIBOPENCL_STUB_H

#define CL_TARGET_OPENCL_VERSION 120
#include "./CL/cl.h"
#include "./CL/cl_gl.h"

typedef void (*fake_pfn_notify)(const char *, const void *, size_t, void *);

typedef cl_int (*fake_clGetPlatformIDs) (cl_uint, cl_platform_id *, cl_uint *);

typedef cl_int (*fake_clGetPlatformInfo) (cl_platform_id, cl_platform_info, size_t, void *, size_t *);

typedef cl_int (*fake_clGetDeviceIDs) (cl_platform_id, cl_device_type, cl_uint, cl_device_id *, cl_uint *);

typedef cl_int (*fake_clGetDeviceInfo) (cl_device_id, cl_device_info, size_t, void *, size_t *);

typedef cl_int (*fake_clCreateSubDevices) (cl_device_id, const cl_device_partition_property *,
					cl_uint, cl_device_id *, cl_uint *);

typedef cl_int (*fake_clRetainDevice) (cl_device_id);

typedef cl_int (*fake_clReleaseDevice) (cl_device_id);

typedef cl_context (*fake_clCreateContext) (const cl_context_properties *, cl_uint, const cl_device_id *,
                			fake_pfn_notify, void *, cl_int *);

typedef cl_context (*fake_clCreateContextFromType) (const cl_context_properties *, cl_device_type,
                        		fake_pfn_notify, void *, cl_int *);

typedef cl_int (*fake_clRetainContext) (cl_context);

typedef cl_int (*fake_clReleaseContext) (cl_context);

typedef cl_int (*fake_clGetContextInfo) (cl_context, cl_context_info, size_t, void *, size_t *);

typedef cl_command_queue (*fake_clCreateCommandQueue) (cl_context, cl_device_id, cl_command_queue_properties, cl_int *);

#ifdef CL_VERSION_2_0
typedef cl_command_queue (*fake_clCreateCommandQueueWithProperties) (cl_context, cl_device_id, const cl_queue_properties *, cl_int *);
#endif

typedef cl_int (*fake_clRetainCommandQueue) (cl_command_queue);

typedef cl_int (*fake_clReleaseCommandQueue) (cl_command_queue);

typedef cl_int (*fake_clGetCommandQueueInfo) (cl_command_queue, cl_command_queue_info, size_t, void *, size_t *);

typedef cl_mem (*fake_clCreateBuffer) (cl_context, cl_mem_flags, size_t, void *, cl_int *);

typedef cl_mem (*fake_clCreateSubBuffer) (cl_mem, cl_mem_flags, cl_buffer_create_type, const void *, cl_int *);

typedef cl_mem (*fake_clCreateImage) (cl_context, cl_mem_flags, const cl_image_format *, const cl_image_desc *, void *, cl_int *);

typedef cl_int (*fake_clRetainMemObject) (cl_mem);

typedef cl_int (*fake_clReleaseMemObject) (cl_mem);

typedef cl_int (*fake_clGetMemObjectInfo) (cl_mem, cl_mem_info, size_t, void *, size_t *);

typedef cl_int (*fake_clGetImageInfo) (cl_mem, cl_image_info, size_t, void *, size_t *);

typedef cl_int (*fake_clSetMemObjectDestructorCallback) (cl_mem, void (*pfn_notify)( cl_mem memobj, void* user_data), void *);

typedef cl_int (*fake_clGetSupportedImageFormats) (cl_context, cl_mem_flags, cl_mem_object_type, cl_uint, cl_image_format *, cl_uint *);

typedef cl_sampler (*fake_clCreateSampler) (cl_context, cl_bool, cl_addressing_mode, cl_filter_mode, cl_int *);

typedef cl_int (*fake_clRetainSampler) (cl_sampler);

typedef cl_int (*fake_clReleaseSampler) (cl_sampler);

typedef cl_int (*fake_clGetSamplerInfo) (cl_sampler, cl_sampler_info, size_t, void *, size_t *);

typedef cl_program (*fake_clCreateProgramWithSource) (cl_context, cl_uint, const char **, const size_t *, cl_int *);

typedef cl_program (*fake_clCreateProgramWithBinary) (cl_context, cl_uint, const cl_device_id *,
        const size_t *, const unsigned char **, cl_int *, cl_int *);

typedef cl_program (*fake_clCreateProgramWithBuiltInKernels) (cl_context, cl_uint, const cl_device_id *, const char *, cl_int *);

typedef cl_int (*fake_clRetainProgram) (cl_program);

typedef cl_int (*fake_clReleaseProgram) (cl_program);

typedef cl_int (*fake_clBuildProgram) (cl_program, cl_uint, const cl_device_id *, const char *,
        void (*pfn_notify)(cl_program program, void * user_data), void *);

typedef cl_int (*fake_clCompileProgram) (cl_program, cl_uint, const cl_device_id *, const char *, cl_uint, const cl_program *,
        const char **, void (*pfn_notify)(cl_program program, void * user_data), void *);

typedef cl_program (*fake_clLinkProgram) (cl_context, cl_uint, const cl_device_id *, const char *, cl_uint, const cl_program *,
                    void (*pfn_notify)(cl_program program, void * user_data), void *, cl_int *);

typedef cl_int (*fake_clUnloadPlatformCompiler)(cl_platform_id);

typedef cl_int (*fake_clGetProgramInfo) (cl_program, cl_program_info, size_t, void *, size_t *);

typedef cl_int (*fake_clGetProgramBuildInfo) (cl_program, cl_device_id, cl_program_build_info, size_t, void *, size_t *);

typedef cl_kernel (*fake_clCreateKernel) (cl_program, const char *, cl_int *);

typedef cl_int (*fake_clCreateKernelsInProgram) (cl_program, cl_uint, cl_kernel *, cl_uint *);

typedef cl_int (*fake_clRetainKernel) (cl_kernel);

typedef cl_int (*fake_clReleaseKernel) (cl_kernel);

typedef cl_int (*fake_clSetKernelArg) (cl_kernel, cl_uint, size_t,const void *);

typedef cl_int (*fake_clGetKernelInfo) (cl_kernel, cl_kernel_info, size_t, void *, size_t *);

typedef cl_int (*fake_clGetKernelArgInfo) (cl_kernel, cl_uint, cl_kernel_arg_info, size_t, void *, size_t *);

typedef cl_int (*fake_clGetKernelWorkGroupInfo) (cl_kernel, cl_device_id, cl_kernel_work_group_info, size_t, void *, size_t *);

typedef cl_int (*fake_clWaitForEvents) (cl_uint, const cl_event *);

typedef cl_int (*fake_clGetEventInfo) (cl_event, cl_event_info, size_t, void *, size_t *);

typedef cl_event (*fake_clCreateUserEvent) (cl_context, cl_int *);

typedef cl_int (*fake_clRetainEvent) (cl_event);

typedef cl_int (*fake_clReleaseEvent) (cl_event);

typedef cl_int (*fake_clSetUserEventStatus) (cl_event, cl_int);

typedef cl_int (*fake_clSetEventCallback) (cl_event, cl_int, void (*pfn_notify)(cl_event, cl_int, void *), void *);

typedef cl_int (*fake_clGetEventProfilingInfo) (cl_event, cl_profiling_info, size_t, void *, size_t *);

typedef cl_int (*fake_clFlush) (cl_command_queue);

typedef cl_int (*fake_clFinish) (cl_command_queue);

typedef cl_int (*fake_clEnqueueReadBuffer) (cl_command_queue, cl_mem, cl_bool, size_t, size_t, void *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueReadBufferRect) (cl_command_queue, cl_mem, cl_bool, const size_t *, const size_t *, const size_t *,
                            size_t, size_t, size_t, size_t, void *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueWriteBuffer) (cl_command_queue, cl_mem, cl_bool, size_t, size_t, const void *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueWriteBufferRect) (cl_command_queue, cl_mem, cl_bool, const size_t *, const size_t *, const size_t *,
                            size_t, size_t, size_t, size_t, const void *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueFillBuffer) (cl_command_queue, cl_mem, const void *, size_t, size_t, size_t, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueCopyBuffer) (cl_command_queue, cl_mem, cl_mem, size_t, size_t, size_t, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueCopyBufferRect) (cl_command_queue, cl_mem, cl_mem, const size_t *, const size_t *, const size_t *,
                            size_t, size_t, size_t, size_t, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueReadImage) (cl_command_queue, cl_mem, cl_bool, const size_t *, const size_t *,
							size_t, size_t, void *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueWriteImage) (cl_command_queue, cl_mem, cl_bool, const size_t *, const size_t *,
							size_t, size_t, const void *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueFillImage) (cl_command_queue, cl_mem, const void *, const size_t *, const size_t *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueCopyImage) (cl_command_queue, cl_mem, cl_mem, const size_t *, const size_t *, const size_t *,
          cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueCopyImageToBuffer) (cl_command_queue, cl_mem, cl_mem, const size_t *, const size_t *, size_t, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueCopyBufferToImage) (cl_command_queue, cl_mem, cl_mem, size_t, const size_t *, const size_t *, cl_uint, const cl_event *, cl_event *);

typedef void * (*fake_clEnqueueMapBuffer) (cl_command_queue, cl_mem, cl_bool, cl_map_flags, size_t,
						size_t, cl_uint, const cl_event *, cl_event *, cl_int *);

typedef void * (*fake_clEnqueueMapImage) (cl_command_queue, cl_mem, cl_bool, cl_map_flags, const size_t *, const size_t *,
                  size_t *, size_t *, cl_uint, const cl_event *, cl_event *, cl_int *);

typedef cl_int (*fake_clEnqueueUnmapMemObject) (cl_command_queue, cl_mem, void *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueMigrateMemObjects)(cl_command_queue, cl_uint, const cl_mem *, cl_mem_migration_flags,
						cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueNDRangeKernel)(cl_command_queue, cl_kernel, cl_uint, const size_t *, const size_t *,
                       const size_t *, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueTask)(cl_command_queue, cl_kernel, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueNativeKernel)(cl_command_queue, void (*user_func)(void *),  void *, size_t,
                      cl_uint, const cl_mem *, const void **, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueMarkerWithWaitList)(cl_command_queue, cl_uint, const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueBarrierWithWaitList)(cl_command_queue, cl_uint, const cl_event *, cl_event *);

typedef void * (*fake_clGetExtensionFunctionAddressForPlatform)(cl_platform_id, const char *);

typedef cl_mem (*fake_clCreateImage2D)(cl_context, cl_mem_flags,const cl_image_format *, size_t, size_t,
                				size_t, void *, cl_int *);

typedef cl_mem (*fake_clCreateImage3D)(cl_context, cl_mem_flags, const cl_image_format *, size_t,
                		size_t, size_t, size_t, size_t, void *, cl_int *);

typedef cl_int (*fake_clEnqueueMarker)(cl_command_queue, cl_event *);

typedef cl_int(*fake_clEnqueueWaitForEvents)(cl_command_queue, cl_uint, const cl_event *);

typedef cl_int (*fake_clEnqueueBarrier)(cl_command_queue);

typedef cl_int (*fake_clUnloadCompiler)(void);

typedef void * (*fake_clGetExtensionFunctionAddress)(const char *);

typedef cl_mem (*fake_clCreateFromGLBuffer) (cl_context, cl_mem_flags, cl_GLuint, int *);

typedef cl_mem (*fake_clCreateFromGLTexture) (cl_context, cl_mem_flags, cl_GLenum, cl_GLint, cl_GLuint, cl_int *);

typedef cl_mem (*fake_clCreateFromGLRenderbuffer) (cl_context, cl_mem_flags, cl_GLuint, cl_int *);

typedef cl_int (*fake_clGetGLObjectInfo) (cl_mem memobj, cl_gl_object_type *, cl_GLuint *);

typedef cl_int (*fake_clGetGLTextureInfo) (cl_mem, cl_gl_texture_info, size_t, void *, size_t *);

typedef cl_int (*fake_clEnqueueAcquireGLObjects) (cl_command_queue, cl_uint, const cl_mem *, cl_uint,
                                        const cl_event *, cl_event *);

typedef cl_int (*fake_clEnqueueReleaseGLObjects) (cl_command_queue, cl_uint, const cl_mem *, cl_uint,
                                        const cl_event *, cl_event *);

typedef cl_mem (*fake_clCreateFromGLTexture2D) (cl_context, cl_mem_flags, cl_GLenum, cl_GLint, cl_GLuint, cl_int *);

typedef cl_mem (*fake_clCreateFromGLTexture3D) (cl_context, cl_mem_flags, cl_GLenum, cl_GLint, cl_GLuint, cl_int *);

typedef cl_int (*fake_clGetGLContextInfoKHR) (const cl_context_properties *, cl_gl_context_info, size_t,
                                        void *, size_t *);


#endif    // LIBOPENCL_STUB_H
