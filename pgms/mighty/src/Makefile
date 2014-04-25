# Ymakefile for program TimberWolfDR
#  "@(#) Ymakefile (Yale) version 6.5 2/5/91 " 
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
OPTIONS=${UNIX} ${DEBUG} ${NOGRAPHICS} ${SYS5} ${DFEED} -Dlinux -Wall
#
# place where Xwindow include files reside
XLIB=/usr/include/X11
#
# where the libraries are
# where the <yalecad/base.h> etc. are located.
# how set set the search directories for compilation
INCLUDE=../../../include/ -I/usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/
YALELIB=${INCLUDE}yalecad/
# ****************** switches for linking *******************
# Yale library - the first library uses the Yale memory manager
# the second library uses the system's memory manager.
NYCADSYS=libycad.sys.a
NYCADMEM=libycad.mem.a
YCADMEM=../../Ylib/lib/${NYCADMEM}
YCADSYS=../../Ylib/lib/${NYCADSYS}
# on this line pick which library you want
# YALECAD=${YCADMEM}
YALECAD=${YCADSYS}


IDIR=-I. -I${INCLUDE} -I${XLIB}
# ****************** switches for linking *******************

#
# place where link libraries exist
# user must supply math library and X11 library.
# use -L option if libraries exist elsewhere ie. -L/usr/bills/X -lX11
#
# for decStation need -lc first because of lame libraries
# (Note:  Use the line with /usr/X11R6/lib64 for 64-bit Linux systems)
# LINKLIB=-L/usr/X11R6/lib -lc -lX11 -lm
LINKLIB=-L/usr/X11R6/lib64 -lc -lX11 -lm
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
MAKE=/usr/bin/make
MAKEDEPEND=makedepend
MV=mv # move program name
# PAS=/com/pas
PAS=${ECHO}
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

#destination of output executable
DEST=../
PNAME=TimberWolfDR

#where the object code is located
objdir=../obj
O=${objdir}/

SRC= \
	allocate.c \
	append.c \
	assign.c \
	cycle.c \
	density.c \
	graph.c \
	impr0.c \
	impr1.c \
	impr2.c \
	impr3.c \
	impr4.c \
	input.c \
	level.c \
	link.c \
	macro.c \
	main.c \
	memory.c \
	misc.c \
	obstacle.c \
	output.c \
	path.c \
	pins.c \
	post.c \
	sched.c \
	stack.c 

OBJ= \
	${O}allocate.o \
	${O}append.o \
	${O}assign.o \
	${O}cycle.o \
	${O}density.o \
	${O}graph.o \
	${O}impr0.o \
	${O}impr1.o \
	${O}impr2.o \
	${O}impr3.o \
	${O}impr4.o \
	${O}input.o \
	${O}level.o \
	${O}link.o \
	${O}macro.o \
	${O}main.o \
	${O}memory.o \
	${O}misc.o \
	${O}obstacle.o \
	${O}output.o \
	${O}path.o \
	${O}pins.o \
	${O}post.o \
	${O}sched.o \
	${O}stack.o 

INS= \
	mighty.h 

info:   ; 
	-@${ECHO} "make ${DEST}${PNAME} - usage:" 
	-@${ECHO} "   make install - build program" 
	-@${ECHO} "   make install_non_yale - build program at foreign host" 
	-@${ECHO} "   make clean - remove binary" 
	-@${ECHO} "   make depend - added makefile dependencies" 
	-@${ECHO} "   make sources - pull sources from SCCS" 
	-@${ECHO} "   make lint - run lint on the sources" 


# how to make TimberWolfDR program
${DEST}${PNAME}:${OBJ} ${YALECAD}
	${GETDATE}
	${CC} ${CFLAGS} -I. -c ${DATE_C}
	${MV} date.o ${O}date.o
	${CC} ${CFLAGS} ${OPTIONS} -o ${DEST}${PNAME} ${OBJ} ${O}date.o \
	${YALECAD} ${LINKLIB}

# we can't do anything about yalecad but want to update if it has changed
${YALECAD}: ;

install:${DEST}${PNAME}

install_non_yale:${DEST}${PNAME}

clean: ;
	${RM} ${O}* ~* core *.bak foo* y.output y.tab.c

# how to build makefile dependencies
depend : ;
	${MAKEDEPEND} ${CFLAGS} ${OPTIONS} ${IDIR} ${SRC}

# how to make TimberWolfDR lint
lint:  ; 
	${LINT} ${LINT_OPT} ${IDIR} ${OPTIONS} *.c > lint.out 

#default sccs operation is get
SCCS_OP=get
#current release
REL=

# how to get sources from sccs
sources : ${SRC} ${INS} ${YMAKEFILE}
${SRC} ${INS} ${YMAKEFILE}: 
	${SCCS} ${SCCS_OP} ${REL} $@

#BEGIN DEPENDENCIES -- DO NOT DELETE THIS LINE

#END DEPENDENCIES -- DO NOT DELETE THIS LINE


# How to compile the sources
${O}allocate.o:allocate.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  allocate.c
	${MV} allocate.o ${O}allocate.o
${O}append.o:append.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  append.c
	${MV} append.o ${O}append.o
${O}assign.o:assign.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  assign.c
	${MV} assign.o ${O}assign.o
${O}cycle.o:cycle.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  cycle.c
	${MV} cycle.o ${O}cycle.o
${O}density.o:density.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  density.c
	${MV} density.o ${O}density.o
${O}graph.o:graph.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  graph.c
	${MV} graph.o ${O}graph.o
${O}impr0.o:impr0.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  impr0.c
	${MV} impr0.o ${O}impr0.o
${O}impr1.o:impr1.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  impr1.c
	${MV} impr1.o ${O}impr1.o
${O}impr2.o:impr2.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  impr2.c
	${MV} impr2.o ${O}impr2.o
${O}impr3.o:impr3.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  impr3.c
	${MV} impr3.o ${O}impr3.o
${O}impr4.o:impr4.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  impr4.c
	${MV} impr4.o ${O}impr4.o
${O}input.o:input.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  input.c
	${MV} input.o ${O}input.o
${O}level.o:level.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  level.c
	${MV} level.o ${O}level.o
${O}link.o:link.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  link.c
	${MV} link.o ${O}link.o
${O}macro.o:macro.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  macro.c
	${MV} macro.o ${O}macro.o
${O}main.o:main.c
	${CC} ${CLEANUP} ${CFLAGS} ${IDIR} ${OPTIONS} -c  main.c
	${MV} main.o ${O}main.o
${O}memory.o:memory.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  memory.c
	${MV} memory.o ${O}memory.o
${O}misc.o:misc.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  misc.c
	${MV} misc.o ${O}misc.o
${O}obstacle.o:obstacle.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  obstacle.c
	${MV} obstacle.o ${O}obstacle.o
${O}output.o:output.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  output.c
	${MV} output.o ${O}output.o
${O}path.o:path.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  path.c
	${MV} path.o ${O}path.o
${O}pins.o:pins.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  pins.c
	${MV} pins.o ${O}pins.o
${O}post.o:post.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  post.c
	${MV} post.o ${O}post.o
${O}sched.o:sched.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  sched.c
	${MV} sched.o ${O}sched.o
${O}stack.o:stack.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  stack.c
	${MV} stack.o ${O}stack.o

# end makefile
# DO NOT DELETE

allocate.o: mighty.h /usr/include/stdio.h /usr/include/features.h
allocate.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
allocate.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
allocate.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
allocate.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
allocate.o: /usr/include/libio.h /usr/include/_G_config.h
allocate.o: /usr/include/wchar.h
allocate.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
allocate.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
allocate.o: /usr/include/math.h /usr/include/bits/huge_val.h
allocate.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
allocate.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
allocate.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
allocate.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
allocate.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
allocate.o: /usr/include/endian.h /usr/include/bits/endian.h
allocate.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
allocate.o: /usr/include/time.h /usr/include/sys/select.h
allocate.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
allocate.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
allocate.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
allocate.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
allocate.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
allocate.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
allocate.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
allocate.o: /usr/include/bits/posix2_lim.h
allocate.o: ../../../include/yalecad/okmalloc.h
append.o: mighty.h /usr/include/stdio.h /usr/include/features.h
append.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
append.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
append.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
append.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
append.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
append.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
append.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
append.o: /usr/include/math.h /usr/include/bits/huge_val.h
append.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
append.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
append.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
append.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
append.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
append.o: /usr/include/endian.h /usr/include/bits/endian.h
append.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
append.o: /usr/include/time.h /usr/include/sys/select.h
append.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
append.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
append.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
append.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
append.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
append.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
append.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
append.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
append.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
assign.o: mighty.h /usr/include/stdio.h /usr/include/features.h
assign.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
assign.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
assign.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
assign.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
assign.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
assign.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
assign.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
assign.o: /usr/include/math.h /usr/include/bits/huge_val.h
assign.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
assign.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
assign.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
assign.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
assign.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
assign.o: /usr/include/endian.h /usr/include/bits/endian.h
assign.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
assign.o: /usr/include/time.h /usr/include/sys/select.h
assign.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
assign.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
assign.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
assign.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
assign.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
assign.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
assign.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
assign.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
assign.o: ../../../include/yalecad/message.h
cycle.o: mighty.h /usr/include/stdio.h /usr/include/features.h
cycle.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
cycle.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
cycle.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
cycle.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
cycle.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
cycle.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
cycle.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
cycle.o: /usr/include/math.h /usr/include/bits/huge_val.h
cycle.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
cycle.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
cycle.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
cycle.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
cycle.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
cycle.o: /usr/include/endian.h /usr/include/bits/endian.h
cycle.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
cycle.o: /usr/include/time.h /usr/include/sys/select.h
cycle.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
cycle.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
cycle.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
cycle.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
cycle.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
cycle.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
cycle.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
cycle.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
density.o: mighty.h /usr/include/stdio.h /usr/include/features.h
density.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
density.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
density.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
density.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
density.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
density.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
density.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
density.o: /usr/include/math.h /usr/include/bits/huge_val.h
density.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
density.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
density.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
density.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
density.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
density.o: /usr/include/endian.h /usr/include/bits/endian.h
density.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
density.o: /usr/include/time.h /usr/include/sys/select.h
density.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
density.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
density.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
density.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
density.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
density.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
density.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
density.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
graph.o: mighty.h /usr/include/stdio.h /usr/include/features.h
graph.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
graph.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
graph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
graph.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
graph.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
graph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
graph.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
graph.o: /usr/include/math.h /usr/include/bits/huge_val.h
graph.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
graph.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
graph.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
graph.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
graph.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
graph.o: /usr/include/endian.h /usr/include/bits/endian.h
graph.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
graph.o: /usr/include/time.h /usr/include/sys/select.h
graph.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
graph.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
graph.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
graph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
graph.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
graph.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
graph.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
graph.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
impr0.o: mighty.h /usr/include/stdio.h /usr/include/features.h
impr0.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
impr0.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
impr0.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
impr0.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
impr0.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
impr0.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
impr0.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
impr0.o: /usr/include/math.h /usr/include/bits/huge_val.h
impr0.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
impr0.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
impr0.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
impr0.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
impr0.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
impr0.o: /usr/include/endian.h /usr/include/bits/endian.h
impr0.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
impr0.o: /usr/include/time.h /usr/include/sys/select.h
impr0.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
impr0.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
impr0.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
impr0.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
impr0.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
impr0.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
impr0.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
impr0.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
impr1.o: mighty.h /usr/include/stdio.h /usr/include/features.h
impr1.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
impr1.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
impr1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
impr1.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
impr1.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
impr1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
impr1.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
impr1.o: /usr/include/math.h /usr/include/bits/huge_val.h
impr1.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
impr1.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
impr1.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
impr1.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
impr1.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
impr1.o: /usr/include/endian.h /usr/include/bits/endian.h
impr1.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
impr1.o: /usr/include/time.h /usr/include/sys/select.h
impr1.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
impr1.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
impr1.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
impr1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
impr1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
impr1.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
impr1.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
impr1.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
impr2.o: mighty.h /usr/include/stdio.h /usr/include/features.h
impr2.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
impr2.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
impr2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
impr2.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
impr2.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
impr2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
impr2.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
impr2.o: /usr/include/math.h /usr/include/bits/huge_val.h
impr2.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
impr2.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
impr2.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
impr2.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
impr2.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
impr2.o: /usr/include/endian.h /usr/include/bits/endian.h
impr2.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
impr2.o: /usr/include/time.h /usr/include/sys/select.h
impr2.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
impr2.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
impr2.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
impr2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
impr2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
impr2.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
impr2.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
impr2.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
impr3.o: mighty.h /usr/include/stdio.h /usr/include/features.h
impr3.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
impr3.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
impr3.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
impr3.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
impr3.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
impr3.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
impr3.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
impr3.o: /usr/include/math.h /usr/include/bits/huge_val.h
impr3.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
impr3.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
impr3.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
impr3.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
impr3.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
impr3.o: /usr/include/endian.h /usr/include/bits/endian.h
impr3.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
impr3.o: /usr/include/time.h /usr/include/sys/select.h
impr3.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
impr3.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
impr3.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
impr3.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
impr3.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
impr3.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
impr3.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
impr3.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
impr4.o: mighty.h /usr/include/stdio.h /usr/include/features.h
impr4.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
impr4.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
impr4.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
impr4.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
impr4.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
impr4.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
impr4.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
impr4.o: /usr/include/math.h /usr/include/bits/huge_val.h
impr4.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
impr4.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
impr4.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
impr4.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
impr4.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
impr4.o: /usr/include/endian.h /usr/include/bits/endian.h
impr4.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
impr4.o: /usr/include/time.h /usr/include/sys/select.h
impr4.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
impr4.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
impr4.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
impr4.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
impr4.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
impr4.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
impr4.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
impr4.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
input.o: mighty.h /usr/include/stdio.h /usr/include/features.h
input.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
input.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
input.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
input.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
input.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
input.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
input.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
input.o: /usr/include/math.h /usr/include/bits/huge_val.h
input.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
input.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
input.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
input.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
input.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
input.o: /usr/include/endian.h /usr/include/bits/endian.h
input.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
input.o: /usr/include/time.h /usr/include/sys/select.h
input.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
input.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
input.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
input.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
input.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
input.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
input.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
input.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
input.o: ../../../include/yalecad/message.h input_l.h
level.o: mighty.h /usr/include/stdio.h /usr/include/features.h
level.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
level.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
level.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
level.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
level.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
level.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
level.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
level.o: /usr/include/math.h /usr/include/bits/huge_val.h
level.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
level.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
level.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
level.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
level.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
level.o: /usr/include/endian.h /usr/include/bits/endian.h
level.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
level.o: /usr/include/time.h /usr/include/sys/select.h
level.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
level.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
level.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
level.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
level.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
level.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
level.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
level.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
link.o: mighty.h /usr/include/stdio.h /usr/include/features.h
link.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
link.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
link.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
link.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
link.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
link.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
link.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
link.o: /usr/include/math.h /usr/include/bits/huge_val.h
link.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
link.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
link.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
link.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
link.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
link.o: /usr/include/endian.h /usr/include/bits/endian.h
link.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
link.o: /usr/include/time.h /usr/include/sys/select.h
link.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
link.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
link.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
link.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
link.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
link.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
link.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
link.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
macro.o: mighty.h /usr/include/stdio.h /usr/include/features.h
macro.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
macro.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
macro.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
macro.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
macro.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
macro.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
macro.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
macro.o: /usr/include/math.h /usr/include/bits/huge_val.h
macro.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
macro.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
macro.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
macro.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
macro.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
macro.o: /usr/include/endian.h /usr/include/bits/endian.h
macro.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
macro.o: /usr/include/time.h /usr/include/sys/select.h
macro.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
macro.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
macro.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
macro.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
macro.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
macro.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
macro.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
macro.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
macro.o: ../../../include/yalecad/message.h
main.o: mighty.h /usr/include/stdio.h /usr/include/features.h
main.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
main.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
main.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
main.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
main.o: /usr/include/math.h /usr/include/bits/huge_val.h
main.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
main.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
main.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
main.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
main.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
main.o: /usr/include/endian.h /usr/include/bits/endian.h
main.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
main.o: /usr/include/time.h /usr/include/sys/select.h
main.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
main.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
main.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
main.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
main.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
main.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
main.o: ../../../include/yalecad/cleanup.h ../../../include/yalecad/message.h
main.o: /usr/include/signal.h /usr/include/bits/signum.h
main.o: /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h
main.o: /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h
main.o: /usr/include/sys/ucontext.h /usr/include/bits/sigthread.h
memory.o: mighty.h /usr/include/stdio.h /usr/include/features.h
memory.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
memory.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
memory.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
memory.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
memory.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
memory.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
memory.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
memory.o: /usr/include/math.h /usr/include/bits/huge_val.h
memory.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
memory.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
memory.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
memory.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
memory.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
memory.o: /usr/include/endian.h /usr/include/bits/endian.h
memory.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
memory.o: /usr/include/time.h /usr/include/sys/select.h
memory.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
memory.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
memory.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
memory.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
memory.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
memory.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
memory.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
memory.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
misc.o: mighty.h /usr/include/stdio.h /usr/include/features.h
misc.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
misc.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
misc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
misc.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
misc.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
misc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
misc.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
misc.o: /usr/include/math.h /usr/include/bits/huge_val.h
misc.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
misc.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
misc.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
misc.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
misc.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
misc.o: /usr/include/endian.h /usr/include/bits/endian.h
misc.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
misc.o: /usr/include/time.h /usr/include/sys/select.h
misc.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
misc.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
misc.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
misc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
misc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
misc.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
misc.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
misc.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
misc.o: ../../../include/yalecad/message.h
obstacle.o: mighty.h /usr/include/stdio.h /usr/include/features.h
obstacle.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
obstacle.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
obstacle.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
obstacle.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
obstacle.o: /usr/include/libio.h /usr/include/_G_config.h
obstacle.o: /usr/include/wchar.h
obstacle.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
obstacle.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
obstacle.o: /usr/include/math.h /usr/include/bits/huge_val.h
obstacle.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
obstacle.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
obstacle.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
obstacle.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
obstacle.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
obstacle.o: /usr/include/endian.h /usr/include/bits/endian.h
obstacle.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
obstacle.o: /usr/include/time.h /usr/include/sys/select.h
obstacle.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
obstacle.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
obstacle.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
obstacle.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
obstacle.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
obstacle.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
obstacle.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
obstacle.o: /usr/include/bits/posix2_lim.h
obstacle.o: ../../../include/yalecad/okmalloc.h
output.o: mighty.h /usr/include/stdio.h /usr/include/features.h
output.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
output.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
output.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
output.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
output.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
output.o: /usr/include/math.h /usr/include/bits/huge_val.h
output.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
output.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
output.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
output.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
output.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
output.o: /usr/include/endian.h /usr/include/bits/endian.h
output.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
output.o: /usr/include/time.h /usr/include/sys/select.h
output.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
output.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
output.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
output.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
output.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
output.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
output.o: ../../../include/yalecad/message.h
path.o: mighty.h /usr/include/stdio.h /usr/include/features.h
path.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
path.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
path.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
path.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
path.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
path.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
path.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
path.o: /usr/include/math.h /usr/include/bits/huge_val.h
path.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
path.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
path.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
path.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
path.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
path.o: /usr/include/endian.h /usr/include/bits/endian.h
path.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
path.o: /usr/include/time.h /usr/include/sys/select.h
path.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
path.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
path.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
path.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
path.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
path.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
path.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
path.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
pins.o: mighty.h /usr/include/stdio.h /usr/include/features.h
pins.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
pins.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
pins.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
pins.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
pins.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
pins.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
pins.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
pins.o: /usr/include/math.h /usr/include/bits/huge_val.h
pins.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
pins.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
pins.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
pins.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
pins.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
pins.o: /usr/include/endian.h /usr/include/bits/endian.h
pins.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
pins.o: /usr/include/time.h /usr/include/sys/select.h
pins.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
pins.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
pins.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
pins.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
pins.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
pins.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
pins.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
pins.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
pins.o: ../../../include/yalecad/message.h
post.o: mighty.h /usr/include/stdio.h /usr/include/features.h
post.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
post.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
post.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
post.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
post.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
post.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
post.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
post.o: /usr/include/math.h /usr/include/bits/huge_val.h
post.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
post.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
post.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
post.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
post.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
post.o: /usr/include/endian.h /usr/include/bits/endian.h
post.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
post.o: /usr/include/time.h /usr/include/sys/select.h
post.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
post.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
post.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
post.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
post.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
post.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
post.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
post.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
sched.o: mighty.h /usr/include/stdio.h /usr/include/features.h
sched.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
sched.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
sched.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
sched.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
sched.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
sched.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
sched.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
sched.o: /usr/include/math.h /usr/include/bits/huge_val.h
sched.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
sched.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
sched.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
sched.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
sched.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
sched.o: /usr/include/endian.h /usr/include/bits/endian.h
sched.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
sched.o: /usr/include/time.h /usr/include/sys/select.h
sched.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
sched.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
sched.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
sched.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
sched.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
sched.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
sched.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
sched.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
sched.o: ../../../include/yalecad/message.h
stack.o: mighty.h /usr/include/stdio.h /usr/include/features.h
stack.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
stack.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
stack.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
stack.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
stack.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
stack.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
stack.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
stack.o: /usr/include/math.h /usr/include/bits/huge_val.h
stack.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
stack.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
stack.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
stack.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
stack.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
stack.o: /usr/include/endian.h /usr/include/bits/endian.h
stack.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
stack.o: /usr/include/time.h /usr/include/sys/select.h
stack.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
stack.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
stack.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
stack.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
stack.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
stack.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
stack.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
stack.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
