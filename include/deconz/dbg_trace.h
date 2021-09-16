#ifndef DECONZ_DBG_TRACE_H
#define DECONZ_DBG_TRACE_H

/*
 * \author    dresden elektronik ingenieurtechnik gmbh: http://www.dresden-elektronik.de
 * \author    Support email: wireless@dresden-elektronik.de
 *
 * Copyright (c) 2016-2020, dresden elektronik ingenieurtechnik gmbh. All rights reserved.
 *
 * Licensed under dresden elektronik's Limited License Agreement --> deEULA.txt
 */

#include <deconz/types.h>

#define DBG_INFO     0x00000001
#define DBG_ERROR    0x00000002
#define DBG_PROT     0x00000004
#define DBG_AIR      0x00000008
#define DBG_WIRE     0x00000010
#define DBG_PROTBUF  0x00000020
#define DBG_ZDP      0x00000040
#define DBG_ZCL      0x00000080
#define DBG_APS      0x00000100
#define DBG_PROT_L2  0x00000200
#define DBG_ZCLDB    0x00000400
#define DBG_INFO_L2  0x00000800
#define DBG_HTTP     0x00001000
#define DBG_TLINK    0x00002000
#define DBG_ERROR_L2 0x00004000
#define DBG_OTA      0x00008000
#define DBG_APS_L2   0x00010000
#define DBG_MEASURE  0x00020000
#define DBG_ROUTING  0x00040000
#define DBG_ZGP      0x00080000
#define DBG_IAS      0x00100000

#define DBG_END      0x00100000

#define DBG_Assert(e) ((e) ? true : (DBG_Printf1(DBG_ERROR, "%s,%d: assertion '%s' failed\n", Q_FUNC_INFO, __LINE__, #e), false))


#define DBG_MEASURE_START(MEAS_ID) \
    QElapsedTimer MEAS_ID##measTimer; \
    const char *MEAS_ID##fn = __FUNCTION__; \
    const int MEAS_ID##line = __LINE__; \
    MEAS_ID##measTimer.start()

#define DBG_MEASURE_END(MEAS_ID) \
    if (DBG_IsEnabled(DBG_MEASURE)) { \
        DBG_Printf1(DBG_MEASURE, "MS " #MEAS_ID " (%s:%d) took %lld ms\n", MEAS_ID##fn, MEAS_ID##line, MEAS_ID##measTimer.elapsed()); \
    }

#define DBG_Printf(level, ...) \
    do { \
        if (DBG_IsEnabled(level)) { DBG_Printf1(level, __VA_ARGS__); } \
    } while(0)

#ifdef __cplusplus

class DebugLog
{

};

extern "C" {
#endif

void DECONZ_DLLSPEC DBG_Init(FILE *logfile);
void DECONZ_DLLSPEC DBG_Destroy();
void DECONZ_DLLSPEC DBG_Flush();
void DECONZ_DLLSPEC DBG_FlushLazy();
void DECONZ_DLLSPEC DBG_WriteString(int level, const char *str);
int DECONZ_DLLSPEC DBG_Printf1(int level, const char *format, ...);
void DECONZ_DLLSPEC DBG_Enable(int item);
void DECONZ_DLLSPEC DBG_Disable(int item);
int DECONZ_DLLSPEC DBG_IsEnabled(int item);
uint8_t * DECONZ_DLLSPEC DBG_HexToAscii(const uint8_t *hex, uint8_t length, uint8_t *ascii);
void DECONZ_DLLSPEC DBG_RegisterCallback(void (*cb)(int, const char*));
int DECONZ_DLLSPEC DBG_ItemFromString(const char *item);
int DECONZ_DLLSPEC DBG_StringFromItem(const int item, char *buf, size_t buflen);

#ifdef __cplusplus
}
#endif

#endif // DECONZ_DBG_TRACE_H
