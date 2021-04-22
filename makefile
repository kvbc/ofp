GXX = gcc
AR = ar rcs
RM = del

########################################################## .o

O_FLG = -Wall -g -m32

########################################################## lib

LIB_T = libofp.dll
LIB_C = argument.c mem.c option.c parser.c state.c
LIB_O = argument.o mem.o option.o parser.o state.o
LIB_FLG = -Wall -g -m32

########################################################## ofp

OFP_T = ofp.exe
OFP_C = ofp.c
OFP_FLG = -Wall -g

ALL_C = $(OFP_C) $(LIB_C)

##########################################################
#
# Targets
#
##########################################################

o:
	$(GXX) $(O_FLG) -c $(LIB_C)

# Dynamic library
dlib:
	$(GXX) -o $(LIB_T) $(LIB_FLG) -shared $(LIB_O)

# Static library
slib:
	$(AR) $(LIB_T) $(LIB_O)

ofp:
	$(GXX) -o $(OFP_T) $(OFP_FLG) $(ALL_C)

clean:
	@$(RM) *.o *.dll *.lib *.so *.a *.exe