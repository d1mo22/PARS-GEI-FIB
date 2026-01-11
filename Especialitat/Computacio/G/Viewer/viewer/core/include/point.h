// GLarena, a plugin based platform to teach OpenGL programming
// © Copyright 2012-2018, ViRVIG Research Group, UPC, https://www.virvig.eu
// 
// This file is part of GLarena
//
// GLarena is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef POINT_H
#define POINT_H

#include "core_global.h"
#include <QVector3D>
#include <iostream>

/*!
	\class Point
	\brief The %Point class represents a point (x,y,z) in 3D space.
	
	For the sake of simplicity, Point is implemented as a typedef of Qt's 
	<a href="http://qt-project.org/doc/qt-4.8/qvector3d.html"> QVector3D. </a>    

	Example of use:
    @code
        #include "point.h"
        #include "vector.h"

        // create two points
        Point p = Point(0.0, 0.0, 0.0);
        Point q = Point(1.0, 0.0, 0.0);
	
	    // get coordinate values
	    float x = p.x(); 
	    float y = p.y(); 
	    float z = p.z();

	    // set coordinate values
	    p.setX(2.0);
	    p.setY(4.0);
	    p.setZ(2.0);

        // common operations
	    Vector v = p - q; // point substraction (returns a Vector)
	    Point r = 0.4*p + 0.6*q; // barycentric combination
    @endcode
		
*/

typedef QVector3D Point;

std::ostream& operator<< (std::ostream &os, const Point &p);

#endif
