#ifndef MACHINE_CLASS_HPP
# define MACHINE_CLASS_HPP

#include <iostream>
#include <stack>
#include "Machine.class.hpp"

class Machine {

private:
	std::stack<IOperand *> _stack;

public:
	Machine();
	Machine( Machine const & src );
	virtual ~Machine( void ) {}

	Machine &	operator=( Machine const & rhs );

	void		push( IOperand const & o );
	void		pop( void );

	void		dump( void ) const;

	void		assert( IOperand const & o ) const;

	void		add( void );
	void		sub( void );
	void		mul( void );
	void		div( void );
	void		mod( void );

	void		print( void ) const;

	void		exit( void ) const;

};









#endif