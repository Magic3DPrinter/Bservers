#-------------------------------------------------
#
# Project created by QtCreator 2015-11-20T11:37:51
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReBeserver
TEMPLATE = app


SOURCES += main.cpp\
        bserverwindow.cpp \
    ImageProcesser/PrintPos/mgraphicsscene.cpp \
    ImageProcesser/PrintPos/mpixmapitem.cpp \
    ImageProcesser/PrintPos/MyItem.cpp \
    ImageProcesser/PrintPos/widget.cpp \
    ImageProcesser/SliceEngine/clipper/clipper.cpp \
    ImageProcesser/SliceEngine/modelFile/modelFile.cpp \
    ImageProcesser/SliceEngine/utils/gettime.cpp \
    ImageProcesser/SliceEngine/utils/logoutput.cpp \
    ImageProcesser/SliceEngine/utils/socket.cpp \
    ImageProcesser/SliceEngine/bridge.cpp \
    ImageProcesser/SliceEngine/comb.cpp \
    ImageProcesser/SliceEngine/gcodeExport.cpp \
    ImageProcesser/SliceEngine/infill.cpp \
    ImageProcesser/SliceEngine/inset.cpp \
    ImageProcesser/SliceEngine/layerPart.cpp \
    ImageProcesser/SliceEngine/optimizedModel.cpp \
    ImageProcesser/SliceEngine/pathOrderOptimizer.cpp \
    ImageProcesser/SliceEngine/polygonOptimizer.cpp \
    ImageProcesser/SliceEngine/raft.cpp \
    ImageProcesser/SliceEngine/settings.cpp \
    ImageProcesser/SliceEngine/skin.cpp \
    ImageProcesser/SliceEngine/skirt.cpp \
    ImageProcesser/SliceEngine/slicer.cpp \
    ImageProcesser/SliceEngine/support.cpp \
    ImageProcesser/SliceEngine/timeEstimate.cpp \
    ImageProcesser/fontdialog.cpp \
    ImageProcesser/imageprinter.cpp \
    PrinterPanel/Plot/qcustomplot.cpp \
    PrinterPanel/Uart/qextserialbase.cpp \
    PrinterPanel/Uart/qextserialenumerator.cpp \
    PrinterPanel/Uart/qextserialport.cpp \
    PrinterPanel/Uart/win_qextserialport.cpp \
    PrinterPanel/controlpanel.cpp \
    PrinterPanel/printthread.cpp \
    PrinterPanel/readgcode.cpp \
    PrinterPanel/settingdialog.cpp \
    ImageProcesser/pgraphicsscene.cpp

HEADERS  += bserverwindow.h \
    ImageProcesser/PrintPos/mgraphicsscene.h \
    ImageProcesser/PrintPos/mpixmapitem.h \
    ImageProcesser/PrintPos/MyItem.h \
    ImageProcesser/PrintPos/widget.h \
    ImageProcesser/SliceEngine/clipper/clipper.hpp \
    ImageProcesser/SliceEngine/modelFile/modelFile.h \
    ImageProcesser/SliceEngine/utils/floatpoint.h \
    ImageProcesser/SliceEngine/utils/gettime.h \
    ImageProcesser/SliceEngine/utils/intpoint.h \
    ImageProcesser/SliceEngine/utils/logoutput.h \
    ImageProcesser/SliceEngine/utils/polygon.h \
    ImageProcesser/SliceEngine/utils/polygondebug.h \
    ImageProcesser/SliceEngine/utils/socket.h \
    ImageProcesser/SliceEngine/bridge.h \
    ImageProcesser/SliceEngine/comb.h \
    ImageProcesser/SliceEngine/fffProcessor.h \
    ImageProcesser/SliceEngine/gcodeExport.h \
    ImageProcesser/SliceEngine/includes.h \
    ImageProcesser/SliceEngine/infill.h \
    ImageProcesser/SliceEngine/inset.h \
    ImageProcesser/SliceEngine/layerPart.h \
    ImageProcesser/SliceEngine/multiVolumes.h \
    ImageProcesser/SliceEngine/optimizedModel.h \
    ImageProcesser/SliceEngine/pathOrderOptimizer.h \
    ImageProcesser/SliceEngine/polygonOptimizer.h \
    ImageProcesser/SliceEngine/raft.h \
    ImageProcesser/SliceEngine/settings.h \
    ImageProcesser/SliceEngine/skin.h \
    ImageProcesser/SliceEngine/skirt.h \
    ImageProcesser/SliceEngine/sliceDataStorage.h \
    ImageProcesser/SliceEngine/slicer.h \
    ImageProcesser/SliceEngine/support.h \
    ImageProcesser/SliceEngine/timeEstimate.h \
    ImageProcesser/fontdialog.h \
    ImageProcesser/imageprinter.h \
    PrinterPanel/Plot/qcustomplot.h \
    PrinterPanel/Uart/qextserialbase.h \
    PrinterPanel/Uart/qextserialenumerator.h \
    PrinterPanel/Uart/qextserialport.h \
    PrinterPanel/Uart/win_qextserialport.h \
    PrinterPanel/controlpanel.h \
    PrinterPanel/printthread.h \
    PrinterPanel/readgcode.h \
    PrinterPanel/settingdialog.h \
    ImageProcesser/pgraphicsscene.h

FORMS    += bserverwindow.ui \
    ImageProcesser/PrintPos/widget.ui \
    ImageProcesser/fontdialog.ui \
    ImageProcesser/imageprinter.ui \
    PrinterPanel/controlpanel.ui \
    PrinterPanel/settingdialog.ui

#here is the opencv libary
INCLUDEPATH+= C:\opencv2.4.9\include\opencv\
              C:\opencv2.4.9\include\opencv2\
              C:\opencv2.4.9\include

LIBS+= C:\opencv2.4.9\x64\mingw\lib\libopencv_calib3d249.dll.a\
        C:\opencv2.4.9\x64\mingw\lib\libopencv_contrib249.dll.a\
        C:\opencv2.4.9\x64\mingw\lib\libopencv_core249.dll.a\
        C:\opencv2.4.9\x64\mingw\lib\libopencv_features2d249.dll.a\
        C:\opencv2.4.9\x64\mingw\lib\libopencv_flann249.dll.a\
        C:\opencv2.4.9\x64\mingw\lib\libopencv_gpu249.dll.a\
        C:\opencv2.4.9\x64\mingw\lib\libopencv_highgui249.dll.a\
        C:\opencv2.4.9\x64\mingw\lib\libopencv_imgproc249.dll.a\
        C:\opencv2.4.9\x64\mingw\lib\libopencv_legacy249.dll.a\
        C:\opencv2.4.9\x64\mingw\lib\libopencv_ml249.dll.a\
        C:\opencv2.4.9\x64\mingw\lib\libopencv_objdetect249.dll.a\
        C:\opencv2.4.9\x64\mingw\lib\libopencv_video249.dll.a

