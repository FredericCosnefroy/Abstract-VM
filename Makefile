#
# avm
#
# Makefile
#

#
# Config
#

# Project name
NAME := avm

# Project directories
DIRS := . .

# Obj directory
O_DIR := o

# Makefiles to call
LIBS := 

# Number of threads
THREADS := 1

# C++ compiler
CPP_CC := clang++

# Linking compiler
LD_CC := clang++

# C++ flags
CPP_FLAGS := -Wall -Wextra -Werror -O2

# Linking flags
LD_FLAGS := 

# C++ include flags
CPP_HEADS := -I .

#
# Internal
#

O_FILES := o/./Factory.o \
	o/./Instruction.o \
	o/./Parameter.o \
	o/./Parser.o \
	o/./VM.o \
	o/./main.o

MSG_0 := printf '\033[0;32m%-17.17s\033[0;0m\r'
MSG_1 := printf '\033[0;31m%-17.17s\033[0;0m\n'
MSG_END := printf '\n'

.SILENT:

all: $(LIBS) $(NAME)
.PHONY: all

$(NAME): $(O_FILES)
	@$(MSG_0) $@ ; $(LD_CC) -o $@ $(O_FILES) $(LD_FLAGS) && $(MSG_END) || $(MSG_1) $@

o/./Factory.o: ./Factory.cpp ./Factory.hpp ./IOperand.hpp ./Operand.hpp ./eOperandType.hpp
	@mkdir -p o/. 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/./Instruction.o: ./Instruction.cpp ./Factory.hpp ./IOperand.hpp ./Instruction.hpp ./Operand.hpp ./Parameter.hpp ./eCommandName.hpp ./eOperandType.hpp
	@mkdir -p o/. 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/./Parameter.o: ./Parameter.cpp ./Factory.hpp ./IOperand.hpp ./Instruction.hpp ./Operand.hpp ./Parameter.hpp ./eCommandName.hpp ./eOperandType.hpp
	@mkdir -p o/. 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/./Parser.o: ./Parser.cpp ./Factory.hpp ./IOperand.hpp ./Instruction.hpp ./Operand.hpp ./Parameter.hpp ./Parser.hpp ./eCommandName.hpp ./eOperandType.hpp
	@mkdir -p o/. 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/./VM.o: ./VM.cpp ./Factory.hpp ./IOperand.hpp ./Instruction.hpp ./Operand.hpp ./Parameter.hpp ./Parser.hpp ./VM.hpp ./eCommandName.hpp ./eOperandType.hpp
	@mkdir -p o/. 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

o/./main.o: ./main.cpp ./Factory.hpp ./IOperand.hpp ./Instruction.hpp ./Operand.hpp ./Parameter.hpp ./Parser.hpp ./VM.hpp ./eCommandName.hpp ./eOperandType.hpp
	@mkdir -p o/. 2> /dev/null || true
	@$(MSG_0) $< ; clang++ $(CPP_FLAGS) $(CPP_HEADS) -c -o $@ $< || ($(MSG_1) $< && false)

$(LIBS):
	@make -C $@
.PHONY: $(LIBS)

clean:
	@rm -f $(O_FILES) 2> /dev/null || true
	@rmdir -p o/. $(O_DIR) 2> /dev/null || true
.PHONY: clean

fclean: clean
	@rm -f $(NAME)
.PHONY: fclean

re: fclean all
.PHONY: re
