/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtLocation module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
** This file is part of the Ovi services plugin for the Maps and
** Navigation API.  The use of these services, whether by use of the
** plugin or by other means, is governed by the terms and conditions
** described by the file OVI_SERVICES_TERMS_AND_CONDITIONS.txt in
** this package, located in the directory containing the Ovi services
** plugin source code.
**
****************************************************************************/

#include "qgeoserviceproviderplugin_nokia.h"

#include "qgeocodingmanagerengine_nokia.h"
#include "qgeoroutingmanagerengine_nokia.h"
#include "qgeotiledmappingmanagerengine_nokia.h"
#include "qplacemanagerengine_nokiav1.h"
#include "qplacemanagerengine_nokiav2.h"
#include "qgeointrinsicnetworkaccessmanager.h"

#include <QtPlugin>
#include <QNetworkProxy>

QT_BEGIN_NAMESPACE


QGeoServiceProviderFactoryNokia::QGeoServiceProviderFactoryNokia()
    : m_informedAboutUsageTerms(false)
{}

QGeoServiceProviderFactoryNokia::~QGeoServiceProviderFactoryNokia() {}

QGeocodingManagerEngine* QGeoServiceProviderFactoryNokia::createGeocodingManagerEngine(const QMap<QString, QVariant> &parameters,
        QGeoServiceProvider::Error *error,
        QString *errorString) const
{
    informOnceAboutUsageTermsIfNecessary(parameters);

    QGeoIntrinsicNetworkAccessManager* networkManager = new QGeoIntrinsicNetworkAccessManager();
    networkManager->configure(parameters);

    return new QGeocodingManagerEngineNokia(networkManager, parameters, error, errorString);
}

QGeoMappingManagerEngine* QGeoServiceProviderFactoryNokia::createMappingManagerEngine(const QMap<QString, QVariant> &parameters,
        QGeoServiceProvider::Error *error,
        QString *errorString) const
{
    informOnceAboutUsageTermsIfNecessary(parameters);

    QGeoIntrinsicNetworkAccessManager* networkManager = new QGeoIntrinsicNetworkAccessManager();
    networkManager->setCustomProxyToken(QStringLiteral("mapping.proxy"));
    networkManager->configure(parameters);

    return new QGeoTiledMappingManagerEngineNokia(networkManager, parameters, error, errorString);
}

QGeoRoutingManagerEngine* QGeoServiceProviderFactoryNokia::createRoutingManagerEngine(const QMap<QString, QVariant> &parameters,
        QGeoServiceProvider::Error *error,
        QString *errorString) const
{
    informOnceAboutUsageTermsIfNecessary(parameters);

    QGeoIntrinsicNetworkAccessManager* networkManager = new QGeoIntrinsicNetworkAccessManager();
    networkManager->setCustomProxyToken(QStringLiteral("routing.proxy"));
    networkManager->configure(parameters);

    return new QGeoRoutingManagerEngineNokia(networkManager, parameters, error, errorString);
}

QPlaceManagerEngine *QGeoServiceProviderFactoryNokia::createPlaceManagerEngine(const QMap<QString, QVariant> &parameters,
                                                                               QGeoServiceProvider::Error *error,
                                                                               QString *errorString) const
{
    informOnceAboutUsageTermsIfNecessary(parameters);

    QGeoIntrinsicNetworkAccessManager* networkManager = new QGeoIntrinsicNetworkAccessManager();
    networkManager->setCustomProxyToken(QStringLiteral("places.proxy"));
    networkManager->configure(parameters);

    switch (parameters.value(QLatin1String("places.api_version"), 2).toUInt()) {
    case 1:
        return new QPlaceManagerEngineNokiaV1(networkManager, parameters, error, errorString);
    case 2:
        return new QPlaceManagerEngineNokiaV2(networkManager, parameters, error, errorString);
    }

    return 0;
}

void QGeoServiceProviderFactoryNokia::informOnceAboutUsageTermsIfNecessary(
        const QMap<QString, QVariant> &parameters) const
{
    if (m_informedAboutUsageTerms)
        return;

    const QString appId = parameters.value(QLatin1String("app_id")).toString();
    const QString token = parameters.value(QLatin1String("token")).toString();

    if (!isValidParameter(appId) || !isValidParameter(token)) {
        m_informedAboutUsageTerms = true;
        qWarning() << "****************************************************************************";
        qWarning() << "* Qt Location requires usage of app_id and token parameters obtained from: *";
        qWarning() << "* https://api.developer.nokia.com/                                         *";
        qWarning() << "****************************************************************************";
    }
}

bool QGeoServiceProviderFactoryNokia::isValidParameter(const QString &param)
{
    if (param.isEmpty())
        return false;

    if (param.length() > 512)
        return false;

    foreach (QChar c, param) {
        if (!c.isLetterOrNumber() && c.toAscii() != '%' && c.toAscii() != '-' &&
            c.toAscii() != '+' && c.toAscii() != '_') {
            return false;
        }
    }

    return true;
}

const QString QGeoServiceProviderFactoryNokia::defaultToken("152022572f0e44e07489c35cd46fa246");
const QString QGeoServiceProviderFactoryNokia::defaultReferer("qtlocationapi");

QT_END_NAMESPACE
