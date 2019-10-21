import os
import sys

work_path = sys.argv[2]
directories = ['HLA-A', 'HLA-B', 'HLA-C', 'HLA-DRB1',
               'HLA-DQA1', 'HLA-DQB1', 'HLA-DPA1', 'HLA-DPB1']

#para todos os locus
for dir in directories:
    path = work_path+"/"+dir

    #lista todos os arquivos daquele locus
    archives = [f for f in os.listdir(path)]
    for i in archives:
        archive = path+"/"+i
        os.rename(archive, work_path+"/"+i)
