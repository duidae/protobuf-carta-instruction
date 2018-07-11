#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#include "Instruction.h"
#include "PBTranslator.h"

int Add_instruction_to_file(Instruction& inst, char* filename)
{
	tutorial::InstructionMsgBook instMsgBook;
	PBTranslator pbtranslator;

	{
		// Read the existing instruction message book.
		fstream input(filename, ios::in | ios::binary);
		if (!input) {
			cout << filename << ": File not found.  Creating a new file." << endl;
		} else if (!instMsgBook.ParseFromIstream(&input)) {
			cerr << "Failed to read instruction message book file." << endl;
			return -1;
		}
	}

	{
		// use protocol buffer to encode instruction
		pbtranslator.encode(inst, instMsgBook.add_inst());
		cout << "[Save instruction to " << filename << "]" << endl;
		cout << inst.getInstruction() << endl;
	}

	{
		// Write the new instruction message book back to disk.
		fstream output(filename, ios::out | ios::trunc | ios::binary);
		if (!instMsgBook.SerializeToOstream(&output)) {
			cerr << "Failed to write message." << endl;
			return -1;
		}
	}

	return 0;
}

int Read_instruction_from_file(char* filename)
{
	tutorial::InstructionMsgBook instMsgBook;
	PBTranslator pbtranslator;

	{
		// Read the existing instruction message book.
		fstream input(filename, ios::in | ios::binary);
		if (!instMsgBook.ParseFromIstream(&input)) {
			cerr << "Failed to parse instruction message book." << endl;
			return -1;
		}

		cout << "\n[List saved instruction in " << filename << "]" << endl;
		for (int i = 0; i < instMsgBook.inst_size(); i++) {
			Instruction inst;
			pbtranslator.decode(inst, instMsgBook.inst(i));

			cout << "Instruction: " << inst.getInstruction() << endl;
		}
	}

	return 0;
}

int main(int argc, char* argv[])
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	if (argc != 2) {
		cerr << "Usage:  " << argv[0] << " INSTRUCTION_FILE" << endl;
		return -1;
	}

	Instruction inst1("SET_CURSOR");

	// add instruction to file
	if(Add_instruction_to_file(inst1, argv[1]) < 0) {
		cout << "Add instruction to " << argv[1] << " error." << endl;
		return -1;
	}

	// read instruction from file
	if(Read_instruction_from_file(argv[1]) < 0) {
		cout << "Read instruction from " << argv[1] << " error." << endl;
		return -1;
	}

	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}
