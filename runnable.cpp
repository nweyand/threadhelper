/*
 * runnable.cpp
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

#include "runnable.h"

Runnable::Runnable(QObject *parent) :
    QObject(parent),
    m_bValid( false )
{

}

void Runnable::setupFinished()
{
	m_bValid = true;
}
