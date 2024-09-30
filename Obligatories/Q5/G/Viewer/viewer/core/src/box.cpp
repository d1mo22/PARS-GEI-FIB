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

#include "box.h"
#include <QtOpenGL/QtOpenGL>
#include "vector.h"

Box::Box(const Point& point)
    : pmin(point), pmax(point)
{}

Box::Box(const Point& minimum, const Point& maximum)
    : pmin(minimum), pmax(maximum)
{}

void Box::expand(const Point& p)
{
    if (p.x() < pmin.x()) pmin.setX(p.x());
    if (p.y() < pmin.y()) pmin.setY(p.y());
    if (p.z() < pmin.z()) pmin.setZ(p.z());
    if (p.x() > pmax.x()) pmax.setX(p.x());
    if (p.y() > pmax.y()) pmax.setY(p.y());
    if (p.z() > pmax.z()) pmax.setZ(p.z());
}

void Box::expand(const Box& b)
{
    expand(b.pmin);
    expand(b.pmax);
}

/*
void Box::render()
{
    glBegin(GL_LINES);
    glVertex3f(pmin.x(), pmin.y(), pmin.z());
    glVertex3f(pmax.x(), pmin.y(), pmin.z());

    glVertex3f(pmax.x(), pmin.y(), pmin.z());
    glVertex3f(pmax.x(), pmax.y(), pmin.z());

    glVertex3f(pmax.x(), pmax.y(), pmin.z());
    glVertex3f(pmin.x(), pmax.y(), pmin.z());

    glVertex3f(pmin.x(), pmax.y(), pmin.z());
    glVertex3f(pmin.x(), pmin.y(), pmin.z());

    glVertex3f(pmin.x(), pmin.y(), pmax.z());
    glVertex3f(pmax.x(), pmin.y(), pmax.z());

    glVertex3f(pmax.x(), pmin.y(), pmax.z());
    glVertex3f(pmax.x(), pmax.y(), pmax.z());

    glVertex3f(pmax.x(), pmax.y(), pmax.z());
    glVertex3f(pmin.x(), pmax.y(), pmax.z());

    glVertex3f(pmin.x(), pmax.y(), pmax.z());
    glVertex3f(pmin.x(), pmin.y(), pmax.z());

    glVertex3f(pmin.x(), pmax.y(), pmin.z());
    glVertex3f(pmin.x(), pmax.y(), pmax.z());

    glVertex3f(pmax.x(), pmax.y(), pmin.z());
    glVertex3f(pmax.x(), pmax.y(), pmax.z());

    glVertex3f(pmin.x(), pmin.y(), pmin.z());
    glVertex3f(pmin.x(), pmin.y(), pmax.z());

    glVertex3f(pmax.x(), pmin.y(), pmin.z());
    glVertex3f(pmax.x(), pmin.y(), pmax.z());

    glEnd();
}
*/

Point Box::center() const
{
    return 0.5f*(pmax+pmin); 
}

float Box::radius() const
{
    Vector v = pmax - pmin;
    return 0.5f*v.length();
}

Point Box::min() const
{
    return pmin;
}

Point Box::max() const
{
    return pmax;
}

