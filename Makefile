# See README.txt.

.PHONY: all cpp clean

all: cpp

cpp: testPBTranslator

clean:
	rm -f testPBTranslator

testPBTranslator: testPBTranslator.cpp
	pkg-config --cflags protobuf  # fails if protobuf is not installed
	c++ -std=c++11 testPBTranslator.cpp Instruction.cpp PBTranslator.cpp protobuf/InstructionMsgBook.pb.cc -o testPBTranslator `pkg-config --cflags --libs protobuf`
