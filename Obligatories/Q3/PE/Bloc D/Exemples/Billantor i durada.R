#Dades
brillantor = c(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
durada = c(241, 193, 205, 169, 174, 134, 163, 124, 111, 92)

#Model lineal
mod = lm(durada~brillantor)
summary(mod)

#Grafics
plot(brillantor, durada)
abline(mod, col='red')
