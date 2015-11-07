#ifndef OPERAND_HPP
#define OPERAND_HPP

#include <sstream>
#include <iostream>
#include "eOperandType.hpp"
#include "Parser.hpp"
#include "Factory.hpp"

template <typename T>
class Operand : public IOperand {

private:
	static Factory	_factory;
	eOperandType	_type;
	T 				_value;
	int 			_precision;
	std::string 	_str;

	Operand<T>( void );

public:

	class OverflowException : public std::exception {

    	public:
			virtual const char* what() const throw() {

				return ("overflow");
			}
    };

    class UnderflowException : public std::exception {

    	public:
			virtual const char* what() const throw() {

				return ("underflow");
			}
    };

	Operand<T>( eOperandType type, T const & value ) : _type(type), _value(value) {

		std::stringstream sstream;

		if (_type == Float || _type == Double)
			_precision = digitCount(value) + 4;
		else
			_precision = 0;
		sstream.precision(_precision);
		if (_type == Int8)
			sstream << static_cast<int16_t>(_value);
		else
			sstream << _value;
		_str = std::string(sstream.str());


	}

	Operand<T>( Operand<T> const & src ) : _type(src.getType()), _value(src.getValue()), _str(src.toString()) {

	}

	Operand<T> & operator=( Operand<T> const & rhs ) {

		_type = rhs.getType();
		_value = rhs.getValue();
		_str = rhs.toString();
		_precision = rhs.getPrecision();
		return (*this);
	}

	int digitCount(T const & value) {

	int64_t number = (int64_t) value;
    int digits = 0;
    if (number < 0) digits = 1;
    while (number) {
        number /= 10;
        digits++;
	}
    return (digits);
}

	int 				getPrecision( void ) const {

		return (_precision);
	}

	eOperandType 		getType( void ) const {

		return (_type);
	}

	T 					getValue( void ) const {

		return (_value);
	}

	void				throwException( std::string const & str, eOperandType type ) const {

		switch(type)
		{
			case Int8:
			if (Parser::isPositive<int16_t>(str))
				throw Operand::OverflowException();
			throw Operand::UnderflowException();
			break;

			case Int16:
			if (Parser::isPositive<int16_t>(str))
				throw Operand::OverflowException();
			throw Operand::UnderflowException();
			break;

			case Int32:
			if (Parser::isPositive<int32_t>(str))
				throw Operand::OverflowException();
			throw Operand::UnderflowException();
			break;

			case Float:
			if (Parser::isPositive<float>(str))
				throw Operand::OverflowException();
			throw Operand::UnderflowException();
			break;

			case Double:
			if (Parser::isPositive<double>(str))
				throw Operand::OverflowException();
			throw Operand::UnderflowException();
			break;
			
			default:break;
		}
	}

	void				checkRange( eOperandType const & newType, std::stringstream const & sstream ) const {

		switch(newType)
		{
			case Int8:
			if (!Parser::isOfType<int16_t>(sstream.str(), true))
				throwException(sstream.str(), newType);
			break;

			case Int16:
			if (!Parser::isOfType<int16_t>(sstream.str(), false))
				throwException(sstream.str(), newType);
			break;

			case Int32:
			if (!Parser::isOfType<int32_t>(sstream.str(), false))
				throwException(sstream.str(), newType);
			break;

			case Float:
			if (!Parser::isOfType<float>(sstream.str(), false))
				throwException(sstream.str(), newType);
			break;

			case Double:
			if (!Parser::isOfType<double>(sstream.str(), false))
				throwException(sstream.str(), newType);
			break;
			
			default:break;
		}
	}


	IOperand const *	operator+( IOperand const & rhs ) const {

		eOperandType 		newType = (_type < rhs.getType() ? rhs.getType() : _type);
		int					newPrecision = (_precision < rhs.getPrecision() ? rhs.getPrecision() : _precision);
		std::string 		rhsStr = rhs.toString();
		double				rhsValue;

		std::stringstream 	sstream;
		std::istringstream 	isstream;

		isstream.str(rhsStr);
		isstream >> rhsValue;

		double value = (_value + rhsValue);

		sstream.precision(newPrecision);
		sstream << std::fixed << value;

		checkRange(newType, sstream);

		return (_factory.createOperand(newType, sstream.str()));
	}

	IOperand const * 	operator-( IOperand const & rhs ) const {

		eOperandType 		newType = (_type < rhs.getType() ? rhs.getType() : _type);
		int					newPrecision = (_precision < rhs.getPrecision() ? rhs.getPrecision() : _precision);
		std::string 		rhsStr = rhs.toString();
		double				rhsValue;

		std::stringstream 	sstream;
		std::istringstream 	isstream;

		isstream.str(rhsStr);
		isstream >> rhsValue;

		double value = (_value - rhsValue);
		
		sstream.precision(newPrecision);
		sstream << std::fixed << value;

		checkRange(newType, sstream);

		return (_factory.createOperand(newType, sstream.str()));
	}

	IOperand const * 	operator*( IOperand const & rhs ) const {

		eOperandType 		newType = (_type < rhs.getType() ? rhs.getType() : _type);
		int					newPrecision = (_precision < rhs.getPrecision() ? rhs.getPrecision() : _precision);
		std::string 		rhsStr = rhs.toString();
		double				rhsValue;

		std::stringstream 	sstream;
		std::istringstream 	isstream;

		isstream.str(rhsStr);
		isstream >> rhsValue;

		double value = (_value * rhsValue);
		
		sstream.precision(newPrecision);
		sstream << std::fixed << value;

		checkRange(newType, sstream);

		return (_factory.createOperand(newType, sstream.str()));
	}

	IOperand const * 	operator/( IOperand const & rhs ) const {

		eOperandType 		newType = (_type < rhs.getType() ? rhs.getType() : _type);
		int					newPrecision = (_precision < rhs.getPrecision() ? rhs.getPrecision() : _precision);
		std::string 		rhsStr = rhs.toString();
		double				rhsValue;

		std::stringstream 	sstream;
		std::istringstream 	isstream;

		isstream.str(rhsStr);
		isstream >> rhsValue;

		double value = (_value / rhsValue);
		
		sstream.precision(newPrecision);
		sstream << std::fixed << value;

		checkRange(newType, sstream);

		return (_factory.createOperand(newType, sstream.str()));
	}

	IOperand const * 	operator%( IOperand const & rhs ) const {

		eOperandType newType = (_type < rhs.getType() ? rhs.getType() : _type);
		std::string rhsStr = rhs.toString();
		int64_t rhsValue;

		std::stringstream sstream;
		std::istringstream isstream;

		isstream.str(rhsStr);
		isstream >> rhsValue;

		int64_t value = ((int64_t)_value % rhsValue);

		sstream << value;
		return (_factory.createOperand(newType, sstream.str()));
	}

	std::string const & toString( void ) const {

		return (_str);
	}

	virtual ~Operand<T>( void ) {};

};
template<typename T>
Factory Operand<T>::_factory = Factory();
#endif