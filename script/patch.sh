#!/usr/bin/bash

for i in $(seq -w 1 100);
do
    filename="${i}-prod-abc.patch"
    touch "${filename}"
    echo "created $filename"
done
