# Ymakefile for program net_util
#  "@(#) Ymakefile (Yale) version 1.6 4/21/91 " 
#
# ******************************************************************
# YMAKE MACRO SUBSTITUTION FILE.
# ****************** switches for compilation *******************
CFLAGS=-g
#
# The target foreign machine is assumed to be running UNIX, if not
# comment out following line.
UNIX=-DUNIX
#
# If users system does not support UNIX signals, comment out the
# signal handler defined on the next line.
CLEANUP=-DCLEANUP_C 
#
# The makefile should automatically define this variable if an X11
# server is not present, that is, /usr/include/X11 is not present.
# uncomment line if you which to override.
#NOGRAPHICS=-DNOGRAPHICS
#
# Normally the program is compiled with assertion checking.  If a 
# on a sys5 machine uncomment out next line systype
# use this only if problems arise with include files.
# also check below for problems with ranlib.
#SYS5=-DSYS5

# smaller faster version is desired comment out next line.
#DEBUG=-DDEBUG
#
# if all feedthrus should have the same name uncomment the next line.
# DFEED=-DNO_FEED_INSTANCES 

# available for adding future options.
OPTIONS=${UNIX} ${DEBUG} ${NOGRAPHICS} ${SYS5} ${DFEED}
#
# place where Xwindow include files reside
XLIB=/usr/include/X11
#
# where the libraries are
# where the <yalecad/base.h> etc. are located.
# how set set the search directories for compilation
INCLUDE=../../../include/
YALELIB=${INCLUDE}yalecad/
IDIR=-I. -I${INCLUDE} -I${XLIB} 
# ****************** switches for linking *******************
# Yale library - the first library uses the Yale memory manager
# the second library uses the system's memory manager.
NYCADSYS=libycad.sys.a 
NYCADMEM=libycad.mem.a
# residence at Yale
#YCADMEM=/usr/local/lib/${NYCADMEM}
#YCADSYS=/usr/local/lib/${NYCADSYS}
# residence on foreign host
YCADMEM=../../../lib/${NYCADMEM}
YCADSYS=../../../lib/${NYCADSYS}
# on this line pick which library you want 
YALECAD=${YCADSYS}

#
# place where link libraries exist
# user must supply math library and X11 library.
# use -L option if libraries exist elsewhere ie. -L/usr/bills/X -lX11
LINKLIB=-lm -lX11 
#
# need these lines for yale installation. Null otherwise.
GETDATE=
DATE_C=../../date/src/date.c
#
# ******************* RENAME PROGRAMS *************************
#
AR=ar # archiving program.
AWK=awk # awk language interpreter.
CAT=cat # concatenate program.
CC=cc # C compiler switch
CHMOD=chmod # C compiler switch
ECHO=echo # echo to the screen
GREP=grep
YMAKE=../../ymake/ymake # path of ymake program
# if problems arise with makedepend uncomment out following line
#YMAKEARGS=nodepend  # path of ymake program
YMAKEFILE=Ymakefile # name of ymakefile.
LEX=${ECHO}
LD=ld # linker
MAKE=/bin/make
MAKEDEPEND=../../makedepend/makedepend # path of makedepend
MV=mv # move program name
PAS=/com/pas
# on sys5 machines ranlib not supported uncomment second line
RANLIB=ranlib
#RANLIB=${ECHO}
RM=/bin/rm -f
STRIP=strip # strip symbol table from code.
SCCS=sccs # software control program
SCCS_OP=get #normal sccs operation
# always use Bourne shell in makefile.
SHELL=/bin/sh
YACC=${ECHO}
# if you dont have yacc and lex set to nop operation like echo
LEXMV=${ECHO}
YACCMV=${ECHO}
# ******************************************************************

DEST=../
PNAME1=build_menu
PNAME2=net_util

#where the object code is located
objdir=../obj
O=${objdir}/

SRC= \
	build_menu.c \
	net_util.c  

OBJ1= \
	${O}build_menu.o 

OBJ2= \
	${O}net_util.o 

INS= 

info:   ; 
	-@${ECHO} "make - usage:" 
	-@${ECHO} "   make ${PNAME1}" 
	-@${ECHO} "   make ${PNAME2}"
	-@${ECHO} "   make clean - remove binary" 
	-@${ECHO} "   make depend - added makefile dependencies" 
	-@${ECHO} "   make sources - pull sources from SCCS" 

install:${PNAME1} ${PNAME2}

# how to make build_menu program
${PNAME1}:${DEST}${PNAME1} ;

${DEST}${PNAME1}:${OBJ1} ${YALECAD} 
	${GETDATE}
	${CC} ${CFLAGS} -I. -c ${DATE_C}
	${MV} date.o ${O}date.o
	${CC} ${CFLAGS} ${OPTIONS} -o ${DEST}${PNAME1} ${OBJ1} ${O}date.o \
	${YALECAD} ${LINKLIB} 

# how to make net_util program
${PNAME2}:${DEST}${PNAME2} ;

${DEST}${PNAME2}:${OBJ2} ${YALECAD}
	${GETDATE}
	${CC} ${CFLAGS} -I. -c ${DATE_C}
	${MV} date.o ${O}date.o
	${CC} ${CFLAGS} ${OPTIONS} -o ${DEST}${PNAME2} ${OBJ2} ${O}date.o \
	${YALECAD} ${LINKLIB} 

clean: ;
	${RM} ${O}* *~ core foo *.bak

# how to build makefile dependencies
depend : ;
	${MAKEDEPEND} ${CFLAGS} ${OPTIONS} ${IDIR} ${SRC}

#default sccs operation is get
SCCS_OP=get
#current release
REL=

# how to get sources from sccs
sources : ${SRC} ${INS} ${YMAKEFILE}
${SRC} ${INS} ${YMAKEFILE}: 
	${SCCS} ${SCCS_OP} ${REL} $@

#BEGIN DEPENDENCIES -- DO NOT DELETE THIS LINE

${O}build_menu.o: ../../../include/yalecad/base.h /usr/include/stdio.h
${O}build_menu.o: ../../../include/math.h ../../../include/yalecad/mac.h
${O}build_menu.o: ../../../include/yalecad/okmalloc.h
${O}build_menu.o: ../../../include/yalecad/file.h
${O}build_menu.o: ../../../include/yalecad/message.h
${O}build_menu.o: ../../../include/yalecad/debug.h
${O}build_menu.o: ../../../include/yalecad/draw.h
${O}build_menu.o: ../../../include/yalecad/dialog.h
${O}build_menu.o: ../../../include/yalecad/colors.h
${O}build_menu.o: ../../../include/yalecad/cleanup.h
${O}net_util.o: ../../../include/yalecad/base.h /usr/include/stdio.h
${O}net_util.o: ../../../include/math.h ../../../include/yalecad/mac.h
${O}net_util.o: ../../../include/yalecad/okmalloc.h
${O}net_util.o: ../../../include/yalecad/file.h
${O}net_util.o: ../../../include/yalecad/string.h

#END DEPENDENCIES -- DO NOT DELETE THIS LINE


# How to compile the sources
${O}net_util.o:net_util.c
	${CC} ${CLEANUP} ${CFLAGS} ${IDIR} ${OPTIONS} -c  net_util.c
	${MV} net_util.o ${O}net_util.o

${O}build_menu.o:build_menu.c
	${CC} ${CLEANUP} ${CFLAGS} ${IDIR} ${OPTIONS} -c  build_menu.c
	${MV} build_menu.o ${O}build_menu.o


# end makefile
