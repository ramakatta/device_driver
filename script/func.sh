#!/usr/bin/bash

say()
{
  printf '[%s] %s\n' "$(date +%T)" "$*"
}

files=( *.patch )

say "found ${#files[@]} patches"

for f in "${files[@]}"; do 
    say "$f"
done
