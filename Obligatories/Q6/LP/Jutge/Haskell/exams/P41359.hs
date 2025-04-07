data LogicExpression
  = Or LogicExpression LogicExpression
  | And LogicExpression LogicExpression
  | Not LogicExpression
  | Var String
  | Val Bool

instance Show LogicExpression where
  show (Val x)
    | x = "1"
    | otherwise = "0"
  show (Var x) = x
  show (Not x) = "(not " ++ show x ++ ")"
  show (And x y) = "(" ++ show x ++ " and " ++ show y ++ ")"
  show (Or x y) = "(" ++ show x ++ " or " ++ show y ++ ")"

pushNegations :: LogicExpression -> LogicExpression
pushNegations (Not (Not x)) = pushNegations x
pushNegations (Not (Val x)) = Val (not x)
pushNegations (Not (And x y)) = Or (pushNegations (Not x)) (pushNegations (Not y))
pushNegations (Not (Or x y)) = And (pushNegations (Not x)) (pushNegations (Not y))
pushNegations (And x y) = And (pushNegations x) (pushNegations y)
pushNegations (Or x y) = Or (pushNegations x) (pushNegations y)
pushNegations x = x

bits :: [[[Int]]]
bits = [[]] : [((:) <$> [0, 1]) <*> b | b <- bits]