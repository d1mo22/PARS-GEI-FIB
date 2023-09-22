Llista reorganitzar_out(const T& x) const {
  Llista l;
  if (longitud == 0) return l;

  node_llista* ult_men = nullptr;
  l.act = l.ultim_node = l.primer_node = nullptr;
  l.longitud = longitud;
  node_llista* act = primer_node;

  while (act != nullptr) {
    if (act->info <= x) {
      if (ult_men == nullptr) {
        ult_men = new node_llista;
        l.primer_node = ult_men;
        l.primer_node->ant = nullptr;
      }
      else {
        ult_men->seg = new node_llista;
        (ult_men->seg)->ant = ult_men;
        ult_men = ult_men->seg;
      }
      ult_men->info = act->info;
    }
    else {
      if (l.ultim_node == nullptr) {
        l.ultim_node = new node_llista;
        l.act = l.ultim_node;
        l.act->ant = nullptr;
      }
      else {
        l.ultim_node->seg = new node_llista;
        l.ultim_node->seg->ant = l.ultim_node;
        l.ultim_node = l.ultim_node->seg;
      }
      l.ultim_node->info = act->info;
    }
    act = act->seg;
  }
  if (l.primer_node == nullptr) l.primer_node = l.act;
  else if (l.act == nullptr) l.ultim_node = ult_men;
  else {
    ult_men->seg = l.act;
    l.act->ant = ult_men;
  }
  l.ultim_node->seg = nullptr;
  return l;
}