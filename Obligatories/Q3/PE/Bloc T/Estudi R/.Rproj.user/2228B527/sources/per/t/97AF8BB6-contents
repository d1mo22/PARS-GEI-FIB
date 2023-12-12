# Import de les taules
# Primer fer el import desde el excel.
# agafem primer la fulla on tenim els temps i nodes
# de els laberints 100x100
library(readxl)
L_100 <- read_excel("~/Desktop/PARS-GEI-FIB/Obligatories/Q3/PE/Bloc T/Bloc T.xlsx", 
    sheet = "Laberintos 100x100")
View(L_100)

# Despres fem el import de la fulla on tenim les dades
# dels laberints 1000x1000
library(readxl)
L1000 <- read_excel("~/Desktop/PARS-GEI-FIB/Obligatories/Q3/PE/Bloc T/Bloc T.xlsx", 
    sheet = "Laberintos 1000x1000")
View(L1000)

# Passem les columnes de les taules a variables amb les que
# podem treballar amb facilitat
# Laberints 100x100
nodes_BFS = L_100$`Nodes visitats...3`;
nodes_DFS = L_100$`Nodes visitats...5`;
temps_BFS = L_100$`Temps(s)...2`;
temps_DFS = L_100$`Temps(s)...4`;

# Laberitns 1000x1000
nodes_B1000 = L1000$`Nodes visitats...3`;
nodes_D1000 = L1000$`Nodes visitats...5`;
temps_B1000 = L1000$`Temps(s)...2`;
temps_D1000 = L1000$`Temps(s)...4`;

# Mitjanes 100x100
mean(nodes_BFS);
mean(nodes_DFS);
mean(temps_BFS);
mean(temps_DFS);

# Mitjanes 1000x1000
mean(nodes_B1000);
mean(nodes_D1000);
mean(temps_B1000);
mean(temps_D1000);

# Variancia i Desviacio tipica 100x100
var(nodes_BFS);
sqrt(var(nodes_BFS));

var(nodes_DFS);
sqrt(var(nodes_DFS));

var(temps_BFS);
sqrt(var(temps_BFS));

var(temps_DFS);
sqrt(var(temps_DFS));

# Variancia i Desviacio tipica 1000x1000
var(nodes_B1000);
sqrt(var(nodes_B1000));

var(nodes_D1000);
sqrt(var(nodes_D1000));

var(temps_B1000);
sqrt(var(temps_B1000));

var(temps_D1000);
sqrt(var(temps_D1000));

# t.test nodes 100x100 (DFS - BFS)
t.test(nodes_DFS, nodes_BFS, paired = TRUE)

# t.test temps 100x100 (DFS -BFS)
t.test(temps_DFS, temps_BFS, paired=TRUE)

# t.test nodes 1000x1000 (DFS - BFS)
t.test(nodes_D1000, nodes_B1000, paired=TRUE)

# t.test temps 1000x1000 (DFS - BFS)
t.test(temps_D1000, temps_B1000, paired=TRUE)

# Histograma
plot(lab, nodes_DFS, type = 'h', col = 'blue', main = "Nodes DFS", xlab = "Nº laberint", ylab = "Nº nodes")
plot(lab, nodes_BFS, type = 'h', col = 'orange', main = "Nodes BFS", xlab = "Nº laberint", ylab = "Nº nodes")

plot(lab, temps_DFS, type = 'h', col = 'blue', main = "Temps DFS", xlab = "Nº laberint", ylab = "Temps (s)")
plot(lab, temps_BFS, type = 'h', col = 'orange', main = "Temps BFS", xlab = "Nº laberint", ylab = "Temps (s)")

plot(lab, nodes_D1000, type = 'h', col = 'blue', main = "Nodes DFS (1000)", xlab = "Nº laberint", ylab = "Nº nodes")
plot(lab, nodes_B1000, type = 'h', col = 'orange', main = "Nodes BFS (1000)", xlab = "Nº laberint", ylab = "Nº nodes")

plot(lab, temps_D1000, type = 'h', col = 'blue', main = "Temps DFS (1000)", xlab = "Nº laberint", ylab = "Temps (s)")
plot(lab, temps_B1000, type = 'h', col = 'orange', main = "Temps BFS (1000)", xlab = "Nº laberint", ylab = "Temps (s)")

# qqnorm/qqline
qqnorm(nodes_BFS, main="Nodes BFS", ylab = "Nodes visitats")
qqline(nodes_BFS, col='red')

qqnorm(nodes_DFS, main="Nodes DFS", ylab = "Nodes visitats")
qqline(nodes_DFS, col='red')

qqnorm(temps_BFS, main="Temps BFS", ylab = "Temps (s)")
qqline(temps_BFS, col='red')

qqnorm(temps_DFS, main="Temps DFS", ylab = "Temps (s)")
qqline(temps_DFS, col='red')

qqnorm(nodes_B1000, main="Nodes BFS (1000)", ylab = "Nodes visitats")
qqline(nodes_B1000, col='red')

qqnorm(nodes_D1000, main="Nodes DFS (1000)", ylab = "Nodes visitats")
qqline(nodes_DFS, col='red')

qqnorm(temps_B1000, main="Temps BFS (1000)", ylab = "Temps (s)")
qqline(temps_B1000, col='red')

qqnorm(temps_D1000, main="Temps DFS (1000)", ylab = "Temps (s)")
qqline(temps_D1000, col='red')

# Boxplot
boxplot(nodes_BFS, nodes_DFS, main = "Nodes visitats", names = c("BFS", "DFS"), ylab = "Nº nodes", col = c('orange', 'blue'))

boxplot(temps_BFS, temps_DFS, main = "Temps", names = c("BFS", "DFS"), ylab = "Temps (s)", col = c('orange', 'blue'))

boxplot(nodes_B1000, nodes_D1000, main = "Nodes visitats (1000)", names = c("BFS", "DFS"), ylab = "Nº nodes", col = c('orange', 'blue'))

boxplot(temps_B1000, temps_D1000, main = "Temps (1000)", names = c("BFS", "DFS"), ylab = "Temps (s)", col = c('orange', 'blue'))

# Dispersió
plot(temps_BFS, main = "Temps BFS", xlab = "Nº laberint", ylab = "Temps (s)")
abline(lm(temps_BFS~lab), col = 'red')

plot(temps_DFS, main = "Temps DFS", xlab = "Nº laberint", ylab = "Temps (s)")
abline(lm(temps_DFS~lab), col = 'red')

plot(temps_B1000, main = "Temps BFS (1000)", xlab = "Nº laberint", ylab = "Temps (s)")
abline(lm(temps_B1000~lab1000), col = 'red')

plot(temps_D1000, main = "Temps DFS (1000)", xlab = "Nº laberint", ylab = "Temps (s)")
abline(lm(temps_D1000~lab1000), col = 'red')






