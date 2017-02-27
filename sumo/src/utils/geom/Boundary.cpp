/****************************************************************************/
/// @file    Boundary.cpp
/// @author  Daniel Krajzewicz
/// @author  Jakob Erdmann
/// @author  Michael Behrisch
/// @date    Sept 2002
/// @version $Id$
///
// A class that stores the 2D geometrical boundary
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
// Copyright (C) 2001-2017 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This file is part of SUMO.
//   SUMO is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif
#include <utility>

#include "GeomHelper.h"
#include "Boundary.h"
#include "PositionVector.h"
#include "Position.h"

#ifdef CHECK_MEMORY_LEAKS
#include <foreign/nvwa/debug_new.h>
#endif // CHECK_MEMORY_LEAKS


// ===========================================================================
// method definitions
// ===========================================================================
Boundary::Boundary()
    : myXmin(10000000000.0), myXmax(-10000000000.0),
      myYmin(10000000000.0), myYmax(-10000000000.0),
      myZmin(10000000000.0), myZmax(-10000000000.0),
      myWasInitialised(false) {}


Boundary::Boundary(double x1, double y1, double x2, double y2)
    : myXmin(10000000000.0), myXmax(-10000000000.0),
      myYmin(10000000000.0), myYmax(-10000000000.0),
      myZmin(10000000000.0), myZmax(-10000000000.0),
      myWasInitialised(false) {
    add(x1, y1);
    add(x2, y2);
}


Boundary::Boundary(double x1, double y1, double z1, double x2, double y2, double z2)
    : myXmin(10000000000.0), myXmax(-10000000000.0),
      myYmin(10000000000.0), myYmax(-10000000000.0),
      myZmin(10000000000.0), myZmax(-10000000000.0),
      myWasInitialised(false) {
    add(x1, y1, z1);
    add(x2, y2, z2);
}


Boundary::~Boundary() {}


void
Boundary::reset() {
    myXmin = 10000000000.0;
    myXmax = -10000000000.0;
    myYmin = 10000000000.0;
    myYmax = -10000000000.0;
    myZmin = 10000000000.0;
    myZmax = -10000000000.0;
    myWasInitialised = false;
}


void
Boundary::add(double x, double y, double z) {
    if (!myWasInitialised) {
        myYmin = y;
        myYmax = y;
        myXmin = x;
        myXmax = x;
        myZmin = z;
        myZmax = z;
    } else {
        myXmin = myXmin < x ? myXmin : x;
        myXmax = myXmax > x ? myXmax : x;
        myYmin = myYmin < y ? myYmin : y;
        myYmax = myYmax > y ? myYmax : y;
        myZmin = myZmin < z ? myZmin : z;
        myZmax = myZmax > z ? myZmax : z;
    }
    myWasInitialised = true;
}


void
Boundary::add(const Position& p) {
    add(p.x(), p.y(), p.z());
}


void
Boundary::add(const Boundary& p) {
    add(p.xmin(), p.ymin(), p.zmin());
    add(p.xmax(), p.ymax(), p.zmax());
}


Position
Boundary::getCenter() const {
    return Position((myXmin + myXmax) / (double) 2.0, (myYmin + myYmax) / (double) 2.0, (myZmin + myZmax) / (double) 2.0);
}


double
Boundary::xmin() const {
    return myXmin;
}


double
Boundary::xmax() const {
    return myXmax;
}


double
Boundary::ymin() const {
    return myYmin;
}


double
Boundary::ymax() const {
    return myYmax;
}


double
Boundary::zmin() const {
    return myZmin;
}


double
Boundary::zmax() const {
    return myZmax;
}


double
Boundary::getWidth() const {
    return myXmax - myXmin;
}


double
Boundary::getHeight() const {
    return myYmax - myYmin;
}


double
Boundary::getZRange() const {
    return myZmax - myZmin;
}


bool
Boundary::around(const Position& p, double offset) const {
    return
        (p.x() <= myXmax + offset && p.x() >= myXmin - offset) &&
        (p.y() <= myYmax + offset && p.y() >= myYmin - offset) &&
        (p.z() <= myZmax + offset && p.z() >= myZmin - offset);
}


bool
Boundary::overlapsWith(const AbstractPoly& p, double offset) const {
    if (
        // check whether one of my points lies within the given poly
        partialWithin(p, offset) ||
        // check whether the polygon lies within me
        p.partialWithin(*this, offset)) {
        return true;
    }
    // check whether the bounderies cross
    return
        p.crosses(Position(myXmax + offset, myYmax + offset), Position(myXmin - offset, myYmax + offset))
        ||
        p.crosses(Position(myXmin - offset, myYmax + offset), Position(myXmin - offset, myYmin - offset))
        ||
        p.crosses(Position(myXmin - offset, myYmin - offset), Position(myXmax + offset, myYmin - offset))
        ||
        p.crosses(Position(myXmax + offset, myYmin - offset), Position(myXmax + offset, myYmax + offset));
}


bool
Boundary::crosses(const Position& p1, const Position& p2) const {
    const PositionVector line(p1, p2);
    return
        line.intersects(Position(myXmax, myYmax), Position(myXmin, myYmax))
        ||
        line.intersects(Position(myXmin, myYmax), Position(myXmin, myYmin))
        ||
        line.intersects(Position(myXmin, myYmin), Position(myXmax, myYmin))
        ||
        line.intersects(Position(myXmax, myYmin), Position(myXmax, myYmax));
}


bool
Boundary::partialWithin(const AbstractPoly& poly, double offset) const {
    return
        poly.around(Position(myXmax, myYmax), offset) ||
        poly.around(Position(myXmin, myYmax), offset) ||
        poly.around(Position(myXmax, myYmin), offset) ||
        poly.around(Position(myXmin, myYmin), offset);
}


Boundary&
Boundary::grow(double by) {
    myXmax += by;
    myYmax += by;
    myXmin -= by;
    myYmin -= by;
    return *this;
}

void
Boundary::growWidth(double by) {
    myXmin -= by;
    myXmax += by;
}


void
Boundary::growHeight(double by) {
    myYmin -= by;
    myYmax += by;
}

void
Boundary::flipY() {
    myYmin *= -1.0;
    myYmax *= -1.0;
    double tmp = myYmin;
    myYmin = myYmax;
    myYmax = tmp;
}



std::ostream&
operator<<(std::ostream& os, const Boundary& b) {
    os << b.myXmin << "," << b.myYmin << "," << b.myXmax << "," << b.myYmax;
    return os;
}


void
Boundary::set(double xmin, double ymin, double xmax, double ymax) {
    myXmin = xmin;
    myYmin = ymin;
    myXmax = xmax;
    myYmax = ymax;
}


void
Boundary::moveby(double x, double y, double z) {
    myXmin += x;
    myYmin += y;
    myZmin += z;
    myXmax += x;
    myYmax += y;
    myZmax += z;
}



/****************************************************************************/

