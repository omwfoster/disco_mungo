/*******************************************************************************
* Copyright (c) 2017, Alan Barr
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice, this
*   list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright notice,
*   this list of conditions and the following disclaimer in the documentation
*   and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "debug.h"

#define SERIAL_PRINT_DRIVER SD1

mutex_t serialPrintMtx;

static const char *statusCodeString[] = {
    "STATUS_OK",
    "STATUS_ERROR_API",
    "STATUS_ERROR_CALLBACK",
    "STATUS_ERROR_INTERNAL",
    "STATUS_ERROR_EXTERNAL_INPUT",
    "STATUS_ERROR_OS",
    "STATUS_ERROR_LIBRARY",
    "STATUS_ERROR_LIBRARY_LWIP",
    "STATUS_ERROR_HW",
    "STATUS_ERROR_TIMEOUT",
    "STATUS_CODE_ENUM_MAX"
};

const char* statusCodeToString(StatusCode code)
{
    if (code > (STATUS_CODE_ENUM_MAX))
    {
        return "UNKNOWN STATUS CODE";
    }
 
    return statusCodeString[code];
}

void debugInit(void)
{
    /* Configure Debug Serial */
    sdStart(&SERIAL_PRINT_DRIVER, NULL);
    palSetPadMode(GPIOB, 6, PAL_MODE_ALTERNATE(7));
    palSetPadMode(GPIOB, 7, PAL_MODE_ALTERNATE(7));
    chMtxObjectInit(&serialPrintMtx);
}

void debugShutdown(void)
{
    sdStop(&SERIAL_PRINT_DRIVER);
}

void debugSerialPrintVa(const char *fmt, va_list argList)
{
    chMtxLock(&serialPrintMtx);
    chvprintf((BaseSequentialStream*)&SERIAL_PRINT_DRIVER, fmt, argList);
    chMtxUnlock(&serialPrintMtx);
}

void debugSerialPrint(const char *fmt, ...)
{
    va_list argList;
    va_start(argList, fmt);
    debugSerialPrintVa(fmt, argList);
    va_end(argList);
}

void HardFault_Handler(void) 
{
    BOARD_LED_RED_SET();
    while (true);
}

void MemManage_Handler(void) 
{
    BOARD_LED_RED_SET();
    while (true);
}

void BusFault_Handler(void) 
{
    BOARD_LED_RED_SET();
    while (true);
}

void UsageFault_Handler(void) 
{
    BOARD_LED_RED_SET();
    while (true);
}

void DebugMon_Handler(void) 
{
    BOARD_LED_RED_SET();
    while (true);
}
