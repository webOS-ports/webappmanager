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

#ifndef REMOTEWINDOWDATAOPENGLHYBRIS_H
#define REMOTEWINDOWDATAOPENGLHYBRIS_H

#include <QGLWidget>
#include <QMutex>

#include "Common.h"
#include "RemoteWindowData.h"

class PGContext;

class RemoteWindowDataOpenGLHybris : public RemoteWindowData
{
public:
	RemoteWindowDataOpenGLHybris(int width, int height, bool hasAlpha);
	virtual ~RemoteWindowDataOpenGLHybris();
	
	virtual void setKey(int key);

	virtual int key() const { return m_key; }
	virtual int width() const { return m_width; }
	virtual int height() const { return m_height; }
	virtual bool hasAlpha() const { return m_hasAlpha; }
	virtual bool needsClear() const { return false; }
	virtual void flip();

	virtual PGContext* renderingContext() { return 0; }
	virtual QPainter* qtRenderingContext();
	virtual void beginPaint();
	virtual void endPaint(bool preserveOnFlip, const QRect& rect, bool flipBuffers = true);
	virtual void sendWindowUpdate(int x, int y, int w, int h);

	virtual bool hasDirectRendering() const { return false; }
	virtual bool directRenderingAllowed(bool val) { return false; }

	virtual void setWindowMetaDataBuffer(PIpcBuffer *metaDataBuffer);
	virtual void resize(int newWidth, int newHeight);
	virtual void clear();

private:
	int m_key;
	int m_width;
	int m_height;
	bool m_hasAlpha;
	QPainter *m_context;
	QGLWidget *m_glWidget;

private:
	RemoteWindowDataOpenGLHybris(const RemoteWindowDataOpenGLHybris&);
	RemoteWindowDataOpenGLHybris& operator=(const RemoteWindowDataOpenGLHybris&);
};

#endif /* REMOTEWINDOWDATAOPENGLHYBRIS_H */
