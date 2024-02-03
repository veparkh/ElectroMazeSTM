# C source files
PROJECT_CSRC 	= main.c\
				src/serial.c\
				engine/src/engine.c
# C++ source files
PROJECT_CPPSRC 	= 
# Directories to search headers in
PROJECT_INCDIR	= include\
					engine/include
# Additional libraries
PROJECT_LIBS	=
# Compiler options
PROJECT_OPT     = --specs=nosys.specs

# Additional .mk files are included here
