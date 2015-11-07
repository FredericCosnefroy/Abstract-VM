#include <iostream>
#include <sstream>
#include "Factory.hpp"
#include "IOperand.hpp"
#include "eOperandType.hpp"
#include "Operand.hpp"

Factory::Factory( void ) {

}

IOperand const * Factory::createInt8( std::string const & value ) const {

	std::istringstream isstream;
	int16_t n;

	isstream.str(value);
	isstream >> n;
	return (new Operand<int8_t>(Int8, n));
}

IOperand const * Factory::createInt16( std::string const & value ) const {

	std::istringstream isstream;
	int16_t n;

	isstream.str(value);
	isstream >> n;
	return (new Operand<int16_t>(Int16, n));

}

IOperand const * Factory::createInt32( std::string const & value ) const {

	std::istringstream isstream;
	int32_t n;

	isstream.str(value);
	isstream >> n;
	return (new Operand<int32_t>(Int32, n));
}

IOperand const * Factory::createFloat( std::string const & value ) const {

	std::istringstream isstream;
	float n;

	isstream.str(value);
	isstream >> n;
	return (new Operand<float>(Float, n));
}

IOperand const * Factory::createDouble( std::string const & value ) const {

	std::istringstream isstream;
	double n;

	isstream.str(value);
	isstream >> n;
	return (new Operand<double>(Double, n));
}

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const {

	IOperand const * (Factory::*ptr[])(std::string const &) const = {
																	 	&Factory::createInt8,
																	 	&Factory::createInt16,
																	 	&Factory::createInt32,
																	 	&Factory::createFloat,
																	 	&Factory::createDouble
																	};									
	return ((this->*ptr[static_cast<int>(type)])(value));
}