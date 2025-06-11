NB. test_basic.j
1 + 2 3          NB. --> 3 4
1 2 + 3          NB. --> 4 5
1 2 + 3 4        NB. --> 4 6
5 + 2 * 3        NB. --> 11 (Evaluación derecha-a-izquierda: 5 + (2*3))
5 * 2 + 3        NB. --> 25 (Evaluación derecha-a-izquierda: 5 * (2+3))
(5 * 2) + 3      NB. --> 13 (Paréntesis)
_1 * 2 3         NB. --> _2 _3 (Negativos)
6 % 2            NB. --> 3 (División entera)
2 | 7            NB. --> 1 (Residuo, args invertidos)
2 ^ 3            NB. --> 8 (Potencia)