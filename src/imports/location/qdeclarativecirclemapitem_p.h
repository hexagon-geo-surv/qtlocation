/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtLocation module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QDECLARATIVECIRCLEMAPITEM_H
#define QDECLARATIVECIRCLEMAPITEM_H

#include "qdeclarativegeomapitembase_p.h"
#include "qdeclarativepolylinemapitem_p.h"
#include "qdeclarativepolygonmapitem_p.h"
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>

QT_BEGIN_NAMESPACE

class QDeclarativeGeoMapQuickItem;

class QGeoMapCircleGeometry : public QGeoMapPolygonGeometry
{
public:
    QGeoMapCircleGeometry();

    void updateScreenPointsInvert(const QGeoMap &map);
};

class QDeclarativeCircleMapItem : public QDeclarativeGeoMapItemBase
{
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate center READ center WRITE setCenter NOTIFY centerChanged)
    Q_PROPERTY(qreal radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QDeclarativeMapLineProperties *border READ border CONSTANT)

public:
    explicit QDeclarativeCircleMapItem(QQuickItem *parent = 0);
    ~QDeclarativeCircleMapItem();

    virtual void setMap(QDeclarativeGeoMap *quickMap, QGeoMap *map) Q_DECL_OVERRIDE;
    virtual QSGNode *updateMapItemPaintNode(QSGNode *, UpdatePaintNodeData *) Q_DECL_OVERRIDE;

    QGeoCoordinate center();
    void setCenter(const QGeoCoordinate &center);

    qreal radius() const;
    void setRadius(qreal radius);

    QColor color() const;
    void setColor(const QColor &color);

    QDeclarativeMapLineProperties *border();

    bool contains(const QPointF &point) const Q_DECL_OVERRIDE;

Q_SIGNALS:
    void centerChanged(const QGeoCoordinate &center);
    void radiusChanged(qreal radius);
    void colorChanged(const QColor &color);

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) Q_DECL_OVERRIDE;

protected Q_SLOTS:
    virtual void updateMapItem() Q_DECL_OVERRIDE;
    void updateMapItemAssumeDirty();
    virtual void afterViewportChanged(const QGeoMapViewportChangeEvent &event) Q_DECL_OVERRIDE;

private:
    bool preserveCircleGeometry(QList<QGeoCoordinate> &path, const QGeoCoordinate &center,
                                qreal distance, QGeoCoordinate &leftBoundCoord);
    void updateCirclePathForRendering(QList<QGeoCoordinate> &path, const QGeoCoordinate &center,
                                      qreal distance);

private:
    QGeoCoordinate center_;
    QDeclarativeMapLineProperties border_;
    QColor color_;
    qreal radius_;
    QList<QGeoCoordinate> circlePath_;
    bool dirtyMaterial_;
    QGeoMapCircleGeometry geometry_;
    QGeoMapPolylineGeometry borderGeometry_;
    bool updatingGeometry_;
};

//////////////////////////////////////////////////////////////////////

QT_END_NAMESPACE

QML_DECLARE_TYPE(QDeclarativeCircleMapItem)

#endif /* QDECLARATIVECIRCLEMAPITEM_H */
