/*############################################################################
  # Copyright (C) 2019 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

#ifndef VPL_EXPORT_H
#define VPL_EXPORT_H

#ifdef VPL_STATIC_DEFINE
#  define VPL_EXPORT
#  define VPL_NO_EXPORT
#  define VPL_EXTENSION
#else
#  if defined(_WIN32)
       #pragma warning( disable : 4251) // Disable link warnings on private STL members 
#    ifdef vpl_EXPORTS
       /* We are building this library */
#      define VPL_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define VPL_EXPORT __declspec(dllimport)
#    endif
#    define VPL_EXTENSION __declspec(dllexport)  
#  else
#    if __GNUC__ >= 4
#      define VPL_EXPORT __attribute__((visibility("default")))
#      define VPL_NO_EXPORT __attribute__((visibility("hidden")))
#      define VPL_EXTENSION VPL_EXPORT
#    else
#      define VPL_EXPORT
#      define VPL_NO_EXPORT
#      define VPL_EXTENSION
#    endif
#  endif
#endif

#endif // VPL_EXPORT_H
