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

#ifndef LIBEV3_H
#define LIBEV3_H
#include <stdbool.h>
#include <stdint.h>
#include <pitches.h>

int ev3Init(); // Call this before anything else

#ifndef EV3_PRIVATE_H
// Sensor and output device types
typedef   enum
{
  MODE_KEEP                     =  -1,  //!< Mode value that won't change mode in byte codes (convenient place to define)
  TYPE_KEEP                     =   0,  //!< Type value that won't change type in byte codes

  // Types defined in "typedata.rcf"
  TYPE_NXT_TOUCH                =   1,  //!< Device is NXT touch sensor
  TYPE_NXT_LIGHT                =   2,  //!< Device is NXT light sensor
  TYPE_NXT_SOUND                =   3,  //!< Device is NXT sound sensor
  TYPE_NXT_COLOR                =   4,  //!< Device is NXT color sensor
  TYPE_NXT_ULTRASONIC           =   5,  //!< Device is NXT ultra sonic sensor
  TYPE_NXT_TEMPERATURE          =   6,  //!< Device is NXT temperature sensor
  TYPE_TACHO                    =   7,  //!< Device is EV3/NXT tacho motor
  TYPE_MINITACHO                =   8,  //!< Device is EV3 mini tacho motor
  TYPE_NEWTACHO                 =   9,  //!< Device is EV3 new tacho motor

  TYPE_TOUCH                    =  16,  //!< Device is EV3 touch sensor

  // Types defined in known EV3 digital devices
  TYPE_COLOR                    =  29,  //!< Device is EV3 color sensor
  TYPE_ULTRASONIC               =  30,  //!< Device is EV3 ultra sonic sensor
  TYPE_GYRO                     =  32,  //!< Device is EV3 gyro sensor
  TYPE_IR                       =  33,  //!< Device is EV3 IR sensor

  // Type range reserved for third party devices
  TYPE_THIRD_PARTY_START        =  50,
  TYPE_THIRD_PARTY_END          =  98,

  // Special types
  TYPE_ENERGYMETER              =  99,  //!< Device is energy meter
  TYPE_IIC_UNKNOWN              = 100,  //!< Device type is not known yet
  TYPE_NXT_TEST                 = 101,  //!< Device is a NXT ADC test sensor

  TYPE_NXT_IIC                  = 123,  //!< Device is NXT IIC sensor
  TYPE_TERMINAL                 = 124,  //!< Port is connected to a terminal
  TYPE_UNKNOWN                  = 125,  //!< Port not empty but type has not been determined
  TYPE_NONE                     = 126,  //!< Port empty or not available
  TYPE_ERROR                    = 127,  //!< Port not empty and type is invalid
}
TYPE;
typedef   enum
{
  CONN_UNKNOWN                  = 111,  //!< Connection is fake (test)

  CONN_DAISYCHAIN               = 117,  //!< Connection is daisy chained
  CONN_NXT_COLOR                = 118,  //!< Connection type is NXT color sensor
  CONN_NXT_DUMB                 = 119,  //!< Connection type is NXT analog sensor
  CONN_NXT_IIC                  = 120,  //!< Connection type is NXT IIC sensor

  CONN_INPUT_DUMB               = 121,  //!< Connection type is LMS2012 input device with ID resistor
  CONN_INPUT_UART               = 122,  //!< Connection type is LMS2012 UART sensor

  CONN_OUTPUT_DUMB              = 123,  //!< Connection type is LMS2012 output device with ID resistor
  CONN_OUTPUT_INTELLIGENT       = 124,  //!< Connection type is LMS2012 output device with communication
  CONN_OUTPUT_TACHO             = 125,  //!< Connection type is LMS2012 tacho motor with series ID resistance

  CONN_NONE                     = 126,  //!< Port empty or not available
  CONN_ERROR                    = 127,  //!< Port not empty and type is invalid
}
CONN;
typedef   enum
{
  BLACKCOLOR   = 1,
  BLUECOLOR    = 2,
  GREENCOLOR   = 3,
  YELLOWCOLOR  = 4,
  REDCOLOR     = 5,
  WHITECOLOR   = 6,
  BROWNCOLOR   = 7
}
NXTCOLOR;
typedef   enum
{
  LED_BLACK                     = 0,
  LED_GREEN                     = 1,
  LED_RED                       = 2,
  LED_ORANGE                    = 3,
  LED_GREEN_FLASH               = 4,
  LED_RED_FLASH                 = 5,
  LED_ORANGE_FLASH              = 6,
  LED_GREEN_PULSE               = 7,
  LED_RED_PULSE                 = 8,
  LED_ORANGE_PULSE              = 9,

  LEDPATTERNS
}
LEDPATTERN;
typedef   enum
{
  NO_BUTTON                     = 0,
  UP_BUTTON                     = 1,
  ENTER_BUTTON                  = 2,
  DOWN_BUTTON                   = 3,
  RIGHT_BUTTON                  = 4,
  LEFT_BUTTON                   = 5,
  BACK_BUTTON                   = 6,
  ANY_BUTTON                    = 7,

  BUTTONTYPES                   = 8
}
BUTTONTYPE;
#endif // EV3_PRIVATE_H

// Enums for all ports
#define OUT_A 1
#define OUT_B 2
#define OUT_C 4
#define OUT_D 8
#define IN_1 16
#define IN_2 17
#define IN_3 18
#define IN_4 19

// Functions defined in ev3Out.c
// Must be an array of length 4
void ev3OutSetAllTypes(TYPE devType[]);
void ev3OutReset(char ports);
void ev3OutStop(char ports, char brake);
void ev3OutPower(char ports, char power);
void ev3OutSpeed(char ports, char speed);
void ev3OutStart(char ports);
void ev3OutPolarity(char ports, char pol);
void ev3OutRead(int8_t portNum, char* speed, int* steps);
bool ev3OutReady(char ports, int maxWait);
void ev3OutStepPower(char ports, char power, int step1, int step2, int step3, char brake);
void ev3OutTimePower(char ports, char power, int time1, int time2, int time3, char brake);
void ev3OutStepSpeed(char ports, char speed, int step1, int step2, int step3, char brake);
void ev3OutTimeSpeed(char ports, char speed, int time1, int time2, int time3, char brake);
void ev3OutStepSync(char ports, char speed, signed short turn, int step, char brake);
void ev3OutTimeSync(char ports, char speed, signed short turn, int time, char brake);
void ev3OutClrCount(char ports);

// Functions defined in ev3In.c
int16_t ev3InReadAnalogRaw(int8_t portNum);
TYPE ev3InGetType(int8_t portNum);
CONN ev3InGetConn(int8_t portNum);
void* ev3InReadUartRaw(int8_t portNum);
int8_t ev3InSetMode(int8_t portNum, int8_t mode);
int32_t ev3InRead(int8_t portNum);

// Functions defined in ev3Btn.c
void ev3SetLEDPattern(int8_t pattern);
int8_t ev3BtnRead(int8_t button);

// Functions defined in ev3Snd.c
int8_t ev3SndReady(int maxWait);
void ev3SndTone(uint16_t hertz, uint16_t msecs, uint8_t level);
void ev3SndStop(void);

int ev3Free(); // Call when you are done with libev3

#endif // LIBEV3_H
