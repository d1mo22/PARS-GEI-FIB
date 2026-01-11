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

#ifndef SCENE_H
#define SCENE_H

//#include <QtOpenGL/qgl.h>
#include "object.h"

using namespace std;

/*!
	\class Scene
	\brief The %Scene class represents a 3D scene as a flat collection of 3D objects.

    A scene is basically a vector of 3D objects. 
*/

class CORE_EXPORT Scene
{
public:
    /*! 
    Constructs an empty scene.
    */
    Scene();

    /*!
    Returns a constant reference (read-only) to the vector of objects forming the scene.
    */
    const vector<Object>& objects() const; 

    /*!
    Returns a reference to the vector of objects forming the scene. VAR
    */
    vector<Object>& objects(); 

    /*!
    Adds an object to the scene.
    */
    void addObject(Object &);

    /*!
    Clears the scene.
    */
    void clear();

    /*!
    If an object is selected, returns the index of that selected object (from 0 to number of objects - 1).
    Otherwise returns -1. 
    */
    int selectedObject() const;         

    /*! 
    Sets the selected object by indicating its index.
    Only one object can be seleted at any given time. 
    \param index is the position of the selected object in the vector of objects.
    */
    void setSelectedObject(int index);  

    /*!
    Recomputes the bounding box of the scene, as the bounding box of its objects.
    */
    void computeBoundingBox(); 

    /*! 
    Returns the value of the bounding box property. 
    This property is undefined unless boundingBox() has been called for this scene.
    */
    Box boundingBox() const;

private:
    vector<Object> pobjects;
    Box pboundingBox;
    int pselectedObject;
};

#endif

