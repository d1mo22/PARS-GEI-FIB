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

#include "scene.h"

Scene::Scene() : pselectedObject(0)  // inicialment l'objecte seleccionat és el 0
{}

Box Scene::boundingBox() const
{
    return pboundingBox;
}

const vector<Object>& Scene::objects() const
{
    return pobjects;
}

vector<Object>& Scene::objects()
{
    return pobjects;
}
    
void Scene::addObject(Object &o)
{
    pobjects.push_back(o);
    computeBoundingBox();
}

void Scene::clear()
{
    pobjects.clear();
}


void Scene::computeBoundingBox()
{
    if (pobjects.size())
    {
        pboundingBox = pobjects[0].boundingBox();
        for (unsigned int i=1; i<pobjects.size(); ++i)
            pboundingBox.expand(pobjects[i].boundingBox()); 
    }
}

int Scene::selectedObject() const 
{
    if (pobjects.size()) return pselectedObject;
    else return -1; 
}

void Scene::setSelectedObject(int index)
{
    pselectedObject = index;
}

