# Imakefile for program draw_route
#  "@(#) Imakefile (Yale) version 1.1 12/16/89 " 
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
DEBUG=-DDEBUG
#
# if all feedthrus should have the same name uncomment the next line.
# DFEED=-DNO_FEED_INSTANCES 

# available for adding future options.
OPTIONS=${UNIX} ${DEBUG} ${NOGRAPHICS} ${SYS5} ${DFEED} -DYALE
#
# place where Xwindow include files reside
XLIB=/usr/include/X11
#
# where the libraries are
# where the <yalecad/base.h> etc. are located.
# how set set the search directories for compilation
INCLUDE=/twolf6/bills/TimberWolf/include/
YALELIB=${INCLUDE}yalecad/
IDIR=-I. -I${INCLUDE} -I${XLIB} 
# ****************** switches for linking *******************
# Yale library - the first library uses the Yale memory manager
# the second library uses the system's memory manager.
NYCADSYS=libycad.sys.a 
NYCADMEM=libycad.mem.a
# residence at Yale
YCADMEM=/twolf6/bills/TimberWolf/lib/${NYCADMEM}
YCADSYS=/twolf6/bills/TimberWolf/lib/${NYCADSYS}
# on this line pick which library you want 
YALECAD=${YCADMEM}

#
# place where link libraries exist
# user must supply math library and X11 library.
# use -L option if libraries exist elsewhere ie. -L/usr/bills/X -lX11
LINKLIB=-lm -lX11 
#
# need these lines for yale installation. Null otherwise.
GETDATE=/twolf6/bills/TimberWolf/pgms/date/getdate
DATE_C=/twolf6/bills/TimberWolf/pgms/date/src/date.c
#
# ******************* RENAME PROGRAMS *************************
#
AR=ar # archiving program.
AWK=awk # awk language interpreter.
CAT=cat # concatenate program.
CC=mcc # C compiler switch
CHMOD=chmod # C compiler switch
ECHO=echo # echo to the screen
GREP=grep
YMAKE=ymake # path of ymake program
# if problems arise with makedepend uncomment out following line
#YMAKEARGS=nodepend  # path of ymake program
YMAKEFILE=Ymakefile # name of ymakefile.
LEX=lex
LD=ld # linker
LINT=/twolf6/bills/bin/mylint
LINT_OPT=-v
LINT_SCRIPT=/twolf6/bills/bin/lint.awk
MAKE=/bin/make
MAKEDEPEND=/twolf6/bills/TimberWolf/bin/makedepend # path of makedepend
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
# TWDIR only needs to be set at Yale
TWDIR=/twolf6/bills/TimberWolf
YACC=byacc
# if you dont have yacc and lex set to nop operation like echo
LEXMV=${MV}
YACCMV=${MV}
# ******************************************************************

#destination of output executable
DEST=../
PNAME=draw_route

#where the object code is located
objdir=.
O=${objdir}/

SRC= \
	main.c \
	grid.c \
	input.l \
	input.y \
	output.c 

OBJ= \
	${O}main.o \
	${O}input.o \
	${O}output.o 

INS= \
	globals.h

info:   ; 
	-@${ECHO} "make ${DEST}${PNAME} - usage:" 
	-@${ECHO} "   make install - build program" 
	-@${ECHO} "   make install_non_yale - build program at foreign host" 
	-@${ECHO} "   make clean - remove binary" 
	-@${ECHO} "   make depend - added makefile dependencies" 
	-@${ECHO} "   make sources - pull sources from SCCS" 


# how to make draw_route program
${DEST}${PNAME}:${OBJ} ${YALECAD}
	${GETDATE}
	${CC} ${CFLAGS} -I. -c ${DATE_C}
#	${MV} date.o ${O}date.o
	${CC} ${CFLAGS} -o ${DEST}${PNAME} ${OBJ} ${O}date.o \
	${YALECAD} ${LINKLIB}

# we can't do anything about yalecad but want to update if it has changed
${YALECAD}: ;

install:${DEST}${PNAME}

install_non_yale:${DEST}${PNAME}

clean: ;
	${RM} ${OBJ}

# how to build makefile dependencies
depend : ;
	${MAKEDEPEND} ${CFLAGS} ${OPTIONS} ${IDIR} ${SRC}

#default sccs operation is get
SCCS_OP=get
#current release
REL=

# how to get sources from sccs
sources : ${SRC} ${INS} ${IMAKEFILE}
${SRC} ${INS} ${IMAKEFILE}: 
	${SCCS} ${SCCS_OP} ${REL} $@

#BEGIN DEPENDENCIES -- DO NOT DELETE THIS LINE

${O}main.o: /usr/include/stdio.h /usr/include/signal.h
${O}main.o: /twolf6/bills/TimberWolf/include/yalecad/base.h
${O}main.o: /twolf6/bills/TimberWolf/include/math.h
${O}main.o: /twolf6/bills/TimberWolf/include/yalecad/cleanup.h
${O}main.o: /twolf6/bills/TimberWolf/include/yalecad/file.h
${O}main.o: /twolf6/bills/TimberWolf/include/yalecad/message.h
${O}main.o: /twolf6/bills/TimberWolf/include/yalecad/string.h
${O}main.o: /twolf6/bills/TimberWolf/include/yalecad/debug.h
${O}main.o: /twolf6/bills/TimberWolf/include/yalecad/wgraphics.h globals.h
${O}grid.o: /usr/include/stdio.h /usr/include/signal.h
${O}grid.o: /twolf6/bills/TimberWolf/include/yalecad/base.h
${O}grid.o: /twolf6/bills/TimberWolf/include/math.h
${O}grid.o: /twolf6/bills/TimberWolf/include/yalecad/cleanup.h
${O}grid.o: /twolf6/bills/TimberWolf/include/yalecad/file.h
${O}grid.o: /twolf6/bills/TimberWolf/include/yalecad/message.h
${O}grid.o: /twolf6/bills/TimberWolf/include/yalecad/string.h
${O}grid.o: /twolf6/bills/TimberWolf/include/yalecad/debug.h
${O}input.o: /twolf6/bills/TimberWolf/include/yalecad/base.h
${O}input.o: /usr/include/stdio.h /twolf6/bills/TimberWolf/include/math.h
${O}input.o: /twolf6/bills/TimberWolf/include/yalecad/message.h
${O}input.o: /twolf6/bills/TimberWolf/include/yalecad/wgraphics.h
${O}input.o: /twolf6/bills/TimberWolf/include/yalecad/colors.h globals.h
${O}input.o: input.h
${O}output.o: /usr/include/stdio.h
${O}output.o: /twolf6/bills/TimberWolf/include/yalecad/base.h
${O}output.o: /twolf6/bills/TimberWolf/include/math.h
${O}output.o: /twolf6/bills/TimberWolf/include/yalecad/wgraphics.h
${O}output.o: /twolf6/bills/TimberWolf/include/yalecad/colors.h
${O}output.o: /twolf6/bills/TimberWolf/include/yalecad/debug.h
${O}output.o: /twolf6/bills/TimberWolf/include/yalecad/message.h globals.h

#END DEPENDENCIES -- DO NOT DELETE THIS LINE

grid : grid.c
	${GETDATE}
	${CC} ${CFLAGS} -I. -c ${DATE_C}
#	${MV} date.o ${O}date.o
	${CC} ${CFLAGS} -o grid grid.c ${O}date.o ${YALECAD} ${LINKLIB}

# How to compile the sources
${O}main.o:main.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  main.c
${O}input.o:input.y input.l
	${LEX} input.l
	${LEXMV} lex.yy.c input.h
	${YACC} input.y
	${YACCMV} y.tab.c input.c
#	use grep to remove # line so dbx works correctly
	${GREP} -v "# line" input.c > tmp; 	${MV} tmp input.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  input.c
input.y:
input.l:
${O}output.o:output.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  output.c

# end makefile
