/*############################################################################
  # Copyright (C) 2019 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

#ifndef  VPL_UTILS_HPP
#define  VPL_UTILS_HPP

#include "vpl_types.h"
#include "vpl_utils.hpp"
#include "vpl_memory.hpp"

namespace vpl {
    vplStatus vplWriteImagesArray(FILE* fOutput, std::vector<image> &images);
}

#endif // VPL_UTILS_HPP