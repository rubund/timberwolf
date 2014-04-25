# Add the following to .cshrc file

# set TimberWolf environment variable.  This is a must.
# it must be the pathname of the root directory.
setenv TWDIR ~/TimberWolf

# add TimberWolf binary to search path
# allows user to type in TimberWolf without full pathname.
# this is really an optional convenience.
set path = ( $path $TWDIR/bin )


# this is the default for the Xserver on local node.
# user should change as appropriate.
setenv DISPLAY unix:0
