/***************************************************************************
                          MSNoLogicJunction.cpp
                             -------------------
    begin                : Thu, 06 Jun 2002
    copyright            : (C) 2001 by DLR/IVF http://ivf.dlr.de/
    author               : Daniel Krajzewicz
    email                : Daniel.Krajzewicz@dlr.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

namespace
{
    const char rcsid[] =
    "$Id$";
}

// $Log$
// Revision 1.3  2003/02/07 10:41:50  dkrajzew
// updated
//
// Revision 1.2  2002/10/16 16:42:29  dkrajzew
// complete deletion within destructors implemented; clear-operator added for container; global file include; junction extended by position information (should be revalidated later)
//
// Revision 1.1  2002/10/16 14:48:26  dkrajzew
// ROOT/sumo moved to ROOT/src
//
// Revision 1.3  2002/08/06 15:50:16  roessel
// SetFirstVehiclesRequests implemented.
//
// Revision 1.2  2002/06/18 10:59:53  croessel
// Removed some ^M.
//
// Revision 1.1  2002/06/07 14:45:17  dkrajzew
// Added MSNoLogicJunction ,,pro forma,,. The code may compile but the
// class has no real functionality...
//
//

/* =========================================================================
 * included modules
 * ======================================================================= */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include "MSNoLogicJunction.h"
#include "MSLane.h"
//#include "MSJunctionLogic.h"
#include <algorithm>
#include <cassert>
#include <cmath>


/* =========================================================================
 * used namespaces
 * ======================================================================= */
using namespace std;


/* =========================================================================
 * static member definitions
 * ======================================================================= */
std::bitset<64> MSNoLogicJunction::myDump((unsigned long) 0xffffffff);



/* =========================================================================
 * method definitions
 * ======================================================================= */
MSNoLogicJunction::MSNoLogicJunction( string id, double x, double y,
				      InLaneCont* in) :
    MSJunction( id, x, y ),
    myInLanes( in )
{
}


bool
MSNoLogicJunction::clearRequests()
{
    return true;
}

//-------------------------------------------------------------------------//

MSNoLogicJunction::~MSNoLogicJunction()
{
}

//-------------------------------------------------------------------------//

void
MSNoLogicJunction::postloadInit()
{
    for(InLaneCont::iterator i=myInLanes->begin(); i!=myInLanes->end(); i++) {
        const MSLinkCont &links = (*i)->getLinkCont();
        for(MSLinkCont::const_iterator j=links.begin(); j!=links.end(); j++) {
            (*j)->setRequestInformation(&myDump, 0,
                &myDump, 0, myDump);
        }
    }
}


/**************** DO NOT DEFINE ANYTHING AFTER THE INCLUDE *****************/
//#ifdef DISABLE_INLINE
//#include "MSNoLogicJunction.icc"
//#endif

// Local Variables:
// mode:C++
// End:
