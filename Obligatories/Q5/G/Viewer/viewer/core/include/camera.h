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

#ifndef CAMERA_H
#define CAMERA_H

#define _USE_MATH_DEFINES 1
//#include "GL/glew.h"
#include "point.h"
#include "vector.h"
#include "box.h"
#include <QMatrix4x4>

/*!
	\class Camera
	\brief The %Camera class represents a perspective camera.
*/

class CORE_EXPORT Camera
{
public:
	/*!
	Initializes the camera from a bounding box of the scene.
	The camera is placed outside the box, ensuring that the whole box fits
	within the viewing frustum. 
	*/
    void init(const Box& b);


	/*!
	Returns a 4x4 matrix representing the viewing transform of the camera.
	*/
    QMatrix4x4 viewMatrix() const;

	/*!
	Returns a 4x4 matrix representing the projection transform of the camera.
	*/
    QMatrix4x4 projectionMatrix() const;

    /*!
	Returns the camera (eye) position.
	*/
    Point getObs() const;
    /*!
      Returns the distance from camera to vrp.
    */
    float getDist() const;

    /*!
	Recomputes the near, far clipping planes according to the given bounding box.
	*/ 
    void updateClippingPlanes(const Box&);
    
	/*!
	Moves the camera away (inc>0) or towards (inc<0) the current VRP.
	*/
    void incrementDistance(float inc);

	/*!
	Sets the distance to the current VRP.
	*/
    void setDistance(float value);

	/*!
	Rotates the camera by increasing the rotation angle around X axis (pitch).
	*/
    void incrementAngleX(float inc);

	/*!
	Rotates the camera by setting the rotation angle around X axis (pitch).
	*/
    void setAngleX(float value);

	/*!
	Rotates the camera by increasing the rotation angle around Y axis (yaw).
	*/
    void incrementAngleY(float inc);

	/*!
	Rotates the camera by setting the rotation angle around Y axis (yaw).
	*/
    void setAngleY(float value);

	/*!
	Rotates the camera by setting the rotation angle around Z axis (roll).
	*/
    void setAngleZ(float value);

	/*!
	Returns v=(x,y,z) with the Euler angles of the camera. 
    Rotation part of the viewing matrix is Rotz(-v.z)*Rotx(v.x)*Roty(-v.y)
	*/
    Vector eulerAngles() const; 

	/*!
	Offsets the camera position and VRP.
	*/     
    void pan(const Vector& offset);
    

    /*!
    Returns the vertical field of view (degrees).
    */
    float fov() const;

    /*!
    Sets the vertical field of view (degrees).
    */
    void setFov(float fovy);

	/*!
	Sets the camera aspect ratio.
	*/    
    void setAspectRatio(float ar);

	/*!
	Returns the camera aspect ratio.
	*/    
    float aspectRatio() const;


	/*!
	Returns znear ( distance to the near clipping plane)
	*/
    float znear() const;

    /*! 
    Sets Z near
    */
    void setZnear(float z); 

	/*!
	Returns zfar ( distance to the far clipping plane)
	*/
    float zfar() const;

    /*! 
    Sets Z far
    */
    void setZfar(float z); 


private:
    Point pvrp;  // view reference point
    float pdist; // distance obs-vrp
    float pangleX, pangleY, pangleZ;  //  Euler angles
    float pfovy; // fielf of view, vertical
    float paspectRatio; // aspect ratio
    float pzNear, pzFar; // clipping planes
};

#endif

