#!/bin/bash

#------------INTRON
cd python
python3 extraction_TXT_v4.py -d /mnt/hgfs/SHARED -k intron

cd ../analysis
make

./analysis -l HLA-A -d /mnt/hgfs/SHARED/HLA-A.txt -k intron -r /mnt/hgfs/SHARED

./analysis -l HLA-B -d /mnt/hgfs/SHARED/HLA-B.txt -k intron -r /mnt/hgfs/SHARED

./analysis -l HLA-C -d /mnt/hgfs/SHARED/HLA-C.txt -k intron -r /mnt/hgfs/SHARED


#------------EXON
cd ../python
python3 extraction_TXT_v4.py -d /mnt/hgfs/SHARED -k exon

cd ../analysis

./analysis -l HLA-A -d /mnt/hgfs/SHARED/HLA-A.txt -k exon -r /mnt/hgfs/SHARED

./analysis -l HLA-B -d /mnt/hgfs/SHARED/HLA-B.txt -k exon -r /mnt/hgfs/SHARED

./analysis -l HLA-C -d /mnt/hgfs/SHARED/HLA-C.txt -k exon -r /mnt/hgfs/SHARED
