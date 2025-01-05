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

#ifndef _DRAW_VBONG_H
#define _DRAW_VBONG_H

#include <vector>
#include "plugin.h"

#define SMOOTH 1

using namespace std;

class draw_smooth : public QObject, public Plugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "Plugin")   
  Q_INTERFACES(Plugin)

 public:
  ~draw_smooth();
  void cleanUp();
 
  void onSceneClear();
  void onPluginLoad();
  void onObjectAdd();
  bool drawScene();
  bool drawObject(int);
   
 private:
  void addVBO(unsigned int currentObject);

  // VAO and VBO identifiers for each object in the scene.
  vector <GLuint> VAOs;
  vector <GLuint> coordBuffers;
  vector <GLuint> normalBuffers;
  vector <GLuint> stBuffers;
  vector <GLuint> colorBuffers;
  #if SMOOTH
  vector <GLuint> indexBuffers;
  #endif
  vector <GLuint> numIndices;
};
 
#endif
