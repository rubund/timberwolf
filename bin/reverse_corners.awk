BEGIN { }
$2 == "corners" { 
    printf( "corners %s ", $1 ) ;
    for( i = 3; i <= NF; i++ ){
	printf( "%s ", $i ) ;
    }
    printf( "\n" ) ;
    continue ;
}
{ print }
END { }
