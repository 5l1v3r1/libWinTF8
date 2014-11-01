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
#pragma once
#ifndef WTF8_ARGV_H_INCLUDED_
#define WTF8_ARGV_H_INCLUDED_

#ifdef __cplusplus
#include <vector>
#include "u8str.h"

namespace WinTF8 {

std::vector<u8string> get_argv(int argc_hint, char* argv_hint[]);

}
#endif

#ifdef __cplusplus
extern "C" {
#endif

char **WTF8_get_argv(int argc_hint, const char **argv_hint);
char **WTF8_free_argv(int argc_got, char **argv_got);

#ifdef __cplusplus
}
#endif

#endif