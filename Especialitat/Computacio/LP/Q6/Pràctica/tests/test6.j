NB. test_precedence.j - Verificar precedencia

NB. Sin paréntesis (derecha a izquierda)
2 + 3 * 4        NB. --> 14 (2 + (3*4))
2 * 3 + 4        NB. --> 14 (2 * (3+4))

NB. Con paréntesis
(2 + 3) * 4      NB. --> 20
2 * (3 + 4)      NB. --> 14

NB. Múltiples niveles
((1 + 2) * 3) + 4 NB. --> 13