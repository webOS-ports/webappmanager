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

RemoteWindowDataOpenGLHybris::RemoteWindowDataOpenGLHybris(int width, int height, bool hasAlpha)
	: m_width(width),
	  m_height(height),
	  m_hasAlpha(hasAlpha)
{
	m_glWidget = new QGLWidget();
	m_glWidget->setGeometry(QRect(0, 0, width, height));
	m_glWidget->show();

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
	platformWindow->setWinId(m_key);
}

void RemoteWindowDataOpenGLHybris::flip()
{
	qDebug() << __PRETTY_FUNCTION__;
	int width = m_width;
	m_width = m_height;
	m_height = width;

	m_glWidget->resize(m_width, m_height);

	if (m_context) {
		delete m_context;
		m_context = new QPainter();
	}
}

QPainter* RemoteWindowDataOpenGLHybris::qtRenderingContext()
{
	return m_context;
}

void RemoteWindowDataOpenGLHybris::beginPaint()
{
	m_context->begin(m_glWidget);
}

void RemoteWindowDataOpenGLHybris::endPaint(bool preserveOnFlip, const QRect& rect, bool flipBuffers)
{
	m_context->end();
}

void RemoteWindowDataOpenGLHybris::sendWindowUpdate(int x, int y, int w, int h)
{
}

void RemoteWindowDataOpenGLHybris::setWindowMetaDataBuffer(PIpcBuffer *metaDataBuffer)
{
	m_metaDataBuffer = metaDataBuffer;
}

void RemoteWindowDataOpenGLHybris::resize(int newWidth, int newHeight)
{
	m_glWidget->resize(newWidth, newHeight);
}

void RemoteWindowDataOpenGLHybris::clear()
{
}
