configure:
	cmake -S . -B build
	cmake --build build

.PHONY: build
build:
	cmake --build build

run:
	build/hello
