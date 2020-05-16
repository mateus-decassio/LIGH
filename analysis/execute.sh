#!/bin/bash


cd analysis2
make

./analysis -l HLA-A -d /mnt/hgfs/SHARED/HLA-A.txt -r /mnt/hgfs/SHARED -i 7 2> not_contigous[HLA-A].txt
mv ./not_contigous[HLA-A].txt /mnt/hgfs/SHARED/RESULTS/HLA-A/not_contigous[HLA-A].txt

./analysis -l HLA-B -d /mnt/hgfs/SHARED/HLA-B.txt -r /mnt/hgfs/SHARED -i 6 2> not_contigous[HLA-B].txt
mv ./not_contigous[HLA-B].txt /mnt/hgfs/SHARED/RESULTS/HLA-B/not_contigous[HLA-B].txt

./analysis -l HLA-C -d /mnt/hgfs/SHARED/HLA-C.txt -r /mnt/hgfs/SHARED -i 7 2> not_contigous[HLA-C].txt
mv ./not_contigous[HLA-C].txt /mnt/hgfs/SHARED/RESULTS/HLA-C/not_contigous[HLA-C].txt

#./analysis -l HLA-DQB1 -d /mnt/hgfs/SHARED/HLA-DQB1.txt -r /mnt/hgfs/SHARED 2> not_contigous[HLA-DQB1].txt

#./analysis -l HLA-DRB1 -d /mnt/hgfs/SHARED/HLA-DRB1.txt -r /mnt/hgfs/SHARED 2> not_contigous[HLA-DRB1].txt