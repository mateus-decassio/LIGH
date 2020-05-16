import lxml.etree as ET
import os
import sys

work_path = sys.argv[2]
directories = ['HLA-A', 'HLA-B', 'HLA-C', 'HLA-DRB1',
               'HLA-DQA1', 'HLA-DQB1', 'HLA-DPA1', 'HLA-DPB1']

#para todos os locus
for dir in directories:
    path = work_path+"/"+dir

    #lista todos os arquivos daquele locus para a extração dos dados
    archives = [f for f in os.listdir(path)]
    for i in archives:
        archive = path+"/"+i
        r_file = open(archive, 'r')
        tree = ET.parse(r_file)
        root = tree.getroot()

        if (root.tag == "ProjectXml"):
            s = root.xpath("./Samples/Sample/Name")
            sample = s[0].text
            file = path+"/"+sample+".txt"
            w_file = open(file, 'w')

            p = root.xpath("./Samples/Sample/Loci/Locus/PhasingRegions")
            phasing = p[0].text
            if (int(phasing) ==  1):
                #print("PHASE1")
                w_file.write("PHASE1/\n")

                #print("AMOSTRA = ", sample)
                w_file.write(sample+"/\n")

                l = root.xpath("./Samples/Sample/Loci/Locus/Name")
                locus = l[0].text
                #print("LOCUS = ", locus)
                w_file.write(locus+"/\n")

                regions = root.find("./Samples/Sample/Loci/Locus/AlleleDB/Regions")
                regions = [f for f in regions.iter('Region')]
                counter_regions = len(regions);
                #print("CONTADOR DE REGIOES = ", counter_regions)
                w_file.write(str(counter_regions)+"/\n")
                for region in regions:
                    ID = region.get('ID')
                    begin = region.get('begin')
                    end = region.get('end')
                    #print("ID, BEGIN, END = ", ID, begin, end)
                    w_file.write(ID+","+begin+","+end+"/\n")


                haplotypes = root.find("./Samples/Sample/Loci/Locus/Haplotypes")
                haplotypes = [f for f in haplotypes.iter('Haplotype')]
                counter_haplotypes = len(haplotypes)
                #print("COUNTER_HAPLOTYPES = ", counter_haplotypes)
                w_file.write(str(counter_haplotypes)+"/\n")
                for haplotype in haplotypes:
                    ID = haplotype.get('ID')
                    begin = haplotype.get('begin')
                    end = haplotype.get('end')
                    sequence = haplotype.text
                    sequence.replace(" ", "")
                    #print("ID, BEGIN, END = ", ID, begin, end, sequence)
                    w_file.write(ID+","+begin+","+end+","+sequence+"/\n")


                matches = root.find("./Samples/Sample/Loci/Locus/Matching/Matches")
                matches = [f for f in matches.iter('Match')]
                counter_matches = len(matches)
                #print("qtde MATCHES ENCONTRADOS = ", counter_matches)
                w_file.write(str(counter_matches)+"/\n")
                for match in matches:
                    ID = match.get('ID')
                    #print(ID)
                    w_file.write(ID+"/\n")
                    combinations = match.find("./HaplotypeCombination")
                    combinations = [f for f in combinations.iter('HaplotypeID')]
                    counter_combinations = len(combinations)
                    #print("combinações para esse match = ", counter_combinations)
                    w_file.write(str(counter_combinations)+"/\n")
                    for combination in combinations:
                        haplo = combination.text
                        #print(haplo)
                        w_file.write(haplo+"/\n")

            else: #if (int(phasing) ==  2):
                #print("PHASE1")
                w_file.write("PHASE2/\n")

                #print("AMOSTRA = ", sample)
                w_file.write(sample+"/\n")

                l = root.xpath("./Samples/Sample/Loci/Locus/Name")
                locus = l[0].text
                #print("LOCUS = ", locus)
                w_file.write(locus+"/\n")

                regions = root.find("./Samples/Sample/Loci/Locus/AlleleDB/Regions")
                regions = [f for f in regions.iter('Region')]
                counter_regions = len(regions);
                #print("CONTADOR DE REGIOES = ", counter_regions)
                w_file.write(str(counter_regions)+"/\n")
                for region in regions:
                    ID = region.get('ID')
                    begin = region.get('begin')
                    end = region.get('end')
                    #print("ID, BEGIN, END = ", ID, begin, end)
                    w_file.write(ID+","+begin+","+end+"/\n")


                haplotypes = root.find("./Samples/Sample/Loci/Locus/Haplotypes")
                haplotypes = [f for f in haplotypes.iter('Haplotype')]
                counter_haplotypes = 0;
                #print("COUNTER_HAPLOTYPES = 3")
                w_file.write("3/\n")
                for haplotype in haplotypes:
                    if (counter_haplotypes < 3):
                        ID = haplotype.get('ID')
                        begin = haplotype.get('begin')
                        end = haplotype.get('end')
                        sequence = haplotype.text
                        sequence.replace(" ", "")
                        #print("ID, BEGIN, END = ", ID, begin, end, sequence)
                        w_file.write(ID+","+begin+","+end+","+sequence+"/\n")
                        counter_haplotypes += 1


                matches = root.find("./Samples/Sample/Loci/Locus/Matching/Matches")
                matches = [f for f in matches.iter('Match')]
                counter_matches = len(matches)
                #print("qtde MATCHES ENCONTRADOS = ", counter_matches)
                w_file.write(str(counter_matches)+"/\n")
                for match in matches:
                    ID = match.get('ID')
                    #print(ID)
                    w_file.write(ID+"/\n")
                    combinations = match.find("./HaplotypeCombination")
                    combinations = [f for f in combinations.iter('HaplotypeID')]
                    counter_combinations = 0
                    #print("combinações para esse match = 3")
                    w_file.write("3/\n")
                    for combination in combinations:
                        if (counter_combinations < 3):
                            haplo = combination.text
                            #print (haplo)
                            w_file.write(haplo+"/\n")
                            counter_combinations += 1
            w_file.close()
#-------------------------------------------------------------------------------
        else: #if (root.tag == "Locus"):
            s = root.xpath("./SampleName")
            sample = s[0].text
            file = path+"/"+sample+".txt"
            w_file = open(file, 'w')

            p = root.xpath("./PhasingRegions")
            phasing = p[0].text
            if (int(phasing) ==  1):
                #print("PHASE1")
                w_file.write("PHASE1/\n")

                s = root.xpath("./SampleName")
                sample = s[0].text
                #print("AMOSTRA = ", sample)
                w_file.write(sample+"/\n")

                l = root.xpath("./Name")
                locus = l[0].text
                #print("LOCUS = ", locus)
                w_file.write(locus+"/\n")

                regions = root.find("./AlleleDB/Regions")
                regions = [f for f in regions.iter('Region')]
                counter_regions = len(regions);
                #print("CONTADOR DE REGIOES = ", counter_regions)
                w_file.write(str(counter_regions)+"/\n")
                for region in regions:
                    ID = region.get('ID')
                    begin = region.get('begin')
                    end = region.get('end')
                    #print("ID, BEGIN, END = ", ID, begin, end)
                    w_file.write(ID+","+begin+","+end+"/\n")


                haplotypes = root.find("./Haplotypes")
                haplotypes = [f for f in haplotypes.iter('Haplotype')]
                counter_haplotypes = len(haplotypes)
                #print("COUNTER_HAPLOTYPES = ", counter_haplotypes)
                w_file.write(str(counter_haplotypes)+"/\n")
                for haplotype in haplotypes:
                    ID = haplotype.get('ID')
                    begin = haplotype.get('begin')
                    end = haplotype.get('end')
                    sequence = haplotype.text
                    sequence.replace(" ", "")
                    #print("ID, BEGIN, END = ", ID, begin, end, sequence)
                    w_file.write(ID+","+begin+","+end+","+sequence+"/\n")


                matches = root.find("./Matching/Matches")
                matches = [f for f in matches.iter('Match')]
                counter_matches = len(matches)
                #print("qtde MATCHES ENCONTRADOS = ", counter_matches)
                w_file.write(str(counter_matches)+"/\n")
                for match in matches:
                    ID = match.get('ID')
                    #print(ID)
                    w_file.write(ID+"/\n")
                    combinations = match.find("./HaplotypeCombination")
                    combinations = [f for f in combinations.iter('HaplotypeID')]
                    counter_combinations = len(combinations)
                    #print("combinações para esse match = ", counter_combinations)
                    w_file.write(str(counter_combinations)+"/\n")
                    for combination in combinations:
                        haplo = combination.text
                        #print(haplo)
                        w_file.write(haplo+"/\n")

            else: #if (int(phasing) ==  2):
                #print("PHASE2")
                w_file.write("PHASE2/\n")

                #print("AMOSTRA = ", sample)
                w_file.write(sample+"/\n")

                l = root.xpath("./Name")
                locus = l[0].text
                #print("LOCUS = ", locus)
                w_file.write(locus+"/\n")

                regions = root.find("./AlleleDB/Regions")
                regions = [f for f in regions.iter('Region')]
                counter_regions = len(regions);
                #print("CONTADOR DE REGIOES = ", counter_regions)
                w_file.write(str(counter_regions)+"/\n")
                for region in regions:
                    ID = region.get('ID')
                    begin = region.get('begin')
                    end = region.get('end')
                    #print("ID, BEGIN, END = ", ID, begin, end)
                    w_file.write(ID+","+begin+","+end+"/\n")


                haplotypes = root.find("./Haplotypes")
                haplotypes = [f for f in haplotypes.iter('Haplotype')]
                counter_haplotypes = 0
                #print("COUNTER_HAPLOTYPES = 3")
                w_file.write("3/\n")
                for haplotype in haplotypes:
                    if (counter_haplotypes < 3):
                        ID = haplotype.get('ID')
                        begin = haplotype.get('begin')
                        end = haplotype.get('end')
                        sequence = haplotype.text
                        sequence.replace(" ", "")
                        #print("ID, BEGIN, END = ", ID, begin, end, sequence)
                        w_file.write(ID+","+begin+","+end+","+sequence+"/\n")
                        counter_haplotypes += 1


                matches = root.find("./Matching/Matches")
                matches = [f for f in matches.iter('Match')]
                counter_matches = len(matches)
                #print("qtde MATCHES ENCONTRADOS = ", counter_matches)
                w_file.write(str(counter_matches)+"/\n")
                for match in matches:
                    ID = match.get('ID')
                    #print(ID)
                    w_file.write(ID+"/\n")
                    combinations = match.find("./HaplotypeCombination")
                    combinations = [f for f in combinations.iter('HaplotypeID')]
                    counter_combinations = 0
                    #print("combinações para esse match = 3")
                    w_file.write("3/\n")
                    for combination in combinations:
                        if (counter_combinations < 3):
                            haplo = combination.text
                            #print(haplo)
                            w_file.write(haplo+"/\n")
                            counter_combinations += 1
            w_file.close()

        r_file.close()