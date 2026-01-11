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

#include "camera.h"
#include <cmath>
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <iostream>
#ifndef __APPLE__
  #include <GL/gl.h>
#else
  #include <gl.h>
#endif
using namespace std;

void Camera::init(const Box& box)
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    Point center = box.center();
    float radius = box.radius();

    pvrp = center;
    pdist = 2*radius;
    pfovy = 60; // 2 * asin (radi/2*radi)
    pzNear = radius;
    pzFar = 3*radius;

    pangleX = 0;
    pangleY = 0;
    pangleZ = 0;

    GLint view[4];
    f->glGetIntegerv(GL_VIEWPORT, view);
    paspectRatio = float(view[2])/float(view[3]);

}

QMatrix4x4 Camera::viewMatrix() const
{
    QMatrix4x4 viewing;
    viewing.translate(0,0,-pdist);
    viewing.rotate(-pangleZ,0,0,1);
    viewing.rotate( pangleX,1,0,0);
    viewing.rotate(-pangleY,0,1,0);
    viewing.translate(-pvrp.x(),-pvrp.y(),-pvrp.z());
    return viewing;
}

QMatrix4x4  Camera::projectionMatrix() const
{
    QMatrix4x4 P;
    float realFovy = pfovy;
    if (paspectRatio < 1.0) 
      realFovy = 360.0/M_PI*atan(tan(pfovy*M_PI/360)/paspectRatio);
    P.perspective(realFovy, paspectRatio, pzNear, pzFar);
    return P;
}

Point Camera::getObs() const
{
    QMatrix4x4 viewing = viewMatrix();
    QMatrix4x4 inv = viewing.inverted(); 
    return QVector3D(inv*QVector4D(0.0, 0.0, 0.0, 1.0));
}

float Camera::getDist() const
{
  return pdist;
}


void Camera::incrementDistance(float inc)
{
    pdist += inc;
}

void Camera::incrementAngleX(float inc)
{
    pangleX += inc;
}

void Camera::incrementAngleY(float inc)
{
    pangleY += inc;
}



void Camera::setDistance(float value)
{
    pdist = value;;
}

void Camera::setAngleX(float value)
{
    pangleX =value;
}

void Camera::setAngleY(float value)
{
    pangleY =value;
}

void Camera::setAngleZ(float value)
{
    pangleZ =value;
}

Vector Camera::eulerAngles() const
{
    return Vector(pangleX, pangleY, pangleZ);
}



void Camera::pan(const Vector& offset)
{
    pvrp = pvrp + offset;
}

void Camera::updateClippingPlanes(const Box& box)
{
    Point obs = getObs();
    Vector v = pvrp - obs;
    v.normalize();
    Vector u = box.center()-obs;
    pzNear = Vector::dotProduct(u,v)-box.radius();
    if (pzNear < 0.1f) pzNear = 0.1f;
    pzFar = Vector::dotProduct(u,v)+box.radius();
}


float Camera::fov() const
{
    return pfovy;
}

void Camera::setFov(float fovy)
{
    pfovy = fovy;
}

float Camera::znear() const
{
    return pzNear;
}

void Camera::setZnear(float z) 
{
    pzNear = z;
}

float Camera::zfar() const
{
    return pzFar;
}

void Camera::setZfar(float z) 
{
    pzFar = z;
}

float Camera::aspectRatio() const
{
    return paspectRatio;
}

void Camera::setAspectRatio(float ar)
{
    paspectRatio = ar;
} 


