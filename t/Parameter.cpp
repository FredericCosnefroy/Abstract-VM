#include <iostream>
#include "Parameter.hpp"
#include "eOperandType.hpp"

Parameter::Parameter(eOperandType operand, std::string const & value) : _operand(operand), _value(value) {

}

Parameter::Parameter(Parameter const & src) : _operand(src.getOperand()), _value(src.getValue()) {

}

Parameter::~Parameter() {

}

Parameter 			&	Parameter::operator=(Parameter const & rhs) {

	_operand = rhs.getOperand();
	_value = rhs.getValue();
	return (*this);
}

eOperandType 			Parameter::getOperand( void ) const {

	return (_operand);
}

std::string const	&	Parameter::getValue( void ) const {

	return (_value);
}