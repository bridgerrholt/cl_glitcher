//
// Created by bridg on 2/12/2021.
//

#ifndef CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_MOD_DEFS_H
#define CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_MOD_DEFS_H

#include <gpu_util/buffer_wrapper.h>

#include <json_defs/json_obj_type.h>
#include <mod_environment/mod_environment.h>

#include "system_environment.h"
#include <opencv2/opencv.hpp>


namespace clglitch {

class JsonObjExecuteParams
{
  public:
    JsonObjType const & data;
    CmdEnvironment const & cmdEnv;
    SystemEnvironment const & systemEnv;
    gpu_util::BufferWrapper & currentImage;
    cv::Mat & currentImageMat;
    int imgSizeBytes;
    gpu_util::GpuHandle const & gpuHandle;
    cl::CommandQueue & commandQueue;
};

/// cmd: JSON-parsed contents of the command file.
/// env: JSON-parsed environment.
using JsonObjExecuteFuncType =
  void(*)(JsonObjExecuteParams const & params);

}

#endif //CL_GLITCHER_INCLUDE_CL_GLITCHER_MOD_SYS_MOD_DEFS_H
