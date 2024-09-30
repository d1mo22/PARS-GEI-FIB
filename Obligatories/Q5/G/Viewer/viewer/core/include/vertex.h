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

#ifndef VERTEX_H
#define VERTEX_H

#include "point.h"
#include "vector.h"

/*!
	\class Vertex
	\brief The %Vertex class represents a vertex with a single attribute (vertex coordinates).
*/

class CORE_EXPORT Vertex
{
public:
    /*!
    Constructs a vertex with the given (x,y,z) coordinates.
    */
    Vertex(const Point& coords);

    /*!
    Returns the (x,y,z) coordinates of the vertex.
    */
    Point coord() const;              

    /*!
    Sets the (x,y,z) coordinates of the vertex.
    */
    void setCoord(const Point& coord);

private:
    Point pcoord;		// vertex coordinates
};

#endif

