#Makefile for BlockEditor
# @author Marek Kalabza
# @author Petr Knetl

all: prepare

prepare:
	qmake src/BlockEditor.pro -o src/Makefile
	make -B CXX=g++ -C src
	mv src/BlockEditor src/blockeditor

run: prepare
	src/blockeditor

clean:
	rm src/blockeditor -rf
	rm src/*.o -rf
	rm src/Makefile -rf
	rm -rf xkalab09-xknetl00.zip
	rm doc/* -rf

doxygen:
	doxygen Doxyfile

zip: clean
	zip -r xkalab09-xknetl00 Doxyfile Makefile doc/ src/ examples/ readme.md
