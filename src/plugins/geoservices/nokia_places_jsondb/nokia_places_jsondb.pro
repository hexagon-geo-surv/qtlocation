load(qt_build_config)

TARGET = qtgeoservices_nokia_places_jsondb
QT += location gui network

load(qt_plugin)

DESTDIR = $$QT.location.plugins/geoservices

HEADERS += \
            qgeoserviceproviderplugin_jsondb.h \
            qplacemanagerengine_jsondb.h \
            jsondb.h \
            matchreply.h \
            searchreply.h \
            detailsreply.h \
            unsupportedreplies.h \
            macro.h \
            idreply.h \
            icon.h \
            iconhandler.h \
            initreply.h

SOURCES += \
            qgeoserviceproviderplugin_jsondb.cpp \
            qplacemanagerengine_jsondb.cpp \
            jsondb.cpp \
            matchreply.cpp \
            searchreply.cpp \
            detailsreply.cpp \
            idreply.cpp \
            icon.cpp \
            iconhandler.cpp \
            initreply.cpp

INCLUDEPATH += $$QT.location.includes

QT += jsondb

target.path += $$[QT_INSTALL_PLUGINS]/geoservices
INSTALLS += target

OTHER_FILES += \
    nokia_plugin_jsondb.json
