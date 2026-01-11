-- Funció que retorna la llista de moviments per moure n discs
hanoi :: Int -> String -> String -> String -> [(String, String)]
hanoi 0 _ _ _ = []
hanoi n origen destí auxiliar =
  hanoi (n - 1) origen auxiliar destí
    ++ [(origen, destí)]
    ++ hanoi (n - 1) auxiliar destí origen

main :: IO ()
main = do
  entrada <- getLine
  let (nStr : origen : destí : auxiliar : _) = words entrada
  let n = read nStr :: Int
  let moviments = hanoi n origen destí auxiliar
  mapM_ (\(o, d) -> putStrLn (o ++ " -> " ++ d)) moviments