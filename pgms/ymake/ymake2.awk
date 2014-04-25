BEGIN { state = 0 }
$1 == "#ifdef" && $2 == "YALE" {
    state = 0 ;
    next ;
}
$1 == "#else" {
    state = 1 ;
    next ;
}
$1 == "#endif" {
    state = 1 ;
    next ;
}
$0 != "#include macros" && state == 1 { print }
$0 == "#include macros" { state = 1 }
