#ifndef PARAMETER_HPP
# define PARAMETER_HPP

#include <iostream>
#include "eOperandType.hpp"

class Parameter {

private:
	Parameter();
	eOperandType	_operand;
	std::string 	_value;

public:
	Parameter(eOperandType operand, std::string const & value);
	Parameter(Parameter const & src);
	virtual ~Parameter();

	Parameter 			&	operator=(Parameter const & rhs);

	eOperandType			getOperand( void ) const;
	std::string const	&	getValue( void ) const;

};

#endif