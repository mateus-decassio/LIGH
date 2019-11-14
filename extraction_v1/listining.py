import os
import sys

work_path = sys.argv[2]
directories = ['HLA-A', 'HLA-B', 'HLA-C', 'HLA-DRB1',
               'HLA-DQA1', 'HLA-DQB1', 'HLA-DPA1', 'HLA-DPB1']

#para todos os locus
for dir in directories:
    path = work_path+"/"+dir

    file = path+".txt"
    w_file = open(file, 'w')

    #lista todos os arquivos daquele locus para a extração dos dados
    archives = [f for f in os.listdir(path)]
    size = len(archives)
    if (size == 0):
        w_file.write("0")
    else:
        w_file.write(str(size//2)+"|\n")
    for i in archives:
        if (i.endswith('.txt')):
            w_file.write(path+"/"+i+"|\n")

    w_file.close()
