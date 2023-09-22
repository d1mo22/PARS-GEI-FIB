  bool buscar(const T& x) const {
    if (primer_node == nullptr) return false;
    return i_trobar(primer_node, x);
  }

  bool i_trobar(node_arbreGen* m, const T& x) const {
    if (m->info == x) return true;
    for (int i = 0; i < m->seg.size(); ++i) {
      if (m->seg[i] != nullptr) {
        bool b = i_trobar(m->seg[i], x);
        if (b) return true;
      }
    }
    return false;
  }