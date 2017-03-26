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
	 * @return <code>true</code> if setup() has been called, <code>false</code> otherwise.
	 */
	inline bool valid() const { return m_bValid; }

protected:
	/**
	 * @brief setupFinished must be called by child classes before returning from setup.
	 */
	void setupFinished();

private:
	bool m_bValid;

signals:
	/**
	 * @brief finished must be emitted when the has finished its work and is ready to be deleted.
	 * Usually, this would be at the end of cleanup() if the Runnable is not to be recycled.
	 */
	void finished();

private slots:
	/**
	 * @brief setup is the place to initialize variables etc.
	 */
	virtual void setup()   = 0;

	/**
	 * @brief cleanup is the spot where all the cleanup work that should not go into the destructor
	 * takes place.
	 */
	virtual void cleanup() = 0;

	friend class Thread;
};

#endif // RUNNABLE_H
