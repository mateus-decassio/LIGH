import lxml.etree as ET
import os
import sys

path = sys.argv[2]
extension = ".xml"
under = "_"

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
        s[0].text = s[0].text+"(conflict)"
        sample = s[0].text

        l = root.xpath("./Samples/Sample/Loci/Locus/Name")
        locus = l[0].text

        output = path+"/"+sample+under+locus+extension
        tree.write(output)
        os.remove(archive)

    elif (root.tag == "Locus"):
        s = root.xpath("./SampleName")
        s[0].text = s[0].text+"(conflict)"
        sample = s[0].text

        l = root.xpath("./Name")
        locus = l[0].text

        output = path+"/"+sample+under+locus+extension
        tree.write(output)
        os.remove(archive)

    file.close()