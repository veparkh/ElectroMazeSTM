# C source files
PROJECT_CSRC 	= main.c\
				src/serial.c\
				uart/src/uart.c\
				gyroscope/src/gyroscope.c
				
# C++ source files
PROJECT_CPPSRC 	= 
# Directories to search headers in
PROJECT_INCDIR	= include\
				uart\include\
				gyroscope\include
# Additional libraries
PROJECT_LIBS	=
# Compiler options
PROJECT_OPT     = --specs=nosys.specs

# Additional .mk files are included here
