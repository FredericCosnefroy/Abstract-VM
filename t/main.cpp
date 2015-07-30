#include <iostream>
#include <vector>
#include "Parser.hpp"
#include "Instruction.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"
#include "VM.hpp"

int main( void ) {

	VM mv = VM(Parser::getInstructionList());
	mv.run();

	//std::cout << i3->toString() << std::endl;
	return (0);
}