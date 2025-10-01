#!/usr/bin/bash
#Program to print timestamp of .patch files
say() 
{
    printf '[%s] %s\n' "$(date +%T)" "$*"
}

files=(*.patch)

say "found ${#files[@]} patches"

for f in "${files[@]}"; do
  say "$f"
done
