#
#  Octtools Makefile
#
#  yacr - channel router
#
#  Makefile created on Tue Aug 6 09:22:48 PDT 1991 by octtools (using 'create-octtools-makefile')
#
#  Copyright (c) 1988, 1989, 1990, Regents of the University of California
#
#  For a description of the 'targets and variables': say "make help"
#------------------------------------------------------------------------------
.SUFFIXES: .c .y .l .cc .o

.cc.o:
	${CPLUSPLUS} ${CFLAGS} -c $*.cc

# for HPUX
SHELL	= /bin/sh

MAKE = /bin/make
AR = ar
RANLIB = ranlib
CPLUSPLUS = g++

# CAD	= /projects/octtools/octtools-5.1/mips
UTILS	= ${OCTTOOLS}/utils
# This works OK at UC Berkeley.
XINCLOC = -I/projects/X11/X11/common/include
XLIBLOC = -L/projects/X11/X11/mips/lib

LINTCREATEFLAG = -C
LINTEXTRAS =
LDEXTRAS =
DBGFLAG =
OPTFLAG =

# an alternative if you want links in the installation locations
# back to the source directories would be:
#   CP = sh -c 'ln -s `pwd`/$$0 $$1'
CP = cp

BUILD = ${OCTTOOLS}/bin/create-octtools-makefile

# cute hack for the sequent
#   setenv PARALLEL 8; make P="&" install
P = 

NAME	= yacr

# packages required for this package/tool
REQUIRE	= mm port

# tools required for this tool
TOOLREQUIRE = 

SRC	= addcol.c addrow.c allocate.c clean.c cost.c cycle.c density.c graph.c input.c irreg.c left.c level.c main.c maze.c maze1.c maze2.c maze3.c misc.c output.c place.c right.c route.c select.c stack.c stats.c verify.c
LSRC	= addcol.c addrow.c allocate.c clean.c cost.c cycle.c density.c graph.c input.c irreg.c left.c level.c main.c maze.c maze1.c maze2.c maze3.c misc.c output.c place.c right.c route.c select.c stack.c stats.c verify.c
OBJ	= addcol.o addrow.o allocate.o clean.o cost.o cycle.o density.o graph.o input.o irreg.o left.o level.o main.o maze.o maze1.o maze2.o maze3.o misc.o output.o place.o right.o route.o select.o stack.o stats.o verify.o
HDR	= yacr.h

CADBIN	= ${OCTTOOLS}/bin

TOOLINSTALL= ${CADBIN}/${TARGET} ${OCTTOOLS}/man/man1/${MAN}
INSTALL	= ${PKGINSTALL} ${TOOLINSTALL} ${OCTTOOLS}/doc/yacr.doc ${OCTTOOLS}/man/man5/yacr.5

DISTDEST= ${OCTTOOLS}/src/${NAME}
DISTHOST= BOGUS-HOST
MISC	= Makefile Makefile.template README1 README2 README3 yacr.5 yacr.doc yacr.typ progs.h tst

LIBS	= 
LINTLIBS= 

TARGET	= ${NAME}
TARGETG	= ${NAME}-g
TARGETPG	= ${NAME}-pg
MAN	= ${NAME}.1

PRINTER	= lps40
MACROS	= -man.4.3
PRINT	= lpr
TROFF	= ptroff
TBL	= tbl

MAKEVARS =	\
		"CAD=${CAD}" \
		"OCTTOOLS=${OCTTOOLS}" \
		"CC=${CC}" \
		"OPTFLAG=${OPTFLAG}" \
		"DBGFLAG=${DBGFLAG}" \
		"RDFLAGS=${RDFLAGS}" \
		"CP=${CP}" \
		"LINTCREATEFLAG=${LINTCREATEFLAG}" \
		"LDEXTRAS=${LDEXTRAS}" \
		"LINTEXTRAS=${LINTEXTRAS}" \
		"MAKE=$(MAKE)" \
		"MACROS=${MACROS}" \
		"P=${P}" \
		"PRINT=${PRINT}" \
		"PRINTER=${PRINTER}" \
		"TBL=${TBL}" \
		"TROFF=${TROFF}" \
		"AR=${AR}" \
		"RANLIB=${RANLIB}" \
		"CPLUSPLUS=${CPLUSPLUS}" \
		"XINCLOC=${XINCLOC}" \
		"XLIBLOC=${XLIBLOC}" \
		"VPATH=${VPATH}"

INCLUDE	= ${XINCLOC}  -I${OCTTOOLS}/include
CFLAGS	= ${OPTFLAG} ${DBGFLAG} ${INCLUDE} 
VERSION	= "-DCUR_DATE=\"`date | awk '{print $$2, $$3, $$6}'`\"" \
	  "-DCUR_TIME=\"`date | awk '{print $$4}'`\""
LINTFLAGS= ${INCLUDE} ${LINTEXTRAS}
LDFLAGS	= ${XLIBLOC}  -lm ${LDEXTRAS}
RDFLAGS    = -Rich
#-----------------------------------------------------------------------

prog: ${TARGET}

all: tags lint ${TARGET}

build: Makefile.template
	@${BUILD} Makefile.template

install: ${INSTALL}

install.lint: ${LINTINSTALL}

uninstall:
	rm -rf ${INSTALL}

version.o: version.c
	${CC} ${CFLAGS} ${VERSION} -c version.c
	-touch -f version.c

debug: debug-g debug-pg


debug-g:
	rm -f ${OBJ}
	$(MAKE) $(MFLAGS) DBGFLAG=-g $(MAKEVARS) ${TARGETG}

debug-pg:
	rm -f ${OBJ}
	$(MAKE) $(MFLAGS) DBGFLAG=-pg $(MAKEVARS) ${TARGETPG}



${TARGET} ${TARGETG} ${TARGETPG}:${P} ${OBJ} ${LIBS}
	${CC} ${OPTFLAG} ${DBGFLAG} -o $@ ${OBJ} ${LIBS} ${LDFLAGS}


header::

${CADBIN}/${TARGET}: ${TARGET}
	rm -f $@
	${CP} $? $@

${OCTTOOLS}/man/man1/${MAN}: ${MAN}
	rm -f $@
	${TBL} < $? > $@

lint: ${LSRC} ${DRVRSRC} ${HDR} ${LINTLIBS}
	lint ${LINTFLAGS} ${LSRC} ${DRVRSRC} ${LINTLIBS} ${LDFLAGS} | tee lint

clean::
	@rm -f ${OBJ} ${DRVROBJ} ${TARGET} ${TARGETG} ${TARGETPG} ${DRIVER} 
	@rm -f tags TAGS ${LIB} ${LIBG} ${LIBPG} ${LINTLIB} lint 
	@rm -f make.out mktemp core .g .pg *~ __________ELEL_

require:
	@echo ${REQUIRE}

help:
	@more ${OCTTOOLS}/lib/utils/Makefile.help

toolrequire:
	@echo ${TOOLREQUIRE}

test::
	@test -f ${CADBIN}/${TARGET}

tags: ${LSRC} ${DRVRSRC} ${HDR}
	ctags ${LSRC} ${DRVRSRC} ${HDR}

TAGS: ${LSRC} ${DRVRSRC} ${HDR}
	etags ${LSRC} ${DRVRSRC} ${HDR}

info:
	@echo '${NAME}:  channel router'

print:: ${DOC} ${MAN}
	${TBL} < ${MAN} | ${TROFF} -P${PRINTER} ${MACROS}

dist: ${SRC} ${DRVRSRC} ${HDR} ${DOC} ${MAN}
	rdist ${RDFLAGS} ${SRC} ${DRVRSRC} ${HDR} ${DOC} ${MAN} ${MISC} ${DISTHOST}:${DISTDEST}

test-dist: ${SRC} ${DRVRSRC} ${HDR} ${DOC} ${MAN}
	rdist ${RDFLAGS} -hv ${SRC} ${DRVRSRC} ${HDR} ${DOC} ${MAN} ${MISC} ${DISTHOST}:${DISTDEST}


depend: ${SRC} ${DRVRSRC} ${HDR}
	@rm -f mktemp
	@sed '/^#--DO NOT CHANGE ANYTHING AFTER THIS LINE/,$$d' Makefile > mktemp
	@echo '#--DO NOT CHANGE ANYTHING AFTER THIS LINE' >> mktemp
	@${OCTTOOLS}/bin/cc-M ${INCLUDE} ${SRC} ${DRVRSRC} | sed 's|${OCTTOOLS}|$${OCTTOOLS}|g' >>mktemp
	@mv mktemp Makefile

strip-depend:
	@rm -f mktemp
	@sed '/^#--DO NOT CHANGE ANYTHING AFTER THIS LINE/,$$d' Makefile > mktemp
	@mv mktemp Makefile

# does not work with 'pat2tap' creation of devnames.h
#${SRC} ${DRVRSRC} ${HDR}:
#	co $@

#--EXTRA TARGETS
test::
	@(${CADBIN}/${TARGET} tst/1 | cmp -s - tst/1.out)
	@(${CADBIN}/${TARGET} tst/ex1 | cmp -s - tst/ex1.out)
	@(${CADBIN}/${TARGET} tst/ex2 | cmp -s - tst/ex2.out)

${OCTTOOLS}/doc/yacr.doc: yacr.doc
	rm -f $@
	${TBL} < yacr.doc | nroff -me > $@

${OCTTOOLS}/man/man5/yacr.5: yacr.5
	rm -f $@
	${TBL} < yacr.5 > $@

print::
	${TBL} < yacr.5 | ${TROFF} -P${PRINTER} ${MACROS}

print-docs::
	${TBL} < yacr.doc | ${TROFF} -P${PRINTER} -me

documentation::


