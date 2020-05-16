#!/bin/bash

path='/mnt/hgfs/SHARED/HLA-B'
samples=(138561)

for file in ${samples[@]}
    do
        mv $path/$file.xml $path/SEPARADOS/$file.xml
    done