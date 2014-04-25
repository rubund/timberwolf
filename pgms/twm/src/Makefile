# Ymakefile for program twm
#  "@(#) Ymakefile (Yale) version 1.3 4/18/91 " 
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
#
# if all feedthrus should have the same name uncomment the next line.
# DFEED=-DNO_FEED_INSTANCES 

# available for adding future options.
OPTIONS=${UNIX} ${DEBUG} ${NOGRAPHICS} ${SYS5} 
#
# place where Xwindow include files reside
XLIB=/usr/include/X11
#
# where the libraries are
# where the <yalecad/base.h> etc. are located.
# how set set the search directories for compilation
INCLUDE=
YALELIB=${INCLUDE}yalecad/
IDIR=-I. -I${XLIB} 
# ****************** switches for linking *******************
# Yale library - the first library uses the Yale memory manager
# the second library uses the system's memory manager.
NYCADSYS=libycad.sys.a 
NYCADMEM=libycad.mem.a
# residence at Yale
YCADMEM=/twolf6/bills/version7/TimberWolf/lib/${NYCADMEM}
YCADSYS=/twolf6/bills/version7/TimberWolf/lib/${NYCADSYS}
# on this line pick which library you want 
YALECAD=${YCADMEM}

#
# place where link libraries exist
# user must supply math library and X11 library.
# use -L option if libraries exist elsewhere ie. -L/usr/bills/X -lX11
LINKLIB=-lm -lX11 
#
# need these lines for yale installation. Null otherwise.
GETDATE=/twolf6/bills/version7/TimberWolf/pgms/date/getdate
DATE_C=/twolf6/bills/version7/TimberWolf/pgms/date/src/date.c
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
MAKEDEPEND=/twolf6/bills/version7/TimberWolf/bin/makedepend # path of makedepend
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
TWDIR=/twolf6/bills/version7/TimberWolf
YACC=yacc
# if you dont have yacc and lex set to nop operation like echo
LEXMV=${MV}
YACCMV=${MV}
# ******************************************************************

#destination of output executable
DEST=../
PNAME=twm

#where the object code is located
objdir=../obj
O=${objdir}/

SRC= \
	events.c \
	add_window.c \
	gc.c \
	gram.y \
	lex.l \
	list.c \
	menus.c \
	parse.c \
	resize.c \
	twm.c \
	util.c \
	version.c 

BITMAPS= focus.bm \
	gray.bm \
	hilite.bm \
	iconify.bm \
	pull.bm \
	resize.bm \
	twm.bm \
	xterm.icon
    
MANUAL= twm.man

OBJ= \
	${O}events.o \
	${O}add_window.o \
	${O}gc.o \
	${O}gram.o \
	${O}lex.o \
	${O}list.o \
	${O}menus.o \
	${O}parse.o \
	${O}resize.o \
	${O}twm.o \
	${O}util.o \
	${O}version.o 

INS= \
	add_window.h \
	events.h \
	gc.h \
	list.h \
	menus.h \
	parse.h \
	resize.h \
	twm.h \
	util.h \
	version.h 

info:   ; 
	-@${ECHO} "make ${DEST}${PNAME} - usage:" 
	-@${ECHO} "   make install - build program" 
	-@${ECHO} "   make clean - remove binary" 
	-@${ECHO} "   make depend - added makefile dependencies" 
	-@${ECHO} "   make sources - pull sources from SCCS" 
	-@${ECHO} "   make lint - run lint on the sources" 


# how to make twm program
${DEST}${PNAME}:${OBJ} 
	${CC} ${CFLAGS} ${OPTIONS} -o ${DEST}${PNAME} ${OBJ} ${LINKLIB} 

install:${DEST}${PNAME}

clean: ;
	${RM} ${O}* ~* core *.bak foo* y.output

# how to build makefile dependencies
depend : ;
	${MAKEDEPEND} ${CFLAGS} ${OPTIONS} ${IDIR} ${SRC}

# how to make twm lint
lint:  ; 
	${LINT} ${LINT_OPT} ${IDIR} ${OPTIONS} *.c > lint.out 

#default sccs operation is get
SCCS_OP=get
#current release
REL=

# how to get sources from sccs
sources : ${SRC} ${INS} ${YMAKEFILE} ${BITMAPS} ${MANUAL}
${SRC} ${INS} ${YMAKEFILE} ${BITMAPS} ${MANUAL}: 
	${SCCS} ${SCCS_OP} ${REL} $@

#BEGIN DEPENDENCIES -- DO NOT DELETE THIS LINE

#END DEPENDENCIES -- DO NOT DELETE THIS LINE


# How to compile the sources
${O}events.o:events.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  events.c
	${MV} events.o ${O}events.o
${O}add_window.o:add_window.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  add_window.c
	${MV} add_window.o ${O}add_window.o
${O}gc.o:gc.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  gc.c
	${MV} gc.o ${O}gc.o

${O}gram.o:gram.y
	${YACC} -d gram.y
	${YACCMV} y.tab.c gram.c
	${YACCMV} y.tab.h gram.h
#	use grep to remove # line so dbx works correctly
	${GREP} -v "# line" gram.c > tmp; 	${MV} tmp gram.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  gram.c
	${MV} gram.o ${O}gram.o
${O}lex.o:lex.l
	${LEX} lex.l
	${LEXMV} lex.yy.c lex.c
#	use grep to remove # line so dbx works correctly
	${GREP} -v "# line" lex.c > tmp; 	${MV} tmp lex.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  lex.c
	${MV} lex.o ${O}lex.o


${O}list.o:list.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  list.c
	${MV} list.o ${O}list.o
${O}menus.o:menus.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  menus.c
	${MV} menus.o ${O}menus.o
${O}parse.o:parse.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  parse.c
	${MV} parse.o ${O}parse.o
${O}resize.o:resize.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  resize.c
	${MV} resize.o ${O}resize.o
${O}twm.o:twm.c
	${CC} ${CLEANUP} ${CFLAGS} ${IDIR} ${OPTIONS} -c  twm.c
	${MV} twm.o ${O}twm.o
${O}util.o:util.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  util.c
	${MV} util.o ${O}util.o
${O}version.o:version.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  version.c
	${MV} version.o ${O}version.o

# end makefile
