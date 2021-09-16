#ifndef DECONZ_TIMEREF_H
#define DECONZ_TIMEREF_H

/*
 * \author    dresden elektronik ingenieurtechnik gmbh: http://www.dresden-elektronik.de
 * \author    Support email: wireless@dresden-elektronik.de
 *
 * Copyright (c) 2021, dresden elektronik ingenieurtechnik gmbh. All rights reserved.
 *
 * Licensed under dresden elektronik's Limited License Agreement --> deEULA.txt
 */

#include <stdint.h>
#include <QtGlobal>

namespace deCONZ {


struct SteadyTimeRef
{
    SteadyTimeRef() : ref(0) {}
    SteadyTimeRef(int64_t r_) : ref(r_) {}
    int64_t ref = 0;
};

struct SystemTimeRef
{
    SystemTimeRef() : ref() {}
    SystemTimeRef(int64_t r_) : ref(r_) {}
    int64_t ref = 0;
};

/*! Strong typed milliseconds. */
struct TimeMs
{
    int64_t val = 0;
};

/*! Strong typed seconds. */
struct TimeSeconds
{
    int64_t val = 0;
};

/*! Returnes milliseconds since Epoch */
int64_t DECONZ_DLLSPEC msecSinceEpoch();

/*! Returnes a time point reference in system time as milliseconds since Epoch.

    Note that on machines without an RTC this time might jump between calls
    until system time is synced via NTP.
 */
SystemTimeRef DECONZ_DLLSPEC systemTimeRef() noexcept;

/*! Returnes a time point reference in milliseconds which is monotonic increasing.

    This is best used for timeouts and measure relative times.
 */
SteadyTimeRef DECONZ_DLLSPEC steadyTimeRef() noexcept;

inline bool DECONZ_DLLSPEC isValid(SteadyTimeRef t) { return t.ref != 0; }
inline bool DECONZ_DLLSPEC isValid(SystemTimeRef t) { return t.ref != 0; }

inline bool DECONZ_DLLSPEC operator<(SystemTimeRef a, SystemTimeRef b) { return a.ref < b.ref; }

inline bool DECONZ_DLLSPEC operator==(SteadyTimeRef a, SteadyTimeRef b) { return a.ref == b.ref; }
inline bool DECONZ_DLLSPEC operator!=(SteadyTimeRef a, SteadyTimeRef b) { return a.ref != b.ref; }
inline bool DECONZ_DLLSPEC operator<(SteadyTimeRef a, SteadyTimeRef b) { return a.ref < b.ref; }
inline bool DECONZ_DLLSPEC operator<=(SteadyTimeRef a, SteadyTimeRef b) { return a.ref <= b.ref; }

inline TimeMs DECONZ_DLLSPEC operator-(SteadyTimeRef a, SteadyTimeRef b) { TimeMs res; res.val = a.ref - b.ref; return res; }
inline SteadyTimeRef DECONZ_DLLSPEC operator+(SteadyTimeRef a, TimeMs t) { return SteadyTimeRef{a.ref + t.val}; }
inline SteadyTimeRef DECONZ_DLLSPEC operator+(SteadyTimeRef a, TimeSeconds t) { return SteadyTimeRef{a.ref + t.val * 1000}; }

inline bool DECONZ_DLLSPEC operator<(TimeMs a, TimeMs b) { return a.val < b.val; }
inline bool DECONZ_DLLSPEC operator<(TimeSeconds a, TimeSeconds b) { return a.val < b.val; }
inline bool DECONZ_DLLSPEC operator<(TimeSeconds a, TimeMs b) { return a.val * 1000 < b.val; }
inline bool DECONZ_DLLSPEC operator<(TimeMs a, TimeSeconds b) { return a.val < b.val * 1000; }

inline TimeSeconds DECONZ_DLLSPEC operator*(TimeSeconds a, int factor) { TimeSeconds res; res.val = a.val * factor; return res; }
inline TimeMs DECONZ_DLLSPEC operator*(TimeMs a, int factor) { TimeMs res; res.val = a.val * factor; return res; }

} // namespace deCONZ

#endif // DECONZ_TIMEREF_H
