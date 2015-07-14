#include <iostream>
#include "Machine.class.hpp"
#include "IOperand.class.hpp"
#include <stack>

Machine::Machine() {

}

Machine::Machine( Machine const & src ) {

	_stack = src.getStack();
}

Machine &	Machine::operator=( Machine const & rhs ) {

	_stack = src.getStack();
}

void		Machine::push( IOperand const & o ) {

	_stack.push(o);
}

void		Machine::pop( void ) {

	if (_stack.size() != 0)
		_stack.pop();
	else
		std::cout << "Pop on empty stack" << std::endl;
}

void		Machine::dump( void ) const {

	std::stack<IOperand *>::const_iterator it;

	for (it = _stack.begin(); it < _stack.end(); it++)
		std::cout << *it << std::endl; 
}

void		Machine::assert( IOperand const & o ) const {

	bool operandsHaveSameType = (_stack.top()->getType() == o.getType());
	bool operandsAreEqual = (_stack.top()->getValue() == o.getValue());
	if (!(operandsAreEqual && operandsHaveSameType))
		exit();
}

void		Machine::add( void ) {

	IOperand * op1 = _stack.top();
	_stack.pop();
	IOperand * op2 = _stack.top();
	_stack.pop();
	_stack.push(*op1 + *op2);
	delete op2;
}

void		Machine::sub( void ) {

	IOperand * op1 = _stack.top();
	_stack.pop();
	IOperand * op2 = _stack.top();
	_stack.pop();
	_stack.push(*op1 - *op2);
	delete op2;
}

void		Machine::mul( void ) {

	IOperand * op1 = _stack.top();
	_stack.pop();
	IOperand * op2 = _stack.top();
	_stack.pop();
	_stack.push(*op1 * *op2);
	delete op2;
}

void		Machine::div( void ) {

	IOperand * op1 = _stack.top();
	_stack.pop();
	IOperand * op2 = _stack.top();
	_stack.pop();
	_stack.push(*op1 / *op2);
	delete op2;
}

void		Machine::mod( void ) {

	IOperand * op1 = _stack.top();
	_stack.pop();
	IOperand * op2 = _stack.top();
	_stack.pop();
	_stack.push(*op1 % *op2);
	delete op2;
}

void		Machine::print( void ) const {


}

void		Machine::exit( void ) const {

	exit();
}