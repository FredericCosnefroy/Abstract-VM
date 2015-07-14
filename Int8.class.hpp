#ifndef INT8_CLASS_HPP
# define INT8_CLASS_HPP

#include <iostream>
#include <cstdint>
#include "IOperand.class.hpp"

class Int8 : public IOperand {

public:
	Int8(int8_t value);
	Int8(int8_t const & src);
	virtual ~Int8( void );

	int8_t				getValue( void ) const;
	int 				getPrecision( void ) const; // Precision of the type of the instance
	eOperandType 		getType( void ) const; // Type of the instance
	IOperand const *	operator+( IOperand const & rhs ) const; // Sum
	IOperand const * 	operator-( IOperand const & rhs ) const; // Difference
	IOperand const * 	operator*( IOperand const & rhs ) const; // Product
	IOperand const * 	operator/( IOperand const & rhs ) const; // Quotient
	IOperand const * 	operator%( IOperand const & rhs ) const; // Modulo
	std::string const & toString( void ) const; // String representation of the instance

	IOperand const &	operator=(IOperand const & rhs);

private:
	Int8();
	int8_t _value;

};

#endif