import lxml.etree as ET
import os
import sys

work_path = sys.argv[2]
#directories = ['HLA-A', 'HLA-B', 'HLA-C', 'HLA-DRB1',
#               'HLA-DQA1', 'HLA-DQB1', 'HLA-DPA1', 'HLA-DPB1']

directories = ['HLA-DPB1']

#para todos os locus
for dir in directories:
    path = work_path+"/"+dir

    #lista todos os arquivos daquele locus para a extração dos dados
    archives = [f for f in os.listdir(path)]
    for i in archives:
        archive = path+"/"+i
        read_file = open(archive, "r")
        tree = ET.parse(read_file)
        root = tree.getroot()

        n = root.xpath("./Samples/Sample/Name")
        name = n[0].text

        l = root.xpath("./Samples/Sample/Loci/Locus/Name")
        locus = l[0].text

        
