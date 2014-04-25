BEGIN { }
/OPTIONS/  { printf( "%s -DYALE\n", $0 ) ; next  }
{ print }
