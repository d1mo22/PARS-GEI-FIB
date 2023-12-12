#Dades
cerveses = c(5,2,9,8,3,7,3,5,3,5,4,6,5,7,1,4)
alcohol = c(0.100,0.030,0.190,0.120,0.040,0.095,0.070,0.060, 0.020, 0.050, 0.070, 0.100, 0.085, 0.090, 0.010, 0.05)

#Model lineal
mod = lm(alcohol~cerveses)
summary(mod)

#Per trobar el interval de confiança
#Podem veure per l'interval de confianca
#si les variables son resulat del atzar o no
confint(mod)

#Amb aquest cas podem veure com que el parametre b0 
#si que conte el 0 doncs podem dir que el valor es resultat del atzar
#ja que no te molt sentit que tinguem alcohol negatiu a la sang amb 0
#cerveses, mentre que el parametre b1 el IC no conte el 0 per aixo podem
#dir que el alcohol en sang augmenta per cada cesvesa ingerida.

#Grafic
plot(cerveses, alcohol)
abline(lm(alcohol~cerveses), col = 'red')

#Diferents grafics
par(mfrow = c(2,2))
plot(mod, c(2,1))                    # QQ-Norm i Standard Resiguals vs. Fitted
hist(rstandard(mod))                 # Histograma dels residus estandaritzats
plot(1:16, rstandard(mod), type="l") # Ordre dels residus estandaritzats

