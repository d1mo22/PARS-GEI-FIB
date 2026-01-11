NB. test_derived.j
+/ 1 2 3 4       NB. --> 10 (Fold suma)
-/ 1 2 3 4       NB. --> _2 (Fold resta, derecha-a-izquierda: 1-(2-(3-4)))
*: 1 2 3         NB. --> 1 4 9 (Monadic apply : con *)
+: 1 2 3         NB. --> 2 4 6 (Monadic apply : con +)
7 |~ 2           NB. --> 1 (Flip ~ con |)
mod2 =: 2 | ]    NB. Definición función mod2
mod2 i. 4        NB. --> 0 1 0 1 (Uso función mod2)
eq0 =: 0 = ]     NB. Definición función eq0
parell =: eq0 @: mod2 NB. Definición función parell por composición
parell i. 6      NB. --> 1 0 1 0 1 0 (Uso función compuesta)