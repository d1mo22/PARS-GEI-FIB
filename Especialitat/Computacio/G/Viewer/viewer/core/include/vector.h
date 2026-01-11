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

#ifndef VECTOR_H
#define VECTOR_H

#include <QVector3D>
#include <iostream>


/*!
	\class Vector
	\brief The %Vector class represents a vector (x,y,z) in 3D space.
	
	For the sake of simplicity, Vector is implemented as a typedef of Qt's 
	<a href="http://qt-project.org/doc/qt-4.8/qvector3d.html"> QVector3D. </a>    

	Example of use:
    @code
        #include "point.h"
        #include "vector.h"

        // create two vectors
        Vector u = Vector(0.0, 0.0, 0.0);
        Vector v = Vector(1.0, 0.0, 0.0);
	
	    // get components
	    float x = u.x(); 
	    float y = u.y(); 
	    float z = u.z();

	    // set components
	    u.setX(2.0);
	    u.setY(4.0);
	    u.setZ(2.0);

        // get length
        float len = u.length();

        // normalize (in place)
        u.normalize();

        // get normalized copy
        v = u.normalized();

        // common operations
	    Vector w;
        w = u + v; // vector addition
        w = u - v; // vector substraction
        w = 2.0*u; // scalar multiplication
        float dot = dotProduct(u, v);  // dot product
        w = crossProduct(u, v);        // cross product
    @endcode
		
*/

typedef QVector3D Vector;

std::ostream& operator<< (std::ostream &os, const Vector &p);

#endif

