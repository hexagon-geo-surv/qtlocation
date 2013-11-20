QT += quick-private network positioning-private location-private qml-private core-private gui-private

INCLUDEPATH += ../../location
INCLUDEPATH += ../../location/maps
INCLUDEPATH += ../../positioning
INCLUDEPATH *= $$PWD

LIBS += -L../../3rdparty/poly2tri -lpoly2tri

win32 {
    CONFIG(debug, debug|release) {
        LIBS += -L../../3rdparty/poly2tri/debug
    } else {
        LIBS += -L../../3rdparty/poly2tri/release
    }
}

qtHaveModule(3d):!no_qt3d {
    QT += 3d

    SOURCES += mapnode_qt3d.cpp

    HEADERS += mapnode_qt3d_p.h
} else {
    DEFINES += NO_QT3D_RENDERER
    SOURCES += mapnode_sg.cpp

    HEADERS += mapnode_sg_p.h
}



HEADERS += \
           qdeclarativegeomapitemview_p.h \
           qdeclarativegeomapmouseevent_p.h \
           qdeclarativegeomapmousearea_p.h \
           qdeclarativegeoserviceprovider_p.h \
           qdeclarativegeocodemodel_p.h \
           qdeclarativegeoroutemodel_p.h \
           qdeclarativegeoroute_p.h \
           qdeclarativegeoroutesegment_p.h \
           qdeclarativegeomaneuver_p.h \
           qdeclarativegeomap_p.h \
           qdeclarativegeomaptype_p.h \
           qdeclarativegeomapitembase_p.h \
           qdeclarativegeomapquickitem_p.h \
           qdeclarativecirclemapitem_p.h \
           qdeclarativerectanglemapitem_p.h \
           qdeclarativepolygonmapitem_p.h \
           qdeclarativepolylinemapitem_p.h \
           qdeclarativeroutemapitem_p.h \
           qgeomapitemgeometry_p.h \
           qdeclarativegeomapcopyrightsnotice_p.h \
           qdeclarativegeomapgesturearea_p.h \
           error_messages.h \
           locationvaluetypehelper_p.h

SOURCES += \
           location.cpp \
           qdeclarativegeomapitemview.cpp \
           qdeclarativegeomapmouseevent.cpp \
           qdeclarativegeomapmousearea.cpp \
           qdeclarativegeoserviceprovider.cpp \
           qdeclarativegeocodemodel.cpp \
           qdeclarativegeoroutemodel.cpp \
           qdeclarativegeoroute.cpp \
           qdeclarativegeoroutesegment.cpp \
           qdeclarativegeomaneuver.cpp \
           qdeclarativegeomap.cpp \
           qdeclarativegeomaptype.cpp \
           qdeclarativegeomapitembase.cpp \
           qdeclarativegeomapquickitem.cpp \
           qdeclarativecirclemapitem.cpp \
           qdeclarativerectanglemapitem.cpp \
           qdeclarativepolygonmapitem.cpp \
           qdeclarativepolylinemapitem.cpp \
           qdeclarativeroutemapitem.cpp \
           qgeomapitemgeometry.cpp \
           qdeclarativegeomapcopyrightsnotice.cpp \
           qdeclarativegeomapgesturearea.cpp \
           error_messages.cpp \
           locationvaluetypehelper.cpp

include(declarativeplaces/declarativeplaces.pri)

load(qml_plugin)

OTHER_FILES += \
    plugin.json \
    qmldir
