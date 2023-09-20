  node_llista* copia_node_llista_it (node_llista* m, node_llista* oact, node_llista* &u, node_llista* &a) {
    if (m == nullptr) {
      u = a = nullptr; 
      return nullptr;
    }
    node_llista* primer = new node_llista;
    node_llista* act = primer;
    act->info = m->info;
    act->ant = nullptr;
    if (oact == m) a = act;
    m = m->seg;
    while (m != nullptr) {
      act->seg = new node_llista;
      (act->seg)->ant = act;
      (act->seg)->info = m->info;
      if (m == oact) a = act->seg;
      act = act->seg;
      //act->info = m->info;
      m = m->seg;
    }
    act->seg = nullptr;
    u = act;
    return primer;
  }

  Llista& operator=(const Llista& original) {
    if (this != &original) {
      longitud = original.longitud;
      esborra_node_llista_it(primer_node);
      primer_node = copia_node_llista_it(original.primer_node, original.act, ultim_node, act);
    }
    return *this;
  }