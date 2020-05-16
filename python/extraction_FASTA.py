import lxml.etree as ET
import os
import sys

work_path = sys.argv[2]
directories = ['HLA-A', 'HLA-B', 'HLA-C', 'HLA-DRB1',
               'HLA-DQA1', 'HLA-DQB1', 'HLA-DPB1']

#para todos os locus
for dir in directories:
    path = work_path+"/"+dir

    #lista todos os arquivos daquele locus para a extração dos dados
    archives = [f for f in os.listdir(path)]

    #cria o arquivo que vai receber todas as sequências
    file = work_path+"/"+dir+".fasta"
    w_file = open(file, 'w')

    for i in archives:
        archive = path+"/"+i
        r_file = open(archive, 'r')
        tree = ET.parse(r_file)
        root = tree.getroot()

        s = root.xpath("./Samples/Sample/Name")
        sample = s[0].text

        p = root.xpath("./Samples/Sample/Loci/Locus/PhasingRegions")
        phasing = p[0].text

        haplotypes = root.find("./Samples/Sample/Loci/Locus/Haplotypes")
        haplotypes = [f for f in haplotypes.iter('Haplotype')]

        for haplotype in haplotypes:
            sequence = haplotype.text
            sequence.replace(" ", "")
            sequence.replace("\n", "")

        matches = root.find("./Samples/Sample/Loci/Locus/Matching/Matches")
        matches = [f for f in matches.iter('Match')]

        if (int(phasing) ==  1):
            for match in matches:
                sequence = ""
                match_ID = match.get('ID')

                combinations = match.find("./HaplotypeCombination")
                combinations = [f for f in combinations.iter('HaplotypeID')]

                for combination in combinations:
                    haplo = combination.text
                    for haplotype in haplotypes:
                        ID = haplotype.get('ID')
                        if (ID == haplo):
                            sequence = sequence+haplotype.text
                fasta = '>'+sample+' '+match_ID+'\n'+sequence+"\n"

                w_file.write(fasta+'\n')

        else: #if (int(phasing) ==  2):
            for match in matches:
                sequence = ""
                match_ID = match.get('ID')

                combinations = match.find("./HaplotypeCombination")
                combinations = [f for f in combinations.iter('HaplotypeID')]

                counter = 0
                for combination in combinations:
                    haplo = combination.text
                    if (counter < 3):
                        for haplotype in haplotypes:
                            ID = haplotype.get('ID')
                            if (ID == haplo):
                                sequence = sequence+haplotype.text
                                counter += 1
                fasta = '>'+sample+' '+match_ID+'\n'+sequence+"\n"

                w_file.write(fasta+'\n')


        r_file.close()