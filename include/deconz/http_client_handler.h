#ifndef DECONZ_HTTP_CLIENT_HANDLER_H
#define DECONZ_HTTP_CLIENT_HANDLER_H

/*
 * \author    dresden elektronik ingenieurtechnik gmbh: http://www.dresden-elektronik.de
 * \author    Support email: wireless@dresden-elektronik.de
 *
 * Copyright (c) 2016, dresden elektronik ingenieurtechnik gmbh. All rights reserved.
 *
 * Licensed under dresden elektronik's Limited License Agreement --> deEULA.txt
 */

#include <deconz/types.h>

class QTcpSocket;
class QHttpRequestHeader;

namespace deCONZ
{

class DECONZ_DLLSPEC HttpClientHandler
{
public:
    /*enum Status
    {
        StatusOk          =  0,
        StatusBusy        = -1,
        StatusNoNetwork   = -2
    };*/

    HttpClientHandler();
    virtual ~HttpClientHandler();
    virtual bool isHttpTarget(const QHttpRequestHeader &hdr) = 0;
    /*!
     * \brief handleHttpRequest
     * \param hdr
     * \param sock
     * \return 0 on success
     */
    virtual int handleHttpRequest(const QHttpRequestHeader &hdr, QTcpSocket *sock) = 0;
    virtual void clientGone(QTcpSocket *sock) = 0;
};

} // namespace deCONZ

#endif // DECONZ_HTTP_CLIENT_HANDLER_H
