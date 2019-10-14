import os
import sys

work_path = sys.argv[2]
directories = ['HLA-A', 'HLA-B', 'HLA-C', 'HLA-DRB1',
               'HLA-DQA1', 'HLA-DQB1', 'HLA-DPA1', 'HLA-DPB1']

#para todos os locus
for dir in directories:
    path = work_path+"/"+dir

    file = work_path+"/"+dir+".txt"
    w_file = open(file, 'w')

    #lista todos os arquivos daquele locus para a extração dos dados
    archives = [f for f in os.listdir(path)]
    for i in archives:
        archive = path+"/"+i
        w_file = open(archive, "r")
