#include "Int8.class.hpp"


Int8::Int8(int8_t value) _value(value) {

}

Int8::Int8(int8_t const & src) {

	_value = src.getValue();
}

virtual Int8::~Int8( void ) {

}

int 				Int8::getPrecision( void ) const {

	return (sizeof(_value));
}

eOperandType 		Int8::getType( void ) const {

}

int8_t				Int8::getValue( void ) const {

	return (_value);
}

IOperand const *	Int8::operator+( IOperand const & rhs ) const {

	if (_precision > rhs.getPrecision())
		return (new Int8(_value + rhs.getValue));
}

IOperand const * 	Int8::operator-( IOperand const & rhs ) const {

	if (_precision > rhs.getPrecision())
		return (new Int8(_value - rhs.getValue));
}

IOperand const * 	Int8::operator*( IOperand const & rhs ) const {

	if (_precision > rhs.getPrecision())
		return (new Int8(_value * rhs.getValue));
}

IOperand const * 	Int8::operator/( IOperand const & rhs ) const {

	if (_precision > rhs.getPrecision())
		return (new Int8(_value / rhs.getValue));
}

IOperand const * 	Int8::operator%( IOperand const & rhs ) const {

	if (_precision > rhs.getPrecision())
		return (new Int8(_value % rhs.getValue));
}

std::string const & Int8::toString( void ) const {

} // String representation of the instance

IOperand const &	Int8::operator=( IOperand const & rhs ) {

	_value = rhs.getValue();
}