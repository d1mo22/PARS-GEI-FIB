NB. test_verbs.j
1 2 3 > 2        NB. --> 0 0 1
1 2 3 = 1 3 3    NB. --> 1 0 1
] 5 6            NB. --> 5 6 (Identidad)
1 , 2 3          NB. --> 1 2 3 (Concatenar)
# 1 2 3          NB. --> 3 (Tamaño monádico)
1 0 1 # 5 6 7    NB. --> 5 7 (Filtrar diádico)
1 { 5 6 7        NB. --> 6 (Indexar)
0 2 { 5 6 7      NB. --> 5 7 (Indexar múltiple)
i. 4             NB. --> 0 1 2 3 (Generar)