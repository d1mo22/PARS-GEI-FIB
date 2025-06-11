NB. test_combinations.j

NB. Definiciones previas (asumiendo que se ejecutan en orden o están predefinidas)
inc =: 1 + ]
square =: *:

NB. Composición más compleja
sumsq =: +/ @: square NB. Suma de cuadrados
sumsq 1 2 3 4    NB. --> 30  (1 + 4 + 9 + 16)

NB. Usar verbos definidos en nuevas definiciones
avg =: (+/) % #     NB. Media (suma total / número de elementos)
avg 1 2 3 4      NB. --> 2   (10 % 4 = 2.5, floor divide -> 2)

NB. Fold con resta (orden importa)
diffsq =: -/ @: square NB. Suma/resta alternada de cuadrados
diffsq 1 2 3 4    NB. --> _10 (1 - (4 - (9 - 16))) = 1 - (4 - (-7)) = 1 - 11 = -10

NB. Composición triple
incsq =: square @: inc
incsq 1 2 3      NB. --> 4 9 16 ((1+1)^2, (2+1)^2, (3+1)^2)

test =: +/ @: inc @: i. NB. De square.j
test 4           NB. --> 10 (0+1+2+3 -> 1+2+3+4 -> 10)

NB. Hook dentro de composición
hook_comp =: (0 = ]) @: (2 | ]) NB. = parell de square.j
hook_comp i. 6   NB. --> 1 0 1 0 1 0

NB. Adverbio aplicado a un Hook
monadic_hook =: 1 + ] NB. = inc
fold_hook =: +/ @: monadic_hook
fold_hook 1 2 3  NB. --> 9 (+/ (1+1 2 3)) = (+/ 2 3 4) = 9

NB. Flip con composición
f =: - ~         NB. f(x,y) es y-x
g =: *           NB. g(x,y) es x*y
h =: f @: g      NB. h(y) = f(g(y,y)) = f(y*y) = y*y - y*y = 0 (si f se aplica monádicamente)
                 NB. O h(x,y) = f(g(x,y)) = g(x,y) - g(x,y) = 0 (si f se aplica diádicamente)
                 NB. La composición @: es monádica, así que h(y) = f(g(y))
                 NB. g monádico es g(y,y) = y*y
                 NB. f monádico es f(y,y) = y-y = 0
                 NB. Entonces h(y) = f(y*y) = 0
h 5              NB. --> 0

NB. Indexación compleja
vec =: 10 20 30 40 50
1 3 { vec        NB. --> 20 40