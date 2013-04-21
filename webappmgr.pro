# @@@LICENSE
#
#      Copyright (c) 2010-2013 Hewlett-Packard Development Company, L.P.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# LICENSE@@@

TEMPLATE = app

CONFIG += qt

TARGET_TYPE =

ENV_BUILD_TYPE = $$(BUILD_TYPE)
!isEmpty(ENV_BUILD_TYPE) {
    CONFIG -= release debug
    CONFIG += $$ENV_BUILD_TYPE
}

# Prevent conflict with usage of "signal" in other libraries
CONFIG += no_keywords

CONFIG += link_pkgconfig
PKGCONFIG = glib-2.0 gthread-2.0 sqlite3 LunaSysMgrIpc

QT = core gui quick webkit network widgets webkitwidgets

QT_VERSION=$$[QT_VERSION]
contains(QT_VERSION, "^5.*") {
    message("Building for Qt5, enabling webkitwidgets")
} else {
    message("Building for Qt4, disabling webkitwidgets")
    QT -= webkitwidgets
}

VPATH += \
    ./Src \
    ./Src/base \
    ./Src/base/application \
    ./Src/base/hosts \
    ./Src/base/gesture \
    ./Src/base/windowdata \
    ./Src/base/settings \
    ./Src/core \
    ./Src/sound \
    ./Src/webbase \
    ./Src/lunaui \
    ./Src/lunaui/cards \
    ./Src/lunaui/notifications \
    ./Src/lunaui/emergency \
    ./Src/lunaui/dock \
    ./Src/minimalui \
    ./Src/lunaui/status-bar


INCLUDEPATH = $$VPATH

DEFINES += QT_WEBOS

# For shipping version of the code, as opposed to a development build. Set this to 1 late in the process...
DEFINES += SHIPPING_VERSION=0

# This allows the use of the % for faster QString concatentation
# See the QString documentation for more information
# DEFINES += QT_USE_FAST_CONCATENATION

# Uncomment this for all QString concatenations using +
# to go through the faster % instead.  Not sure what impact
# this has performance wise or behaviour wise.
# See the QString documentation for more information
# DEFINES += QT_USE_FAST_OPERATOR_PLUS

SOURCES += \
        AlertWebApp.cpp \
        ApplicationDescription.cpp \
        BackupManager.cpp \
        BannerMessageEventFactory.cpp \
        CardWebApp.cpp \
        DashboardWebApp.cpp \
        DeviceInfo.cpp \
        DockWebApp.cpp \
        EventReporter.cpp \
        KeyboardMapping.cpp \
        KeywordMap.cpp \
        Main.cpp \
        MemoryWatcher.cpp \
        PalmSystem.cpp \
        ProcessManager.cpp \
        RemoteWindowData.cpp \
        SyncTask.cpp \
        SysMgrWebBridge.cpp \
        WebAppBase.cpp \
        WebAppCache.cpp \
        WebAppDeferredUpdateHandler.cpp \
        WebAppFactory.cpp \
        WebAppFactoryMinimal.cpp \
        WebAppFactoryLuna.cpp \
        WebAppManager.cpp \
        WebKitEventListener.cpp \
        WindowedWebApp.cpp

HEADERS += \
        AlertWebApp.h \
        ApplicationDescription.h \
        BackupManager.h \
        BannerMessageEventFactory.h \
        CardWebApp.h \
        DashboardWebApp.h \
        Debug.h \
        DeviceInfo.h \
        DockWebApp.h \
        EventReporter.h \
        KeyboardMapping.h \
        KeywordMap.h \
        MemoryWatcher.h \
        NewContentIndicatorEventFactory.h \
        PalmSystem.h \
        ProcessBase.h \
        ProcessManager.h \
        RemoteWindowData.h \
        SharedGlobalProperties.h \
        SyncTask.h \
        SysMgrWebBridge.h \
        SystemUiController.h \
        WebAppBase.h \
        WebAppCache.h \
        WebAppDeferredUpdateHandler.h \
        WebAppFactory.h \
        WebAppFactoryMinimal.h \
        WebAppFactoryLuna.h \
        WebAppManager.h \
        WebKitEventListener.h \
        WindowedWebApp.h \
        WindowMetaData.h

QMAKE_CXXFLAGS += -fno-rtti -fno-exceptions -fvisibility=hidden -fvisibility-inlines-hidden -Wall -fpermissive
QMAKE_CXXFLAGS += -DFIX_FOR_QT 
#-DNO_WEBKIT_INIT

# Override the default (-Wall -W) from g++.conf mkspec (see linux-g++.conf)
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter -Wno-unused-variable -Wno-reorder -Wno-missing-field-initializers -Wno-extra

LIBS += -lcjson -lLunaSysMgrIpc -llunaservice -lpbnjson_cpp -lssl -lsqlite3 -lssl -lcrypto # -lgcov
LIBS += -lLunaSysMgrCommon

linux-g++ {
    include(desktop.pri)
} else:linux-g++-64 {
    include(desktop.pri)
} else:linux-qemux86-g++ {
	include(emulator.pri)
	QMAKE_CXXFLAGS += -fno-strict-aliasing
} else {
    ## First, check to see if this in an emulator build
    include(emulator.pri)
    contains (CONFIG_BUILD, webosemulator) {
        QMAKE_CXXFLAGS += -fno-strict-aliasing
    } else {
        ## Neither a desktop nor an emulator build, so must be a device
        include(device.pri)
    }
}


contains(CONFIG_BUILD, opengl) {
    QT += opengl
    DEFINES += HAVE_OPENGL
    DEFINES += P_BACKEND=P_BACKEND_SOFT

    contains(CONFIG_BUILD, texturesharing) {
        DEFINES += HAVE_TEXTURESHARING OPENGLCOMPOSITED
        SOURCES += \
            HostWindowDataOpenGLTextureShared.cpp \
            RemoteWindowDataSoftwareTextureShared.cpp \
            RemoteWindowDataSoftwareQt.cpp \
            RemoteWindowDataSoftwareOpenGLComposited.cpp
        HEADERS += \
            HostWindowDataOpenGLTextureShared.h \
            RemoteWindowDataSoftwareTextureShared.h \
            RemoteWindowDataSoftwareQt.h \
            RemoteWindowDataSoftwareOpenGLComposited.h \
            NAppWindow.h
                #LIBS += -lnapp -lnrwindow
    } else {

        contains(CONFIG_BUILD, openglcomposited) {
            DEFINES += OPENGLCOMPOSITED
            SOURCES += RemoteWindowDataSoftwareOpenGLComposited.cpp
            HEADERS += RemoteWindowDataSoftwareOpenGLComposited.h \
                       NAppWindow.h
        }

        contains(CONFIG_BUILD, hybris) {
            DEFINES += HAVE_HYBRIS Q_WS_QPA
            SOURCES += RemoteWindowDataOpenGLHybris.cpp
            HEADERS += RemoteWindowDataOpenGLHybris.h
        }

        SOURCES += \
            # HostWindowDataOpenGL.cpp \
            RemoteWindowDataSoftwareQt.cpp \
            RemoteWindowDataOpenGLQt.cpp
        HEADERS += \
            # HostWindowDataOpenGL.h \
            RemoteWindowDataSoftwareQt.h \
            RemoteWindowDataOpenGLQt.h
            # RemoteWindowDataOpenGL.h \
            # RemoteWindowDataOpenGL.cpp \
    }
}
else {
    DEFINES += P_BACKEND=P_BACKEND_SOFT
    SOURCES += RemoteWindowDataSoftwareQt.cpp
    HEADERS += RemoteWindowDataSoftwareQt.h
}

contains(CONFIG_BUILD, directrendering) {
    DEFINES += DIRECT_RENDERING=1
}

contains(CONFIG_BUILD, memchute) {
    LIBS += -lmemchute
    DEFINES += HAS_MEMCHUTE
}

DESTDIR = ./$${BUILD_TYPE}-$${MACHINE_NAME}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc

TARGET = WebAppMgr

# Comment these out to get verbose output
#QMAKE_CXX = @echo Compiling $(@)...; $$QMAKE_CXX
#QMAKE_LINK = @echo Linking $(@)...; $$QMAKE_LINK
#QMAKE_MOC = @echo Mocing $(@)...; $$QMAKE_MOC
