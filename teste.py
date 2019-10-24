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
        #print(sample)

        p = root.xpath("./Samples/Sample/Loci/Locus/PhasingRegions")
        phasing = p[0].text
        #print(phasing)

        l = root.xpath("./Samples/Sample/Loci/Locus/Name")
        locus = l[0].text
        #print(locus)

        #falta arrumar para pegar só os aprovados

        st = root.xpath("./Samples/Sample/Loci/Locus/ReviewList")
        status = st[0].attrib.get('CurrentApprovalStatus')
        print(status)

    file.close()
