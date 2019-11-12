import lxml.etree as ET
import os
import sys

path = sys.argv[2]
extension = ".xml"
under = "_"

#listagem das pastas presentes no diretório
folders = [f for f in os.listdir(path)]


#renomeação dos arquivos
for f in folders:
    work_path = path+"/"+f
    archives = [f for f in os.listdir(work_path)]

    for i in archives:
        archive = work_path+"/"+i
        file = open(archive, "r")
        tree = ET.parse(file)
        root = tree.getroot()

        if (root.tag == "ProjectXml"):
            s = root.xpath("./Samples/Sample/Name")
            sample = s[0].text.split("-")
            sample = sample[0]

            l = root.xpath("./Samples/Sample/Loci/Locus/Name")
            locus = l[0].text

            os.rename(archive, work_path+"/"+sample+under+locus+extension)


        elif (root.tag == "Locus"):
            s = root.xpath("./SampleName")
            sample = s[0].text

            l = root.xpath("./Name")
            locus = l[0].text

            os.rename(archive, work_path+"/"+sample+under+locus+extension)

        file.close()
