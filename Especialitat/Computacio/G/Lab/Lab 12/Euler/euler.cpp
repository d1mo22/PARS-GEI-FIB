#include "euler.h"
#include "glwidget.h"
#include <set>

void Euler::onPluginLoad()
{
	faces = scene()->objects()[0].faces().size();
	vertex = scene()->objects()[0].vertices().size();
	
	// Crear set para aristas únicas
    set<pair<int,int>> uniqueEdges;
    
    // Recorrer todas las caras
    const vector<Face> &f = scene()->objects()[0].faces();
    for (const Face& face : f) {
        // Para cada cara, procesar sus 3 aristas
        for (int i = 0; i < 3; ++i) {
            int v1 = face.vertexIndex(i);
            int v2 = face.vertexIndex((i+1)%3);
            
            // Ordenar vértices para evitar duplicados
            if (v1 > v2) swap(v1, v2);
            
            // Insertar arista en el set
            uniqueEdges.insert({v1, v2});
        }
    }
    
    // Asignar número de aristas únicas
    edges = uniqueEdges.size();
}

void Euler::preFrame()
{
	
}

void Euler::postFrame()
{
	cout << "F=" << faces << "\n";
	cout << "V=" << vertex << "\n";
	cout << "E=" << edges << "\n";
	cout << "X=" << faces+vertex-edges << "\n";
}

void Euler::onObjectAdd()
{
	onPluginLoad();
}

bool Euler::drawScene()
{
	return false; // return true only if implemented
}

bool Euler::drawObject(int)
{
	return false; // return true only if implemented
}

bool Euler::paintGL()
{
	return false; // return true only if implemented
}

void Euler::keyPressEvent(QKeyEvent *)
{
	
}

void Euler::mouseMoveEvent(QMouseEvent *)
{
	
}

