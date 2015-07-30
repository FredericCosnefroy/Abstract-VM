#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <sstream>
#include <iostream>
#include "eOperandType.hpp"
#include "Factory.hpp"

template <typename T>
class Operand : public IOperand {

private:
	static Factory	_factory;
	eOperandType	_type;
	T 				_value;

	Operand<T>( void );
public:

	
	Operand<T>( eOperandType type, T const & value ) : _type(type), _value(value) {

	}

	Operand<T>( Operand<T> const & src ) : _type(src.getType()), _value(src.getValue()) {

	}

	Operand<T> & operator=( Operand<T> const & rhs ) {

		_type = rhs.getType();
		_value = rhs.getValue();
		return (*this);
	}

	int 				getPrecision( void ) const {

		return (0);
	}

	eOperandType 		getType( void ) const {

		return (_type);
	}

	T 					getValue( void ) const {

		return (_value);
	}

	IOperand const *	operator+( IOperand const & rhs ) const {

		eOperandType newType = (_type < rhs.getType() ? rhs.getType() : _type);
		std::string rhsStr = rhs.toString();
		long double rhsValue;

		std::stringstream sstream;
		std::istringstream isstream;

		isstream.str(rhsStr);
		isstream >> rhsValue;

		long double value = (_value + rhsValue);

		if (_type == Float || _type == Double) {
			if (static_cast<T>(value) != (static_cast<long double>(_value + rhsValue)))
				std::cout << "FATAL: (Over|Under)flow" << std::endl;
		}
		else {
			if (static_cast<T>(value) != static_cast<long int>((static_cast<double>(_value + rhsValue))))
				std::cout << "FATAL: (Over|Under)flow" << std::endl;
		}
		sstream << value;
		return (_factory.createOperand(newType, sstream.str()));
	}

	IOperand const * 	operator-( IOperand const & rhs ) const {

		eOperandType newType = (_type < rhs.getType() ? rhs.getType() : _type);
		std::string rhsStr = rhs.toString();
		double rhsValue;

		std::stringstream sstream;
		std::istringstream isstream;

		isstream.str(rhsStr);
		isstream >> rhsValue;

		double value = static_cast<double>(_value - rhsValue);
		sstream << value;

		//delete &rhsStr;
		return (_factory.createOperand(newType, sstream.str()));
	}

	IOperand const * 	operator*( IOperand const & rhs ) const {

		eOperandType newType = (_type < rhs.getType() ? rhs.getType() : _type);
		std::string rhsStr = rhs.toString();
		double rhsValue;

		std::stringstream sstream;
		std::istringstream isstream;

		isstream.str(rhsStr);
		isstream >> rhsValue;

		double value = static_cast<double>(_value * rhsValue);
		sstream << value;

		//delete &rhsStr;
		return (_factory.createOperand(newType, sstream.str()));
	}

	IOperand const * 	operator/( IOperand const & rhs ) const {

		eOperandType newType = (_type < rhs.getType() ? rhs.getType() : _type);
		std::string rhsStr = rhs.toString();
		double rhsValue;

		std::stringstream sstream;
		std::istringstream isstream;

		isstream.str(rhsStr);
		isstream >> rhsValue;

		double value = static_cast<double>(_value / rhsValue);
		sstream << value;

		//delete &rhsStr;
		return (_factory.createOperand(newType, sstream.str()));
	}

	IOperand const * 	operator%( IOperand const & rhs ) const {

		eOperandType newType = (_type < rhs.getType() ? rhs.getType() : _type);
		std::string rhsStr = rhs.toString();
		int32_t rhsValue;

		std::stringstream sstream;
		std::istringstream isstream;

		isstream.str(rhsStr);
		isstream >> rhsValue;

		int32_t value = static_cast<int32_t>(_value + rhsValue);
		sstream << value;

		return (_factory.createOperand(newType, sstream.str()));
	}

	std::string const & toString( void ) const {

		std::stringstream sstream;
		std::string  * str;

		if (_type == Int8)
			sstream << static_cast<int16_t>(_value);
		else
			sstream << _value;
		str = new std::string(sstream.str());
		return (*str);
	}

	virtual ~Operand<T>( void ) {};

};
template<typename T>
Factory Operand<T>::_factory = Factory();
#endif