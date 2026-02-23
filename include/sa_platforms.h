/*
    SA Engine

    Copyright (c) 2026 DBQ Studio

    This file is part of the SA Engine project.
    Licensed under the MIT License.

    See the LICENSE file in the project root for full license information.
*/

#pragma once

/* Allow forcing static build: */
#ifdef SA_STATIC
    #define SA_API
#else

/* Windows */
#if defined(_WIN32) || defined(__CYGWIN__)
// #   include <windows.h>
    #ifdef SA_BUILD        /* defined when building the DLL */
        #define SA_API __declspec(dllexport)
    #else
        #define SA_API __declspec(dllimport)
    #endif

/* POSIX (GCC/Clang) */
#else
    #if __GNUC__ >= 4
        #define SA_API __attribute__((visibility("default")))
    #else
        #define SA_API
    #endif
#endif

#endif /* SA_STATIC */



















