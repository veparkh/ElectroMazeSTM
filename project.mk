# C source files
PROJECT_CSRC 	= main.c\
				src/serial.c\
				uart/src/uart.c\
				positionSensor/src/Sensors.c\
				positionSensor/src/SensorsThread.c\
				positionSensor/src/FusionAhrs.c\
				positionSensor/src/FusionCompass.c\
				positionSensor/src/FusionOffset.c
				
# C++ source files
PROJECT_CPPSRC 	= 
# Directories to search headers in
PROJECT_INCDIR	= include\
				uart\include\
				positionSensor\include
# Additional libraries
PROJECT_LIBS	=
# Compiler options
PROJECT_OPT     = --specs=nosys.specs

# Additional .mk files are included here
