#ifndef DECONZ_NODE_INTERFACE_H
#define DECONZ_NODE_INTERFACE_H

/*
 * \author    dresden elektronik ingenieurtechnik gmbh: http://www.dresden-elektronik.de
 * \author    Support email: wireless@dresden-elektronik.de
 *
 * Copyright (c) 2016, dresden elektronik ingenieurtechnik gmbh. All rights reserved.
 *
 * Licensed under dresden elektronik's Limited License Agreement --> deEULA.txt
 */

// forward declarations
class QDialog;
class QWidget;

namespace deCONZ
{

class Node;

/*!
    \ingroup aps
    \class NodeInterface
    \brief Main interface to create a deCONZ plugin.
 */
class NodeInterface
{
public:
    /*! Features the plugin _might_ support. */
    enum Features
    {
        WidgetFeature,
        DialogFeature,
        HttpClientHandlerFeature
    };

    /*! Deconstructor. */
    virtual ~NodeInterface() { }
    /*! Plugin name. */
    virtual const char *name() = 0;
    /*! Returns true if the plugin supports the \p feature. */
    virtual bool hasFeature(Features feature) = 0;
    /*! Returns a widget if the plugin supports the WidgetFeature otherwise 0. */
    virtual QWidget *createWidget() { return 0; }
    /*! Returns a dialog if the plugin supports the DialogFeature otherwise 0. */
    virtual QDialog *createDialog() { return 0; }
};

} // namespace deCONZ

Q_DECLARE_INTERFACE(deCONZ::NodeInterface, "com.deCONZ.NodeInterface/1.0")

#endif // DECONZ_NODE_INTERFACE_H
