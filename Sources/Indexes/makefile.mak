
# $Id$
# $Source$
# $Log$
# Revision 1.3  2001/06/12 15:05:34  lballabio
# Renamed Libor to GBPLibor and LiborManager to XiborManager
#
# Revision 1.2  2001/05/24 12:52:02  nando
# smoothing #include xx.hpp
#
#
# makefile for QuantLib finite differences library under Borland C++
#

.autodepend
.silent

# Debug version
!ifdef DEBUG
    _D = _d
!endif

# Directories
INCLUDE_DIR    = ..\..\Include
BCC_INCLUDE    = $(MAKEDIR)\..\include
BCC_LIBS       = $(MAKEDIR)\..\lib

# Object files
OBJS = xibor.obj$(_D) \
       xibormanager.obj$(_D)
       
# Tools to be used
CC        = bcc32
TLIB      = tlib

# Options
CC_OPTS        = -q -c -tWM -n$(OUTPUT_DIR) \
    -w-8026 -w-8027 -w-8012 \
    -I$(INCLUDE_DIR) \
    -I$(BCC_INCLUDE)
!ifdef DEBUG
CC_OPTS = $(CC_OPTS) -v -DQL_DEBUG
!endif

TLIB_OPTS    = /P32
!ifdef DEBUG
TLIB_OPTS    = /P128
!endif

# Generic rules
.cpp.obj:
    $(CC) $(CC_OPTS) $<
.cpp.obj_d:
    $(CC) $(CC_OPTS) -o$@ $<

# Primary target:
# static library
Indexes$(_D).lib:: $(OBJS)
    if exist Indexes$(_D).lib     del Indexes$(_D).lib
    $(TLIB) $(TLIB_OPTS) Indexes$(_D).lib /a $(OBJS)


# Clean up
clean::
    if exist *.obj   del /q *.obj
    if exist *.lib   del /q *.lib

