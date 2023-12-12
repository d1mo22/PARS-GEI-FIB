Vino <- read.delim("~/Downloads/In_vino_veritas_-_A.txt")
View(Vino)
x1 = Vino$x1
x2 = Vino$x2
x3 = Vino$x3
x4 = Vino$x4
Q = Vino$Q

modA = lm(Q~x1+x2+x3)
summary(modA)

# Residual standar error 0.7842

modB = lm(Q~x1+x3)
summary(modB)

# Residual standar error 0.8118
# Variability in the wine = Multiple R-squared = 0.1014
# "" model B 0.03288

modC = lm(Q~x3)
summary(modC) 
confint(modC)

# IC(modC, 95%) = [0.0232461, 0.1463076]
