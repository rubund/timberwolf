#  Makefile for TimberWolf draw program.
#  "@(#) Ymakefile (Yale) version 3.15 2/5/91"
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

SCCS_OP=get #normal sccs operation

#destination of output executable
DEST=../
PNAME=draw

# name of the graphics menu and its final destination
MENU=draw_menu

#where object code is located
objdir=../obj
O=${objdir}/

SRC=    main.c\
	read.c\
	cif.c\
	colors.c\
	rtf.c\
	window_manager.c

OBJ =   ${O}main.o\
	${O}read.o\
	${O}cif.o\
	${O}colors.o\
	${O}rtf.o\
	${O}window_manager.o


INS= globals.h menus.h

info:
	-@echo "make ${PNAME} - usage:"
	-@echo "Non-yale users should type "
	-@echo "    'make install_non_yale' - for first compile or "
	-@echo "    'make non_yale' for subsequent compiles"
	-@echo " "

# how to make TimberWolfMC compactor
${DEST}${PNAME}:${OBJ} ${YALECAD} ${MENU}
	${GETDATE}
	${CC} ${CFLAGS} -I. -c ${DATE_C}
	${MV} date.o ${O}date.o 
	${CC} ${CFLAGS} ${OPTIONS} -o ${DEST}${PNAME} ${OBJ} ${O}date.o \
	${YALECAD} ${LINKLIB} 

# we can't do anything about yalecad but want to update if it has changed
${YALECAD}:


install:${DEST}${PNAME} ${MENU}

install_non_yale:
	-${S}if( test -d ${XLIB}${NOGRAPHICS} ) then \
		echo " " ; \
		echo "Note:found ${XLIB}"; \
		echo "making version with XWindow graphics..." ; \
		make ${DEST}${PNAME} GETDATE= CC=${CC} \
		    CLEANUP=${CLEANUP} NOGRAPHICS=${NOGRAPHICS} \
		    UNIX=${UNIX} DEBUG=${DEBUG} YALECAD=${YALECAD} \
		    CFLAGS="${CFLAGS}" LINKLIB="${LINKLIB}" ; \
		echo " " ; \
	else \
		echo " " ; \
		echo "Note:didn't find ${XLIB} or NOGRAPHICS requested"; \
		echo "making version without XWindow graphics..." ; \
		make ${DEST}${PNAME} GETDATE= CC=${CC} \
		    CLEANUP=${CLEANUP} NOGRAPHICS=-DNOGRAPHICS \
		    UNIX=${UNIX} DEBUG=${DEBUG} YALECAD=${YALECAD} \
		    CFLAGS="${CFLAGS}" LINKLIB=-lm ; \
	fi ; 

clean:
	${RM} ${O}* *~ core *.bak

map :   
	nm -apg ${PNAME}

lint:
#	lint ${IDIR} -Ctwtmp ${SRC2}
#	lint ${IDIR} ${SRC} llib-ltwtmp.ln
	lint ${IDIR} *.c  > fool

# how to build makefile dependencies
depend : ;
	${MAKEDEPEND} ${CFLAGS} ${OPTIONS} ${IDIR} ${SRC}

# ********************* begin sccs *********************************
#default sccs operation is get
SCCS_OP=get
#current release
REL=

# how to get sources from sccs
sources : ${SRC} ${INS} ${YMAKEFILE} ${MENU}
${SRC} ${INS} ${YMAKEFILE} ${MENU}: 
	${SCCS} ${SCCS_OP} ${REL} $@
# **********************  end sccs *********************************

#BEGIN DEPENDENCIES -- DO NOT DELETE THIS LINE

#END DEPENDENCIES -- DO NOT DELETE THIS LINE

# sort srcfiles for ${SRC}: 
#    grep '\-c ${placer}' makefile | cut -f5 -d" " | sort

#
#how to compile the source
#
${O}cif.o : cif.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c cif.c 
	${MV} cif.o ${O}cif.o
${O}colors.o : colors.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c colors.c 
	${MV} colors.o ${O}colors.o
${O}main.o : main.c
	${CC} ${CFLAGS} ${IDIR} ${CLEANUP} ${OPTIONS} -c main.c 
	${MV} main.o ${O}main.o
${O}misc.o : misc.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c misc.c 
	${MV} misc.o ${O}misc.o
${O}read.o : read.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c read.c 
	${MV} read.o ${O}read.o
${O}rtf.o : rtf.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c rtf.c 
	${MV} rtf.o ${O}rtf.o
${O}mst.o : mst.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c mst.c 
	${MV} mst.o ${O}mst.o
${O}window_manager.o : window_manager.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c window_manager.c 
	${MV} window_manager.o ${O}window_manager.o
#end of makefile
# DO NOT DELETE

main.o: /usr/include/ctype.h /usr/include/features.h /usr/include/sys/cdefs.h
main.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
main.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
main.o: /usr/include/bits/typesizes.h /usr/include/endian.h
main.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
main.o: /usr/include/xlocale.h /usr/include/stdio.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
main.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
main.o: globals.h ../../../include/yalecad/base.h /usr/include/stdlib.h
main.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
main.o: /usr/include/sys/types.h /usr/include/time.h
main.o: /usr/include/sys/select.h /usr/include/bits/select.h
main.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
main.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
main.o: /usr/include/alloca.h /usr/include/math.h
main.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
main.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
main.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
main.o: /usr/include/bits/mathcalls.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
main.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
main.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
main.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
main.o: ../../../include/yalecad/dbinary.h ../../../include/yalecad/draw.h
main.o: ../../../include/yalecad/cleanup.h ../../../include/yalecad/debug.h
main.o: ../../../include/yalecad/message.h ../../../include/yalecad/file.h
main.o: ../../../include/yalecad/colors.h ../../../include/yalecad/string.h
main.o: ./menus.h
read.o: globals.h ../../../include/yalecad/base.h /usr/include/stdio.h
read.o: /usr/include/features.h /usr/include/sys/cdefs.h
read.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
read.o: /usr/include/gnu/stubs-64.h
read.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
read.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
read.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
read.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
read.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
read.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
read.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
read.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
read.o: /usr/include/sys/types.h /usr/include/time.h
read.o: /usr/include/sys/select.h /usr/include/bits/select.h
read.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
read.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
read.o: /usr/include/alloca.h /usr/include/math.h
read.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
read.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
read.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
read.o: /usr/include/bits/mathcalls.h
read.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
read.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
read.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
read.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
read.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
read.o: ../../../include/yalecad/dbinary.h ../../../include/yalecad/draw.h
read.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
read.o: ../../../include/yalecad/file.h
cif.o: ../../../include/yalecad/base.h /usr/include/stdio.h
cif.o: /usr/include/features.h /usr/include/sys/cdefs.h
cif.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
cif.o: /usr/include/gnu/stubs-64.h
cif.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
cif.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
cif.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
cif.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
cif.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
cif.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
cif.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
cif.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
cif.o: /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h
cif.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
cif.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
cif.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
cif.o: /usr/include/math.h /usr/include/bits/huge_val.h
cif.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
cif.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
cif.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
cif.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
cif.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
cif.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
cif.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
cif.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
cif.o: ../../../include/yalecad/colors.h ../../../include/yalecad/file.h
cif.o: ../../../include/yalecad/message.h
colors.o: /usr/include/stdio.h /usr/include/features.h
colors.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
colors.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
colors.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
colors.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
colors.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
colors.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
colors.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
colors.o: globals.h ../../../include/yalecad/base.h /usr/include/stdlib.h
colors.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
colors.o: /usr/include/endian.h /usr/include/bits/endian.h
colors.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
colors.o: /usr/include/time.h /usr/include/sys/select.h
colors.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
colors.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
colors.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
colors.o: /usr/include/math.h /usr/include/bits/huge_val.h
colors.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
colors.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
colors.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
colors.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
colors.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
colors.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
colors.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
colors.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
colors.o: ../../../include/yalecad/dbinary.h ../../../include/yalecad/draw.h
colors.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
colors.o: ../../../include/yalecad/string.h
rtf.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
rtf.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
rtf.o: /usr/include/gnu/stubs-64.h
rtf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
rtf.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
rtf.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
rtf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
rtf.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
rtf.o: ../../../include/yalecad/base.h /usr/include/stdlib.h
rtf.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
rtf.o: /usr/include/endian.h /usr/include/bits/endian.h
rtf.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
rtf.o: /usr/include/time.h /usr/include/sys/select.h
rtf.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
rtf.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
rtf.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
rtf.o: /usr/include/math.h /usr/include/bits/huge_val.h
rtf.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
rtf.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
rtf.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
rtf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
rtf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
rtf.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
rtf.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
rtf.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
rtf.o: ../../../include/yalecad/draw.h ../../../include/yalecad/colors.h
rtf.o: globals.h ../../../include/yalecad/dbinary.h
window_manager.o: globals.h ../../../include/yalecad/base.h
window_manager.o: /usr/include/stdio.h /usr/include/features.h
window_manager.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
window_manager.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
window_manager.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
window_manager.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
window_manager.o: /usr/include/libio.h /usr/include/_G_config.h
window_manager.o: /usr/include/wchar.h
window_manager.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
window_manager.o: /usr/include/bits/stdio_lim.h
window_manager.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
window_manager.o: /usr/include/bits/waitflags.h
window_manager.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
window_manager.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
window_manager.o: /usr/include/sys/types.h /usr/include/time.h
window_manager.o: /usr/include/sys/select.h /usr/include/bits/select.h
window_manager.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
window_manager.o: /usr/include/sys/sysmacros.h
window_manager.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
window_manager.o: /usr/include/math.h /usr/include/bits/huge_val.h
window_manager.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
window_manager.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
window_manager.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
window_manager.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
window_manager.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
window_manager.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
window_manager.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
window_manager.o: /usr/include/bits/posix2_lim.h
window_manager.o: ../../../include/yalecad/okmalloc.h
window_manager.o: ../../../include/yalecad/dbinary.h
window_manager.o: ../../../include/yalecad/draw.h
window_manager.o: ../../../include/yalecad/message.h
window_manager.o: ../../../include/yalecad/debug.h ./menus.h
