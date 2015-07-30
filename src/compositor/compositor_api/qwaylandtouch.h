/****************************************************************************
**
** Copyright (C) 2015 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtWaylandCompositor module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QWAYLANDTOUCH_H
#define QWAYLANDTOUCH_H

#include <QtCompositor/QWaylandExtensionContainer>

#include <QtCore/QObject>
#include <QtGui/QTouchEvent>

QT_BEGIN_NAMESPACE

class QWaylandTouch;
class QWaylandTouchPrivate;
class QWaylandInputDevice;
class QWaylandView;
class QWaylandClient;

class Q_COMPOSITOR_EXPORT QWaylandTouchGrabber {
public:
    QWaylandTouchGrabber();
    virtual ~QWaylandTouchGrabber();

    virtual void down(uint32_t time, int touch_id, const QPointF &position) = 0;
    virtual void up(uint32_t time, int touch_id) = 0;
    virtual void motion(uint32_t time, int touch_id, const QPointF &position) = 0;

    QWaylandTouch *touch;
};

class Q_COMPOSITOR_EXPORT QWaylandDefaultTouchGrabber : public QWaylandTouchGrabber
{
public:
    QWaylandDefaultTouchGrabber();

    void down(uint32_t time, int touch_id, const QPointF &position) Q_DECL_OVERRIDE;
    void up(uint32_t time, int touch_id) Q_DECL_OVERRIDE;
    void motion(uint32_t time, int touch_id, const QPointF &position) Q_DECL_OVERRIDE;
};

class Q_COMPOSITOR_EXPORT QWaylandTouch : public QObject, public QWaylandExtensionContainer
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QWaylandTouch)
public:
    QWaylandTouch(QWaylandInputDevice *seat, QObject *parent = 0);

    QWaylandInputDevice *inputDevice() const;
    QWaylandCompositor *compositor() const;

    void startGrab(QWaylandTouchGrabber *grab);
    void endGrab();

    virtual void sendTouchPointEvent(int id, const QPointF &position, Qt::TouchPointState state);
    virtual void sendFrameEvent();
    virtual void sendCancelEvent();

    virtual void sendFullTouchEvent(QTouchEvent *event);

    virtual void addClient(QWaylandClient *client, uint32_t id);

    struct wl_resource *focusResource() const;

    QWaylandView *mouseFocus() const;
private:
    void focusDestroyed(void *data);
    void mouseFocusChanged(QWaylandView *newFocus, QWaylandView *oldFocus);
};

QT_END_NAMESPACE

#endif  /*QWAYLANDTOUCH_H*/
