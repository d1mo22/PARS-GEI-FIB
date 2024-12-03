export CLASSPATH=".:./lib/AIMA.jar:./lib/Azamon.jar"
rm -f Main.class ./IA/Azamon/*.class
javac -d . ./IA/Azamon/*.java
javac ./IA/Azamon/Main.java
java IA/Azamon/Main

rm -f ./IA/Azamon/*.class


