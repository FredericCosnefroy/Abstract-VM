#ifndef VM_CLASS_HPP
# define VM_CLASS_HPP

#include <iostream>
#include <vector>
#include "IOperand.hpp"
#include "Factory.hpp"
#include "Instruction.hpp"

class VM {

private:
	std::vector<IOperand const *> 		_stack;
	std::vector<Instruction const *> 	_instructions;

	std::vector<IOperand const *> const & getStack( void ) const;
	std::vector<Instruction const *> const & getInstructions( void ) const;
	VM();

public:
	VM(std::vector<Instruction const *> const & instructions);
	VM( VM const & src );
	virtual ~VM( void ) {};

	VM &			operator=( VM const & rhs );

	

	void				push( IOperand const & o );
	IOperand const *	pop( void );

	void				dump( void );

	void				assert( IOperand const & o );

	void				add( void );
	void			sub( void );
	void			mul( void );
	void			div( void );
	void			mod( void );

	void			print( void );

	void			exit( void );

	void			execute( Factory const & factory );

	void			run( void );

};









#endif