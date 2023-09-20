  void arb_sumes(Arbre<int>& asum) const {
    asum.primer_node = suma(primer_node);
  }

  static node_arbre* suma(node_arbre* m) {
    if (m != nullptr) {
      node_arbre* n = new node_arbre;
      n->segE = suma(m->segE);
      n->segD = suma(m->segD);
      int e = 0;
      int d = 0;
      if (n->segE != nullptr) e = (n->segE)->info;
      if (n->segD != nullptr) d = (n->segD)->info;
      n->info = e + d + m->info;
      return n;
    }
    return nullptr;
  }