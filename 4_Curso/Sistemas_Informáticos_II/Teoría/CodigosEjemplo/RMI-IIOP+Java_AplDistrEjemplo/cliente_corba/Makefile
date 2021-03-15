all: generar-idl generar-esqueletos compilar 

clean:
	rm -rf *.class 
	rm  HelloInterfaceHolder.java  HelloInterfaceOperations.java HelloInterfaceHelper.java  HelloInterface.java _HelloInterfaceStub.java HelloInterface.idl

compilar:
	javac *.java
	
generar-idl:
	rmic -classpath .. -idl HelloImpl

generar-esqueletos:
	idlj -i /usr/lib/jvm/java-8-oracle/lib/ HelloInterface.idl
	

