#include <iostream>
#include <vector>
#include <sstream>
#include "VM.hpp"
#include "IOperand.hpp"
#include "Factory.hpp"


VM::VM(std::vector<Instruction const *> const & instructions) : _instructions(instructions) {

}

VM::VM( VM const & src ) : _stack(src.getStack()), _instructions(src.getInstructions()) {

}

VM &	VM::operator=( VM const & rhs ) {

	_stack = rhs.getStack();
	_instructions = rhs.getInstructions();
	return (*this);
}

std::vector<IOperand const *> const & VM::getStack( void ) const {

	return (_stack);
}

std::vector<Instruction const *> const & VM::getInstructions( void ) const {

	return (_instructions);
}

void		VM::push( IOperand const & o ) {

	_stack.push_back(&o);
}

IOperand const *VM::pop( void ) {

	if (_stack.size() != 0) {
		const IOperand * tmp;
		tmp = _stack.back();
		_stack.pop_back();
		return (tmp);
	}
	std::cout << "Pop on empty stack" << std::endl;
	return (NULL);
}

void		VM::dump( void ) {

	for (int i = _stack.size() - 1; i > 0; i--)
		std::cout << _stack.at(i)->toString() << std::endl; 
}

void		VM::assert( IOperand const & o ) {

	std::istringstream iss;
	double thisValue;
	double operandValue;

	iss.str(_stack.back()->toString());
	iss >> thisValue;
	iss.clear();
	iss.str(o.toString());
	iss >> operandValue;
	bool operandsHaveSameType = (_stack.back()->getType() == o.getType());
	bool operandsAreEqual = (thisValue == operandValue);
	if (!(operandsAreEqual && operandsHaveSameType))
		std::cout << "Assertion failed " << thisValue  << " " << operandValue << std::endl;
}

void		VM::add( void ) {

	const IOperand * op1 = this->pop();
	const IOperand * op2 = this->pop();
	this->push(*(*op1 + *op2));
	delete op1;
	delete op2;
}

void		VM::sub( void ) {

	const IOperand * op1 = this->pop();
	const IOperand * op2 = this->pop();
	this->push(*(*op1 + *op2));
	delete op1;
	delete op2;
}

void		VM::mul( void ) {

	const IOperand * op1 = this->pop();
	const IOperand * op2 = this->pop();
	this->push(*(*op1 + *op2));
	delete op1;
	delete op2;
}

void		VM::div( void ) {

	const IOperand * op1 = this->pop();
	const IOperand * op2 = this->pop();
	this->push(*(*op1 + *op2));
	delete op1;
	delete op2;
}

void		VM::mod( void ) {

	const IOperand * op1 = this->pop();
	const IOperand * op2 = this->pop();
	this->push(*(*op1 + *op2));
	delete op1;
	delete op2;
}

void		VM::print( void ) {

	Factory factory;
	std::string stringValue = _stack.back()->toString();
	IOperand const * operand = factory.createOperand(Int8, stringValue);

	this->assert(*operand);

	int16_t character;
	std::istringstream iss(stringValue);
	
	iss >> character;

	std::cout << static_cast<int8_t>(character);
	delete operand;
}

void		VM::exit( void ) {

	exit();
}

void		VM::execute( Factory const & factory ) {

	void (VM::*voidInstructions[])( void ) =	{
														&VM::add,
														&VM::sub,
														&VM::mul,
														&VM::div,
														&VM::mod,
														&VM::print,
														&VM::dump,
														&VM::exit
												};
	void (VM::*paramInstructions[])( IOperand const & ) = 	{
																	&VM::push,
																	&VM::assert
																};

	Instruction const * i = _instructions.at(0);
	eCommandName name = i->getCommandName();
	_instructions.erase(_instructions.begin());

	if (name == Push || name == Assert) {
		IOperand const * newOperand = factory.createOperand(i->getParameter()->getOperand(),
															i->getParameter()->getValue());
		((this->*paramInstructions[static_cast<int>(name)])(*newOperand));
	} else if (name == Pop) {
		this->pop();
	} else {
		((this->*voidInstructions[static_cast<int>(name) - 3])());
	}
	delete i;
}

void 	VM::run( void ) {

	Factory factory;
	while (_instructions.size() > 0) {
		execute( factory );
	}
}





