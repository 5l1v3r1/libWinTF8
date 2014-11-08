/*
  Copyright (c) 2014 StarBrilliant <m13253@hotmail.com>
  All rights reserved.

  Redistribution and use in source and binary forms are permitted
  provided that the above copyright notice and this paragraph are
  duplicated in all such forms and that any documentation,
  advertising materials, and other materials related to such
  distribution and use acknowledge that the software was developed by
  StarBrilliant.
  The name of StarBrilliant may not be used to endorse or promote
  products derived from this software without specific prior written
  permission.

  THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*/
#include <stdexcept>
#include <fstream>
#include <vector>
#include "utils.h"
#include "u8str.h"
#include "argv.h"

#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__) && defined(__MACH__)
extern "C" {
    extern int* _NSGetArgc();
    extern char*** _NSGetArgv();
}
#endif

namespace WinTF8 {

std::vector<u8string> get_argv() {
#if defined(_WIN32)
    int argc;
    wchar_t** wargv = CommandLineToArgvW(GetCommandLineW(), &argc);
    std::vector<u8string> result;
    result.reserve(argc);
    for(int i = 0; i < argc; ++i)
        result.push_back(u8string(wargv[i]));
    LocalFree(static_cast<void*>(wargv));
    return result;
#elif defined(__APPLE__) && defined(__MACH__)
    int argc = *_NSGetArgc();
    char** argv = *_NSGetArgv();
    std::vector<u8string> result;
    result.reserve(argc);
    for(int i = 0; i < argc; ++i)
        result.push_back(u8string(argv[i]));
    return result;
#else
    std::ifstream cmdline("/proc/self/cmdline");
    if(cmdline.good()) {
        std::vector<u8string> result;
        while(!cmdline.eof()) {
            u8string argi;
            for(;;) {
                char c;
                cmdline.get(c);
                if(cmdline.good())
                    if(c != '\0')
                        argi.push_back(c);
                    else
                        break;
                else
                    throw std::runtime_error("unable to get commandline arguments");
            }
            result.push_back(std::move(argi));
        }
        return result;
    } else
        throw std::runtime_error("unable to get commandline arguments");
#endif
}

}

extern "C" {

char **WTF8_get_argv(int *argc) {
#if defined(_WIN32)
    int argc_;
    wchar_t** wargv = CommandLineToArgvW(GetCommandLineW(), &argc_);
    if(argc)
        *argc = argc_;
    char** result = new char*[argc_+1];
    for(int i = 0; i < argc_; ++i)
        result[i] = WinTF8::new_c_str(WinTF8::u8string(wargv[i]));
    result[argc_] = nullptr;
    return result;
#elif defined(__APPLE__) && defined(__MACH__)
    if(argc)
        *argc = *_NSGetArgc();
    return *_NSGetArgv();
#else
    try {
        std::vector<WinTF8::u8string> argv = WinTF8::get_argv();
        if(argc)
            *argc = argv.size();
        char** result = new char*[argv.size()+1];
        for(size_t i = 0; i < argv.size(); ++i)
            result[i] = WinTF8::new_c_str(argv[i]);
        result[argv.size()] = nullptr;
        return result;
    } catch(std::runtime_error) {
        if(argc)
            *argc = 0;
        return nullptr;
    }
#endif
}

char **WTF8_free_argv(char **argv) {
#if !defined(__APPLE__) || !defined(__MACH__)
    if(argv) {
        for(size_t i = 0; argv[i]; ++i)
            argv[i] = WinTF8::delete_c_str(argv[i]);
        delete[] argv;
    }
#endif
    return nullptr;
}

}
