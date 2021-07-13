all: src

lib:
	cd srclib && $(MAKE)

tests: lib
	cd test && $(MAKE)

src: lib
	cd src && $(MAKE)

.PHONY: cleansrc cleanlib cleantests clean
cleansrc:
	cd src && $(MAKE) clean

cleanlib:
	cd srclib && $(MAKE) clean

cleantests:
	cd test && $(MAKE) clean

clean: cleansrc cleanlib cleantests
	rm -rf *.o
