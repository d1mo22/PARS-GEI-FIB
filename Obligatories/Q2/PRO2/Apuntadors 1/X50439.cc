  node_pila* copia_node_pila_it(node_pila* m) {
    if (m == nullptr) return nullptr;
    node_pila* primer = new node_pila;
    node_pila* act = primer;
    act->info = m->info;
    m = m->seguent;
    while (m != nullptr) {
      act->seguent = new node_pila;
      act = act->seguent;
      act->info = m->info;
      m = m->seguent;
    }
    act->seguent = nullptr;
    return primer;
  }

  Pila& operator=(const Pila& original) {
    if (this != &original) {
      altura = original.altura;
      esborra_node_pila_it(primer_node);
      primer_node = copia_node_pila_it(original.primer_node);
    }
    return *this;
  }