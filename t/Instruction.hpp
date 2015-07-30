#ifndef INSTRUCTION_CLASS_HPP
# define INSTRUCTION_CLASS_HPP

#include <iostream>
#include "Parameter.hpp"
#include "eCommandName.hpp"

class Instruction {

private:
	int 			_commandIndex;
	eCommandName	_commandName;
	Parameter 	*	_parameter;
	bool		 	_expectsParameter;

public:
	Instruction( void );
	Instruction( int commandIndex, eCommandName commandName, bool expectsParameter );
	Instruction( Instruction const & src );

	virtual ~Instruction( void );

	Instruction 		&	operator=( Instruction const & rhs );

	int 					getCommandIndex( void ) const;
	eCommandName			getCommandName( void ) const;
	Parameter 			*	getParameter( void ) const;
	bool					expectsParameter( void ) const;

	void					setParameter( Parameter & parameter );
};

#endif