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

#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "box.h"
#include "face.h"
//#include <QtOpenGL/qgl.h>

using namespace std;

/*!
	\class Object
	\brief The %Object class represents a 3D object. 

    Each object consists of a collection of vertices and a collection of faces. 
    Objects also store a bounding box. 
*/

class CORE_EXPORT Object
{
public:
    /*!
    Constructs an empty object.
    \param name is the name of the new object. 
    */
    Object(std::string name);

    /*!
     Imports a Wavefront OBJ file as a single object. 
     Previous faces and vertices, if any, are deleted.

     This is a minimalistic parser. It can only handle polyhedral models, 
     and then with limitations:
     * faces with more than three sides are assumed to be convex, and
       are triangulated as a fan of triangles. This will give wrong
       results if a face is not convex.
     * negative indices are not supported
     * information is expected to be homogeneous (if one face has
     texture coordinates, for example, then every face does).
     * it does not understand grouping or multi-object files
     * for now, we do not use materials
    */
    void readObj(string filename); 

    /*!
    Returns the value of the bounding box property. 
    This property is undefined unless computeBoundingBox() has been called.
    */
    Box boundingBox() const;  
    
    /*!
    Returns a constant reference (read-only) to the vector of faces of the object. 
    */
    const vector<Face>& faces() const;  

    /*!
    Returns a constant reference (read-only) to the vector of vertices of the object. 
    */
    const vector<Vertex>& vertices() const;

    /*!
    Returns a reference to the vector of vertices of the object. 
    If vertices are modified, computeNormals() and computeBoundingBox() methods should 
    be called to update per-face normals and the object's bounding box. 
    */
    vector<Vertex>& vertices();  

    /*!
    Returns a reference to the vector of vertex normals of the object. 
    */
    const vector<Vector>& vertNormals() const;  

    /*!
    Returns a reference to the vector of texture coordinates of the object. 
    */
    const vector<std::pair<float, float> >& vertTexCoords() const;  

    
    /*!
    Recomputes per-face normals (for all faces of the object).
    */
    void computeNormals();     

    /*!
    Recomputes the object bounding box.
    */
    void computeBoundingBox(); 

    /*!
    Applies geometric transform to all vertices; updates normals & bounding box.
    */
    void applyGT(const QMatrix4x4& mat);

private:
    void parseVOnly(std::stringstream & ss, std::string & block);
    void parseVN(std::stringstream & ss, std::string & block);
    void parseVT(std::stringstream & ss, std::string & block);
    void parseVTN(std::stringstream & ss, std::string & block);
    void computeTexCoordinates();
    void computeNormalsPerVertex();
    void buildVF(const Object& obj, vector<vector<int> >& VF);
    void clear();

    vector<Vertex> pvertices;  // vector amb els vertexs de l'objecte
    vector<Vector> pnormals;
    vector<std::pair<float,float> > ptexCoords;
    vector<Face> pfaces;       // vector amb les cares de l'objecte

    std::string pname;
    Box pboundingBox;   // caixa contenidora de l'objecte.
};

#endif

