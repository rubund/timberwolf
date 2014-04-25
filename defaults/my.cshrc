# The systype variables are needed for the Apollo
#setenv SYSTYPE bsd4.3
#set systype=bsd4.3
setenv TWDIR ~/TimberWolf
setenv DATADIR ~/DATA
set path = ( . ~/bin $TWDIR/bin /usr/ucb /usr/local/bin /bin /usr/bin /usr/new /usr/bin/X11 )
if ($?prompt) then
    set ignoreeof
    setenv PRINTER sun-alw
    setenv COMPILER cc
    stty erase  kill 
    set notify
    source ~/.aliases
    set history = 50 
    set time = 1
endif
unsetenv EXINIT
rehash
