T maxim() const {
  return i_max(primer_node);
}

T i_max(node_arbreNari* m) const {
  T aux = m->info;
  for (int i = 0; i < N; ++i) {
    if (m->seg[i] != nullptr) {
      T max = i_max(m->seg[i]);
      if (max > aux) aux = max;
    }
  }
  return aux;
}