#include <iostream>
#include <vector>
#include <sstream>
#include "eOperandType.hpp"
#include "Instruction.hpp"
#include "Parameter.hpp"
#include "Parser.hpp"

eOperandType 	Parser::findOperand( std::string const & data, Instruction const & ins) {

	const std::string operands[] = {"int8", "int16", "int32", "float", "double"};

	unsigned int size = ins.getCommandIndex();

	if (data.size() < size + 8 || data[size] != ' ')
		return (Void);
	for (int i = 0; i < 5 ; i++) {
		if (data.compare(size + 1, operands[i].size(), operands[i]) == 0)
			return (static_cast<eOperandType> (i));
	}
	return (Void);
}

bool			Parser::checkComment( std::string const & data, size_t eoc )
{
	size_t comPos = data.find_first_of(";");

	if (comPos == std::string::npos)
		comPos = data.size();
	if (comPos < eoc)
		return (false);
	for (size_t i = eoc ; i < comPos ; i++)
	{
		if (data[i] != ' ')
			return (false);
	}
	return (true);
}

std::string 	 Parser::findValue( std::string const & data, eOperandType e) {

	size_t opPar = data.find_first_of("(");
	size_t clPar = data.find_first_of(")");
	std::string value;

	if (opPar > clPar || opPar == std::string::npos || clPar == std::string::npos)
		return ("");
	if (!checkComment(data, clPar + 1))
		return ("");
	value = data.substr(opPar + 1, clPar - opPar - 1);
	switch (e) {
		case Int8 : return (isOfType<int16_t>(value, true) ? value : ""); break;
		case Int16 : return (isOfType<int16_t>(value, false) ? value : ""); break;
		case Int32 : return (isOfType<int32_t>(value, false) ? value : ""); break;
		case Float : return (isOfType<float>(value, false) ? value : ""); break;
		case Double : return (isOfType<double>(value, false) ? value : ""); break;
		default : return ("");
	}
}

Parameter 			* Parser::findParameter( std::string const & data, Instruction const & ins) {

	eOperandType operand = findOperand(data, ins);
	if (operand != Void) {
		std::string value = findValue(data, operand);
		if (!value.empty()) {
			return (new Parameter(operand, value));
		}
	}
	return (NULL);
}

Instruction 		 Parser::findCommand( std::string const & data ) {

	const std::string commands[] = {	"push", "assert", "pop", "add", "sub", "mul",
										"div", "mod", "print", "dump", "exit" 		};
	bool expectsParam = true;

	for (int i = 0; i < 12 ; i++) {
		if (i >= 2) {
			if (data.compare(0, commands[i].size(), commands[i]) == 0 && checkComment(data, commands[i].size()))
				return (Instruction(commands[i].size(), static_cast<eCommandName>(i), !expectsParam));
		} else if (data.compare(0, commands[i].size(), commands[i]) == 0)
			return (Instruction(commands[i].size(), static_cast<eCommandName>(i), expectsParam));
	}
	return (Instruction());
}

Instruction 		Parser::getInstruction( std::string data ) {

	Instruction ins = findCommand(data);
	if (ins.getCommandName() != Unknown) {
		if (ins.expectsParameter()) {
			Parameter * param = findParameter(data, ins);
			ins.setParameter(*param);
		}
	}
	return (ins);
}

bool				Parser::instructionIsValid( Instruction const & ins ) {

	if ((ins.getCommandName() == Unknown || (ins.expectsParameter() && ins.getParameter() == NULL)))
		   return (false);
	return (true);
}

std::vector<Instruction const *> const 	 Parser::getInstructionList( void ) {

	std::vector<Instruction const *> insVec;
	std::string data;
	int lineNo = 1;
	
	do {
		std::getline(std::cin, data);
		if (std::cin.eof() || !data.compare(";;"))
			break;
		if (data.empty())
			continue;
		Instruction *ins = new Instruction(getInstruction(data));
		if (instructionIsValid(*ins))
			insVec.push_back(ins);
		else
			std::cout << "Error at line " << lineNo << std::endl;
		lineNo++;
	} while (true);
	return (insVec);
}
