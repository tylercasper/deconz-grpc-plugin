#ifndef BINDING_TABLE_H
#define BINDING_TABLE_H

/*
 * \author    dresden elektronik ingenieurtechnik gmbh: http://www.dresden-elektronik.de
 * \author    Support email: wireless@dresden-elektronik.de
 *
 * Copyright (c) 2016-2020, dresden elektronik ingenieurtechnik gmbh. All rights reserved.
 *
 * Licensed under dresden elektronik's Limited License Agreement --> deEULA.txt
 */

#include "deconz/types.h"
#include "deconz/aps.h"
#include "deconz/timeref.h"

class QDataStream;

namespace deCONZ {


class DECONZ_DLLSPEC Binding
{
public:
    Binding() = default;
    Binding(const quint64 src, const quint64 dst, const quint16 clusterId, const quint8 srcEndpoint, const quint8 dstEndpoint);
    Binding(const quint64 src, const quint16 dstGroup, const quint16 clusterId, const quint8 srcEndpoint);

    quint64 srcAddress() const { return m_srcAddr; }
    void setSrcAddress(quint64 src) { m_srcAddr = src; }
    uint8_t srcEndpoint() const { return m_srcEndpoint; }
    void setSrcEndpoint(const uint8_t srcEndpoint) { m_srcEndpoint = srcEndpoint; }
    uint16_t clusterId() const { return m_cluster; }
    void setClusterId(const uint16_t clusterId) { m_cluster = clusterId; }
    deCONZ::ApsAddressMode dstAddressMode() const { return m_dstAddrMode; }
    void setDstAddressMode(const deCONZ::ApsAddressMode mode) { m_dstAddrMode = mode; }
    deCONZ::Address &dstAddress() { return m_dstAddr; }
    const deCONZ::Address &dstAddress() const { return m_dstAddr; }
    uint8_t dstEndpoint() const { return m_dstEndpoint; }
    void setDstEndpoint(const uint8_t dstEndpoint) { m_dstEndpoint = dstEndpoint; }
    /*! Reads a binding entry from stream. */
    bool readFromStream(QDataStream &stream);
    bool isValid() const;
    /*! Timestamp when the binding was last confirmed.
        Either by receiving a binding related command or by ZDP Mgmt_Bind_rsp.
     */
    deCONZ::SteadyTimeRef confirmedTimeRef() const { return m_confirmedTimeRef; }
    void setConfirmedTimeRef(deCONZ::SteadyTimeRef t) { m_confirmedTimeRef = t; }

    bool operator==(const Binding &other) const
    {
        if (dstAddress() == other.dstAddress() &&
            dstAddressMode() == other.dstAddressMode() &&
            srcAddress() == other.srcAddress() &&
            srcEndpoint() == other.srcEndpoint() &&
            dstEndpoint() == other.dstEndpoint() &&
            clusterId() == other.clusterId())
        {
            return true;
        }

        return false;
    }

    bool operator !=(const Binding &other)
    {
        return !(*this == other);
    }

private:
    deCONZ::Address m_dstAddr;
    deCONZ::SteadyTimeRef m_confirmedTimeRef{};
    quint64 m_srcAddr = 0;
    deCONZ::ApsAddressMode m_dstAddrMode = deCONZ::ApsNoAddress;
    uint16_t m_cluster = 0xffff;
    uint8_t m_srcEndpoint = 0xff;
    uint8_t m_dstEndpoint = 0xff;
};

class DECONZ_DLLSPEC BindingTable
{
public:
    BindingTable() = default;

    using size_type = std::vector<Binding>::size_type;
    using iterator = std::vector<Binding>::iterator;
    using const_iterator = std::vector<Binding>::const_iterator;

    bool add(const Binding &binding);
    bool remove(const Binding &binding);
    size_type size() const { return m_table.size(); }
    bool contains(const Binding &binding) const;
    const_iterator const_begin() const;
    const_iterator const_end() const;
    iterator begin();
    iterator end();

private:
    std::vector<Binding> m_table;
};

} // namespace deCONZ

Q_DECLARE_METATYPE(deCONZ::BindingTable)


#endif // BINDING_TABLE_H

