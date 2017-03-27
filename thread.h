/*
 * thread.h
 *
 * Copyright © NWeyand 2017.
 * This file is part of the threadhelper library.
 * See https://github.com/nweyand/threadhelper for more information and related downloads.
 *
 * The threadhelper library is free software; this file may be used under the terms of the GNU
 * General Public License version 3.0 or later or later as published by the Free Software Foundation
 * and appearing in the file LICENSE included in the packaging of this file.
 *
 * The threadhelper library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 * Please review the following information to ensure the GNU General Public License version 3.0
 * requirements will be met:
 * http://www.gnu.org/copyleft/gpl.html.
 *
 * You should have received a copy of the GNU General Public License version 3.0 along with the
 * threadhelper library; if not, write to the Free Software Foundation, Inc., 59 Temple Place,
 * Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef THREADHELPER_HS
#define THREADHELPER_H

#include <QThread>

#include "Runnable.h"

/**
 * @brief The Thread class works together with the Runnable class to create a Thread that maintains
 * a Runnable object. It assures that Runnable’s setup() and cleanup() slots are called and that
 * the Runnable object is deleted after it has emitted its finished() signal.
 */
class Thread: public QThread
{
	Q_OBJECT

public:
	/**
	 * @brief Thread creates a new Thread wrapper object.
	 * @param parent allows to specify a parent to handle memory cleanup if this is desired.
	 */
	Thread( QObject* parent = nullptr );

	/**
	 * @brief name allows access to the thread name.
	 * @return A QString representation of the thread’s name.
	 */
	inline QString name() const { return objectName(); }

	/**
	 * @brief start         allows to start the thread using a specified name and a Runnable object
	 * to be managed.
	 * @param sThreadName   The name of the Thread.
	 * @param pRunnable     The Runnable object to be managed. This may be <code>NULL</code> and
	 * there may (of course) be other objects residing in the thread.
	 * @param p             The process priority. See the documentation of QThread for more details.
	 */
	void start( QString sThreadName, Runnable* pRunnable, QThread::Priority p = InheritPriority );

public slots:
	/**
	 * @brief requestShutDown allows the caller to request a thread to stop operation in a
	 * (self-)controlled manner.
	 */
	void requestShutDown();

protected:
	void run();

private:
	Runnable* m_pRunnable;
};

#endif // THREADHELPER_H
