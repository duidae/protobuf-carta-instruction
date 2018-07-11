#include <iostream>
#include <string>

using namespace std;

#include "Instruction.h"

int main(int argc, char* argv[])
{
	Instruction inst1("SET_CURSOR");
	Instruction inst2("START_ANIMATION_ACK");

	cout << "Instruction: " << inst1.getInstruction() << endl;
	cout << "Instruction: " << inst2.getInstruction() << endl;

	return 0;
}
