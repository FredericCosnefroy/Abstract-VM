#include <iostream>
#include <vector>
#include <sstream>
#include "eOperandType.hpp"
#include "Instruction.hpp"
#include "Parameter.hpp"
#include "Parser.hpp"

template<typename T> 
bool	Parser::isOfType( std::string const & value) {

	std::istringstream iss(value);
	std::stringstream ss;
	bool convertionIsValid;
	T i;

	convertionIsValid = iss >> std::fixed >> i >> std::fixed;
	ss << std::fixed << i;
	std::cout << iss.str() << " " << ss.str() << std::endl;
	return ((iss.str().compare(ss.str()) == 0) && convertionIsValid && iss.eof());
}

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

std::string 	 Parser::findValue( std::string const & data, eOperandType e) {

	size_t opPar = data.find_first_of("(");
	size_t clPar = data.find_first_of(")");
	std::string value;

	if (opPar > clPar || opPar == std::string::npos || clPar == std::string::npos)
		return ("");
	value = data.substr(opPar + 1, clPar - opPar - 1);
	switch (e) {
		case Int8 : return (isOfType<int16_t>(value) ? value : ""); break;
		case Int16 : return (isOfType<int16_t>(value) ? value : ""); break;
		case Int32 : return (isOfType<int32_t>(value) ? value : ""); break;
		case Float : return (isOfType<float>(value) ? value : ""); break;
		case Double : return (isOfType<double>(value) ? value : ""); break;
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
			if (data.compare(commands[i]) == 0)
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
	
	std::getline(std::cin, data);
	while (data.compare(";;") != 0) {
		Instruction *ins = new Instruction(getInstruction(data));
		if (instructionIsValid(*ins))
			insVec.push_back(ins);
		else
			std::cout << "Error at line " << lineNo << std::endl;
		std::getline(std::cin, data);
		lineNo++;
	}
	return (insVec);
}
