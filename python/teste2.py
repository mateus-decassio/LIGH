import lxml.etree as ET
import os
import sys

path = sys.argv[2]


#listagem dos arquivos contidos nesse diretório
archives = [f for f in os.listdir(path)]



#renomeação e filtragem dos arquivos para as respectivas pastas
for i in archives:
    archive = path+"/"+i
    file = open(archive, "r")
    tree = ET.parse(file)
    root = tree.getroot()

    if (root.tag == "ProjectXml"):
        s = root.xpath("./Samples/Sample/Name")
        sample = s[0].text

        p = root.xpath("./Samples/Sample/Loci/Locus/PhasingRegions")
        phasing = p[0].text

        haplotypes = root.find("./Samples/Sample/Loci/Locus/Haplotypes")
        haplotypes = [f for f in haplotypes.iter('Haplotype')]

        for haplotype in haplotypes:
            ID = haplotype.get('ID')
            if (ID=="homozygous1"):
                begin = haplotype.get('begin')
                end = haplotype.get('end')
                print("PHASE = ",phasing, "ID, BEGIN, END = ", ID, begin, end)
    file.close()
