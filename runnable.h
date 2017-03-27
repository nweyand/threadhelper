/*
 * runnable.h
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
#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <QObject>

/**
 * @brief The Runnable class represents objects that may be used with the Thread class. Subclass it
 * in order to create other classes that work together with Thread.
 *
 * Attention: Note that you may not allocate memory using “new” within the constructor of your
 * subclasses if you whish for your complete subclass to live in the target thread.  It is
 * considered best practice to use the setup() slot for initializing all kinds of variables of your
 * subclass and leave them uninitialized up to that point.
 */
class Runnable : public QObject
{
	Q_OBJECT
public:
	/**
	 * @brief Runnable constructs a new runnable object.
	 * @param parent
	 */
	explicit Runnable(QObject *parent = nullptr);

	/**
	 * @brief valid
	 * @return <code>true</code> if <code>setup()</code> has been called, <code>false</code>
	 * otherwise.
	 */
	inline bool valid() const { return m_bValid; }

protected:
	/**
	 * @brief setupFinished must be called by child classes before returning from setup.
	 */
	inline void setupFinished() { m_bValid = true; }

	/**
	 * @brief shutDownRequested should be called repeatedly by tasks requiring lengthy continuous
	 * work to check whether aborting the work is desired by the thread.
	 * Note that the runnable is expected to emit <code>finished()</code> after finishing the abort.
	 * @return <code>true</code> if a shutdown has been requested, <code>false</code> otherwise.
	 */
	inline bool shutDownRequested() const { return m_bShutDownFlag; }

private:
	bool m_bValid;
	bool m_bShutDownFlag;

	/**
	 * @brief requestShutDown is to be called by Thread only. :)
	 */
	inline void requestShutDown() { m_bShutDownFlag = true; }

signals:
	/**
	 * @brief finished must be emitted when the has finished its work and is ready to be deleted.
	 * Note that it is guaranteed for this signal to be emitted only once – therefore child classes
	 * must use the slot <code>finish()</code> to emit this signal and not emit it directly.
	 * The only method that is guaranteed to be entered from the Thread’s event loop after emitting
	 * this signal is <code>cleanup()</code>
	 */
	void finished();

protected slots:
	/**
	 * @brief finish will be called via <code>Qt::QueuedConnection<code> by Thread on recieving a
	 * shutdown request. Call it yourself if your Runnable has finished its work and whishes to be
	 * deleted. Reimplement this if you need to do something on shutdown that you don’t want to put
	 * into cleanup(). Note that your reimplementation must always guarantee for
	 * <code>finished()</code> to be emitted no more than once.
	 */
	void finish();

	/**
	 * @brief setup is the place to initialize variables etc.
	 */
	virtual void setup()   = 0;

	/**
	 * @brief cleanup is the spot where all the cleanup work that should not go into the destructor
	 * takes place. Note: This happens after <code>finished()</code> has been emitted.
	 */
	virtual void cleanup() = 0;

	friend class Thread;
};

#endif // RUNNABLE_H
