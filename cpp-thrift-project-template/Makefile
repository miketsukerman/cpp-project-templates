all: build

conan-install: 
	conan install -if build .

conan-build: conan-install
	conan build -bf build .

build: conan-build

info: 
	conan info --graph=dependencies.dot .

run: build 
	./build/bin/sample_app

test: build 
	make -C build test