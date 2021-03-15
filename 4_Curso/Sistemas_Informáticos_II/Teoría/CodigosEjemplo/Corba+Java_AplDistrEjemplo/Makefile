all: generar-stubs compilar

clean:
	rm -rf HelloApp orb.db *.class
generar-stubs: 
	idlj -fall Hello.idl
compilar:
	javac *.java HelloApp/*java

