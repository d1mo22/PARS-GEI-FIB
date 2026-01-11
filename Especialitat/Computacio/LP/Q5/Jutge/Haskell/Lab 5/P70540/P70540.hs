data Expr = Val Int | Add Expr Expr | Sub Expr Expr | Mul Expr Expr | Div Expr Expr

eval1 :: Expr -> Int
eval1 (Val x) = x
eval1 (Add x y) = eval1 x + eval1 y
eval1 (Sub x y) = eval1 x - eval1 y
eval1 (Mul x y) = eval1 x * eval1 y
eval1 (Div x y) = eval1 x `div` eval1 y

opera2 :: (Int -> Int -> Int) -> Expr -> Expr -> Maybe Int 
opera2 f x y = do
    x' <- eval2 x
    y' <- eval2 y
    Just (f x' y')

opera3 :: (Int -> Int -> Int) -> Expr -> Expr -> Either String Int 
opera3 f x y = do
    x' <- eval3 x
    y' <- eval3 y
    Right (f x' y')

eval2 :: Expr -> Maybe Int
eval2 (Val x) = Just x
eval2 (Add x y) = opera2 (+) x y
eval2 (Sub x y) = opera2 (-) x y
eval2 (Mul x y) = opera2 (*) x y
eval2 (Div x y) = do
    x' <- eval2 x 
    y' <- eval2 y
    if y' == 0 then Nothing else Just (x' `div` y')

eval3 :: Expr -> Either String Int
eval3 (Val x) = Right x
eval3 (Add x y) = opera3 (+) x y
eval3 (Sub x y) = opera3 (-) x y
eval3 (Mul x y) = opera3 (*) x y
eval3 (Div x y) = do
    x' <- eval3 x 
    y' <- eval3 y
    if y' == 0 then Left "div0" else Right (x' `div` y')
