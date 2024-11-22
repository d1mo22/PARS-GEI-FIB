# Podem asignar valor a les variables
x = 10

# Podem fer operacions basiques amb les variables
y = x + 5
t = x - 5
z = x * y
w = z / x

# Les variables no necesiten tipus (Python)
x = "Hello, World!"

# Les variables son case-sensitive y acepten caracters unicode
println(π)
δ = 0.00001
안녕하세요 = "Hello"

# Vectors
v = [1, 2, 3, 4, 5]
a = v # a i v apunten a la mateixa direcció de memòria
a = copy(v) # a i v apunten a diferents direccions de memòria

# Matrius
m = [1 2 3; 4 5 6; 7 8 9]

# Depenent del sistema els enters poden ser de 32 o 64 bits
Sys.WORD_SIZE

# Podem fer servir tambe la notaicio hexadecimal/octal/binaria
x = 0x1f 
x = 0x1p0
x = 0b1010
x = 0o17

# Podem fer servir la notacio cientifica
x = 1.0e-3

# Podem fer servir la notacio de complexos
z = 1 + 2im

# Bucle per imprimir els rangs dels enters
for T in [Int8,Int16,Int32,Int64,Int128,UInt8,UInt16,UInt32,UInt64,UInt128]
    println("$(lpad(T,7)): [$(typemin(T)),$(typemax(T))]")
end

# Com tracta el overflow
x = typemax(Int64)
x + 1 == typemin(Int64)

# Podem fer servir numeros grans
x = big(2)^1000

# Operacions de coma flotant
x = 1.0 
y = 2.5e-4
# A la coma flotant tenim 2 0
0.0 == -0.0 #Pero son diferents en la representació binaria
bitstring(0.0)
bitstring(-0.0)

# Podem fer servir Float32
z = 0.5f0
# Podem fer servir Inf, -Inf, NaN
1/0 == Inf
1/Inf == 0.0
0/0 == NaN
Inf - Inf == NaN
Inf/Inf == NaN

(typemin(Float64), typemax(Float64))

# Podem fer servir _ per separar els nombres
10_000
0xdead_beef

# Podem veure quin es el seguent float representable
nextfloat(1.0)
prevfloat(1.0)