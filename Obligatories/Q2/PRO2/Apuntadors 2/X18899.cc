void arbsuma(ArbreNari& asum) const {
  asum.N = N;
  asum.primer_node = suma(primer_node);
}

static node_arbreNari* suma(node_arbreNari* m) {
  if (m == nullptr) return nullptr;

  node_arbreNari* aux = new node_arbreNari;
  int s = m->info;
  for (int i = 0; i < m->seg.size(); ++i) {
    node_arbreNari* fill = suma(m->seg[i]);
    aux->seg.push_back(fill);
    if (fill != nullptr) s+= fill->info;
  }
  
  aux->info = s;
  return aux;
}