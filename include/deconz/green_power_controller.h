#ifndef DECONZ_GREEN_POWER_CONTROLLER_H
#define DECONZ_GREEN_POWER_CONTROLLER_H

/*
 * \author    dresden elektronik ingenieurtechnik gmbh: http://www.dresden-elektronik.de
 * \author    Support email: wireless@dresden-elektronik.de
 *
 * Copyright (c) 2016-2020, dresden elektronik ingenieurtechnik gmbh. All rights reserved.
 *
 * Licensed under dresden elektronik's Limited License Agreement --> deEULA.txt
 */

#include <QObject>
#include <deconz/types.h>
#include <deconz/green_power.h>

namespace deCONZ {

class GreenPowerControllerPrivate;

/*!
    \ingroup greenpower
    \class GreenPowerController
    \brief Provides services to access green power functionality.
 */
class DECONZ_DLLSPEC GreenPowerController : public QObject
{
    Q_OBJECT

public:
    /*! Constructor. */
    GreenPowerController(QObject *parent);
    /*! Deconstructor. */
    virtual ~GreenPowerController();
    /*! Get the singleton instance of the GreenPowerController. */
    static GreenPowerController *instance();

    void processIncomingData(const QByteArray &data);
    void processIncomingProxyNotification(const QByteArray &data);

Q_SIGNALS:
    /*! Is emitted on the reception of a green power frame.

        \param ind the green power data indication frame
     */
    void gpDataIndication(const deCONZ::GpDataIndication&);

private:
    GreenPowerControllerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(GreenPowerController)
};

} // namespace deCONZ

#endif // DECONZ_GREEN_POWER_CONTROLLER_H
