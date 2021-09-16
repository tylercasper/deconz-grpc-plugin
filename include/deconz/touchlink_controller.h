#ifndef DECONZ_TOUCHLINK_CONTROLLER_H
#define DECONZ_TOUCHLINK_CONTROLLER_H

/*
 * \author    dresden elektronik ingenieurtechnik gmbh: http://www.dresden-elektronik.de
 * \author    Support email: wireless@dresden-elektronik.de
 *
 * Copyright (c) 2016, dresden elektronik ingenieurtechnik gmbh. All rights reserved.
 *
 * Licensed under dresden elektronik's Limited License Agreement --> deEULA.txt
 */

#include <QObject>
#include <deconz/types.h>
#include <deconz/touchlink.h>

namespace deCONZ {

class TouchlinkControllerPrivate;

/*!
    \ingroup touchlink
    \class TouchlinkController
    \brief Provides services to access interpan and touchlink functionality.
 */
class DECONZ_DLLSPEC TouchlinkController : public QObject
{
    Q_OBJECT

public:
    /*! Constructor. */
    TouchlinkController(QObject *parent);
    /*! Deconstructor. */
    virtual ~TouchlinkController();
    /*! Get the singleton instance of the TouchlinkController. */
    static TouchlinkController *instance();
    /*! Start interpan networking.

        Interpan networking is only possible then the network state is NotInNetwork.

        \param channel the channel to tune in (11-26)
        \retval  0 if the request will be processed
        \retval -1 then the request could not be done
        \retval -2 then the network state is not NotInNetwork
        \retval -3 if channel is not valid (11-26)
     */
    virtual int startInterpanMode(uint8_t channel) = 0;
    /*! Sends a interpan request.

        \param req the request parameters
        \retval  0 if the request will be processed
        \retval -1 then the request could not be done
     */
    virtual int sendInterpanRequest(const TouchlinkRequest &req) = 0;
    /*! Generates a new random transaction identifier.

        \return a non zero random number
     */
    uint32_t generateTransactionId() const;

Q_SIGNALS:
    /*! Is emitted after starting interpan mode request is processed.

        \param status the result of the request
        \sa startInterpanMode()
     */
    void startInterpanModeConfirm(TouchlinkStatus status);
    /*! Is emitted after send interpan request is processed.

        \param status the result of the request
        \sa sendInterpanRequest()
     */
    void sendInterpanConfirm(TouchlinkStatus status);
    /*! Is emitted on the reception of a interpan frame.

        \param ind hold the raw interpan indication frame in the following format
            \code{.cpp}
            // all fields are little endian
            uint16_t srcPanId
            uint64_t srcAddress
            uint16_t dstPanId
            uint8_t  dstAddressMode
            uint64_t dstExtAddress   // (if dstAddressmode is 0x03)
            uint16_t dstShortAddress // (if dstAddressmode is not 0x03)
            uint16_t profileId
            uint16_t clusterId
            uint8_t  asduLength
            uint8_t  asdu[asduLength]
            \endcode
     */
    void interpanIndication(const QByteArray &ind);

private:
    TouchlinkControllerPrivate *d_ptr;
    Q_DECLARE_PRIVATE(TouchlinkController)
};

} // namespace deCONZ

#endif // DECONZ_TOUCHLINK_CONTROLLER_H
