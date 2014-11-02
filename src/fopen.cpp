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
#include <cstdio>
#include "utils.h"
#include "u8str.h"
#include "fopen.h"

namespace WinTF8 {

std::FILE* fopen(const char* filename, const char* mode) {
#ifdef _WIN32
    return std::_wfopen(WinTF8::u8string(filename).to_wide().c_str(), WinTF8::u8string(mode).to_wide().c_str());
#else
    return std::fopen(filename, mode);
#endif
}

std::FILE* fclose(std::FILE *fp) {
    std::fclose(fp);
    return nullptr;
}

}

extern "C" {

std::FILE *WTF8_fopen(const char *filename, const char *mode) {
    return WinTF8::fopen(filename, mode);
}

std::FILE *WTF8_fclose(std::FILE *fp) {
    return WinTF8::fclose(fp);
}

}
