//---------------------------------------------------------------------------//
//                        NewQMutex.cpp -
//  A QMutex-encapsulation needed due to some QMutex bugs
//                           -------------------
//  project              : SUMO - Simulation of Urban MObility
//  begin                : Sept 2002
//  copyright            : (C) 2002 by Daniel Krajzewicz
//  organisation         : IVF/DLR http://ivf.dlr.de
//  email                : Daniel.Krajzewicz@dlr.de
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
//---------------------------------------------------------------------------//
namespace
{
    const char rcsid[] =
    "$Id$";
}
// $Log$
// Revision 1.2  2003/02/07 10:52:29  dkrajzew
// updated
//
//


/* =========================================================================
 * included modules
 * ======================================================================= */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H
#include <qthread.h>
#include "NewQMutex.h"


NewQMutex::NewQMutex()
    : _mutex(new QMutex())
{
}


NewQMutex::~NewQMutex()
{
    delete _mutex;
}


void
NewQMutex::lock()
{
    _mutex->lock();
}


void
NewQMutex::unlock()
{
    _mutex->unlock();
}


bool
NewQMutex::locked ()
{
    return _mutex->locked();
}



/**************** DO NOT DEFINE ANYTHING AFTER THE INCLUDE *****************/
//#ifdef DISABLE_INLINE
//#include "NewQMutex.icc"
//#endif

// Local Variables:
// mode:C++
// End:


