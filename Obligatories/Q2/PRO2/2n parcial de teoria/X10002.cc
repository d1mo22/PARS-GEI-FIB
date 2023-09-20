  void esborrar_tots(const T& x) { 
    node_llista* n = primer_node;
    while (n != nullptr) {
      if (n->info == x) {
        if (n == primer_node and n  == ultim_node) primer_node = ultim_node = nullptr;
        else if (n == primer_node) {
          primer_node = n->seg;
          (n->seg)->ant = nullptr;
        }
        else if (n == ultim_node) {
          ultim_node = n->ant;
          (n->ant)->seg = nullptr;
        }
        else {
          (n->seg)->ant = n->ant;
          (n->ant)->seg = n->seg;   
        }
        if (act == n) act = n->seg;
        node_llista* aux = n;
        n = n->seg;
        delete aux;
        --longitud;
      }
      else n = n->seg;
    }
  }