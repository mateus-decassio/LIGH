import lxml.etree as ET
import os
import sys

path = sys.argv[2]
not_used = path+"/not_used"
extension = ".xml"
under = "_"

#listagem dos arquivos contidos nesse diretório
files = [f for f in os.listdir(path)]

if (os.path.exists(not_used) == False):
    os.mkdir(not_used)

for i in files:
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

    if (phasing > '1'):
        os.rename(path+"/"+i, not_used+"/"+name+under+locus+extension)
    else:
        os.rename(path+"/"+i, path+"/"+name+under+locus+extension)
