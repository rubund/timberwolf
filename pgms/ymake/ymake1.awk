BEGIN { }
$0 != "#include macros" { print }
$0 == "#include macros" { exit }
