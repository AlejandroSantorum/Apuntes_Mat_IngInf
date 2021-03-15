all: compilar generar-stubs

clean:
	rm -rf *.class
compilar:
	javac HelloClient.java  HelloImpl.java  HelloInterface.java  HelloServer.java

generar-stubs:
	rmic -iiop HelloImpl
