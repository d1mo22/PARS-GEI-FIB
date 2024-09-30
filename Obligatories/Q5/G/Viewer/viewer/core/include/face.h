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

#ifndef FACE_H
#define FACE_H
#include <vector>
#include <string>
struct Material {
  std::string name;
  float ambient[4];
  float diffuse[4];
  float specular[4];
  float shininess;
  Material();
};
#ifndef __MODEL__DEF__ 
extern
#endif
std::vector<Material> Materials
#ifdef __MODEL__DEF__
(1); 
#else
;
#endif

#include "vertex.h"
using namespace std;

/*!
	\class Face
	\brief The %Face class represents a face of a 3D object. 

    Each face keeps a list of vertices (actually vertex indices) and a normal vector.
    The face is assumed to be convex. 
*/

class CORE_EXPORT Face
{
public:
  friend class Object;
    /*! 
    Constructs an empty face.
    */
    Face();

    /*!
    Constructs a face with 3 or 4 vertices (actually vertex indices). 
    */
    Face(int i0, int i1, int i2, int i3=-1); 

    /*!
    Adds a new vertex index i to the face (at the end, i.e. push_back).
    */ 
    void addVertexIndex(int i);       

    /*!
    Returns the number of vertices forming the face.
    */
    int numVertices() const;        

    /*!
    Returns the vertex index at the i-th position. First vertex has index 0. 
    */
    int vertexIndex(int i) const;   

    /*! 
    Returns the current normal vector of the face (undefined by default). 
    The return value is thus undefined unless computeNormal() has been called for this face.
    */
    Vector normal() const;          

    /*! 
    Recomputes the normal vector of the face. This method must be called explicitly
    after constructing/modifying the face.
    \param verts contains actual vertex coordinates from the object containing the face.
    */
    void computeNormal(const vector<Vertex> &verts);

    /*!
      Enumerated type to describe the information for the face originating from the file.
     */
    typedef enum {
      VONLY,       /*!< Model file contained only vertex coordinates  */
      VN,          /*!< Model file provided coordinates and normals  */
      VT,          /*!< Model file provided coordinates and texture coordinates  */
      VTN          /*!< Model file provided coordinates, normals and texture coordinates  */
    } infoInSource;

    /*!
      returns a constant enum indicating the info that was contained originally in the file.
      Other info may be available nonetheless, but will have been computed by the driver
    */
    infoInSource faceInfo() const;

    /*!
      returns the position of the vertex normal in the object's vector of normals.
      (a reference to that vector is returned by Object::vertNormals())
      \param i index of the vertex for which we want to retrieve the normal; must be in 0..2
    */
    int normalIndex(int i) const;

    /*!
      returns the position of the texture coordinates for a vertex in the object's vector of same.
      (a reference to this vector may be obtained with Object::vertTexCoords())
      \param i index of the vertex for which we want to retrieve the texture coordinates; must be in 0..2
     */
    int texcoordsIndex(int i) const;
    
private:
    // atributs
    infoInSource fromFile;
    int mat;
    Vector pnormal;         // normal de la cara    
    vector<int> pvertices;  // vector amb els indexs dels vertexs de la cara
    vector<int> pvertnormals;
    vector<int> ptexcoords;
};

#endif
