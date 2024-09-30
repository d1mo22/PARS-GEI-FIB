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

#include "face.h"
#include <cmath>

Face::Face() 
{}

Face::Face(int i0, int i1, int i2, int i3)
{
    pvertices.push_back(i0);
    pvertices.push_back(i1);
    pvertices.push_back(i2);
    if (i3!=-1) pvertices.push_back(i3);
}

void Face::computeNormal(const vector<Vertex> &v)
{
    int j;
    pnormal=Vector(0.0f, 0.0f, 0.0f);
    int n = pvertices.size();
    for (int i=0; i<n; i++)
    {
        j = (i+1)%n;
        const Point& pi = v[pvertices[i]].coord();
        const Point& pj = v[pvertices[j]].coord();

        pnormal.setX(pnormal.x() + ((pi.z() + pj.z()) * (pi.y() - pj.y())));
        pnormal.setY(pnormal.y() + ((pi.x() + pj.x()) * (pi.z() - pj.z())));
        pnormal.setZ(pnormal.z() + ((pi.y() + pj.y()) * (pi.x() - pj.x())));
    }
    pnormal.normalize();
}


int Face::numVertices() const
{
    return pvertices.size();
}

int Face::vertexIndex(int i) const
{
    return pvertices[i];
}

void Face::addVertexIndex(int i)
{
    pvertices.push_back(i);
}

Vector Face::normal() const
{
    return pnormal;
}

Face::infoInSource Face::faceInfo() const {
  return fromFile;
}

int Face::normalIndex(int i) const {
  return pvertnormals.at(i);
}

int Face::texcoordsIndex(int i) const {
  return ptexcoords.at(i);
}
