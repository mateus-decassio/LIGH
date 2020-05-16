#USO: python3 extraction_TXT_v2.py -d /mnt/hgfs/SHARED

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
    file = work_path+"/"+dir+".txt"
    w_file = open(file, 'w')

    number_of_files = len(archives);
    #print('NUMERO DE ARQUIVOS = ', number_of_files)
    w_file.write(str(number_of_files)+"/\n")

    #pega a sequência de regiões
    i = archives[0]
    archive = path+"/"+i
    r_file = open(archive, 'r')
    tree = ET.parse(r_file)
    root = tree.getroot()

    regions = root.find("./Samples/Sample/Loci/Locus/AlleleDB/Regions")
    regions = [f for f in regions.iter('Region')]
    counter_regions = len(regions)
    #print("CONTADOR DE REGIOES = ", counter_regions)
    w_file.write(str(counter_regions)+"/\n")
    for region in regions:
        ID = region.get('ID')
        begin = region.get('begin')
        end = region.get('end')
        #print("ID, BEGIN, END = ", ID, begin, end)
        w_file.write(ID+","+begin+","+end+"/\n")

    r_file.close()

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
            sequence.replace("-", "")

        matches = root.find("./Samples/Sample/Loci/Locus/Matching/Matches")
        matches = [f for f in matches.iter('Match')]
        counter_matches = len(matches)
        #print('')
        #print(counter_matches)
        w_file.write(str(counter_matches)+"/\n")

        if (int(phasing) ==  1):
            for match in matches:
                sequence = ""
                match_ID = match.get('ID')

                combinations = match.find("./HaplotypeCombination")
                combinations = [f for f in combinations.iter('HaplotypeID')]
                counter_combinations = len(combinations)

                parameter = str(counter_combinations)

                for combination in combinations:
                    haplo = combination.text
                    for haplotype in haplotypes:
                        ID = haplotype.get('ID')
                        if (ID == haplo):
                            begin = haplotype.get('begin')
                            end = haplotype.get('end')
                            parameter = parameter+','+str(begin)+'~'+str(end)

                            sequence = sequence+haplotype.text
                parameter = parameter+"/\n"
                w_file.write(parameter)
                
                fasta = sample+'/\n'+match_ID+'/\n'+sequence+'\n'
                w_file.write(fasta)

        else: #if (int(phasing) ==  2):
            for match in matches:
                sequence = ""
                match_ID = match.get('ID')

                combinations = match.find("./HaplotypeCombination")
                combinations = [f for f in combinations.iter('HaplotypeID')]

                parameter = str(3)

                counter = 0
                for combination in combinations:
                    haplo = combination.text
                    if (counter < 3):
                        for haplotype in haplotypes:
                            ID = haplotype.get('ID')
                            if (ID == haplo):
                                begin = haplotype.get('begin')
                                end = haplotype.get('end')
                                parameter = parameter+','+str(begin)+'~'+str(end)

                                sequence = sequence+haplotype.text
                                counter += 1
                parameter = parameter+"/\n"
                w_file.write(parameter)
                
                fasta = sample+'/\n'+match_ID+'/\n'+sequence+'\n'
                w_file.write(fasta)


        r_file.close()