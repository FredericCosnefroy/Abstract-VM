#ifndef PARSER_HPP
# define PARSER_HPP

#include <iostream>
#include <vector>

#include "Instruction.hpp"
#include "Parameter.hpp"

class Parser {

private:
	Parser( void );

	template<typename T> 
	static bool								isOfType( std::string const & value);

	static eOperandType 					findOperand( std::string const & data, Instruction const & ins);
	static std::string 	 					findValue( std::string const & data, eOperandType e );
	static Parameter 			 		*	findParameter( std::string const & data, Instruction const & ins );
	static Instruction 						findCommand( std::string const & data );
	static Instruction 						getInstruction( std::string data );
	static bool								instructionIsValid( Instruction const & i );
	
public:
	
	virtual ~Parser( void );

	static std::vector<Instruction const *> const 		getInstructionList( void );
};

#endif