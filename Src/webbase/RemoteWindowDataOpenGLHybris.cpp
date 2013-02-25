/* @@@LICENSE
*
*      Copyright (c) 2010-2012 Hewlett-Packard Development Company, L.P.
*                    2013 Simon Busch <morphis@gravedo.de>
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* LICENSE@@@ */

#include <QDebug>

#include "Common.h"
#include "RemoteWindowDataOpenGLHybris.h"
#include <PIpcChannel.h>

#define MESSAGES_INTERNAL_FILE "SysMgrMessagesInternal.h"
#include <PIpcMessageMacros.h>

#include "Logging.h"
#include "qweboswindow.h"

RemoteWindowDataOpenGLHybris::RemoteWindowDataOpenGLHybris(int width, int height, bool hasAlpha)
	: m_width(width),
	  m_height(height),
	  m_hasAlpha(hasAlpha),
	  m_directRendering(false)
{
	qDebug() << __PRETTY_FUNCTION__ << "width =" << width << "height =" << height;

	m_glWidget = new QGLWidget();
	m_glWidget->setGeometry(QRect(0, 0, width, height));

	m_context = new QPainter();
}

RemoteWindowDataOpenGLHybris::~RemoteWindowDataOpenGLHybris()
{
	if (m_context)
		delete m_context;
}

void RemoteWindowDataOpenGLHybris::setKey(int key)
{
	m_key = key;

	QPlatformWindow *platformWindow = m_glWidget->platformWindow();
	QWebOSWindow *window = reinterpret_cast<QWebOSWindow*>(platformWindow);
	window->setWinId(m_key);
}

void RemoteWindowDataOpenGLHybris::flip()
{
	qDebug() << __PRETTY_FUNCTION__;
	int width = m_width;
	m_width = m_height;
	m_height = width;
}

QPainter* RemoteWindowDataOpenGLHybris::qtRenderingContext()
{
	qDebug() << __PRETTY_FUNCTION__;
	return m_context;
}

void RemoteWindowDataOpenGLHybris::beginPaint()
{
	qDebug() << __PRETTY_FUNCTION__;
	m_context->begin(m_glWidget);
}

void RemoteWindowDataOpenGLHybris::endPaint(bool preserveOnFlip, const QRect& rect, bool flipBuffers)
{
	qDebug() << __PRETTY_FUNCTION__;
	m_context->end();
}

void RemoteWindowDataOpenGLHybris::sendWindowUpdate(int x, int y, int w, int h)
{
	qDebug() << __PRETTY_FUNCTION__;

	m_channel->sendAsyncMessage(new ViewHost_UpdateWindowRegion(key(), x, y, w, h));
}

bool RemoteWindowDataOpenGLHybris::directRenderingAllowed(bool val)
{
	qDebug() << __PRETTY_FUNCTION__;
	return false;
}
	
bool RemoteWindowDataOpenGLHybris::needsClear() const
{
	qDebug() << __PRETTY_FUNCTION__;
	return false;
}

void RemoteWindowDataOpenGLHybris::setWindowMetaDataBuffer(PIpcBuffer *metaDataBuffer)
{
	qDebug() << __PRETTY_FUNCTION__;
	m_metaDataBuffer = metaDataBuffer;
}

void RemoteWindowDataOpenGLHybris::resize(int newWidth, int newHeight)
{
	qDebug() << __PRETTY_FUNCTION__ << "newWidth =" << newWidth << "newHeight =" << newHeight;

	m_glWidget->resize(newWidth, newHeight);
}

void RemoteWindowDataOpenGLHybris::clear()
{
	qDebug() << __PRETTY_FUNCTION__;
}
