.PHONY: all makebin build cls doc

all: makebin doc

makebin: cls build

cls:
	clear

build:
	$(CXX) logmlsl.cpp -o logmlsl.exe -std=c++98 -pedantic

doc:
	doxygen