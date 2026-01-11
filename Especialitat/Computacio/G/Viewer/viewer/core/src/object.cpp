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

#define __MODEL__DEF__ 1
#include "object.h"
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <clocale>
#include "scene.h"
#include <QMatrix4x4>
#include <utility> 
#include <cassert>

using namespace std;
// === Local stuff:
static int material = 1;
static void loadMTL(std::string filename);
static int findMat(string material);


Object::Object(std::string name):pname(name)
{
}

Box Object::boundingBox() const
{
  return pboundingBox;
}

void Object::computeBoundingBox()
{
  if (pvertices.size())
    {
      Point p = pvertices[0].coord();
      pboundingBox=Box(p, p);
      for (unsigned int i=1; i<pvertices.size(); i++)
	pboundingBox.expand(pvertices[i].coord());
    }
}

void Object::computeNormals()
{
  for(unsigned int i=0; i<pfaces.size(); ++i)
    pfaces[i].computeNormal(pvertices);
}

void Object::computeTexCoordinates()
{
  cerr << "About to try to compute texture coordinates per vertex to complete the model." << endl;
  assert(ptexCoords.empty());
  float r=pboundingBox.radius();
  for (unsigned int i=0; i < pvertices.size(); ++i) {
    Point P = pvertices[i].coord();
    float s = Vector::dotProduct((1.0/r)*Vector(1, 0, 1), P);
    float t = Vector::dotProduct((1.0/r)*Vector(0, 1, 0), P);
    ptexCoords.push_back(std::pair<float,float>(s, t));
  }
  for (unsigned int i=0; i < pfaces.size(); ++i) {
    Face& f=pfaces[i];
    f.ptexcoords = f.pvertices;
  }
  assert(pvertices.size()==ptexCoords.size());
}

//--- Auxiliary d.s., method and functions to compute missing normals
//    per vertex: 
//
class Cluster
{
public:
  vector<int> faces;
  Vector normal;
};

static int findCluster(const Object& obj, int face, vector<Cluster>& clusters)
{
  const float MAX_ANGLE = 80; // degrees
  const float MIN_COS = cos(MAX_ANGLE/180*3.14);
  unsigned int i;
  for (i=0; i<clusters.size(); ++i)
    {
      Vector n1 = clusters[i].normal.normalized();
      Vector n2 = obj.faces()[face].normal().normalized();
      float c = Vector::dotProduct(n1,n2);
      if (c > MIN_COS) return i;
    }
  return -1;
}

static void cluster(const Object& obj, vector<vector<int> >& VF,
		    vector<vector<Cluster> >& clusters)
{
  clusters.clear();
  clusters.resize(VF.size());
  // group vertices in V:{F} into clusters, according to per-face normals
  for (unsigned int i=0; i<VF.size(); ++i) // for each vertex 
    {
      vector<int>& faces = VF[i]; 
      // assign first face to cluster 0
      Cluster cluster; 
      int f = faces[0];
      cluster.faces.push_back(f); 
      cluster.normal = obj.faces()[f].normal();
      clusters[i].push_back(cluster);
      // for each remaining face in V:{F}, try to add to an existing
      // cluster or create new cluster
      for (unsigned int j=1; j<faces.size(); ++j)
        {
	  f = faces[j];
	  int index = findCluster(obj, f, clusters[i]); 
	  if (index>=0) // add to an existing cluster
            {
	      clusters[i][index].faces.push_back(f); 
	      clusters[i][index].normal +=  obj.faces()[f].normal();           
            }
	  else    // add to new cluster
            {
	      Cluster cluster; 
	      cluster.faces.push_back(f); 
	      cluster.normal = obj.faces()[f].normal();
	      clusters[i].push_back(cluster);
            }
        }
    }
}

void Object::buildVF(const Object& obj, vector<vector<int> >& VF)
{
  // build V:{F} relationship
  VF.clear();
  VF.resize(obj.vertices().size());
  for(unsigned int j=0; j<obj.faces().size(); j++)  // for each face
    {
      const Face& face = obj.faces()[j];
      //Vector N = face.normal();
      for(unsigned int k=0; k<(unsigned int)face.numVertices(); k++) 
	{  // for each vertex:
	  VF[face.vertexIndex(k)].push_back(j); 
	}
    }
}
//------------------

void Object::computeNormalsPerVertex()
{
  cerr << "About to try to compute perVertex normals to complete the model." << endl;
  assert(pnormals.empty());
  pnormals.resize(pvertices.size());
  vector<vector<int> > VF;
  buildVF(*this, VF); // compute V:{F} incidence relationship
  vector<vector<Cluster> > clusters;
  cluster(*this, VF, clusters); // clusters[i] contains the clusters for
			      // vertex i. 
  for (unsigned int j=0; j<clusters.size(); ++j)   // for each vertex
    {
      vector<Cluster>& cl = clusters[j];
      pnormals[j] = cl[0].normal.normalized();      
      for (unsigned int k=1; k<cl.size(); ++k)  // for each other cluster
        {
	  Cluster& cluster = cl[k];
	  pvertices.push_back(pvertices[j]);
	  pnormals.push_back(cluster.normal.normalized());
	  int newvert = pvertices.size()-1;
	  for (int f: cluster.faces) {
	    std::replace(pfaces[f].pvertices.begin(),
			 pfaces[f].pvertices.end(), int(j), newvert);
	  }
        }    
    }
  for (auto &f:pfaces) f.pvertnormals = f.pvertices;
}

const vector<Face>& Object::faces() const
{
  return pfaces;
}
 
vector<Vertex>& Object::vertices()
{
  return pvertices;
}

const vector<Vector>& Object::vertNormals() const {
  return pnormals;
}

const vector<std::pair<float, float> >& Object::vertTexCoords() const {
  return ptexCoords;
}

const vector<Vertex>& Object::vertices() const
{
  return pvertices;
}

//------------------------------
// Load an .obj file.
// this simple loader does the minimum needed for our purposes.
// it only handles polyhedral models, and then with several
// limitations (see ..h)
static string modelPath("");
void Object::readObj(string filename) {
  if (not pvertices.empty()) {
    pvertices.erase(pvertices.begin(), pvertices.end());
    pnormals.erase(pnormals.begin(), pnormals.end());
    ptexCoords.erase(ptexCoords.begin(), ptexCoords.end());
    pfaces.erase(pfaces.begin(), pfaces.end());
  }
  size_t fiPath = filename.rfind("/");
  if (fiPath == string::npos) modelPath = "";
  else modelPath = filename.substr(0, fiPath+1);

  fstream input(filename.data(), ios::in);
  if (input.rdstate() != ios::goodbit) {
    cerr << "Cannot load OBJ file " << filename << endl;
    return;
  }
  string line;
  stringstream ss;
  while (getline(input, line)) {
#if DEBUGPARSER
    cerr << "Just read '" << line << "'" << endl;
#endif
    ss.clear(); ss.str(line);
    char c = '#'; // to skip whitelines...
    ss >> c;
    // The following variables need to be declared before entering the switch.
    // They are intended for use in the different cases...
    string tail;
    Face auxFace;
    stringstream auxss;
    size_t first, second;
    float x, y, z;
    switch(c){
      //-------------
    case '#':    // comment line
      break;
      //-------------
    case 'v':    // vertex information...
      ss >> noskipws >> c >> skipws;
      switch (c) {
      case ' ':  // coordinates
	ss >> x >> y >> z;
	pvertices.push_back(Vertex(Point(x, y, z)));
	break;
      case 'n':  // normal components
	ss >> x >> y >> z;
	pnormals.push_back(Vector(Point(x, y, z)));
	break;
      case 't':  // texture coords.
	ss >> x >> y;
	ptexCoords.push_back(std::make_pair(x, y));
	break;
      default:
	cerr << "Seen unknown vertex info of type '" << c << "', ignoring it..." << endl;
	break; 
      }
      break;
      //-------------
    case 'f':  // face info
      ss >> tail;   // tail will contain  d/d/d or d/d or d//d or d:  (same for the rest underneath...)
      first = tail.find("/");
      if (first == string::npos) parseVOnly(ss, tail);
      else {
	second = tail.find("/", first + 1);
	if (second == first + 1)  parseVN(ss, tail);
	else if (second == string::npos) parseVT(ss, tail);
	else parseVTN(ss, tail);
      }
      break;
      //-------------
    case 'm':  // material library
      ss >> tail;
      if (tail != "tllib") {
	cerr << "unknown line of type 'm" << tail << "'. Ignoring..." << endl;
	break;
      }
      ss >> tail;
      loadMTL(modelPath+tail);
      break;
      //-------------
    case 'u':  // material info
      ss >> tail;
      if (tail != "semtl") {
	cerr << "unknown line of type 'u" << tail << "'. Ignoring..." << endl;
	break;
      }
      ss >> tail;
      material = findMat(tail);
      break;
      //-------------
    case 'g':
#if DEBUGPARSER
      cout << "[outer]:Seen line of type '" << c << "', which is not supported. Ignoring it..." << endl;
#endif
      break;
      //-------------
    case 's':
#if DEBUGPARSER
      cout << "[outer]:Seen line of type '" << c << "', which is not supported. Ignoring it..." << endl;
#endif
      break;
      //-------------
    case 'o':
#if DEBUGPARSER
      cout << "[outer]:Seen line of type '" << c << "', which is not supported. Ignoring it..." << endl;
#endif
      break;
      //-------------
    default:
      cout << "[outer]:Seen unknown line of type '" << c << "', ignoring it..." << endl;
      break;
    }
  }
  //
  // Now complete the data:
  computeBoundingBox();
  computeNormals();
  Face::infoInSource dataInFile = pfaces.at(0).faceInfo();
  if (dataInFile == Face::VONLY or dataInFile == Face::VN) computeTexCoordinates();
  if (dataInFile == Face::VONLY or dataInFile == Face::VT) computeNormalsPerVertex();
#ifdef DEBUGPARSER
  for (unsigned int i=0; i < pfaces.size(); ++i) {
    Face &f = pfaces[i];
    if (f.pvertices.size() != 3) {
      cerr << "Error in face "<< i << ", with " << f.pvertices.size() << " vertices" << endl;
    }
    if (f.pvertnormals.size() != 3) {
      cerr << "Error in face "<< i << ", with " << f.pvertnormals.size() << " normals" << endl;
    }
    if (f.ptexcoords.size() != 3) {
      cerr << "Error in face "<< i << ", with " << f.ptexcoords.size() << " texcoords" << endl;
    }
  }
#endif
}


string getPath(const string& filename)
{
  int i=filename.length()-1;
  bool found = false;
  while (i>=0 && !found)
    {
      if (filename[i]=='/' || filename[i]=='\\') found=true;
      else --i;
    }
  return filename.substr(0, i+1);
}
 

// Netela les dades de l'objecte 
void Object::clear()
{
  pvertices.clear();
  pfaces.clear();
  pnormals.clear();
  ptexCoords.clear();
}

void Object::applyGT(const QMatrix4x4& mat)
{
  for (unsigned int i=0; i<pvertices.size(); i++)
    {
      Point p = mat.map(pvertices[i].coord());
      pvertices[i].setCoord(p);
    }
  computeNormals();
  computeBoundingBox();
}

Material::Material() : name("__load_object_default_material__") {
  ambient[0] = ambient[1] = ambient[2] = 0.1; ambient[3] = 1.0;
  diffuse[0] = diffuse[1] = 0.7; diffuse[2] = 0.0; diffuse[3] = 1.0;
  specular[0] = specular[1] = specular[2] = 1.0; specular[3] = 1.0;
  shininess = 64;
}

//======== private methods and auxiliary functions ==========
void Object::parseVOnly(stringstream & ss, string & block) {
#if DEBUGPARSER
  cout << "Entering parseVOnly(..., \""<< block << "\")" << endl;
#endif
  Face f;
  f.fromFile=Face::VONLY;
  stringstream ssb;
  ssb.str(block);
  int index;
  ssb >> index;
  f.pvertices.push_back(index-1);
  ss >> index;
  f.pvertices.push_back(index-1);  
  ss >> index;
  f.pvertices.push_back(index-1);
  f.mat = material;
  pfaces.push_back(f);
  Face fAnt(f);
  while(ss >> index) {
    f.pvertices.clear();
    f.pvertices.push_back(fAnt.pvertices[0]);
    f.pvertices.push_back(fAnt.pvertices[2]);
    f.pvertices.push_back(index-1);
    pfaces.push_back(f);
    fAnt = f;
  }
}

void Object::parseVN(stringstream & ss, string & block) {
#if DEBUGPARSER
  cout << "Entering parseVN(..., \""<< block << "\")" << endl;
#endif
  Face f;
  f.fromFile=Face::VN;
  stringstream ssb;
  ssb.str(block);
  int index, n;
  char sep;
  ssb >> index; ssb >> sep; assert(sep == '/'); ssb >> sep; assert(sep == '/');
  ssb >> n;
  f.pvertices.push_back(index-1); f.pvertnormals.push_back(n-1);
  ss >> block; 
  ssb.clear(); ssb.str(block);
  ssb >> index; ssb >> sep; assert(sep == '/'); ssb >> sep; assert(sep == '/');
  ssb >> n;
  f.pvertices.push_back(index-1); f.pvertnormals.push_back(n-1); 
  
  ss >> block;
  ssb.clear(); ssb.str(block);
  ssb >> index; ssb >> sep; assert(sep == '/'); ssb >> sep; assert(sep == '/');
  ssb >> n;
  f.pvertices.push_back(index-1); f.pvertnormals.push_back(n-1);
  f.mat = material;
  pfaces.push_back(f);
  Face fAnt(f);
  while(ss >> block) {
    f.pvertices.clear(); f.pvertnormals.clear();
    ssb.clear(); ssb.str(block);
    ssb >> index; ssb >> sep; assert(sep == '/'); ssb >> sep; assert(sep == '/');
    ssb >> n;
    f.pvertices.push_back(fAnt.pvertices[0]); f.pvertnormals.push_back(fAnt.pvertnormals[0]);
    f.pvertices.push_back(fAnt.pvertices[2]); f.pvertnormals.push_back(fAnt.pvertnormals[2]);
    f.pvertices.push_back(index-1); f.pvertnormals.push_back(n-1);
    pfaces.push_back(f);
    fAnt = f;
  }
}

void Object::parseVT(stringstream & ss, string & block) {
#if DEBUGPARSER
  cout << "Entering parseVT(..., \""<< block << "\")" << endl;
#endif
  Face f;
  f.fromFile=Face::VT;
  stringstream ssb;
  ssb.str(block);
  int index; char sep;
  ssb >> index;ssb >> sep; assert(sep == '/');
  f.pvertices.push_back(index-1);
  ssb >> index;
  f.ptexcoords.push_back(index-1);

  ss >> block;
  ssb.clear(); ssb.str(block);
  ssb >> index;ssb >> sep; assert(sep == '/');
  f.pvertices.push_back(index-1);
  ssb >> index;
  f.ptexcoords.push_back(index-1);
  
  ss >> block;
  ssb.clear(); ssb.str(block);
  ssb >> index; ssb >> sep; assert(sep == '/');
  f.pvertices.push_back(index-1);
  ssb >> index;
  f.ptexcoords.push_back(index-1);

  f.mat = material;
  pfaces.push_back(f);
  Face fAnt(f);
  while(ss >> block) {
    f.pvertices.clear();
    f.ptexcoords.clear();
    f.pvertices.push_back(fAnt.pvertices[0]);
    f.ptexcoords.push_back(fAnt.ptexcoords[0]);
    f.pvertices.push_back(fAnt.pvertices[2]);
    f.ptexcoords.push_back(fAnt.ptexcoords[2]);
    ssb.clear(); ssb.str(block);
    ssb >> index; ssb >> sep; assert(sep == '/');
    f.pvertices.push_back(index-1);
    ssb >> index;
    f.ptexcoords.push_back(index-1);
    pfaces.push_back(f);
    fAnt = f;
  }
}

void Object::parseVTN(stringstream & ss, string & block) {
#if DEBUGPARSER
  cout << "Entering parseVTN(..., \""<< block << "\")" << endl;
#endif
  Face f;
  f.fromFile=Face::VTN;
  stringstream ssb;
  ssb.str(block);
  int index, n, t;
  char sep;
  ssb >> index; ssb >> sep; assert(sep == '/'); ssb >> t >> sep; assert(sep == '/');
  ssb >> n;
  f.pvertices.push_back(index-1); f.ptexcoords.push_back(t-1); f.pvertnormals.push_back(n-1);

  ss >> block;
  ssb.clear(); ssb.str(block);
  ssb >> index; ssb >> sep; assert(sep == '/'); ssb >> t >> sep; assert(sep == '/');
  ssb >> n;
  f.pvertices.push_back(index-1); f.ptexcoords.push_back(t-1); f.pvertnormals.push_back(n-1);
  
  ss >> block;
  ssb.clear(); ssb.str(block);
  ssb >> index; ssb >> sep; assert(sep == '/'); ssb >> t >> sep; assert(sep == '/');
  ssb >> n;
  f.pvertices.push_back(index-1); f.ptexcoords.push_back(t-1); f.pvertnormals.push_back(n-1);
  f.mat = material;
  pfaces.push_back(f);
  Face fAnt(f);
  while(ss >> block) {
    f.pvertices.clear(); f.ptexcoords.clear(); f.pvertnormals.clear();
    ssb.clear(); ssb.str(block);
    ssb >> index; ssb >> sep; assert(sep == '/'); ssb >> t >>sep; assert(sep == '/');
    ssb >> n;
    f.pvertices.push_back(fAnt.pvertices[0]); f.ptexcoords.push_back(fAnt.ptexcoords[0]);
    f.pvertnormals.push_back(fAnt.pvertnormals[0]);
    f.pvertices.push_back(fAnt.pvertices[2]); f.ptexcoords.push_back(fAnt.ptexcoords[2]);
    f.pvertnormals.push_back(fAnt.pvertnormals[2]);
    f.pvertices.push_back(index-1); f.ptexcoords.push_back(t-1); f.pvertnormals.push_back(n-1);
    pfaces.push_back(f);
    fAnt = f;
  }
}


//--- material parsing
static void loadMTL(std::string filename) {
  fstream input(filename.data(), ios::in);
  if (input.rdstate() != ios::goodbit) {
    cerr << "Cannot load MTL file " << filename << endl;
    return;
  }
  string line;
  stringstream ss;
  while (getline(input, line)) {
#if DEBUGPARSER
    cerr << "Just read [" << line << "]" << endl;
#endif
    ss.clear(); ss.str(line);
    string wrd;
    ss >> wrd;
    if (wrd[0] == '#') ;
    else if (wrd == "newmtl") {
#if DEBUGPARSER
      cerr << "Processing '" << wrd << "'" << endl;
#endif
      Material noumat;
      ss >> noumat.name;
      Materials.push_back(noumat);
#if DEBUGPARSER
      Material &current = Materials.back();
      cerr << "Now defining material " << current.name << "(size=" << Materials.size() << ")" <<endl;
#endif
    }
    else if (wrd == "Ns") {
#if DEBUGPARSER
      cerr << "Processing '" << wrd << "'" << endl;
#endif
      ss >> Materials.back().shininess;
    }
    else if (wrd == "Ka") {
#if DEBUGPARSER
      cerr << "Processing '" << wrd << "'" << endl;
#endif
      for (int i = 0; i < 3; ++i) 
	ss >> Materials.back().ambient[i];
    }
    else if (wrd == "Kd") {
#if DEBUGPARSER
      cerr << "Processing '" << wrd << "'" << endl;
#endif
      for (int i = 0; i < 3; ++i) 
	ss >> Materials.back().diffuse[i];
    }
    else if (wrd == "Ks") {
#if DEBUGPARSER
      cerr << "Processing '" << wrd << "'" << endl;
#endif
      for (int i = 0; i < 3; ++i) 
	ss >> Materials.back().specular[i];
    } else {
#if DEBUGPARSER
      cerr << "MTL parser: read line of type " << wrd << " which is not supported. Skipped..." << endl;
#endif
    }
  }
}

static int findMat(string material) {
  for (size_t i = 0; i < Materials.size(); ++i) 
    if (Materials[i].name == material) return i;
  return 0;
}
