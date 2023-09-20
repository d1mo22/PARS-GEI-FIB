void sub_arrel(Arbre& asub, const T& x) {
  asub.primer_node = NULL;
  int min_d = -1;
  cerca(primer_node, asub.primer_node, x, 0, min_d);
}

void cerca(node_arbre* n, node_arbre* &m, const T& x, int d, int& min_d) {
  if (n != NULL) {
    if (n->info == x and (d <= min_d or min_d == -1)) {
      min_d = d;
      m = copia_node_arbre(n);
    }
    else {
      cerca(n->segE, m, x, ++d, min_d);
      cerca(n->segD, m, x, ++d, min_d);
    }
  }
}