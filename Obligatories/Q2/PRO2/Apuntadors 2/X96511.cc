  int freq(const T& x) const {
    if (primer_node == nullptr) return 0;
    return i_freq(primer_node, x);
  }

  int i_freq(node_arbreGen* m, const T& x) const {
    int f = 0;
    if (m->info == x) ++f;
    for (int i = 0; i < m->seg.size(); ++i) {
      if (m->seg[i] != nullptr) {
        f += i_freq(m->seg[i], x);
      }
    }
    return f;
  }