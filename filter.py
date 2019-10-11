import lxml.etree as ET
import os
import sys

path = sys.argv[2]
directories = ['undefined_phase', 'undefined_format', 'HLA-A', 'HLA-B', 'HLA-C',
               'HLA-DRB1', 'HLA-DQA1', 'HLA-DQB1', 'HLA-DPA1', 'HLA-DPB1']
undefined_phase = path+"/undefined_phase"
undefined_format = path+"/undefined_format"
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

    if (root.tag == "ProjectXml"):
        g = root.xpath("./Samples/Sample/Loci/Locus/NumberOfGenotypes")
        numberofgenotypes = g[0].text
        if (int(numberofgenotypes) > 0):
            s = root.xpath("./Samples/Sample/Name")
            sample = s[0].text

            p = root.xpath("./Samples/Sample/Loci/Locus/PhasingRegions")
            phasing = p[0].text

            l = root.xpath("./Samples/Sample/Loci/Locus/Name")
            locus = l[0].text

            if (int(phasing) > 2):
                os.rename(archive, undefined_phase+"/"+sample+under+locus+extension)
            else:
                os.rename(archive, path+"/"+locus+"/"+sample+extension)
        else:
            os.rename(archive, undefined_format+"/"+i+extension)


    elif (root.tag == "Locus"):
        g = root.xpath("./NumberOfGenotypes")
        numberofgenotypes = g[0].text
        if (int(numberofgenotypes) > 0):
            s = root.xpath("./SampleName")
            sample = s[0].text

            p = root.xpath("./PhasingRegions")
            phasing = p[0].text

            l = root.xpath("./Name")
            locus = l[0].text

            if (int(phasing) > 2):
                os.rename(archive, undefined_phase+"/"+sample+under+locus+extension)
            else:
                os.rename(archive, path+"/"+locus+"/"+sample+extension)
        else:
            os.rename(archive, undefined_format+"/"+i+extension)

    else:
        os.rename(archive, undefined_format+"/"+i)

    file.close()
