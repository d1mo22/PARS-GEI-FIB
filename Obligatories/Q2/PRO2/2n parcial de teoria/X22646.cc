void trenat(Cua &c) { 
    if (longitud == 0 and c.longitud == 0) {
      longitud = 0;
      primer_node = nullptr;
      ultim_node = nullptr;
    }
    else if (longitud == 0 and c.longitud != 0) {
      primer_node = c.primer_node;
      ultim_node = c.ultim_node;
      longitud = c.longitud;
    }
    else if (longitud != 0 and c.longitud == 0) {

    }
    else {
      longitud += c.longitud;
      node_cua* c1 = primer_node;
      node_cua* c2 = c.primer_node;
      while (c1 != nullptr and c2 != nullptr) {
        node_cua* c1s = c1->seguent;
        node_cua* c2s = c2->seguent;
        c2->seguent = c1->seguent;
        c1->seguent = c2;
        if (c1s == nullptr) c2->seguent = c2s;
        c1 = c1s;
        c2 = c2s;
      }
    }
    c.longitud = 0;
    c.primer_node = nullptr;
    c.ultim_node = nullptr;
  }