#!/bin/bash

	key="<Name>"

	#grep "<Name>" Teste\ Mateus_49934-sg_HLA-A.tarr.xml
	printf "$(grep "$key" Teste\ Mateus_49934-sg_HLA-A.tarr.xml | awk -F" " '{print $1}' | tr ">" " " | tr "<Name" " " | tr "/" " " | awk -F" " '{print $1}')\n"