#include <iostream>
#include "Instruction.hpp"
#include "Parameter.hpp"
#include "eCommandName.hpp"

Instruction::Instruction( void ) : 	_commandIndex(-1),
									_commandName(Unknown),
									_parameter(NULL),
									_expectsParameter(false) {

}

Instruction::Instruction( int commandIndex, eCommandName commandName, bool expectsParameter ) :	_commandIndex(commandIndex),
																								_commandName(commandName),
																								_parameter(NULL),
																								_expectsParameter(expectsParameter) {

}

Instruction::Instruction( Instruction const & src ) : 	_commandIndex(src.getCommandIndex()),
														_commandName(src.getCommandName()),
														_parameter(src.getParameter()),
														_expectsParameter(src.expectsParameter()) {


}

Instruction::~Instruction( void ) {

	delete _parameter;
}

Instruction 		&	Instruction::operator=( Instruction const & rhs ) {

	_commandIndex = rhs.getCommandIndex();
	_commandName = rhs.getCommandName();
	_parameter = rhs.getParameter();
	_expectsParameter = rhs.expectsParameter();
	return (*this);
}

int 					Instruction::getCommandIndex( void ) const {

	return (_commandIndex);
}

eCommandName 			Instruction::getCommandName( void ) const {

	return (_commandName);
}

Parameter 			*	Instruction::getParameter( void ) const {

	return (_parameter);
}

bool					Instruction::expectsParameter( void ) const {

	return (_expectsParameter);
}

void					Instruction::setParameter( Parameter & parameter ) {

	_parameter = &parameter;
}