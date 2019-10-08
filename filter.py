import lxml.etree as ET
import os
import sys

path = sys.argv[2]
directories = ['undefined_phase', 'HLA-A', 'HLA-B', 'HLA-C',
               'HLA-DRB1', 'HLA-DQA1', 'HLA-DQB1', 'HLA-DPA1', 'HLA-DPB1']
undefined_phase = path+"/undefined_phase"
extension = ".xml"
under = "_"

#listagem dos arquivos contidos nesse diretório
archives = [f for f in os.listdir(path)]


#criação das pastas de destinos dos arquivos
for dir in directories:
    directory = path+"/"+dir
    if (os.path.exists(directory) == False):
        os.mkdir(directory)


#renomeação e filtragem dos arquivos para as respectivas pastas
for i in archives:
    archive = path+"/"+i
    file = open(archive, "r")
    tree = ET.parse(file)
    root = tree.getroot()

    n = root.xpath("./Samples/Sample/Name")
    name = n[0].text

    p = root.xpath("./Samples/Sample/Loci/Locus/PhasingRegions")
    phasing = p[0].text

    l = root.xpath("./Samples/Sample/Loci/Locus/Name")
    locus = l[0].text

    file.close()

    if (int(phasing) > 1):
        os.rename(path+"/"+i, undefined_phase+"/"+name+under+locus+extension)
    else:
        os.rename(path+"/"+i, path+"/"+locus+"/"+name+extension)
