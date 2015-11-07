#include <iostream>
#include <vector>
#include "Parser.hpp"
#include "Instruction.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"
#include "VM.hpp"

int main( void ) {

	VM mv = VM(Parser::getInstructionList());
	try { mv.run(); }
	catch(VM::TerminateException & e) { return (0); }
	catch(std::exception & e) { std::cout << "Error at line " << mv.getLine() << ": " << e.what() << std::endl; return (-1); }

	std::cout << "Error: exit call not found" << std::endl;
	return (0);
}