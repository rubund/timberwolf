#  Master Makefile for the TimberWolf system
#  "@(#) Ymakefile (Yale) version 1.27 4/22/92"
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

# relative directory to programs
R=./pgms

# relative directory to example files
T=./test

# where the program source resides
PGMSRC=${R}/Ylib/lib \
	${R}/draw/src \
	${R}/drawnets/src \
	${R}/drawTW/src \
	${R}/gengraph/src \
	${R}/genrows/src \
	${R}/makedepend/src \
	${R}/mc_compact/src \
	${R}/mickey/src \
	${R}/mighty/src \
	${R}/mincut/src \
	${R}/psc/src \
	${R}/syntax/src \
	${R}/tomus/src \
	${R}/twflow/src \
	${R}/twmc/src \
	${R}/twsc/src


PGMBIN= ${R}/draw/draw \
	${R}/drawnets/analyze_nets \
	${R}/drawTW/drawTW \
	${R}/gengraph/gengraph \
	${R}/genrows/genrows \
	${R}/makedepend/makedepend \
	${R}/mc_compact/mc_compact \
	${R}/mickey/Mickey \
	${R}/mighty/TimberWolfDR \
	${R}/mincut/Mincut \
	${R}/psc/psc \
	${R}/syntax/syntax \
	${R}/tomus/Tomus \
	${R}/twflow/twflow \
	${R}/twmc/TimberWolfMC \
	${R}/twsc/TimberWolfSC 

# example file directories
TESTSRC=${T}/macro \
	${T}/mixed \
	${T}/part \
	${T}/stdcell \
	${T}/stdcell2

ARCHIVE=${R}/Ylib/lib/libycad.mem.a \
	${R}/Ylib/lib/libycad.sys.a

# auxillary code compiled only at Yale
AUXSRC= ${R}/mcc/src \
	${R}/date/src \
	${R}/condraw/src \
	${R}/convert/src \
	${R}/utils/src \
	${R}/ymake/src 

# auxillary code compiled only at Yale
AUXBIN=${R}/condraw/condraw \
	${R}/convert/convert \
	${R}/date/getdate \
	${R}/mcc/mcc \
	${R}/sc_route/sc_route \
	${R}/utils/build_menu \
	${R}/utils/net_util \
	${R}/ymake/makehelper 

SRC = .twrc Ymakefile maketape DISCLAIMER README

info:   ;
	-@${ECHO} " "
	-@${ECHO} "Master makefile for the TimberWolf system"
	-@${ECHO} " "
	-@${ECHO} "Non-yale users should first set the TimberWolf"
	-@${ECHO} "    environment variables TWDIR and DATADIR."
	-@${ECHO} "    TWDIR is the pathname of the TimberWolf directory."
	-@${ECHO} "    DATADIR is the pathname of the directory where"
	-@${ECHO} "    graphics dumps are stored.  TWDIR and DATADIR"
	-@${ECHO} "    can be set to their default settings by typing"
	-@${ECHO} "    'source .twrc' <CR>"
	-@${ECHO} " "
	-@${ECHO} "Next users should set compile switches in "
	-@${ECHO} "    ./pgms/ymake/Ymake.macro file"
	-@${ECHO} " "
	-@${ECHO} "Then return to this directory and type "
	-@${ECHO} "    'ymake' <CR>"
	-@${ECHO} "This will reset the top level Makefile"
	-@${ECHO} "Next type:"
	-@${ECHO} "    'make Makefiles' <CR>"
	-@${ECHO} "This will make the machine dependent makefiles"
	-@${ECHO} " "
	-@${ECHO} "Now type"
	-@${ECHO} "    'make install_non_yale' <CR>"
	-@${ECHO} "     to build system"
	-@${ECHO} " "
	-@${ECHO} "Use 'make production' to strip all programs "
	-@${ECHO} " "

init:
	-@defaults/inittw

install:
	@for i in $(PGMSRC); do \
		(cd $$i ;${ECHO} "yale make in $$i..."; \
		make install ; ) \
	done;

install_non_yale:
	for i in $(PGMSRC); do \
		(cd $$i ;${ECHO} "non-yale make in $$i..."; \
		make install_non_yale CLEANUP=${CLEANUP} \
		NOGRAPHICS=${NOGRAPHICS} UNIX=${UNIX} DEBUG=${DEBUG} \
		YALECAD=${YALECAD} CC=${CC} \
		CFLAGS="${CFLAGS} -DSIZEOF_VOID_P=`getconf LONG_BIT`" \
		LINKLIB="${LINKLIB}" GETDATE= ; ) \
	done;

clean:
	@for i in $(PGMSRC); do \
		(cd $$i ;${ECHO} "cleaning binary in $$i..."; \
		make clean ;) \
	done;

veryclean:
	@${MAKE} delpgms
	@${MAKE} delarchives
	@${MAKE} clean
	@${RM} DATA/*
	@for i in $(TESTSRC); do \
		(cd $$i ;${ECHO} "cleaning runtime files in $$i..."; \
		.clean ;) \
	done;

Makefiles:
	( ${R}/ymake/ymake ) ;
#	( cd ${R}/makedepend/src;${YMAKE} nodepend;${MAKE} install_non_yale CC=${CC} ;);
	@for i in $(PGMSRC); do \
		(cd $$i ;${ECHO} "making makefile in $$i..."; \
		${YMAKE} ${YMAKEARGS};) \
	done;

production:
	@for i in $(PGMBIN); do \
		(${ECHO} "striping program $$i..."; \
		${STRIP} $$i ;) \
	done;

delpgms:
	@for i in $(PGMBIN); do \
		(${ECHO} "removing program $$i..."; \
		${RM} $$i ;) \
	done;

delarchives:
	@${ECHO} "removing archives"
	@${RM} ${ARCHIVE}

yacc:
	${RM} doc/tar.yacc doc/tar.yacc.Z
	tar cvf doc/tar.yacc `find ${PGMSRC} ${AUXSRC} -name '*.[ly]' -print | /bin/grep -v SCCS`
	compress doc/tar.yacc


depend: ;

#default sccs operation is get
SCCS_OP=get
#current release
REL=

# how to get sources from sccs
sources : ${SRC}
${SRC}: 
	${SCCS} ${SCCS_OP} ${REL} $@


util:
	@for i in $(PGMSRC); do \
		(cd $$i ;${ECHO} "execing utility - ${UTIL} in $$i..."; \
		${UTIL} ;) \
	done;

sccsclean:
	@for i in $(PGMSRC); do \
		(cd $$i ;${ECHO} "cleaning sccs source in $$i..."; \
		${SCCS} clean; ) \
	done;

sccsutil:
	@for i in $(PGMSRC); do \
		(cd $$i ;${ECHO} "preforming sccs utility - ${UTIL} in $$i..."; \
		${SCCS} ${UTIL}; ) \
	done;

transport:
	@${ECHO} "Ymake.macro file should be correct at this point."
	@${ECHO} "In addition, 'make clean' and 'make cleanaux' should have been run"
	@${ECHO} "You have 10 seconds to kill job"
	sleep 10
	@for i in $(PGMSRC); do \
		(cd $$i ;${ECHO} "readying files in $$i..."; \
		trap "" 1 ; \
		${SCCS} get Ymakefile ; \
		${YMAKE} nodepend ; \
		${MAKE} sources ; \
		trap 1 ; ) ; \
	done;
	@for i in $(AUXSRC); do \
		(cd $$i ;${ECHO} "readying files in $$i..."; \
		trap "" 1 ; \
		${SCCS} get Ymakefile ; \
		${SCCS} get Ymakefile ; \
		${YMAKE} nodepend ; \
		${MAKE} sources ; \
		trap 1 ; ) ; \
	done;
	${ECHO} "build utilities...";
	${MAKE} -i aux
	${MAKE} -i install
	${MAKE} Makefiles

auxinfo:
	-@${ECHO} " "
	-@${ECHO} "Master makefile for the TimberWolf system"
	-@${ECHO} "Auxillary utilities"
	-@${ECHO} "Use 'ymakeaux'     to make aux Makefiles"
	-@${ECHO} "Use 'cleanaux'     to make clean aux objects"
	-@${ECHO} "Use 'aux'          to make aux programs"
	-@${ECHO} "Use 'delaux'       to remove aux programs"
	-@${ECHO} "Use 'sccscleanaux' to remove aux sccs sources"
	-@${ECHO} "Use 'sccsutilaux'  to perform sccs util in aux sources"
	-@${ECHO} "Use 'utilaux'      to perform any util in aux directories"
	-@${ECHO} "Use 'utilaux UTIL="make sources"' to get all sccs sources"
	-@${ECHO} " "

ymakeaux:
	@for i in $(AUXSRC); do \
		(cd $$i ;${ECHO} "making makefile in $$i..."; \
		${YMAKE} ${YMAKEARGS};) \
	done;

cleanaux:
	@for i in $(AUXSRC); do \
		(cd $$i ;${ECHO} "cleaning binary in $$i..."; \
		make clean ;) \
	done;

aux:
	@for i in $(AUXSRC); do \
		(cd $$i ;${ECHO} "yale make in $$i..."; \
		make install ; ) \
	done;

delaux:
	@for i in $(AUXBIN); do \
		(${ECHO} "removing program $$i..."; \
		${RM} $$i ;) \
	done;

sccscleanaux:
	@for i in $(AUXSRC); do \
		(cd $$i ;${ECHO} "cleaning sccs source in $$i..."; \
		${SCCS} clean; ) \
	done;

sccsutilaux:
	@for i in $(AUXSRC); do \
		(cd $$i ;${ECHO} "preforming sccs utility - ${UTIL} in $$i..."; \
		${SCCS} ${UTIL}; ) \
	done;

utilaux:
	@for i in $(AUXSRC); do \
		(cd $$i ;${ECHO} "execing utility - ${UTIL} in $$i..."; \
		${UTIL} ;) \
	done;


sccsinfo: ;
	sccs info ;
	(cd ${R}/Ylib/include; sccs info ; ) ;
	(cd ${R}/Ylib/lib; sccs info ; ) ;
	find . -name src -print -exec sccs -d {} info \;

clean_data: ;
	(cd ; find . -name cell.bin.\* -print -exec rm {} \; )
	(cd ; find . -name pin.bin.\* -print -exec rm {} \; )
	(cd ; find . -name net.bin.\* -print -exec rm {} \; )
	(cd ; find . -name symb.bin.\* -print -exec rm {} \; )

# start off with the directories originally set for 68k
setup_apollo: ;
	for i in $(PGMSRC); do \
	(   if( test $$i = ${R}/Ylib/lib ) then \
		make delarchives ; \
		(cd $$i ; make clean ; \
		ar r libycad.mem.a.68k ; \
		ar r libycad.sys.a.68k ; \
		ar r libycad.mem.a.88k ; \
		ar r libycad.sys.a.88k ; ) ; \
	     fi ; \
	     ${ECHO} "setting up object directories in $$i" ; \
	     ( cd $$i ; \
	       ${MV} ../obj ../obj.68k ; \
	       mkdir ../obj.88k ; \
	       ln -s ./obj.68k ../obj ; \
	     ) ; \
	) ; \
	done;

clean_apollo: ;
	for i in $(PGMSRC); do \
	(   if( test $$i = ${R}/Ylib/lib ) then \
		make delarchives ; \
		(cd $$i ; make clean ; \
		${RM} libycad.mem.a.68k ; \
		${RM} libycad.sys.a.68k ; \
		${RM} libycad.mem.a.88k ; \
		${RM} libycad.sys.a.88k ; ) ; \
	     fi ; \
	     ${ECHO} "Removing apollo object directories in $$i" ; \
	     ( cd $$i ; \
	       /bin/rm -rf ../obj.68k ; \
	       /bin/rm -rf ../obj.88k ; \
	       /bin/rm -rf ../obj ; \
	       mkdir ../obj ; \
	     ) ; \
	) ; \
	done;

apollo: ;
	for i in $(PGMSRC); do \
	( if( test $$i = ${R}/Ylib/lib ) then \
		 ${ECHO} "setting up library archives in $$i" ; \
		 (cd $$i; \
		    ${RM} libycad.mem.a ; \
		    ln -s libycad.mem.a.68k libycad.mem.a ; \
		    ${RM} libycad.sys.a ; \
		    ln -s libycad.sys.a.68k libycad.sys.a ; ) ; \
	     fi ; \
	     ${ECHO} "setting up object directories in $$i" ; \
	     ( cd $$i ; \
	       ${RM} ../obj ; \
	       ln -s ./obj.68k ../obj ; \
	     ) ; \
	) ; \
	done;
	make install_non_yale
dn10000: ;
	${ECHO} "You should be logged onto a DN10000"
	${ECHO} "You have 10 seconds to kill make"
	sleep 10
	( trap "" 1 ; \
	for i in $(PGMBIN); do \
	   if( test -f $$i.68k ) then \
		${ECHO} "moving $$i back to correct place..."; \
		${MV} $$i.68k $$i; \
	    fi ; \
	done; \
	trap 1 ; \
	) ;
	for i in $(PGMSRC); do \
	(   if( test $$i = ${R}/Ylib/lib ) then \
		 ${ECHO} "setting up library archives in $$i" ; \
		 (cd $$i; \
		    ${RM} libycad.mem.a ; \
		    ln -s libycad.mem.a.88k libycad.mem.a ; \
		    ${RM} libycad.sys.a ; \
		    ln -s libycad.sys.a.88k libycad.sys.a ; ) ; \
	     fi ; \
	     ${ECHO} "setting up object directories in $$i" ; \
	     ( cd $$i ; \
	       ${RM} ../obj ; \
	       ln -s ./obj.88k ../obj ; \
	     ) ; \
	) ; \
	done;
	for i in $(PGMBIN); do \
	(   if( test -f $$i ) then \
		${ECHO} "moving 68k version of $$i..."; \
		${MV} $$i $$i.68k; \
	    fi ; \
	) ; \
	done;
	make install_non_yale CC=${CC} GETDATE=getdate.prism CFLAGS="-O" \
		YACC=echo LEX=echo YACCMV=echo LEXMV=echo

	for i in $(PGMBIN); do \
	(   ${MV} $$i $$i.prism; \
	    if( test -f $$i.68k ) then \
		${ECHO} "moving $$i back..."; \
		${MV} $$i.68k $$i; \
	    fi ; \
	) ; \
	done;

#end of makefile
