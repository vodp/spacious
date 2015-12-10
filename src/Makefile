# Makefile for partiview - please do not edit if the file is named "Makefile",
# since configure would overwrite it on the next configure. Edit "Makefile.in"
# instead, and run configure instead!!!
# If you must change configure.in, run autoconf, and then configure etc.

# the following variables are under AC control
# KIRA_INC, KIRA_LIB
# FLTK_INC, FLTK_LIB
# PV_FLAGS

SHELL = /bin/sh

# TARGET
TARGET   = spacious
LIBTARGET = libparti.a

#	Override with --with-fltk=
FLTK_INC   = -I../bin/include 
FLTK_LIB   = -L../bin/lib -lfltk_gl -lfltk -lfltk_images -lfltk_jpeg -lfltk_png -lfltk_z

CAVE_INC   = 
CAVE_LIB   = 

#KIRA_INC = -I$(STARLAB_PATH)/inc
#KIRA_LIB = -L${STARLAB_PATH)/lib

#  AC variables KIRA_INC and KIRA_LIB automatically created
#  if $STARLAB_PATH present; override with --with-kira=
KIRA_INC = 
KIRA_LIB = 

THREAD_CFLAGS = 
THREAD_LIB = 

IEEEIO_INC = 
IEEEIO_LIB = 

ELUMENS_INC = 
ELUMENS_LIB = 

PORT_OBJS = 

GL_LIB   = -lGLU -lGL
X_LIB    =   -lSM -lICE -lXext -lX11 
M_LIB    = -lm

MAKEGUI	 = true

# FLAGS and BINARIES
PV_FLAGS    = -Dunix -DUSE_WARP -DUSE_CONSTE -DUSE_MODEL
DEFS	    = $(PV_FLAGS)
#OPT         = -g -O2 ${OTYPE}
OPT	    = -g -O2 
INCL	    = ${FLTK_INC} ${CAVE_INC} $(KIRA_INC) ${ELUMENS_INC} ${IEEEIO_INC}
CC          = gcc
CFLAGS      = ${OPT} ${THREAD_CFLAGS} ${DEFS} ${INCL}
CXX	    = g++
CXXFLAGS    = -g -O2 $(OPT) $(DEFS) $(INCL)
AR	    = ar
ARFLAGS	    = -cr
LINK        = ${CXX} ${CXXFLAGS} ${THREAD_CFLAGS}
LIBS        = ${KIRA_LIB} ${ELUMENS_LIB} ${IEEEIO_LIB} ${FLTK_LIB} ${CAVE_LIB} ${THREAD_LIB} ${GL_LIB} ${X_LIB} ${M_LIB}

API_CSRCS   = \
		geometry.c partibrains.c specks.c version.c \
		mgtexture.c textures.c async.c shmem.c \
		findfile.c sfont.c warp.c plugins.c version.c
API_CXXSRCS =   \
		kira_parti.cc parti_model.cc cat_model.cc parti_ieee.cc \
		tcpsocket.cc
APP_CXXSRCS = \
		partiview.cc partiviewc.cc partipanel.cc Gview.cc Hist.cc \
		Fl_Log_Slider.cxx Plot.cc nethack.cc Fl_Scroll_Thin.cxx \
		genericslider.cc conste.cc Fl_Image_Display.cc spacious.cc

PLUGIN_OBJS =   \
		plugins.o kira_parti.o warp.o nethack.o parti_ieee.o \
		elumens.o parti_model.o cat_model.o \
		conste.o

APP_OBJS    = \
		partiview.o partiviewc.o partipanel.o spacious.o \
		Gview.o Hist.o Fl_Log_Slider.o Plot.o Fl_Scroll_Thin.o genericslider.o \
		Fl_Image_Display.o

API_OBJS    = \
		geometry.o partibrains.o specks.o version.o \
		mgtexture.o textures.o async.o \
		futil.o findfile.o sfont.o \
		sclock.o notify.o shmem.o \
		tcpsocket.o \
		${PORT_OBJS} \
		${PLUGIN_OBJS} \
		${MORE_OBJS}

default: all lib

all:	depended $(TARGET)

lib:	libdepended $(LIBTARGET)

${LIBTARGET}: libdepended ${API_OBJS}
	${AR} ${ARFLAGS} $@  ${API_OBJS}

Makefile: Makefile.in configure
	@if [ -f config.status ]; then \
		echo "Re-running config.status to regenerate Makefile"; \
		./config.status; \
	else \
		echo "Beware -- you probably need to re-run 'configure'"; \
	fi

depended: Makefile version.c
	${MAKE} depend
	touch depended  libdepended
	@echo "Re-running 'make'"
	${MAKE}

libdepended: Makefile version.c
	${MAKE} libdepend
	touch $@
	rm -f depended
	@echo "Re-running 'make ${LIBTARGET}'"
	${MAKE} ${LIBTARGET}

WARPCFLAGS = ${CFLAGS} -DSTANDALONE -UCAVE -UCAVEMENU
warpsdb: warp.o geometry.o
	${CC} -o $@ warp.c geometry.o -lm  ${WARPCFLAGS}

KIRA_SERVER_OBJS = kiraserver.o geometry.o findfile.o futil.o
kiraserver: ${KIRA_SERVER_OBJS}
	${CXX} -o $@ ${CFLAGS} ${KIRA_SERVER_OBJS} ${KIRA_LIB} ${M_LIB}

help:
	@echo  Partiview
	@echo  

clean:
	rm -f *.o core Makedepend config.cache $(TARGET) $(LIBTARGET)
	touch Makedepend

cleanall: clean
	rm -f Makefile config.log config.status config.h

$(TARGET):  $(APP_OBJS) $(API_OBJS)
	$(LINK)  -o $@  $(APP_OBJS) $(API_OBJS) $(LIBS)
	$(MAKEGUI)

version.c: VERSION
	echo "char partiview_version[] = \"`cat VERSION`\";" > version.c

version.o: version.c

# Force recompiling all plugins if any -D opts might have changed.  Ugh.
${PLUGIN_OBJS}: Makefile

ptest:  ptest.o
	$(CXX) -o $@ $(OPT) ptest.o $(LIBS)

dometest:  dometest.o geometry.o
	$(CXX) -o $@ $(OPT) dometest.o geometry.o $(LIBS)

partipanel.H partipanel.cc: partipanel.fl
	fluid -c partipanel.fl

.PHONEY: depend

# dep: depend
# depend:	_always

depend:
	rm -f Makedepend
	${CC} -M ${CFLAGS} ${APP_CSRCS} ${API_CSRCS} > Makedepend
	${CXX} -M ${CXXFLAGS} ${APP_CXXSRCS} ${API_CXXSRCS} >> Makedepend

libdepend:
	rm -f Makedepend
	${CC} -M ${CFLAGS} ${API_CSRCS} > Makedepend
	${CXX} -M ${CXXFLAGS} ${API_CXXSRCS} >> Makedepend

_always:

.SUFFIXES: .C .cc .cxx .cpp

.C.o:
	${CXX} -c $< ${CXXFLAGS} 
.cc.o:
	${CXX} -c $< ${CXXFLAGS} 
.cxx.o:
	${CXX} -c $< ${CXXFLAGS}
.cpp.o:
	${CXX} -c $< ${CXXFLAGS} 

include Makedepend
