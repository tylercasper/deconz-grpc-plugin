#ifndef DECONZ_UTIL_H
#define DECONZ_UTIL_H

/*
 * \author    dresden elektronik ingenieurtechnik gmbh: http://www.dresden-elektronik.de
 * \author    Support email: wireless@dresden-elektronik.de
 *
 * Copyright (c) 2016-2021, dresden elektronik ingenieurtechnik gmbh. All rights reserved.
 *
 * Licensed under dresden elektronik's Limited License Agreement --> deEULA.txt
 */

#include <deconz/aps.h>

namespace deCONZ {

enum StorageLocation
{
    HomeLocation,
    ApplicationsLocation,
    ApplicationsDataLocation,
    DocumentsLocation,
    ZcldbLocation,
    ConfigLocation,
    NodeCacheLocation,
    RuntimeLocation,
    DdfLocation
};

int DECONZ_DLLSPEC appArgumentNumeric(const QString &arg, int defaultValue);
QString DECONZ_DLLSPEC appArgumentString(const QString &arg, const QString &defaultValue);
time_t DECONZ_DLLSPEC current_time_t();
QString DECONZ_DLLSPEC jsonStringFromMap(const QVariantMap &map);
QString DECONZ_DLLSPEC jsonStringFromList(const QVariantList &ls);
bool DECONZ_DLLSPEC getDestination(Address *addr, ApsAddressMode *addrMode, quint8 *endpoint);
void DECONZ_DLLSPEC setDestination(const Address &addr, deCONZ::ApsAddressMode addrMode, quint8 endpoint);
QString DECONZ_DLLSPEC getStorageLocation(StorageLocation location);
bool DECONZ_DLLSPEC isVirtualMachine();
} // namespace deCONZ

#endif // DECONZ_UTIL_H
