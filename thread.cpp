/*
 * thread.cpp
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

#include "thread.h"

Thread::Thread( QObject* parent ) :
    QThread( parent ),
    m_pRunnable( nullptr )
{
}

void Thread::start( QString sThreadName, Runnable* pRunnable, QThread::Priority p )
{
	QThread::setObjectName( sThreadName );

	m_pRunnable = pRunnable;
	if ( m_pRunnable )
	{
		m_pRunnable->moveToThread( this );
	}

	// make sure to free Runnable’s memory later
	connect( m_pRunnable, &Runnable::finished,
	         m_pRunnable, &Runnable::deleteLater, Qt::UniqueConnection );

	QThread::start( p );
}

void Thread::run()
{
	// TODO 1) Use Function pointer syntax for invoking methods once this is available in Qt
	// TODO 2) Add some kind of logging for debugging purposes

	if ( m_pRunnable )
	{
		QMetaObject::invokeMethod( m_pRunnable, "setup", Qt::DirectConnection );
	}

	// start event loop
	const int returnValue = QThread::exec();

	// maybe use it later
	Q_UNUSED( returnValue );

	if ( m_pRunnable )
	{
		QMetaObject::invokeMethod( m_pRunnable, "cleanup", Qt::DirectConnection );
	}
}

