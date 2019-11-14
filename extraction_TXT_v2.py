import lxml.etree as ET
import os
import sys

work_path = sys.argv[2]
#directories = ['HLA-A', 'HLA-B', 'HLA-C', 'HLA-DRB1',
#               'HLA-DQA1', 'HLA-DQB1', 'HLA-DPA1', 'HLA-DPB1']

directories = ['HLA-DPB1']

#para todos os locus
for dir in directories:
    path = work_path+"/"+dir

    #lista todos os arquivos daquele locus para a extração dos dados
    archives = [f for f in os.listdir(path)]

    #cria o arquivo que vai receber todas as sequências
    file = work_path+"/"+dir+".txt"
    w_file = open(file, 'w')

    number_of_files = len(archives);
    print('NUMERO DE ARQUIVOS = ', number_of_files)
    #w_file.write(str(number_of_files)+"/\n")

    #pega a sequência de regiões
    i = archives[0]
    archive = path+"/"+i
    r_file = open(archive, 'r')
    tree = ET.parse(r_file)
    root = tree.getroot()

    regions = root.find("./Samples/Sample/Loci/Locus/AlleleDB/Regions")
    regions = [f for f in regions.iter('Region')]
    counter_regions = len(regions);
    print("CONTADOR DE REGIOES = ", counter_regions)
    #w_file.write(str(counter_regions)+"/\n")
    for region in regions:
        ID = region.get('ID')
        begin = region.get('begin')
        end = region.get('end')
        print("ID, BEGIN, END = ", ID, begin, end)
        #w_file.write(ID+","+begin+","+end+"/\n")

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
        if (int(phasing) ==  1):
            #print("AMOSTRA = ", sample)
            #w_file.write(">"+sample+" ")

            haplotypes = root.find("./Samples/Sample/Loci/Locus/Haplotypes")
            haplotypes = [f for f in haplotypes.iter('Haplotype')]
            counter_haplotypes = len(haplotypes)
            #print("COUNTER_HAPLOTYPES = ", counter_haplotypes)
            #w_file.write(str(counter_haplotypes)+"/\n")
            for haplotype in haplotypes:
                ID = haplotype.get('ID')
                begin = haplotype.get('begin')
                end = haplotype.get('end')
                sequence = haplotype.text
                sequence.replace(" ", "")
                #print("ID, BEGIN, END = ", ID, begin, end, sequence)
                #w_file.write(ID+","+begin+","+end+","+sequence+"/\n")


            matches = root.find("./Samples/Sample/Loci/Locus/Matching/Matches")
            matches = [f for f in matches.iter('Match')]
            counter_matches = len(matches)
            #print("qtde MATCHES ENCONTRADOS = ", counter_matches)
            #w_file.write(str(counter_matches)+"/\n")
            for match in matches:
                ID = match.get('ID')
                #print(ID)
                #w_file.write(ID+"/\n")
                combinations = match.find("./HaplotypeCombination")
                combinations = [f for f in combinations.iter('HaplotypeID')]
                counter_combinations = len(combinations)
                #print("combinações para esse match = ", counter_combinations)
                #w_file.write(str(counter_combinations)+"/\n")
                for combination in combinations:
                    haplo = combination.text
                    #print(haplo)
                    #w_file.write(haplo+"/\n")

        #else: #if (int(phasing) ==  2):
            #print("PHASE1")


        r_file.close()
