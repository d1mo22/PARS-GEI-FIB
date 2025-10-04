#  READING CREDSCO.CSV. NOTE: Change the path of the file for the proper one in your computer

#Note: Take care to use "/" fo the directory file. "\" provides errors

setwd("/Users/davidmorais/Desktop/PARS-GEI-FIB/Obligatories/Q7/MD")

dd <- read.table("credsco.csv",header=T);

#dd <- read.table("credsco.csv",header=T, sep=";",na.strings="\"\"");
dd <- read.table("credsco.csv",header=T, sep=";");

class(dd)
dim(dd)
n<-dim(dd)[1]
n
K<-dim(dd)[2]
K
names(dd)


#select some variables
#DO NOT INCLUDE identifiers in the analysis!!!!
#actives<-c(9,10:14)
#ddActives<-dd[,actives]
#CAre! update K

#seleccion some rows
#Dselection<-dd[Condition, ]

#Learning
# FIRST CONTROL: MAXIMS, MINIMUMS, ... (FINDING ERRORS AND OUTLIERS)
# WHICH RESPONSE?
# WHICH ARE CATEGORICAL AND WHICH ARE CONTINUOUS?
# ARE THERE MISSINGS?

hist(dd[,14])
hist(dd$Precio.del.bien.financiado)
boxplot(dd[,14], main=paste("Boxplot of", names(dd)[14]))
boxplot(dd[,14],horizontal=TRUE, main=paste("Boxplot of", names(dd)[14]))
summary(dd[,14])
sd(dd$Precio.del.bien.financiado)
cv<-sd(dd$Precio.del.bien.financiado)/mean(dd$Precio.del.bien.financiado)
cv


summary(dd)
#anyadir stdev de cada variable


attach(dd)

summary(dd[,14])
summary(Precio.del.bien.financiado)
hist(Precio.del.bien.financiado)
boxplot(Precio.del.bien.financiado, horizontal=TRUE, main=paste("Boxplot of", names(dd)[14]))
boxplot(Precio.del.bien.financiado,  main=paste("Boxplot of", names(dd)[14]))


summary(Dictamen)
boxplot(Dictamen)
#end learning

# DECLARE CATEGORICAL 
#identify which categorical are not recognized by the system yet
names(dd)
class(dd)
class(dd[,1])
sapply(dd, class)


#declare factors
Dictamen    <- as.factor(Dictamen)
Vivienda     <- factor(Vivienda)
Estado.civil <- factor(Estado.civil)
Registros   <- factor(Registros)
Tipo.trabajo <-factor(Tipo.trabajo)

mean(Dictamen)
class(Dictamen)


#look at modalities

dfactor<-c(2:K)
sapply(dd[,dfactor],levels)

levels(Dictamen)

levels(Vivienda)
levels(Estado.civil)
levels(Registros)
levels(Tipo.trabajo)

class(Dictamen)
class(dd[,1])
summary(Dictamen)
summary(dd[,1])
barplot(table(Dictamen))
pie(table(Dictamen))

pie(table(Vivienda))

#labelling modalities, when required. Check dictionary. WARNING: Sequential assignment with levels

levels(Dictamen) <- c(NA, "positiu","negatiu")
table(Dictamen)
table(Dictamen, useNA="ifany")

levels(Vivienda) <- c("VivUnkown", "lloguer","escriptura","contr_privat","ignora_cont","pares","altres viv")
pie(table(Vivienda))
levels(Estado.civil) <- c("ECUnknown", "solter","casat","vidu","separat","divorciat")
levels(Registros) <- c("reg_no","reg_si")
#levels(Tipo.trabajo) <- c("WorkingTypeUnknown","fixe","temporal","autonom","altres sit")
Tipo.trabajo<-factor(Tipo.trabajo, levels=c( "1", "2", "3", "4", "0"), labels=c("fixe","temporal","autonom","altres sit", "WorkingTypeUnknown"))

#relabelling<-c(,,,)
#for (k in relabelling){levels(dd[,k]) <- c(NA, "positiu","negatiu")}

#ordering modalities!
Tipo.trabajo <- factor(Tipo.trabajo, ordered=TRUE,  levels= c("WorkingTypeUnknown","temporal","fixe","autonom","altres sit"))
frecs<-table(Tipo.trabajo)

#recodificacions
table(Tipo.trabajo)
newvalues<-c("WTUnk","Fix","Temp","Auto","Other")
Tipo.trabajo <- newvalues[ match(Tipo.trabajo,
                                 c("WorkingTypeUnknown","fixe",                                             
                                   "temporal","autonom","altres sit"
                                 )
) 
]

table(Tipo.trabajo)
frecs<-table(Tipo.trabajo)
barplot(frecs, las=3, cex.names=0.7, main=paste("Barplot of", "Tipo.trabajo"))


class(Dictamen)
class(dd[,1])

dd[,1]<-Dictamen
dd[,3]<-Vivienda
dd[,6]<-Estado.civil
dd[,7]<-Registros
dd[,8]<-Tipo.trabajo

class(dd[,1])


write.table(dd, file = "credscoCategoriques.csv", sep = ";", na = "NA", dec = ".", row.names = FALSE, col.names = TRUE)


#Multivalued

components<- c(indexes of columns containing modalities of the variable)
freqs<-NULL
for (k in components){
  newvalues<-c(paste(names(dd)[k],"Si",sep"")), "No)
     dd[,k]<-newvalues[match(dd[,k],c("Si","No))]
freqs[k]<-table(dd[,1])[1]
}
barplot(freqs)


class(Dictamen)
class(dd[,1])

dd[,1]<-Dictamen
dd[,3]<-Vivienda
dd[,6]<-Estado.civil
dd[,7]<-Registros
dd[,8]<-Tipo.trabajo

class(dd[,1])
View(dd)

summary(dd)

table(dd[,8])
barplot(table(dd[,8]))
pie(table(dd[,8]))

#more efficiently
frecs<-table(dd[,8])
barplot(frecs)

pie(frecs)



#To treat all categorical variables at one

dcat<- c(1,2,3,6,7,8)
dd[,dcat]<-lapply(dd[,dcat],factor)
lapply(dd[,dcat],levels)


#graphical loops with stops
par(ask=TRUE)
for(k in varNum){hist(dd[,k], main=paste("Histogram of", names(dd)[k]))}
par(ask=FALSE)

#Output graphs to a pdf
pdf("outputs/informeDescripCredsCo.pdf")
for(k in varNum){hist(dd[,k], main=paste("Histogram of", names(dd)[k]))}
dev.off()

#output console to a doc file
sink("outputs/informeDescripCredsCo.doc")
names(dd)
#care, graphs are skipped
hist(dd[,14])
sink()
names(dd)



hist(dd[,10])
boxplot(dd[,10])

#save transformation
write.table(dd, file = "credscoCategoriques.csv", sep = ";", na = "NA", dec = ".", row.names = FALSE, col.names = TRUE)

max(dd$total_of_special_requests)
min(dd$total_of_special_requests)
