/************************************************************
 *
 *  Program: mcc
 *  By:      Brent Callaghan
 *  Date:    July 1984
 *
 *  Function: Runs the C compiler, passing all command line 
 *	    arguments. If the compiler returns a non-zero
 *	    result, the syntax errors are merged with the
 *	    source and the user's editor is invoked. The
 *	    cursor is placed on the first line in error.
 *	    Exit from the editor re-invokes the C compiler.
 *	    This loop continues until the C compiler exits
 *	    to the linker, the source file is not changed,
 *	    or the user kills mcc with a keyboard interrupt
 *	    after exiting the editor.
 *
 *	    Environment variables EDITOR and COMPILER may
 *	    be used to set an alternative editor or compiler.
 *
 *		      ~~~  PUBLIC DOMAIN  ~~~
 *	    
 *	   This program may be freely used and distributed
 *	   but I would rather you did not sell it.
 *
 *         Sat Nov 23 21:34:43 EST 1991 - updated for gcc.
 *
 ************************************************************
 */

 /*------------------------------------------------------------
   If mcc does not work, the a replacement for the routine
   errinfo can be written.

   To add support for a machine, create a conditional compile
   for the routine errinfo().

   #ifdef machine                  /* distinguishing symbol  *\
   #define MCC_ERRINFO             /* do not compile default *\
     errinfo() {
       actions;                    /* parse cc error info    *\
     }
   #endif machine 

   WEIER 9/90
   -----------------------------------------------------------*/

/* #define DEBUG */

#include <stdio.h>
#include <ctype.h>
#include <signal.h>

#ifdef BSD
#include <strings.h>
#define strchr  index
#define strrchr rindex
#endif

/* The following Y routines will only be used on apollo or mips machines */

#define STRINGEQ   0
extern char **Ystrparser(/* char *, char *, int * */) ;

extern char * getenv();
static char *errname  = "/tmp/errXXXXXX";
static char mergename[128];
static char *editor, *edname, *compiler;
static int pid, viedit, firsterr, emacsedit;
static int chksum1, chksum2;

/*
 * Form 16 bit checksum of source line
 */
int 
checksum(sum, line)
    register int sum;
    register char *line;
{
    while (*line++) {
	if (sum & 1)
	    sum = (sum >> 1) + 0x8000;
	else
	    sum >>= 1;

	sum = (sum + *line) & 0xFFFF;
    }
    return sum;
}

int 
runc(argv, errname)
    char **argv;
    char *errname;
{
    int status;

    switch (pid = fork()) {
    case 0:			/* child */
	(void) freopen(errname, "w", stderr);
	execvp(compiler, argv);
	perror("Couldn't exec compiler");
	exit (1);

    case -1:			/* Error */
	perror("Couldn't fork compiler");
	exit (1);

    default:			/* Parent */
	while (wait(&status) != pid);	/* wait for compile to finish */
	break;
    }
    return ((status >> 8) & 0xFF);
}

void 
listerrs(errname)
    char *errname;
{
    FILE *errfile;
    char errline[BUFSIZ + 1];

    if ((errfile = fopen(errname, "r")) == NULL)
	return;
    while (fgets(errline, BUFSIZ, errfile) != NULL)
	(void) fputs(errline, stderr);
    (void) fclose(errfile);
    (void) unlink(errname);
}

void 
edit(mergename)
    char *mergename;
{
    int status;
    char sfirsterr[6];

    switch (pid = fork()) {
    case 0:			/* Child */
	if (viedit) {
	    (void) sprintf(sfirsterr, "+%d", firsterr);
	    (void) printf(" vi %s %s\n", sfirsterr, mergename);
	    execlp(editor, "vi", sfirsterr, mergename, NULL);
	} else if( emacsedit ){
	    (void) sprintf(sfirsterr, "+%d", firsterr);
	    (void) printf(" emacs %s %s\n", sfirsterr, mergename);
	    execlp(editor, "emacs", sfirsterr, mergename, NULL);
	} else {
	    (void) printf(" %s %s\n", edname, mergename);
	    execlp(editor, edname, mergename, NULL);
	}
	perror("Couldn't exec editor");
	listerrs(errname);
	exit (1);

    case -1:			/* Error */
	perror("Couldn't fork editor");
	listerrs(errname);
	exit (1);

    default:			/* Parent */
	while (wait(&status) != pid);	/* wait for editor to finish */
	break;
    }
}

#ifdef apollo
                                                      /* apollo version */
#define MCC_ERRINFO

int errinfo(errfile, srcname, errmsg)
    FILE *errfile;
    char *srcname, *errmsg;
{
    static char errline[BUFSIZ + 1];
    char *bufferptr ;
    char **tokens ;
    char **Ystrparser() ;
    int  numtokens ;
    int  i ;

    while( bufferptr=fgets(errline,BUFSIZ, errfile )){
	/* parse file */
	if( *bufferptr == '*' ){
	    break ;
	}
    }

    /* first get msg */
#   ifdef DEBUG 
    fprintf( stderr, "%s\n", bufferptr ) ;
#   endif

    tokens = Ystrparser( bufferptr, "\]\t\n", &numtokens );
    if(!(numtokens)){
	return 0;
    }

#   ifdef DEBUG 
    fprintf( stderr, "numtokens =%d\n", numtokens ) ;
    for( i = 0 ; i < numtokens; i++ ){
	fprintf( stderr, "token[%d]:%s\n", i, tokens[i] ) ;
    }
#   endif

    (void) strcpy(errmsg, tokens[1] );

    /* next get file */
    tokens = Ystrparser( tokens[0], " \"\t\n", &numtokens );

#   ifdef DEBUG 
    for( i = 0 ; i < numtokens; i++ ){
	fprintf( stderr, "token[%d]:%s\n", i, tokens[i] ) ;
    }
#   endif

    /* save file */
    (void) strcpy(srcname, tokens[4] );

    /* return line number */
    return atoi(tokens[2]);
}

#endif                        /* end apollo version */

#ifdef mips
                              /* mips version  (for Ultrix DECstation 5000/200) */
#define MCC_ERRINFO

int errinfo(errfile, srcname, errmsg)
    FILE *errfile;
    char *srcname, *errmsg;
{
    static char errline[BUFSIZ + 1];
    char *bufferptr ;
    char **tokens ;
    char **Ystrparser() ;
    int  numtokens ;
    int  i ;

    /* first get msg */

   /* if 4 tokens are not found , parsing below is bogus */
   /* strip out extra messages                           */

    do {
      bufferptr=fgets(errline,BUFSIZ, errfile);
      
      if( !bufferptr ){
	return 0;            /* end of file */
      }
      
#   ifdef DEBUG 
      fprintf( stderr, "bufferptr=%s\n", bufferptr ) ;
#   endif
      
      tokens = Ystrparser( bufferptr, ":\t\n", &numtokens );
    } while ( numtokens < 4 || strcmp( tokens[0], "ccom") != STRINGEQ );
    
#   ifdef DEBUG 
    fprintf( stderr, "numtokens =%d\n", numtokens ) ;
    for( i = 0 ; i < numtokens; i++ ){
      fprintf( stderr, "token[%d]:%s\n", i, tokens[i] ) ;
    }
#   endif
    
    (void) sprintf(errmsg, "%s %s", tokens[1], tokens[3] );

    /* next get file */
    tokens = Ystrparser( tokens[2], ", \t\n", &numtokens );

#   ifdef DEBUG 
    for( i = 0 ; i < numtokens; i++ ){
	fprintf( stderr, "token[%d]:%s\n", i, tokens[i] ) ;
    }
#   endif

    /* save file */
    (void) strcpy(srcname, tokens[0] );

    /* return line number */
    return atoi(tokens[2]);
}

#endif mips                                /* end ifdef mips */

#ifndef MCC_ERRINFO

/* the routine errinfo() has not been defined yet */
/* use this as the standard C compiler output     */

int errinfo(errfile, srcname, errmsg)
    FILE *errfile;
    char *srcname, *errmsg;
{
    static char errline[BUFSIZ + 1];
    char slineno[8];
    char *p1, *p2;
    char *strchr() ;

    if (fgets(errline, BUFSIZ, errfile) == NULL)
	return 0;

    errline[strlen(errline) - 1] = '\0';	/* trim newline */
    p1 = errline;

    /* Get source file id */

    if (*p1 == '"')		/* cc  msg */
	p2 = strchr(++p1, '"');
    else			/* cpp msg */
	p2 = strchr(p1, ':');
    if (p2 == NULL || p1 == p2)
	return 0;
    *p2 = '\0';
    (void) strcpy(srcname, p1);

    /* Get source line number */

    for (p1 = p2 + 1 ; *p1 ; p1++)
	if (isdigit(*p1)) break;
    if (*p1 == '\0')
	return 0;
    p2 = strchr(p1, ':');
    if (p2 == NULL)
	return 0;
    *p2 = '\0';
    (void) strcpy(slineno, p1);

    /* The rest is the error message */

    (void) strcpy(errmsg, p2 + 1);

    return atoi(slineno);
}

#endif ERRINFO

/* ------------------ This version works with GCC -------------------- */
int gnu_errinfo(errfile, srcname, errmsg)
    FILE *errfile;
    char *srcname, *errmsg;
{
    static char errline[BUFSIZ + 1];
    char *bufferptr ;
    char **tokens ;
    char **Ystrparser() ;
    int  numtokens ;
    int  i, j, len ;
    int  line_no ;
    char *line_number ;

    do {
      bufferptr=fgets(errline,BUFSIZ, errfile);
      
      if( !bufferptr ){
	return 0;            /* end of file */
      }
      
#   ifdef DEBUG 
      fprintf( stderr, "bufferptr=%s\n", bufferptr ) ;
#   endif
      
      tokens = Ystrparser( bufferptr, " \t\n", &numtokens );
    } while ( strcmp( tokens[0], "In") == STRINGEQ );

    if(!(numtokens)){
	return 0;
    }

#   ifdef DEBUG 
    fprintf( stderr, "numtokens =%d\n", numtokens ) ;
    for( i = 0 ; i < numtokens; i++ ){
	fprintf( stderr, "token[%d]:%s\n", i, tokens[i] ) ;
    }
#   endif

    line_no = 0 ;
    for( i = numtokens-1; i >= 0; i-- ){
	/* look for the token ending in : */
	line_number = tokens[i] ;
	len = strlen( line_number ) ;
	if( line_number[len-1] == ':' ){
	    /* now see if we have digits up to the next : */
	    for( j = len-2; j >= 0 ; j -- ){
		if( !(isdigit(line_number[j])) || line_number[j] == ':' ){
		    break ;
		}
	    } /* end for( j = len-2... */
	    if( j < 0 || line_number[j] != ':' ){
		/* we didn't find :number: in token */
		continue ;
	    }
	    /* now we can start to build case for this being the line # */
	    line_number[len-1] = '\0' ;
	    line_no = atoi( &(line_number[j+1]) ) ;
#ifdef DEBUG
	    fprintf( stderr, "line no:%d\n", line_no ) ;
#endif
	    /* now get filename */
	    line_number[j] = '\0' ;
	    /* save file */
	    (void) strcpy(srcname, tokens[i] );
	    /* now build error message */
	    errmsg[0] = '\0' ;
	    for( i = i+1; i < numtokens; i++ ){
		strcat( errmsg, tokens[i] ) ;
		strcat( errmsg, " " ) ;
	    }
#ifdef DEBUG
	    fprintf( stderr, "filename:%s\n", srcname ) ;
	    fprintf( stderr, "errmsg:%s\n", errmsg ) ;
#endif
	    break ;

	}
    } /* end for( i = numtokens-1... */
    if( line_no == 0 ){
	/* try to read another line */
	line_no = gnu_errinfo(errfile, srcname, errmsg) ;
    }
    return( line_no ) ;
} /* end gnu_errinfo() */

char *
merge(errname, mergename)
    char *errname, *mergename;
{
    FILE *errfile, *srcfile, *mergefile;
    int eof = 0, slineno, elineno, elines;
    static char firstname[128];
    char srcline[BUFSIZ + 1];
    char srcname[128], errmsg[BUFSIZ];
    char *p;
    char *comp_shortname ;
    char *rindex() ;
    int (*get_error)() ; /* remember which function */

    if ((errfile = fopen(errname, "r")) == NULL) {
	perror(errname);
	exit (1);
    }
    if( comp_shortname = rindex( compiler, '/' ) ){
	comp_shortname++ ;
    } else {
	comp_shortname = compiler ;
    }
    if( strcmp( comp_shortname, "gcc" ) == 0 ){
	get_error = gnu_errinfo ;
    } else {
	get_error = errinfo ;
    }

    if ((firsterr = (*get_error)(errfile, srcname, errmsg)) == 0)
	return NULL;
    if (access(srcname, 2) < 0)	/* writeable ? */
	return NULL;
    if ((srcfile = fopen(srcname, "r")) == NULL) {
	perror(srcname);
	exit (1);
    }
    if (*mergename == '\0') {
	p = (char*) strrchr(srcname, '/');
	if (p == NULL)
	    p = srcname;
	else
	    p++;
	(void) sprintf(mergename, "/tmp/%d.%s", getpid(), p);
    }
    if ((mergefile = fopen(mergename, "w")) == NULL) {
	perror(mergename);
	exit (1);
    }
    slineno = 0;
    elineno = firsterr;
    elines = 0;
    (void) strcpy(firstname, srcname);
    chksum1 = 0;

    if (!viedit) {
	    (void) fprintf(mergefile, ">>>><<<< (%d)\n", firsterr + 1);
	    elines++;
    }
    while (!eof) {
	if (!(eof = (fgets(srcline, BUFSIZ, srcfile) == NULL))) {
	    chksum1 = checksum(chksum1, srcline);
	    (void) fputs(srcline, mergefile);
	}
	slineno++;

	while (slineno >= elineno && elineno != 0 ) {
	    elines++;
	    (void) fprintf(mergefile, ">>>> %s <<<<", errmsg);
	    if ((elineno = (*get_error)(errfile, srcname, errmsg)) == 0
		|| strcmp(firstname, srcname) != 0)
	      (void) fprintf(mergefile, " (last error)\n");
	    else
	      (void) fprintf(mergefile, " (%d)\n", elineno + elines);
	}
    }
    (void) fclose(errfile);
    (void) fclose(srcfile);
    (void) fclose(mergefile);
    return (firstname);
}

/*
 * Strip out merged error messages and compute checksum
 */
void 
unmerge(mergename, srcname)
    char *mergename, *srcname;
{
    FILE *mergefile, *srcfile;
    char *p, srcline[BUFSIZ + 1];

    if ((mergefile = fopen(mergename, "r")) == NULL) {
	perror(mergename);
	exit (1);
    }
    if ((srcfile = fopen(srcname, "w")) == NULL) {
	perror(srcname);
	exit (1);
    }
    chksum2 = 0;
    while (fgets(srcline, BUFSIZ, mergefile) != NULL) {
	for (p = srcline; isspace(*p); p++);
	if (strncmp(p, ">>>>", 4) != 0) {
	    chksum2 = checksum(chksum2, srcline);
	    (void) fputs(srcline, srcfile);
	}
    }

    (void) fclose(mergefile);
    (void) fclose(srcfile);
}

void 
quit()
{
    (void) kill(pid, SIGTERM);
    (void) unlink(errname);
    (void) unlink(mergename);
    exit (1);
}

/* this routine will only be used if "apollo" or "mips" is Defined */
char **Ystrparser(str,dels,numtokens)
char *str;
char *dels ; /* delimiters */
int  *numtokens ; /* pass back number of tokens */
{

    static char *tokenBuf[BUFSIZ] ; /* impossible to have more tokens */
				  /* than length of input line length */
    char *strtok() ;
    int  index = 0 ;

    /* use strtok to strip away delimiters */
    /* first call to strtok requires the string reference */
    tokenBuf[index] = strtok(str,dels) ;
    while( tokenBuf[index] ){
	/* subsequent calls to strtok doesn't requires the string ref */
	/* strtok remembers place in string */
	tokenBuf[++index] = strtok(NULL,dels) ;
    }
    /* return number of tokens and token buffer */
    *numtokens = index ;
    return(tokenBuf) ;
} /* end Ystrparser */


main(argc, argv)
    int argc;
    char *argv[];
{
    int i, status;
    char *srcname ;

    if ((editor = getenv("EDITOR")) == NULL)
	editor = "vi";
    edname = (edname = (char*) strrchr(editor, '/')) == NULL ? editor : edname + 1;
    viedit = strcmp(edname, "vi") == 0;
    emacsedit = strcmp(edname, "emacs") == 0;

    if ((compiler = getenv("COMPILER")) == NULL)
	compiler = "cc";
    argv[0] = compiler;

    (void) mktemp(errname);

    signal(SIGINT, quit);
    signal(SIGTERM, quit);
    signal(SIGHUP, quit);

    while (status = runc(argv, errname)) {
	if ((srcname = merge(errname, mergename)) == NULL) {
	    listerrs(errname);
	    exit (status);	/* couldn't merge */
	}
	edit(mergename);
	(void) unlink(errname);

	signal(SIGINT,  SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGHUP,  SIG_IGN);

	unmerge(mergename, srcname);
	(void) unlink(mergename);

	signal(SIGINT,  quit);
	signal(SIGTERM, quit);
	signal(SIGHUP,  quit);

	if (chksum1 == chksum2)	/* file unchanged ? */
	    break;

	putchar(' ');
	for (i = 0; i < argc; i++)
	    (void) printf("%s ", argv[i]);
	putchar('\n');
    }
    listerrs(errname);
    (void) unlink(errname);
    exit (status);
}
