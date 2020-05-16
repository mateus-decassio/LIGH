#USO: python3 extraction_TXT_v4.py -d /mnt/hgfs/SHARED -k intron
#USO: python3 extraction_TXT_v4.py -d /mnt/hgfs/SHARED -k exon
import lxml.etree as ET
import os
import sys

work_path = sys.argv[2]
key = sys.argv[4]
'''
directories = ['HLA-A', 'HLA-B', 'HLA-C', 'HLA-DRB1',
               'HLA-DQA1', 'HLA-DQB1', 'HLA-DPB1']
'''

directories = ['HLA-A', 'HLA-B', 'HLA-C', 'HLA-DRB1', 'HLA-DQB1']

#para todos os locus
for dir in directories:
    if (dir == 'HLA-A'):
        MAX_EXONS = 8
    elif (dir == 'HLA-B'):
        MAX_EXONS = 7
    elif (dir == 'HLA-C'):
        MAX_EXONS = 8
    
    path = work_path+"/"+dir

    #lista todos os arquivos daquele locus para a extração dos dados
    archives = [f for f in os.listdir(path)]

    #cria o arquivo que vai receber todas as sequências
    file = work_path+"/"+dir+".txt"
    w_file = open(file, 'w')

    number_of_files = len(archives)
    #print('NUMERO DE ARQUIVOS = ', number_of_files)
    w_file.write(str(number_of_files)+"/\n")

    #pega a sequência
    i = archives[0]
    archive = path+"/"+i
    r_file = open(archive, 'r')
    tree = ET.parse(r_file)
    root = tree.getroot()

    for i in archives:
        archive = path+"/"+i
        r_file = open(archive, 'r')
        tree = ET.parse(r_file)
        root = tree.getroot()


        s = root.xpath("./Samples/Sample/Name")
        sample = s[0].text


        p = root.xpath("./Samples/Sample/Loci/Locus/PhasingRegions")
        phasing = p[0].text


        an_alleles = root.find("./Samples/Sample/Loci/Locus/AnnotatedAlleles")
        an_alleles = [f for f in an_alleles.iter('AnnotatedAllele')]
        counter_alleles = len(an_alleles)
        w_file.write(str(counter_alleles)+"/\n")
        
        
        haplotypes = root.find("./Samples/Sample/Loci/Locus/Haplotypes")
        haplotypes = [f for f in haplotypes.iter('Haplotype')]
        base_num = haplotypes[0].get('begin')
        w_file.write(str(base_num)+"/\n")
        
        if (key == 'intron'):
            for allele in an_alleles:
                AlleleSequence = allele.find('./AlleleSequence')
                match_ID = AlleleSequence.get('Match')
                sequence = AlleleSequence.text
                
                
                features = allele.find('./Features')
                feature = [f for f in features.iter('Feature')]
                to_print = ''
                parameter = ''
                count_feat = 0
                for feat in feature:
                    f_key = feat.get('Key')
                    if (f_key == key):
                        n_range = feat.get('location')
                        begin = n_range.split('..')[0]
                        end = n_range.split('..')[1]
                        to_print = to_print+','+str(begin)+'~'+str(end)
                        count_feat += 1
                parameter = str(count_feat)+to_print+"/\n"
                
                w_file.write(parameter)
                
                fasta = sample+'/\n'+match_ID+'/\n'+sequence+'\n'
                w_file.write(fasta)
        else:
            regions = root.find("./Samples/Sample/Loci/Locus/AlleleDB/Regions")
            regions = [f for f in regions.iter('Region')]
            count_regions = len(regions)
            
            a = regions[count_regions-2].get('begin')
            b = regions[count_regions-2].get('end')
            stride = int(b) - int(a)
            
            for allele in an_alleles:
                AlleleSequence = allele.find('./AlleleSequence')
                match_ID = AlleleSequence.get('Match')
                sequence = AlleleSequence.text
                
                
                features = allele.find('./Features')
                feature = [f for f in features.iter('Feature')]
                to_print = ''
                parameter = ''
                count_feat = 0
                for feat in feature:
                    f_key = feat.get('Key')
                    if (f_key == key):
                        max_e = feat.get('Number')
                        n_range = feat.get('location')
                        if (max_e == str(MAX_EXONS)):
                            begin = n_range.split('..')[0]
                            end = int(begin) + int(stride)
                        else:
                            begin = n_range.split('..')[0]
                            end = n_range.split('..')[1]
                        to_print = to_print+','+str(begin)+'~'+str(end)
                        count_feat += 1
                parameter = str(count_feat)+to_print+"/\n"
                
                parameter = parameter.replace('<', '')
                parameter = parameter.replace('>', '')
                w_file.write(parameter)
                
                fasta = sample+'/\n'+match_ID+'/\n'+sequence+'\n'
                w_file.write(fasta)

        r_file.close()
