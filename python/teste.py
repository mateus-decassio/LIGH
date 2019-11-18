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

        regions = root.find("./Samples/Sample/Loci/Locus/AlleleDB/Regions")
        regions = [f for f in regions.iter('Region')]

        for region in regions:
            ID = region.get('ID')
            if (ID == "UTR"):
                begin = region.get('begin')
                end = region.get('end')
                #print("SAMPLE =", sample, "PHASE = ",phasing, "ID, BEGIN, END = ", ID, begin, end)
                print("PHASE = ",phasing, "ID, BEGIN, END = ", ID, begin, end)

    file.close()
