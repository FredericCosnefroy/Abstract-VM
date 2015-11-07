#ifndef PARSER_HPP
# define PARSER_HPP

#include <iostream>
#include <vector>
#include <sstream>

#include "Instruction.hpp"
#include "Parameter.hpp"

class Parser {

private:
	Parser( void );

	static eOperandType 					findOperand( std::string const & data, Instruction const & ins);
	static bool								checkComment( std::string const & data, size_t eoc );
	static std::string 	 					findValue( std::string const & data, eOperandType e );
	static Parameter 			 		*	findParameter( std::string const & data, Instruction const & ins );
	static Instruction 						findCommand( std::string const & data );
	static Instruction 						getInstruction( std::string data );
	static bool								instructionIsValid( Instruction const & i );
	
public:
	
	virtual ~Parser( void );

	static std::vector<Instruction const *> const 		getInstructionList( void );

	template<typename T>
	static bool	isOfType( std::string const & value, bool spec) {

		std::istringstream iss(value);
		std::stringstream ss;
		bool convertionIsValid;
		T i;

		convertionIsValid = iss >> i;
		if (spec && (i < SCHAR_MIN || i > SCHAR_MAX))
			return (false);
		
		ss << i;
		
		return (convertionIsValid && iss.eof());
	}


	template<typename T>
	static bool	isPositive( std::string const & value) {

		std::istringstream iss(value);
		T i;

		iss >> i;
		return (i > 0);
	}

};

#endif