/*
 * legoev3 - a simple library for Lego Mindstorms
 * Copyright (C) 2020 David Stumph
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */


#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ev3Private.h>

#ifdef DEBUG
void ev3Log(const char* message, ...) {
  va_list vl;
  va_start(vl, message);
  FILE* pFile = fopen("/home/root/lms2012/prjs/test/log", "a");
  vfprintf(pFile, message, vl);
  fclose(pFile);
  va_end(vl);
}
#endif // DEBUG

int ev3Init() {
  if (!ev3OutInit() || !ev3InInit() || !ev3BtnInit() || !ev3SndInit()) {
    ev3Free(); // Call ev3Free to clear anything that may have been allocated
#ifdef DEBUG
    ev3Log("Error initializing library!\n");
#endif // DEBUG
    return 0;
  }
  return 1;
}

int ev3Free() {
  ev3InFree();
  ev3OutFree();
  ev3BtnFree();
  ev3SndInit();
  return 1;
}
