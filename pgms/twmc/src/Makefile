# Ymakefile for program TimberWolfMC
#  "@(#) Ymakefile (Yale) version 3.13 5/5/91 " 
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
PNAME=TimberWolfMC


# name of the graphics menu and destination
MENU=mc_menu mc.dialog menus.h dialog.h

#where object code is located
O=../obj/

SRC= \
	acceptt.c \
	analyze.c \
	compact.c \
	config1.c \
	config2.c \
	configpads.c \
	debug.c \
	finalout.c \
	finalpin.c \
	findcheck.c \
	findcost.c \
	findloc.c \
	findside.c \
	fixcell.c \
	genorient.c \
	gmain.c \
	graphics.c \
	initialize.c \
	initnets.c \
	loadbins.c \
	main.c \
	makebins.c \
	makesite.c \
	mergecell.c \
	neworient.c \
	newtemp.c \
	outgeo.c \
	outpin.c \
	output.c \
	overlap.c \
	partition.c \
	paths.c \
	penalties.c \
	perimeter.c \
	placepads.c \
	placepin.c \
	prboard.c \
	readcells.c \
	readnets.c \
	readpar.c \
	reconfig.c \
	rmain.c \
	savewolf.c \
	scrapnet.c \
	selectpin.c \
	setpwates.c \
	sortpad.c \
	sortpin.c \
	twstats.c \
	uaspect.c \
	uinst.c \
	uloop.c \
	unbust.c \
	unet.c \
	upin.c \
	upinswap.c \
	usite1.c \
	usite2.c \
	usoftmove.c \
	utemp.c \
	watesides.c \
	window.c \
	wirecosts.c \
	wireest.c \
	wireratio.c 

OBJ= \
	${O}acceptt.o \
	${O}analyze.o \
	${O}compact.o \
	${O}config1.o \
	${O}config2.o \
	${O}configpads.o \
	${O}debug.o \
	${O}finalout.o \
	${O}finalpin.o \
	${O}findcheck.o \
	${O}findcost.o \
	${O}findloc.o \
	${O}findside.o \
	${O}fixcell.o \
	${O}genorient.o \
	${O}gmain.o \
	${O}graphics.o \
	${O}initialize.o \
	${O}initnets.o \
	${O}loadbins.o \
	${O}main.o \
	${O}makebins.o \
	${O}makesite.o \
	${O}mergecell.o \
	${O}neworient.o \
	${O}newtemp.o \
	${O}outgeo.o \
	${O}outpin.o \
	${O}output.o \
	${O}overlap.o \
	${O}partition.o \
	${O}paths.o \
	${O}penalties.o \
	${O}perimeter.o \
	${O}placepads.o \
	${O}placepin.o \
	${O}prboard.o \
	${O}readcells.o \
	${O}readnets.o \
	${O}readpar.o \
	${O}reconfig.o \
	${O}rmain.o \
	${O}savewolf.o \
	${O}scrapnet.o \
	${O}selectpin.o \
	${O}setpwates.o \
	${O}sortpad.o \
	${O}sortpin.o \
	${O}twstats.o \
	${O}uaspect.o \
	${O}uinst.o \
	${O}uloop.o \
	${O}unbust.o \
	${O}unet.o \
	${O}upin.o \
	${O}upinswap.o \
	${O}usite1.o \
	${O}usite2.o \
	${O}usoftmove.o \
	${O}utemp.o \
	${O}watesides.o \
	${O}window.o \
	${O}wirecosts.o \
	${O}wireest.o \
	${O}wireratio.o 

INS= \
	analog.h \
	custom.h \
	dens.h \
	initialize.h \
	main.h \
	pads.h \
	partition.h \
	readcells.h \
	readnets.h \
	temp.h \
	tidialog.h 

info:   ;
	-@echo "make ${PNAME} - usage:"
	-@echo "Non-Yale users should type "
	-@echo "    'make install_non_yale' <CR>"
	-@echo "Yale users should type "
	-@echo "    'make install' <CR>"
	-@echo " "

# how to make TimberWolfMC
${DEST}${PNAME}:${OBJ} ${YALECAD}
	${GETDATE}
	${CC} ${CFLAGS} -I. -c ${DATE_C}
	${MV} date.o ${O}date.o 
	${CC} ${CFLAGS} ${OPTIONS} -o ${DEST}${PNAME} ${OBJ} ${O}date.o \
	${YALECAD} ${LINKLIB} 

# we can't do anything about yalecad but want to update if it has changed
${YALECAD}:

# need this lines for yale installation. Null otherwise.  

install:${DEST}${PNAME} 

install_non_yale:
	-${S}if( test -d ${XLIB}${NOGRAPHICS} ) then \
		echo " " ; \
		echo "Note:found ${XLIB}"; \
		echo "making version with XWindow graphics..." ;\
		make ${DEST}${PNAME} GETDATE= CC=${CC} \
		    CLEANUP=${CLEANUP} NOGRAPHICS=${NOGRAPHICS} \
		    UNIX=${UNIX} DEBUG=${DEBUG} YALECAD=${YALECAD} \
		    CFLAGS="${CFLAGS}" LINKLIB="${LINKLIB}" ;\
		echo " " ; \
	else \
		echo " " ; \
		echo "Note:didn't find ${XLIB} or NOGRAPHICS requested"; \
		echo "making version without XWindow graphics..." ; \
		make ${DEST}${PNAME} GETDATE= CC=${CC} \
		    CLEANUP=${CLEANUP} NOGRAPHICS=-DNOGRAPHICS \
		    UNIX=${UNIX} DEBUG=${DEBUG} YALECAD=${YALECAD} \
		    CFLAGS="${CFLAGS}" LINKLIB=-lm ;\
	fi ; 

clean:
	${RM} ${O}* ~* core *.bak foo y.output

cleanall:
	make clean
	${RM} readcells_l.h readcells.c readnets_l.h readnets.c

# how to build makefile dependencies
depend : ;
	${MAKEDEPEND} ${CFLAGS} ${OPTIONS} ${IDIR} ${SRC}

map :   
	nm -apg ${PNAME}

#used to make documentation
bnf :  ys.awk 
	${AWK} -f ys.awk readcells.y > foo
	sed -e 's/;//' foo > cells_bnf
	${AWK} -f ys.awk readnets.y > foo
	sed -e 's/;//' foo > nets_bnf
	${RM} foo

user_parser :  parsery.awk parserl.awk
	${AWK} -f parserl.awk readcells.l > uparser.l
	${AWK} -f parsery.awk readcells.y > uparser.y
	${LEX}  uparser.l
	${YACC} uparser.y
	${CC} -DTEST -o uparser y.tab.c

cleanbnf: ;
	${RM} *_bnf ys.awk

lint:
	lint ${LINT_OPT} ${IDIR} ${OPTIONS} ${SRC} >lint.out

# *************************** SCCS *******************************
sources: ${SRC} ${INS} ${MENU} Ymakefile ys.awk
	
${SRC} ${INS} ${MENU} Ymakefile ys.awk:
	${SCCS} ${SCCS_OP} ${REL} $@

# ************************ END SCCS *****************************
#BEGIN DEPENDENCIES -- DO NOT DELETE THIS LINE

#END DEPENDENCIES -- DO NOT DELETE THIS LINE


# How to compile the sources
${O}acceptt.o:acceptt.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  acceptt.c
	${MV} acceptt.o ${O}acceptt.o
${O}analyze.o:analyze.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  analyze.c
	${MV} analyze.o ${O}analyze.o
${O}compact.o:compact.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  compact.c
	${MV} compact.o ${O}compact.o
${O}config1.o:config1.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  config1.c
	${MV} config1.o ${O}config1.o
${O}config2.o:config2.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  config2.c
	${MV} config2.o ${O}config2.o
${O}configpads.o:configpads.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  configpads.c
	${MV} configpads.o ${O}configpads.o
${O}debug.o:debug.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  debug.c
	${MV} debug.o ${O}debug.o
${O}finalout.o:finalout.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  finalout.c
	${MV} finalout.o ${O}finalout.o
${O}finalpin.o:finalpin.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  finalpin.c
	${MV} finalpin.o ${O}finalpin.o
${O}findcheck.o:findcheck.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  findcheck.c
	${MV} findcheck.o ${O}findcheck.o
${O}findcost.o:findcost.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  findcost.c
	${MV} findcost.o ${O}findcost.o
${O}findloc.o:findloc.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  findloc.c
	${MV} findloc.o ${O}findloc.o
${O}findside.o:findside.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  findside.c
	${MV} findside.o ${O}findside.o
${O}fixcell.o:fixcell.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  fixcell.c
	${MV} fixcell.o ${O}fixcell.o
${O}genorient.o:genorient.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  genorient.c
	${MV} genorient.o ${O}genorient.o
${O}gmain.o:gmain.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  gmain.c
	${MV} gmain.o ${O}gmain.o
${O}graphics.o:graphics.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  graphics.c
	${MV} graphics.o ${O}graphics.o
${O}initialize.o:initialize.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  initialize.c
	${MV} initialize.o ${O}initialize.o
${O}initnets.o:initnets.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  initnets.c
	${MV} initnets.o ${O}initnets.o
${O}loadbins.o:loadbins.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  loadbins.c
	${MV} loadbins.o ${O}loadbins.o
${O}main.o:main.c
	${CC} ${CLEANUP} ${CFLAGS} ${IDIR} ${OPTIONS} -c  main.c
	${MV} main.o ${O}main.o
${O}makebins.o:makebins.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  makebins.c
	${MV} makebins.o ${O}makebins.o
${O}makesite.o:makesite.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  makesite.c
	${MV} makesite.o ${O}makesite.o
${O}mergecell.o:mergecell.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  mergecell.c
	${MV} mergecell.o ${O}mergecell.o
${O}neworient.o:neworient.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  neworient.c
	${MV} neworient.o ${O}neworient.o
${O}newtemp.o:newtemp.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  newtemp.c
	${MV} newtemp.o ${O}newtemp.o
${O}outgeo.o:outgeo.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  outgeo.c
	${MV} outgeo.o ${O}outgeo.o
${O}outpin.o:outpin.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  outpin.c
	${MV} outpin.o ${O}outpin.o
${O}output.o:output.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  output.c
	${MV} output.o ${O}output.o
${O}overlap.o:overlap.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  overlap.c
	${MV} overlap.o ${O}overlap.o
${O}partition.o:partition.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  partition.c
	${MV} partition.o ${O}partition.o
${O}paths.o:paths.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  paths.c
	${MV} paths.o ${O}paths.o
${O}penalties.o:penalties.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  penalties.c
	${MV} penalties.o ${O}penalties.o
${O}perimeter.o:perimeter.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  perimeter.c
	${MV} perimeter.o ${O}perimeter.o
${O}placepads.o:placepads.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  placepads.c
	${MV} placepads.o ${O}placepads.o
${O}placepin.o:placepin.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  placepin.c
	${MV} placepin.o ${O}placepin.o
${O}prboard.o:prboard.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  prboard.c
	${MV} prboard.o ${O}prboard.o
${O}readcells.o:readcells.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  readcells.c
	${MV} readcells.o ${O}readcells.o
${O}readnets.o:readnets.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  readnets.c
	${MV} readnets.o ${O}readnets.o
${O}readpar.o:readpar.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  readpar.c
	${MV} readpar.o ${O}readpar.o
${O}reconfig.o:reconfig.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  reconfig.c
	${MV} reconfig.o ${O}reconfig.o
${O}rmain.o:rmain.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  rmain.c
	${MV} rmain.o ${O}rmain.o
${O}savewolf.o:savewolf.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  savewolf.c
	${MV} savewolf.o ${O}savewolf.o
${O}scrapnet.o:scrapnet.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  scrapnet.c
	${MV} scrapnet.o ${O}scrapnet.o
${O}selectpin.o:selectpin.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  selectpin.c
	${MV} selectpin.o ${O}selectpin.o
${O}setpwates.o:setpwates.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  setpwates.c
	${MV} setpwates.o ${O}setpwates.o
${O}sortpad.o:sortpad.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  sortpad.c
	${MV} sortpad.o ${O}sortpad.o
${O}sortpin.o:sortpin.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  sortpin.c
	${MV} sortpin.o ${O}sortpin.o
${O}twstats.o:twstats.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  twstats.c
	${MV} twstats.o ${O}twstats.o
${O}uaspect.o:uaspect.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  uaspect.c
	${MV} uaspect.o ${O}uaspect.o
${O}uinst.o:uinst.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  uinst.c
	${MV} uinst.o ${O}uinst.o
${O}uloop.o:uloop.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  uloop.c
	${MV} uloop.o ${O}uloop.o
${O}unbust.o:unbust.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  unbust.c
	${MV} unbust.o ${O}unbust.o
${O}unet.o:unet.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  unet.c
	${MV} unet.o ${O}unet.o
${O}upin.o:upin.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  upin.c
	${MV} upin.o ${O}upin.o
${O}upinswap.o:upinswap.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  upinswap.c
	${MV} upinswap.o ${O}upinswap.o
${O}usite1.o:usite1.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  usite1.c
	${MV} usite1.o ${O}usite1.o
${O}usite2.o:usite2.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  usite2.c
	${MV} usite2.o ${O}usite2.o
${O}usoftmove.o:usoftmove.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  usoftmove.c
	${MV} usoftmove.o ${O}usoftmove.o
${O}utemp.o:utemp.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  utemp.c
	${MV} utemp.o ${O}utemp.o
${O}watesides.o:watesides.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  watesides.c
	${MV} watesides.o ${O}watesides.o
${O}window.o:window.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  window.c
	${MV} window.o ${O}window.o
${O}wirecosts.o:wirecosts.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  wirecosts.c
	${MV} wirecosts.o ${O}wirecosts.o
${O}wireest.o:wireest.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  wireest.c
	${MV} wireest.o ${O}wireest.o
${O}wireratio.o:wireratio.c
	${CC} ${CFLAGS} ${IDIR} ${OPTIONS} -c  wireratio.c
	${MV} wireratio.o ${O}wireratio.o

# end makefile
# DO NOT DELETE

acceptt.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
acceptt.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
acceptt.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
acceptt.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
acceptt.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
acceptt.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
acceptt.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
acceptt.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
acceptt.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
acceptt.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
acceptt.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
acceptt.o: /usr/include/sys/types.h /usr/include/time.h
acceptt.o: /usr/include/sys/select.h /usr/include/bits/select.h
acceptt.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
acceptt.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
acceptt.o: /usr/include/alloca.h /usr/include/math.h
acceptt.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
acceptt.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
acceptt.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
acceptt.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
acceptt.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
acceptt.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
acceptt.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
acceptt.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
acceptt.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
acceptt.o: ../../../include/yalecad/message.h ./analog.h
acceptt.o: ../../../include/yalecad/debug.h
analyze.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
analyze.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
analyze.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
analyze.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
analyze.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
analyze.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
analyze.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
analyze.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
analyze.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
analyze.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
analyze.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
analyze.o: /usr/include/sys/types.h /usr/include/time.h
analyze.o: /usr/include/sys/select.h /usr/include/bits/select.h
analyze.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
analyze.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
analyze.o: /usr/include/alloca.h /usr/include/math.h
analyze.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
analyze.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
analyze.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
analyze.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
analyze.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
analyze.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
analyze.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
analyze.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
analyze.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
analyze.o: ../../../include/yalecad/message.h ./analog.h
analyze.o: ../../../include/yalecad/debug.h ../../../include/yalecad/string.h
analyze.o: ../../../include/yalecad/file.h
compact.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
compact.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
compact.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
compact.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
compact.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
compact.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
compact.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
compact.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
compact.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
compact.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
compact.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
compact.o: /usr/include/sys/types.h /usr/include/time.h
compact.o: /usr/include/sys/select.h /usr/include/bits/select.h
compact.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
compact.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
compact.o: /usr/include/alloca.h /usr/include/math.h
compact.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
compact.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
compact.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
compact.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
compact.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
compact.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
compact.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
compact.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
compact.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
compact.o: ../../../include/yalecad/message.h ./analog.h ./dens.h
compact.o: ../../../include/yalecad/debug.h ../../../include/yalecad/file.h
compact.o: ../../../include/yalecad/string.h
config1.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
config1.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
config1.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
config1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
config1.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
config1.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
config1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
config1.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
config1.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
config1.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
config1.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
config1.o: /usr/include/sys/types.h /usr/include/time.h
config1.o: /usr/include/sys/select.h /usr/include/bits/select.h
config1.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
config1.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
config1.o: /usr/include/alloca.h /usr/include/math.h
config1.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
config1.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
config1.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
config1.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
config1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
config1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
config1.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
config1.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
config1.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
config1.o: ../../../include/yalecad/message.h ./analog.h
config1.o: ../../../include/yalecad/debug.h ../../../include/yalecad/file.h
config2.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
config2.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
config2.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
config2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
config2.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
config2.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
config2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
config2.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
config2.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
config2.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
config2.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
config2.o: /usr/include/sys/types.h /usr/include/time.h
config2.o: /usr/include/sys/select.h /usr/include/bits/select.h
config2.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
config2.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
config2.o: /usr/include/alloca.h /usr/include/math.h
config2.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
config2.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
config2.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
config2.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
config2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
config2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
config2.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
config2.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
config2.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
config2.o: ../../../include/yalecad/message.h ./analog.h
config2.o: ../../../include/yalecad/debug.h
configpads.o: ./custom.h ./main.h /usr/include/stdio.h
configpads.o: /usr/include/features.h /usr/include/sys/cdefs.h
configpads.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
configpads.o: /usr/include/gnu/stubs-64.h
configpads.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
configpads.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
configpads.o: /usr/include/libio.h /usr/include/_G_config.h
configpads.o: /usr/include/wchar.h
configpads.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
configpads.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
configpads.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
configpads.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
configpads.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
configpads.o: /usr/include/sys/types.h /usr/include/time.h
configpads.o: /usr/include/sys/select.h /usr/include/bits/select.h
configpads.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
configpads.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
configpads.o: /usr/include/alloca.h /usr/include/math.h
configpads.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
configpads.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
configpads.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
configpads.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
configpads.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
configpads.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
configpads.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
configpads.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
configpads.o: /usr/include/bits/posix2_lim.h
configpads.o: ../../../include/yalecad/okmalloc.h
configpads.o: ../../../include/yalecad/message.h ./analog.h ./pads.h
configpads.o: ../../../include/yalecad/debug.h
configpads.o: ../../../include/yalecad/relpos.h
debug.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
debug.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
debug.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
debug.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
debug.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
debug.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
debug.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
debug.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
debug.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
debug.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
debug.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
debug.o: /usr/include/sys/types.h /usr/include/time.h
debug.o: /usr/include/sys/select.h /usr/include/bits/select.h
debug.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
debug.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
debug.o: /usr/include/alloca.h /usr/include/math.h
debug.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
debug.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
debug.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
debug.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
debug.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
debug.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
debug.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
debug.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
debug.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
debug.o: ../../../include/yalecad/message.h ./analog.h
debug.o: ../../../include/yalecad/debug.h ../../../include/yalecad/file.h
debug.o: ../../../include/yalecad/string.h
finalout.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
finalout.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
finalout.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
finalout.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
finalout.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
finalout.o: /usr/include/libio.h /usr/include/_G_config.h
finalout.o: /usr/include/wchar.h
finalout.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
finalout.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
finalout.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
finalout.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
finalout.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
finalout.o: /usr/include/sys/types.h /usr/include/time.h
finalout.o: /usr/include/sys/select.h /usr/include/bits/select.h
finalout.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
finalout.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
finalout.o: /usr/include/alloca.h /usr/include/math.h
finalout.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
finalout.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
finalout.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
finalout.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
finalout.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
finalout.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
finalout.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
finalout.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
finalout.o: /usr/include/bits/posix2_lim.h
finalout.o: ../../../include/yalecad/okmalloc.h
finalout.o: ../../../include/yalecad/message.h ./analog.h
finalout.o: ../../../include/yalecad/debug.h
finalpin.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
finalpin.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
finalpin.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
finalpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
finalpin.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
finalpin.o: /usr/include/libio.h /usr/include/_G_config.h
finalpin.o: /usr/include/wchar.h
finalpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
finalpin.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
finalpin.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
finalpin.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
finalpin.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
finalpin.o: /usr/include/sys/types.h /usr/include/time.h
finalpin.o: /usr/include/sys/select.h /usr/include/bits/select.h
finalpin.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
finalpin.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
finalpin.o: /usr/include/alloca.h /usr/include/math.h
finalpin.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
finalpin.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
finalpin.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
finalpin.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
finalpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
finalpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
finalpin.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
finalpin.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
finalpin.o: /usr/include/bits/posix2_lim.h
finalpin.o: ../../../include/yalecad/okmalloc.h
finalpin.o: ../../../include/yalecad/message.h ./analog.h
finalpin.o: ../../../include/yalecad/debug.h
findcheck.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
findcheck.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
findcheck.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
findcheck.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
findcheck.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
findcheck.o: /usr/include/libio.h /usr/include/_G_config.h
findcheck.o: /usr/include/wchar.h
findcheck.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
findcheck.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
findcheck.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
findcheck.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
findcheck.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
findcheck.o: /usr/include/sys/types.h /usr/include/time.h
findcheck.o: /usr/include/sys/select.h /usr/include/bits/select.h
findcheck.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
findcheck.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
findcheck.o: /usr/include/alloca.h /usr/include/math.h
findcheck.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
findcheck.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
findcheck.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
findcheck.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
findcheck.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
findcheck.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
findcheck.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
findcheck.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
findcheck.o: /usr/include/bits/posix2_lim.h
findcheck.o: ../../../include/yalecad/okmalloc.h
findcheck.o: ../../../include/yalecad/message.h ./analog.h
findcheck.o: ../../../include/yalecad/relpos.h
findcheck.o: ../../../include/yalecad/debug.h
findcost.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
findcost.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
findcost.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
findcost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
findcost.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
findcost.o: /usr/include/libio.h /usr/include/_G_config.h
findcost.o: /usr/include/wchar.h
findcost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
findcost.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
findcost.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
findcost.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
findcost.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
findcost.o: /usr/include/sys/types.h /usr/include/time.h
findcost.o: /usr/include/sys/select.h /usr/include/bits/select.h
findcost.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
findcost.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
findcost.o: /usr/include/alloca.h /usr/include/math.h
findcost.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
findcost.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
findcost.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
findcost.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
findcost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
findcost.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
findcost.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
findcost.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
findcost.o: /usr/include/bits/posix2_lim.h
findcost.o: ../../../include/yalecad/okmalloc.h
findcost.o: ../../../include/yalecad/message.h ./analog.h
findcost.o: ../../../include/yalecad/relpos.h
findcost.o: ../../../include/yalecad/debug.h
findloc.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
findloc.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
findloc.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
findloc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
findloc.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
findloc.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
findloc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
findloc.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
findloc.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
findloc.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
findloc.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
findloc.o: /usr/include/sys/types.h /usr/include/time.h
findloc.o: /usr/include/sys/select.h /usr/include/bits/select.h
findloc.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
findloc.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
findloc.o: /usr/include/alloca.h /usr/include/math.h
findloc.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
findloc.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
findloc.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
findloc.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
findloc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
findloc.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
findloc.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
findloc.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
findloc.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
findloc.o: ../../../include/yalecad/message.h ./analog.h
findloc.o: ../../../include/yalecad/debug.h
findside.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
findside.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
findside.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
findside.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
findside.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
findside.o: /usr/include/libio.h /usr/include/_G_config.h
findside.o: /usr/include/wchar.h
findside.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
findside.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
findside.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
findside.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
findside.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
findside.o: /usr/include/sys/types.h /usr/include/time.h
findside.o: /usr/include/sys/select.h /usr/include/bits/select.h
findside.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
findside.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
findside.o: /usr/include/alloca.h /usr/include/math.h
findside.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
findside.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
findside.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
findside.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
findside.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
findside.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
findside.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
findside.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
findside.o: /usr/include/bits/posix2_lim.h
findside.o: ../../../include/yalecad/okmalloc.h
findside.o: ../../../include/yalecad/message.h ./analog.h ./initialize.h
findside.o: ../../../include/yalecad/debug.h ../../../include/yalecad/set.h
fixcell.o: /usr/include/string.h /usr/include/features.h
fixcell.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
fixcell.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
fixcell.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
fixcell.o: /usr/include/xlocale.h ./custom.h ./main.h /usr/include/stdio.h
fixcell.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
fixcell.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
fixcell.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
fixcell.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
fixcell.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
fixcell.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
fixcell.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
fixcell.o: /usr/include/sys/types.h /usr/include/time.h
fixcell.o: /usr/include/sys/select.h /usr/include/bits/select.h
fixcell.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
fixcell.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
fixcell.o: /usr/include/alloca.h /usr/include/math.h
fixcell.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
fixcell.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
fixcell.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
fixcell.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
fixcell.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
fixcell.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
fixcell.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
fixcell.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
fixcell.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
fixcell.o: ../../../include/yalecad/message.h ./analog.h
fixcell.o: ../../../include/yalecad/debug.h
genorient.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
genorient.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
genorient.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
genorient.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
genorient.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
genorient.o: /usr/include/libio.h /usr/include/_G_config.h
genorient.o: /usr/include/wchar.h
genorient.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
genorient.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
genorient.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
genorient.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
genorient.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
genorient.o: /usr/include/sys/types.h /usr/include/time.h
genorient.o: /usr/include/sys/select.h /usr/include/bits/select.h
genorient.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
genorient.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
genorient.o: /usr/include/alloca.h /usr/include/math.h
genorient.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
genorient.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
genorient.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
genorient.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
genorient.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
genorient.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
genorient.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
genorient.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
genorient.o: /usr/include/bits/posix2_lim.h
genorient.o: ../../../include/yalecad/okmalloc.h
genorient.o: ../../../include/yalecad/message.h ./analog.h ./pads.h
genorient.o: ../../../include/yalecad/debug.h
genorient.o: ../../../include/yalecad/relpos.h
gmain.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
gmain.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
gmain.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
gmain.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
gmain.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
gmain.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
gmain.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
gmain.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
gmain.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
gmain.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
gmain.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
gmain.o: /usr/include/sys/types.h /usr/include/time.h
gmain.o: /usr/include/sys/select.h /usr/include/bits/select.h
gmain.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
gmain.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
gmain.o: /usr/include/alloca.h /usr/include/math.h
gmain.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
gmain.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
gmain.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
gmain.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
gmain.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
gmain.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
gmain.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
gmain.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
gmain.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
gmain.o: ../../../include/yalecad/message.h ./analog.h ./dens.h
gmain.o: ../../../include/yalecad/debug.h ../../../include/yalecad/file.h
gmain.o: ../../../include/yalecad/string.h
graphics.o: /usr/include/string.h /usr/include/features.h
graphics.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
graphics.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
graphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
graphics.o: /usr/include/xlocale.h ./custom.h ./main.h /usr/include/stdio.h
graphics.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
graphics.o: /usr/include/libio.h /usr/include/_G_config.h
graphics.o: /usr/include/wchar.h
graphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
graphics.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
graphics.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
graphics.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
graphics.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
graphics.o: /usr/include/sys/types.h /usr/include/time.h
graphics.o: /usr/include/sys/select.h /usr/include/bits/select.h
graphics.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
graphics.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
graphics.o: /usr/include/alloca.h /usr/include/math.h
graphics.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
graphics.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
graphics.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
graphics.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
graphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
graphics.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
graphics.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
graphics.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
graphics.o: /usr/include/bits/posix2_lim.h
graphics.o: ../../../include/yalecad/okmalloc.h
graphics.o: ../../../include/yalecad/message.h ./analog.h ./dens.h
graphics.o: ../../../include/yalecad/debug.h
graphics.o: ../../../include/yalecad/relpos.h
graphics.o: ../../../include/yalecad/colors.h ../../../include/yalecad/draw.h
graphics.o: ../../../include/yalecad/dialog.h
graphics.o: ../../../include/yalecad/system.h ./menus.h ./dialog.h
initialize.o: /usr/include/string.h /usr/include/features.h
initialize.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
initialize.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
initialize.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
initialize.o: /usr/include/xlocale.h ./custom.h ./main.h /usr/include/stdio.h
initialize.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
initialize.o: /usr/include/libio.h /usr/include/_G_config.h
initialize.o: /usr/include/wchar.h
initialize.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
initialize.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
initialize.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
initialize.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
initialize.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
initialize.o: /usr/include/sys/types.h /usr/include/time.h
initialize.o: /usr/include/sys/select.h /usr/include/bits/select.h
initialize.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
initialize.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
initialize.o: /usr/include/alloca.h /usr/include/math.h
initialize.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
initialize.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
initialize.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
initialize.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
initialize.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
initialize.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
initialize.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
initialize.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
initialize.o: /usr/include/bits/posix2_lim.h
initialize.o: ../../../include/yalecad/okmalloc.h
initialize.o: ../../../include/yalecad/message.h ./analog.h ./pads.h
initialize.o: ./initialize.h ../../../include/yalecad/buster.h
initialize.o: ../../../include/yalecad/hash.h
initialize.o: ../../../include/yalecad/debug.h
initialize.o: ../../../include/yalecad/string.h
initnets.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
initnets.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
initnets.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
initnets.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
initnets.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
initnets.o: /usr/include/libio.h /usr/include/_G_config.h
initnets.o: /usr/include/wchar.h
initnets.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
initnets.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
initnets.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
initnets.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
initnets.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
initnets.o: /usr/include/sys/types.h /usr/include/time.h
initnets.o: /usr/include/sys/select.h /usr/include/bits/select.h
initnets.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
initnets.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
initnets.o: /usr/include/alloca.h /usr/include/math.h
initnets.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
initnets.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
initnets.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
initnets.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
initnets.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
initnets.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
initnets.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
initnets.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
initnets.o: /usr/include/bits/posix2_lim.h
initnets.o: ../../../include/yalecad/okmalloc.h
initnets.o: ../../../include/yalecad/message.h ./analog.h
initnets.o: ../../../include/yalecad/hash.h ../../../include/yalecad/debug.h
initnets.o: ./readnets.h
loadbins.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
loadbins.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
loadbins.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
loadbins.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
loadbins.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
loadbins.o: /usr/include/libio.h /usr/include/_G_config.h
loadbins.o: /usr/include/wchar.h
loadbins.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
loadbins.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
loadbins.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
loadbins.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
loadbins.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
loadbins.o: /usr/include/sys/types.h /usr/include/time.h
loadbins.o: /usr/include/sys/select.h /usr/include/bits/select.h
loadbins.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
loadbins.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
loadbins.o: /usr/include/alloca.h /usr/include/math.h
loadbins.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
loadbins.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
loadbins.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
loadbins.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
loadbins.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
loadbins.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
loadbins.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
loadbins.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
loadbins.o: /usr/include/bits/posix2_lim.h
loadbins.o: ../../../include/yalecad/okmalloc.h
loadbins.o: ../../../include/yalecad/message.h ./analog.h
loadbins.o: ../../../include/yalecad/debug.h
main.o: /usr/include/string.h /usr/include/features.h
main.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
main.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
main.o: /usr/include/xlocale.h ./custom.h ./main.h /usr/include/stdio.h
main.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
main.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
main.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
main.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
main.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
main.o: /usr/include/sys/types.h /usr/include/time.h
main.o: /usr/include/sys/select.h /usr/include/bits/select.h
main.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
main.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
main.o: /usr/include/alloca.h /usr/include/math.h
main.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
main.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
main.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
main.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
main.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
main.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
main.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
main.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
main.o: ../../../include/yalecad/message.h ./analog.h
main.o: ../../../include/yalecad/debug.h ../../../include/yalecad/cleanup.h
main.o: ../../../include/yalecad/file.h
makebins.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
makebins.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
makebins.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
makebins.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
makebins.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
makebins.o: /usr/include/libio.h /usr/include/_G_config.h
makebins.o: /usr/include/wchar.h
makebins.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
makebins.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
makebins.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
makebins.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
makebins.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
makebins.o: /usr/include/sys/types.h /usr/include/time.h
makebins.o: /usr/include/sys/select.h /usr/include/bits/select.h
makebins.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
makebins.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
makebins.o: /usr/include/alloca.h /usr/include/math.h
makebins.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
makebins.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
makebins.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
makebins.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
makebins.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
makebins.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
makebins.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
makebins.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
makebins.o: /usr/include/bits/posix2_lim.h
makebins.o: ../../../include/yalecad/okmalloc.h
makebins.o: ../../../include/yalecad/message.h ./analog.h
makebins.o: ../../../include/yalecad/debug.h
makesite.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
makesite.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
makesite.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
makesite.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
makesite.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
makesite.o: /usr/include/libio.h /usr/include/_G_config.h
makesite.o: /usr/include/wchar.h
makesite.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
makesite.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
makesite.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
makesite.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
makesite.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
makesite.o: /usr/include/sys/types.h /usr/include/time.h
makesite.o: /usr/include/sys/select.h /usr/include/bits/select.h
makesite.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
makesite.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
makesite.o: /usr/include/alloca.h /usr/include/math.h
makesite.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
makesite.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
makesite.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
makesite.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
makesite.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
makesite.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
makesite.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
makesite.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
makesite.o: /usr/include/bits/posix2_lim.h
makesite.o: ../../../include/yalecad/okmalloc.h
makesite.o: ../../../include/yalecad/message.h ./analog.h
makesite.o: ../../../include/yalecad/debug.h
mergecell.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
mergecell.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
mergecell.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
mergecell.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
mergecell.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
mergecell.o: /usr/include/libio.h /usr/include/_G_config.h
mergecell.o: /usr/include/wchar.h
mergecell.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
mergecell.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
mergecell.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
mergecell.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
mergecell.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
mergecell.o: /usr/include/sys/types.h /usr/include/time.h
mergecell.o: /usr/include/sys/select.h /usr/include/bits/select.h
mergecell.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
mergecell.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
mergecell.o: /usr/include/alloca.h /usr/include/math.h
mergecell.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
mergecell.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
mergecell.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
mergecell.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
mergecell.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
mergecell.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
mergecell.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
mergecell.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
mergecell.o: /usr/include/bits/posix2_lim.h
mergecell.o: ../../../include/yalecad/okmalloc.h
mergecell.o: ../../../include/yalecad/message.h ./analog.h
mergecell.o: ../../../include/yalecad/debug.h
neworient.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
neworient.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
neworient.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
neworient.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
neworient.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
neworient.o: /usr/include/libio.h /usr/include/_G_config.h
neworient.o: /usr/include/wchar.h
neworient.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
neworient.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
neworient.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
neworient.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
neworient.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
neworient.o: /usr/include/sys/types.h /usr/include/time.h
neworient.o: /usr/include/sys/select.h /usr/include/bits/select.h
neworient.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
neworient.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
neworient.o: /usr/include/alloca.h /usr/include/math.h
neworient.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
neworient.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
neworient.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
neworient.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
neworient.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
neworient.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
neworient.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
neworient.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
neworient.o: /usr/include/bits/posix2_lim.h
neworient.o: ../../../include/yalecad/okmalloc.h
neworient.o: ../../../include/yalecad/message.h ./analog.h
neworient.o: ../../../include/yalecad/debug.h
newtemp.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
newtemp.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
newtemp.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
newtemp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
newtemp.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
newtemp.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
newtemp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
newtemp.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
newtemp.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
newtemp.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
newtemp.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
newtemp.o: /usr/include/sys/types.h /usr/include/time.h
newtemp.o: /usr/include/sys/select.h /usr/include/bits/select.h
newtemp.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
newtemp.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
newtemp.o: /usr/include/alloca.h /usr/include/math.h
newtemp.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
newtemp.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
newtemp.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
newtemp.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
newtemp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
newtemp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
newtemp.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
newtemp.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
newtemp.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
newtemp.o: ../../../include/yalecad/message.h ./analog.h ./temp.h
newtemp.o: ../../../include/yalecad/debug.h
outgeo.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
outgeo.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
outgeo.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
outgeo.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
outgeo.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
outgeo.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
outgeo.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
outgeo.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
outgeo.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
outgeo.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
outgeo.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
outgeo.o: /usr/include/sys/types.h /usr/include/time.h
outgeo.o: /usr/include/sys/select.h /usr/include/bits/select.h
outgeo.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
outgeo.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
outgeo.o: /usr/include/alloca.h /usr/include/math.h
outgeo.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
outgeo.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
outgeo.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
outgeo.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
outgeo.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
outgeo.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
outgeo.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
outgeo.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
outgeo.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
outgeo.o: ../../../include/yalecad/message.h ./analog.h
outgeo.o: ../../../include/yalecad/debug.h ../../../include/yalecad/buster.h
outgeo.o: ../../../include/yalecad/file.h ../../../include/yalecad/relpos.h
outgeo.o: ./pads.h
outpin.o: /usr/include/string.h /usr/include/features.h
outpin.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
outpin.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
outpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
outpin.o: /usr/include/xlocale.h ./custom.h ./main.h /usr/include/stdio.h
outpin.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
outpin.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
outpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
outpin.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
outpin.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
outpin.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
outpin.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
outpin.o: /usr/include/sys/types.h /usr/include/time.h
outpin.o: /usr/include/sys/select.h /usr/include/bits/select.h
outpin.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
outpin.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
outpin.o: /usr/include/alloca.h /usr/include/math.h
outpin.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
outpin.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
outpin.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
outpin.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
outpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
outpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
outpin.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
outpin.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
outpin.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
outpin.o: ../../../include/yalecad/message.h ./analog.h ./initialize.h
outpin.o: ../../../include/yalecad/debug.h ../../../include/yalecad/file.h
outpin.o: ../../../include/yalecad/relpos.h ./pads.h
output.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
output.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
output.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
output.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
output.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
output.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
output.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
output.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
output.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
output.o: /usr/include/sys/types.h /usr/include/time.h
output.o: /usr/include/sys/select.h /usr/include/bits/select.h
output.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
output.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
output.o: /usr/include/alloca.h /usr/include/math.h
output.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
output.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
output.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
output.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
output.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
output.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
output.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
output.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
output.o: ../../../include/yalecad/message.h ./analog.h ./pads.h
output.o: ./initialize.h ../../../include/yalecad/buster.h
output.o: ../../../include/yalecad/debug.h ../../../include/yalecad/relpos.h
output.o: ../../../include/yalecad/file.h ../../../include/yalecad/string.h
overlap.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
overlap.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
overlap.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
overlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
overlap.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
overlap.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
overlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
overlap.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
overlap.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
overlap.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
overlap.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
overlap.o: /usr/include/sys/types.h /usr/include/time.h
overlap.o: /usr/include/sys/select.h /usr/include/bits/select.h
overlap.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
overlap.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
overlap.o: /usr/include/alloca.h /usr/include/math.h
overlap.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
overlap.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
overlap.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
overlap.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
overlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
overlap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
overlap.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
overlap.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
overlap.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
overlap.o: ../../../include/yalecad/message.h ./analog.h
overlap.o: ../../../include/yalecad/file.h ../../../include/yalecad/debug.h
partition.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
partition.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
partition.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
partition.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
partition.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
partition.o: /usr/include/libio.h /usr/include/_G_config.h
partition.o: /usr/include/wchar.h
partition.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
partition.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
partition.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
partition.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
partition.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
partition.o: /usr/include/sys/types.h /usr/include/time.h
partition.o: /usr/include/sys/select.h /usr/include/bits/select.h
partition.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
partition.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
partition.o: /usr/include/alloca.h /usr/include/math.h
partition.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
partition.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
partition.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
partition.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
partition.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
partition.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
partition.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
partition.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
partition.o: /usr/include/bits/posix2_lim.h
partition.o: ../../../include/yalecad/okmalloc.h
partition.o: ../../../include/yalecad/message.h ./analog.h ./partition.h
partition.o: ./pads.h ../../../include/yalecad/buster.h
partition.o: ../../../include/yalecad/file.h
partition.o: ../../../include/yalecad/relpos.h
partition.o: ../../../include/yalecad/string.h
partition.o: ../../../include/yalecad/debug.h
partition.o: ../../../include/yalecad/yreadpar.h
partition.o: ../../../include/yalecad/rbtree.h
paths.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
paths.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
paths.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
paths.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
paths.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
paths.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
paths.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
paths.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
paths.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
paths.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
paths.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
paths.o: /usr/include/sys/types.h /usr/include/time.h
paths.o: /usr/include/sys/select.h /usr/include/bits/select.h
paths.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
paths.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
paths.o: /usr/include/alloca.h /usr/include/math.h
paths.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
paths.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
paths.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
paths.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
paths.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
paths.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
paths.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
paths.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
paths.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
paths.o: ../../../include/yalecad/message.h ./analog.h
paths.o: ../../../include/yalecad/debug.h ../../../include/yalecad/file.h
paths.o: ../../../include/yalecad/stat.h
penalties.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
penalties.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
penalties.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
penalties.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
penalties.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
penalties.o: /usr/include/libio.h /usr/include/_G_config.h
penalties.o: /usr/include/wchar.h
penalties.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
penalties.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
penalties.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
penalties.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
penalties.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
penalties.o: /usr/include/sys/types.h /usr/include/time.h
penalties.o: /usr/include/sys/select.h /usr/include/bits/select.h
penalties.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
penalties.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
penalties.o: /usr/include/alloca.h /usr/include/math.h
penalties.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
penalties.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
penalties.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
penalties.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
penalties.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
penalties.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
penalties.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
penalties.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
penalties.o: /usr/include/bits/posix2_lim.h
penalties.o: ../../../include/yalecad/okmalloc.h
penalties.o: ../../../include/yalecad/message.h ./analog.h ./temp.h
penalties.o: ../../../include/yalecad/debug.h ../../../include/yalecad/file.h
perimeter.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
perimeter.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
perimeter.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
perimeter.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
perimeter.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
perimeter.o: /usr/include/libio.h /usr/include/_G_config.h
perimeter.o: /usr/include/wchar.h
perimeter.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
perimeter.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
perimeter.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
perimeter.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
perimeter.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
perimeter.o: /usr/include/sys/types.h /usr/include/time.h
perimeter.o: /usr/include/sys/select.h /usr/include/bits/select.h
perimeter.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
perimeter.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
perimeter.o: /usr/include/alloca.h /usr/include/math.h
perimeter.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
perimeter.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
perimeter.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
perimeter.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
perimeter.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
perimeter.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
perimeter.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
perimeter.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
perimeter.o: /usr/include/bits/posix2_lim.h
perimeter.o: ../../../include/yalecad/okmalloc.h
perimeter.o: ../../../include/yalecad/message.h ./analog.h
perimeter.o: ../../../include/yalecad/buster.h
perimeter.o: ../../../include/yalecad/debug.h
placepads.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
placepads.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
placepads.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
placepads.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
placepads.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
placepads.o: /usr/include/libio.h /usr/include/_G_config.h
placepads.o: /usr/include/wchar.h
placepads.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
placepads.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
placepads.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
placepads.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
placepads.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
placepads.o: /usr/include/sys/types.h /usr/include/time.h
placepads.o: /usr/include/sys/select.h /usr/include/bits/select.h
placepads.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
placepads.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
placepads.o: /usr/include/alloca.h /usr/include/math.h
placepads.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
placepads.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
placepads.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
placepads.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
placepads.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
placepads.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
placepads.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
placepads.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
placepads.o: /usr/include/bits/posix2_lim.h
placepads.o: ../../../include/yalecad/okmalloc.h
placepads.o: ../../../include/yalecad/message.h ./analog.h ./pads.h ./dens.h
placepads.o: ../../../include/yalecad/debug.h ../../../include/yalecad/file.h
placepads.o: ../../../include/yalecad/string.h ../../../include/yalecad/set.h
placepin.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
placepin.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
placepin.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
placepin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
placepin.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
placepin.o: /usr/include/libio.h /usr/include/_G_config.h
placepin.o: /usr/include/wchar.h
placepin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
placepin.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
placepin.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
placepin.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
placepin.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
placepin.o: /usr/include/sys/types.h /usr/include/time.h
placepin.o: /usr/include/sys/select.h /usr/include/bits/select.h
placepin.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
placepin.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
placepin.o: /usr/include/alloca.h /usr/include/math.h
placepin.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
placepin.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
placepin.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
placepin.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
placepin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
placepin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
placepin.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
placepin.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
placepin.o: /usr/include/bits/posix2_lim.h
placepin.o: ../../../include/yalecad/okmalloc.h
placepin.o: ../../../include/yalecad/message.h ./analog.h
placepin.o: ../../../include/yalecad/debug.h ./initialize.h
placepin.o: ../../../include/yalecad/relpos.h ./dens.h
prboard.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
prboard.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
prboard.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
prboard.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
prboard.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
prboard.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
prboard.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
prboard.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
prboard.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
prboard.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
prboard.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
prboard.o: /usr/include/sys/types.h /usr/include/time.h
prboard.o: /usr/include/sys/select.h /usr/include/bits/select.h
prboard.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
prboard.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
prboard.o: /usr/include/alloca.h /usr/include/math.h
prboard.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
prboard.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
prboard.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
prboard.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
prboard.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
prboard.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
prboard.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
prboard.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
prboard.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
prboard.o: ../../../include/yalecad/message.h ./analog.h
prboard.o: ../../../include/yalecad/debug.h
readcells.o: /usr/include/string.h /usr/include/features.h
readcells.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
readcells.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
readcells.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
readcells.o: /usr/include/xlocale.h ../../../include/yalecad/string.h
readcells.o: ../../../include/yalecad/base.h /usr/include/stdio.h
readcells.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
readcells.o: /usr/include/libio.h /usr/include/_G_config.h
readcells.o: /usr/include/wchar.h
readcells.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
readcells.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
readcells.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
readcells.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
readcells.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
readcells.o: /usr/include/sys/types.h /usr/include/time.h
readcells.o: /usr/include/sys/select.h /usr/include/bits/select.h
readcells.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
readcells.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
readcells.o: /usr/include/alloca.h
readcells.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
readcells.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
readcells.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
readcells.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
readcells.o: /usr/include/bits/posix2_lim.h
readcells.o: ../../../include/yalecad/okmalloc.h ./custom.h ./main.h
readcells.o: /usr/include/math.h /usr/include/bits/huge_val.h
readcells.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
readcells.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
readcells.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
readcells.o: ../../../include/yalecad/message.h ./analog.h ./initialize.h
readcells.o: ./readcells.h readcells_l.h
readnets.o: /usr/include/string.h /usr/include/features.h
readnets.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
readnets.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
readnets.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
readnets.o: /usr/include/xlocale.h ../../../include/yalecad/base.h
readnets.o: /usr/include/stdio.h /usr/include/bits/types.h
readnets.o: /usr/include/bits/typesizes.h /usr/include/libio.h
readnets.o: /usr/include/_G_config.h /usr/include/wchar.h
readnets.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
readnets.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
readnets.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
readnets.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
readnets.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
readnets.o: /usr/include/sys/types.h /usr/include/time.h
readnets.o: /usr/include/sys/select.h /usr/include/bits/select.h
readnets.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
readnets.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
readnets.o: /usr/include/alloca.h
readnets.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
readnets.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
readnets.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
readnets.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
readnets.o: /usr/include/bits/posix2_lim.h
readnets.o: ../../../include/yalecad/okmalloc.h
readnets.o: ../../../include/yalecad/message.h
readnets.o: ../../../include/yalecad/string.h ./readnets.h ./analog.h
readnets.o: readnets_l.h
readpar.o: /usr/include/string.h /usr/include/features.h
readpar.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
readpar.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
readpar.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
readpar.o: /usr/include/xlocale.h ./custom.h ./main.h /usr/include/stdio.h
readpar.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
readpar.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
readpar.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
readpar.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
readpar.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
readpar.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
readpar.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
readpar.o: /usr/include/sys/types.h /usr/include/time.h
readpar.o: /usr/include/sys/select.h /usr/include/bits/select.h
readpar.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
readpar.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
readpar.o: /usr/include/alloca.h /usr/include/math.h
readpar.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
readpar.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
readpar.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
readpar.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
readpar.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
readpar.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
readpar.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
readpar.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
readpar.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
readpar.o: ../../../include/yalecad/message.h ./analog.h
readpar.o: ../../../include/yalecad/debug.h ../../../include/yalecad/file.h
readpar.o: ../../../include/yalecad/string.h
readpar.o: ../../../include/yalecad/yreadpar.h
readpar.o: ../../../include/yalecad/rbtree.h
reconfig.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
reconfig.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
reconfig.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
reconfig.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
reconfig.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
reconfig.o: /usr/include/libio.h /usr/include/_G_config.h
reconfig.o: /usr/include/wchar.h
reconfig.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
reconfig.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
reconfig.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
reconfig.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
reconfig.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
reconfig.o: /usr/include/sys/types.h /usr/include/time.h
reconfig.o: /usr/include/sys/select.h /usr/include/bits/select.h
reconfig.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
reconfig.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
reconfig.o: /usr/include/alloca.h /usr/include/math.h
reconfig.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
reconfig.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
reconfig.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
reconfig.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
reconfig.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
reconfig.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
reconfig.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
reconfig.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
reconfig.o: /usr/include/bits/posix2_lim.h
reconfig.o: ../../../include/yalecad/okmalloc.h
reconfig.o: ../../../include/yalecad/message.h ./analog.h
reconfig.o: ../../../include/yalecad/debug.h
rmain.o: ../../../include/yalecad/base.h /usr/include/stdio.h
rmain.o: /usr/include/features.h /usr/include/sys/cdefs.h
rmain.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
rmain.o: /usr/include/gnu/stubs-64.h
rmain.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
rmain.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
rmain.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
rmain.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
rmain.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
rmain.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
rmain.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
rmain.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
rmain.o: /usr/include/sys/types.h /usr/include/time.h
rmain.o: /usr/include/sys/select.h /usr/include/bits/select.h
rmain.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
rmain.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
rmain.o: /usr/include/alloca.h
rmain.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
rmain.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
rmain.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
rmain.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
rmain.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
rmain.o: ../../../include/yalecad/debug.h ../../../include/yalecad/message.h
rmain.o: ../../../include/yalecad/file.h ../../../include/yalecad/string.h
rmain.o: ./custom.h ./main.h /usr/include/math.h /usr/include/bits/huge_val.h
rmain.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
rmain.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
rmain.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h ./analog.h
savewolf.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
savewolf.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
savewolf.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
savewolf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
savewolf.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
savewolf.o: /usr/include/libio.h /usr/include/_G_config.h
savewolf.o: /usr/include/wchar.h
savewolf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
savewolf.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
savewolf.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
savewolf.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
savewolf.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
savewolf.o: /usr/include/sys/types.h /usr/include/time.h
savewolf.o: /usr/include/sys/select.h /usr/include/bits/select.h
savewolf.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
savewolf.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
savewolf.o: /usr/include/alloca.h /usr/include/math.h
savewolf.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
savewolf.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
savewolf.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
savewolf.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
savewolf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
savewolf.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
savewolf.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
savewolf.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
savewolf.o: /usr/include/bits/posix2_lim.h
savewolf.o: ../../../include/yalecad/okmalloc.h
savewolf.o: ../../../include/yalecad/message.h ./analog.h ./temp.h
savewolf.o: ../../../include/yalecad/debug.h ../../../include/yalecad/file.h
scrapnet.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
scrapnet.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
scrapnet.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
scrapnet.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
scrapnet.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
scrapnet.o: /usr/include/libio.h /usr/include/_G_config.h
scrapnet.o: /usr/include/wchar.h
scrapnet.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
scrapnet.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
scrapnet.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
scrapnet.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
scrapnet.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
scrapnet.o: /usr/include/sys/types.h /usr/include/time.h
scrapnet.o: /usr/include/sys/select.h /usr/include/bits/select.h
scrapnet.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
scrapnet.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
scrapnet.o: /usr/include/alloca.h /usr/include/math.h
scrapnet.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
scrapnet.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
scrapnet.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
scrapnet.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
scrapnet.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
scrapnet.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
scrapnet.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
scrapnet.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
scrapnet.o: /usr/include/bits/posix2_lim.h
scrapnet.o: ../../../include/yalecad/okmalloc.h
scrapnet.o: ../../../include/yalecad/message.h ./analog.h
scrapnet.o: ../../../include/yalecad/debug.h
selectpin.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
selectpin.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
selectpin.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
selectpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
selectpin.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
selectpin.o: /usr/include/libio.h /usr/include/_G_config.h
selectpin.o: /usr/include/wchar.h
selectpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
selectpin.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
selectpin.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
selectpin.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
selectpin.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
selectpin.o: /usr/include/sys/types.h /usr/include/time.h
selectpin.o: /usr/include/sys/select.h /usr/include/bits/select.h
selectpin.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
selectpin.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
selectpin.o: /usr/include/alloca.h /usr/include/math.h
selectpin.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
selectpin.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
selectpin.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
selectpin.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
selectpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
selectpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
selectpin.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
selectpin.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
selectpin.o: /usr/include/bits/posix2_lim.h
selectpin.o: ../../../include/yalecad/okmalloc.h
selectpin.o: ../../../include/yalecad/message.h ./analog.h
selectpin.o: ../../../include/yalecad/debug.h
setpwates.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
setpwates.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
setpwates.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
setpwates.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
setpwates.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
setpwates.o: /usr/include/libio.h /usr/include/_G_config.h
setpwates.o: /usr/include/wchar.h
setpwates.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
setpwates.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
setpwates.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
setpwates.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
setpwates.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
setpwates.o: /usr/include/sys/types.h /usr/include/time.h
setpwates.o: /usr/include/sys/select.h /usr/include/bits/select.h
setpwates.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
setpwates.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
setpwates.o: /usr/include/alloca.h /usr/include/math.h
setpwates.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
setpwates.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
setpwates.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
setpwates.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
setpwates.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
setpwates.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
setpwates.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
setpwates.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
setpwates.o: /usr/include/bits/posix2_lim.h
setpwates.o: ../../../include/yalecad/okmalloc.h
setpwates.o: ../../../include/yalecad/message.h ./analog.h
setpwates.o: ../../../include/yalecad/debug.h
sortpad.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
sortpad.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
sortpad.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
sortpad.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
sortpad.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
sortpad.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
sortpad.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
sortpad.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
sortpad.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
sortpad.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
sortpad.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
sortpad.o: /usr/include/sys/types.h /usr/include/time.h
sortpad.o: /usr/include/sys/select.h /usr/include/bits/select.h
sortpad.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
sortpad.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
sortpad.o: /usr/include/alloca.h /usr/include/math.h
sortpad.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
sortpad.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
sortpad.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
sortpad.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
sortpad.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
sortpad.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
sortpad.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
sortpad.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
sortpad.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
sortpad.o: ../../../include/yalecad/message.h ./analog.h ./pads.h
sortpad.o: ../../../include/yalecad/debug.h
sortpin.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
sortpin.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
sortpin.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
sortpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
sortpin.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
sortpin.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
sortpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
sortpin.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
sortpin.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
sortpin.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
sortpin.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
sortpin.o: /usr/include/sys/types.h /usr/include/time.h
sortpin.o: /usr/include/sys/select.h /usr/include/bits/select.h
sortpin.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
sortpin.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
sortpin.o: /usr/include/alloca.h /usr/include/math.h
sortpin.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
sortpin.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
sortpin.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
sortpin.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
sortpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
sortpin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
sortpin.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
sortpin.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
sortpin.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
sortpin.o: ../../../include/yalecad/message.h ./analog.h
sortpin.o: ../../../include/yalecad/debug.h
twstats.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
twstats.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
twstats.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
twstats.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
twstats.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
twstats.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
twstats.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
twstats.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
twstats.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
twstats.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
twstats.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
twstats.o: /usr/include/sys/types.h /usr/include/time.h
twstats.o: /usr/include/sys/select.h /usr/include/bits/select.h
twstats.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
twstats.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
twstats.o: /usr/include/alloca.h /usr/include/math.h
twstats.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
twstats.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
twstats.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
twstats.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
twstats.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
twstats.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
twstats.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
twstats.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
twstats.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
twstats.o: ../../../include/yalecad/message.h ./analog.h
twstats.o: ../../../include/yalecad/debug.h
uaspect.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
uaspect.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
uaspect.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
uaspect.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
uaspect.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
uaspect.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
uaspect.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
uaspect.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
uaspect.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
uaspect.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
uaspect.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
uaspect.o: /usr/include/sys/types.h /usr/include/time.h
uaspect.o: /usr/include/sys/select.h /usr/include/bits/select.h
uaspect.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
uaspect.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
uaspect.o: /usr/include/alloca.h /usr/include/math.h
uaspect.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
uaspect.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
uaspect.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
uaspect.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
uaspect.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
uaspect.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
uaspect.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
uaspect.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
uaspect.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
uaspect.o: ../../../include/yalecad/message.h ./analog.h ./initialize.h
uaspect.o: ../../../include/yalecad/debug.h ../../../include/yalecad/relpos.h
uinst.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
uinst.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
uinst.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
uinst.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
uinst.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
uinst.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
uinst.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
uinst.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
uinst.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
uinst.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
uinst.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
uinst.o: /usr/include/sys/types.h /usr/include/time.h
uinst.o: /usr/include/sys/select.h /usr/include/bits/select.h
uinst.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
uinst.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
uinst.o: /usr/include/alloca.h /usr/include/math.h
uinst.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
uinst.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
uinst.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
uinst.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
uinst.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
uinst.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
uinst.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
uinst.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
uinst.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
uinst.o: ../../../include/yalecad/message.h ./analog.h ./initialize.h
uinst.o: ../../../include/yalecad/debug.h ../../../include/yalecad/relpos.h
uloop.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
uloop.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
uloop.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
uloop.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
uloop.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
uloop.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
uloop.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
uloop.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
uloop.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
uloop.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
uloop.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
uloop.o: /usr/include/sys/types.h /usr/include/time.h
uloop.o: /usr/include/sys/select.h /usr/include/bits/select.h
uloop.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
uloop.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
uloop.o: /usr/include/alloca.h /usr/include/math.h
uloop.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
uloop.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
uloop.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
uloop.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
uloop.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
uloop.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
uloop.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
uloop.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
uloop.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
uloop.o: ../../../include/yalecad/message.h ./analog.h ./temp.h
uloop.o: ../../../include/yalecad/debug.h ../../../include/yalecad/file.h
unbust.o: ../../../include/yalecad/base.h /usr/include/stdio.h
unbust.o: /usr/include/features.h /usr/include/sys/cdefs.h
unbust.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
unbust.o: /usr/include/gnu/stubs-64.h
unbust.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
unbust.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
unbust.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
unbust.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
unbust.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
unbust.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
unbust.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
unbust.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
unbust.o: /usr/include/sys/types.h /usr/include/time.h
unbust.o: /usr/include/sys/select.h /usr/include/bits/select.h
unbust.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
unbust.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
unbust.o: /usr/include/alloca.h
unbust.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
unbust.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
unbust.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
unbust.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
unbust.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
unbust.o: ../../../include/yalecad/buster.h ../../../include/yalecad/debug.h
unbust.o: ../../../include/yalecad/message.h
unet.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
unet.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
unet.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
unet.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
unet.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
unet.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
unet.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
unet.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
unet.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
unet.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
unet.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
unet.o: /usr/include/sys/types.h /usr/include/time.h
unet.o: /usr/include/sys/select.h /usr/include/bits/select.h
unet.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
unet.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
unet.o: /usr/include/alloca.h /usr/include/math.h
unet.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
unet.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
unet.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
unet.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
unet.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
unet.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
unet.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
unet.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
unet.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
unet.o: ../../../include/yalecad/message.h ./analog.h
unet.o: ../../../include/yalecad/debug.h
upin.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
upin.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
upin.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
upin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
upin.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
upin.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
upin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
upin.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
upin.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
upin.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
upin.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
upin.o: /usr/include/sys/types.h /usr/include/time.h
upin.o: /usr/include/sys/select.h /usr/include/bits/select.h
upin.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
upin.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
upin.o: /usr/include/alloca.h /usr/include/math.h
upin.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
upin.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
upin.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
upin.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
upin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
upin.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
upin.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
upin.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
upin.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
upin.o: ../../../include/yalecad/message.h ./analog.h
upin.o: ../../../include/yalecad/debug.h ../../../include/yalecad/relpos.h
upinswap.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
upinswap.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
upinswap.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
upinswap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
upinswap.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
upinswap.o: /usr/include/libio.h /usr/include/_G_config.h
upinswap.o: /usr/include/wchar.h
upinswap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
upinswap.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
upinswap.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
upinswap.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
upinswap.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
upinswap.o: /usr/include/sys/types.h /usr/include/time.h
upinswap.o: /usr/include/sys/select.h /usr/include/bits/select.h
upinswap.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
upinswap.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
upinswap.o: /usr/include/alloca.h /usr/include/math.h
upinswap.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
upinswap.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
upinswap.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
upinswap.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
upinswap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
upinswap.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
upinswap.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
upinswap.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
upinswap.o: /usr/include/bits/posix2_lim.h
upinswap.o: ../../../include/yalecad/okmalloc.h
upinswap.o: ../../../include/yalecad/message.h ./analog.h ./initialize.h
upinswap.o: ../../../include/yalecad/debug.h
upinswap.o: ../../../include/yalecad/relpos.h
usite1.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
usite1.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
usite1.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
usite1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
usite1.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
usite1.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
usite1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
usite1.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
usite1.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
usite1.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
usite1.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
usite1.o: /usr/include/sys/types.h /usr/include/time.h
usite1.o: /usr/include/sys/select.h /usr/include/bits/select.h
usite1.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
usite1.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
usite1.o: /usr/include/alloca.h /usr/include/math.h
usite1.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
usite1.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
usite1.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
usite1.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
usite1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
usite1.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
usite1.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
usite1.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
usite1.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
usite1.o: ../../../include/yalecad/message.h ./analog.h
usite1.o: ../../../include/yalecad/debug.h
usite2.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
usite2.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
usite2.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
usite2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
usite2.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
usite2.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
usite2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
usite2.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
usite2.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
usite2.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
usite2.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
usite2.o: /usr/include/sys/types.h /usr/include/time.h
usite2.o: /usr/include/sys/select.h /usr/include/bits/select.h
usite2.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
usite2.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
usite2.o: /usr/include/alloca.h /usr/include/math.h
usite2.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
usite2.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
usite2.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
usite2.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
usite2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
usite2.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
usite2.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
usite2.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
usite2.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
usite2.o: ../../../include/yalecad/message.h ./analog.h
usite2.o: ../../../include/yalecad/debug.h
usoftmove.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
usoftmove.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
usoftmove.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
usoftmove.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
usoftmove.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
usoftmove.o: /usr/include/libio.h /usr/include/_G_config.h
usoftmove.o: /usr/include/wchar.h
usoftmove.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
usoftmove.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
usoftmove.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
usoftmove.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
usoftmove.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
usoftmove.o: /usr/include/sys/types.h /usr/include/time.h
usoftmove.o: /usr/include/sys/select.h /usr/include/bits/select.h
usoftmove.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
usoftmove.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
usoftmove.o: /usr/include/alloca.h /usr/include/math.h
usoftmove.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
usoftmove.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
usoftmove.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
usoftmove.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
usoftmove.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
usoftmove.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
usoftmove.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
usoftmove.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
usoftmove.o: /usr/include/bits/posix2_lim.h
usoftmove.o: ../../../include/yalecad/okmalloc.h
usoftmove.o: ../../../include/yalecad/message.h ./analog.h
usoftmove.o: ../../../include/yalecad/relpos.h
usoftmove.o: ../../../include/yalecad/debug.h
utemp.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
utemp.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
utemp.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
utemp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
utemp.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
utemp.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
utemp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
utemp.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
utemp.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
utemp.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
utemp.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
utemp.o: /usr/include/sys/types.h /usr/include/time.h
utemp.o: /usr/include/sys/select.h /usr/include/bits/select.h
utemp.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
utemp.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
utemp.o: /usr/include/alloca.h /usr/include/math.h
utemp.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
utemp.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
utemp.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
utemp.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
utemp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
utemp.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
utemp.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
utemp.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
utemp.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
utemp.o: ../../../include/yalecad/message.h ./analog.h ./temp.h
utemp.o: ../../../include/yalecad/debug.h
watesides.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
watesides.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
watesides.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
watesides.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
watesides.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
watesides.o: /usr/include/libio.h /usr/include/_G_config.h
watesides.o: /usr/include/wchar.h
watesides.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
watesides.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
watesides.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
watesides.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
watesides.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
watesides.o: /usr/include/sys/types.h /usr/include/time.h
watesides.o: /usr/include/sys/select.h /usr/include/bits/select.h
watesides.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
watesides.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
watesides.o: /usr/include/alloca.h /usr/include/math.h
watesides.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
watesides.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
watesides.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
watesides.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
watesides.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
watesides.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
watesides.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
watesides.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
watesides.o: /usr/include/bits/posix2_lim.h
watesides.o: ../../../include/yalecad/okmalloc.h
watesides.o: ../../../include/yalecad/message.h ./analog.h
watesides.o: ../../../include/yalecad/debug.h
window.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
window.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
window.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
window.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
window.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
window.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
window.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
window.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
window.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
window.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
window.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
window.o: /usr/include/sys/types.h /usr/include/time.h
window.o: /usr/include/sys/select.h /usr/include/bits/select.h
window.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
window.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
window.o: /usr/include/alloca.h /usr/include/math.h
window.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
window.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
window.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
window.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
window.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
window.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
window.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
window.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
window.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
window.o: ../../../include/yalecad/message.h ./analog.h ./temp.h
window.o: ../../../include/yalecad/debug.h
wirecosts.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
wirecosts.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
wirecosts.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
wirecosts.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
wirecosts.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
wirecosts.o: /usr/include/libio.h /usr/include/_G_config.h
wirecosts.o: /usr/include/wchar.h
wirecosts.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
wirecosts.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
wirecosts.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
wirecosts.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
wirecosts.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
wirecosts.o: /usr/include/sys/types.h /usr/include/time.h
wirecosts.o: /usr/include/sys/select.h /usr/include/bits/select.h
wirecosts.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
wirecosts.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
wirecosts.o: /usr/include/alloca.h /usr/include/math.h
wirecosts.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
wirecosts.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
wirecosts.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
wirecosts.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
wirecosts.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
wirecosts.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
wirecosts.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
wirecosts.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
wirecosts.o: /usr/include/bits/posix2_lim.h
wirecosts.o: ../../../include/yalecad/okmalloc.h
wirecosts.o: ../../../include/yalecad/message.h ./analog.h
wirecosts.o: ../../../include/yalecad/debug.h
wireest.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
wireest.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
wireest.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
wireest.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
wireest.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
wireest.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
wireest.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
wireest.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
wireest.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
wireest.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
wireest.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
wireest.o: /usr/include/sys/types.h /usr/include/time.h
wireest.o: /usr/include/sys/select.h /usr/include/bits/select.h
wireest.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
wireest.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
wireest.o: /usr/include/alloca.h /usr/include/math.h
wireest.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
wireest.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
wireest.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
wireest.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
wireest.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
wireest.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
wireest.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
wireest.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
wireest.o: /usr/include/bits/posix2_lim.h ../../../include/yalecad/okmalloc.h
wireest.o: ../../../include/yalecad/message.h ./analog.h
wireest.o: ../../../include/yalecad/debug.h
wireratio.o: ./custom.h ./main.h /usr/include/stdio.h /usr/include/features.h
wireratio.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
wireratio.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
wireratio.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stddef.h
wireratio.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
wireratio.o: /usr/include/libio.h /usr/include/_G_config.h
wireratio.o: /usr/include/wchar.h
wireratio.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/stdarg.h
wireratio.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
wireratio.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
wireratio.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
wireratio.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
wireratio.o: /usr/include/sys/types.h /usr/include/time.h
wireratio.o: /usr/include/sys/select.h /usr/include/bits/select.h
wireratio.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
wireratio.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
wireratio.o: /usr/include/alloca.h /usr/include/math.h
wireratio.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
wireratio.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
wireratio.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
wireratio.o: /usr/include/bits/mathcalls.h ../../../include/yalecad/base.h
wireratio.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/limits.h
wireratio.o: /usr/lib/gcc/x86_64-redhat-linux/4.6.3/include/syslimits.h
wireratio.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
wireratio.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
wireratio.o: /usr/include/bits/posix2_lim.h
wireratio.o: ../../../include/yalecad/okmalloc.h
wireratio.o: ../../../include/yalecad/message.h ./analog.h ./dens.h
wireratio.o: ../../../include/yalecad/debug.h ../../../include/yalecad/file.h
wireratio.o: ../../../include/yalecad/linalg.h
