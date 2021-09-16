#ifndef DEVICE_ENUMERATOR_H
#define DEVICE_ENUMERATOR_H

/*
 * \author    dresden elektronik ingenieurtechnik gmbh: http://www.dresden-elektronik.de
 * \author    Support email: wireless@dresden-elektronik.de
 *
 * Copyright (c) 2016, dresden elektronik ingenieurtechnik gmbh. All rights reserved.
 *
 * Licensed under dresden elektronik's Limited License Agreement --> deEULA.txt
 */

#include <QObject>
#include <vector>

namespace deCONZ
{

/*! Descriptor of a device.
 */
struct DeviceEntry
{
    DeviceEntry() :
        failedConnects(0),
        idVendor(0),
        idProduct(0)
    {

    }
    bool operator==(const DeviceEntry &other) const
    {
        return path == other.path
            && friendlyName == other.friendlyName
            && idVendor == other.idVendor
            && idProduct == other.idProduct
            && serialNumber == other.serialNumber;
    }
    QString friendlyName;
    QString path;
    QString serialNumber;
    int failedConnects;
    quint16 idVendor;
    quint16 idProduct;
};

QString DECONZ_DLLSPEC DEV_StableDevicePath(const QString &path);

class DeviceEnumeratorPrivate;

/*!
    \ingroup util
    \class DeviceEnumerator
    \brief Lists all devices which are available for serial communication.
 */
class DECONZ_DLLSPEC DeviceEnumerator : public QObject
{
    Q_OBJECT

public:
    DeviceEnumerator() = delete;
    explicit DeviceEnumerator(QObject *parent);
    ~DeviceEnumerator();
    static DeviceEnumerator *instance();
    bool listSerialPorts();
    const std::vector<DeviceEntry> &getList() const;

private:
    Q_DECLARE_PRIVATE_D(d_ptr2, DeviceEnumerator)
    DeviceEnumeratorPrivate *d_ptr2 = nullptr;
};

} // namespace deCONZ

#endif // DEVICE_ENUMERATOR_H
