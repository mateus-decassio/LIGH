#USO: python3 verify_complete.py -d /mnt/hgfs/SHARED -k intron
#USO: python3 verify_complete.py -d /mnt/hgfs/SHARED -k exon
import lxml.etree as ET
import os
import sys

work_path = sys.argv[2]
key = sys.argv[4]
'''
directories = ['HLA-A', 'HLA-B', 'HLA-C', 'HLA-DRB1',
               'HLA-DQA1', 'HLA-DQB1', 'HLA-DPB1']
'''

directories = ['HLA-A', 'HLA-B', 'HLA-C']

#para todos os locus
for dir in directories:
    if (dir == 'HLA-A'):
        MAX_EXONS = 8
        MAX_INTRONS = 7
    elif (dir == 'HLA-B'):
        MAX_EXONS = 7
        MAX_INTRONS = 6
    elif (dir == 'HLA-C'):
        MAX_EXONS = 6
        MAX_INTRONS = 6
    
    path = work_path+"/"+dir

    #lista todos os arquivos daquele locus para a extração dos dados
    archives = [f for f in os.listdir(path)]

    for i in archives:
        archive = path+"/"+i
        r_file = open(archive, 'r')
        tree = ET.parse(r_file)
        root = tree.getroot()


        an_alleles = root.find("./Samples/Sample/Loci/Locus/AnnotatedAlleles")
        an_alleles = [f for f in an_alleles.iter('AnnotatedAllele')]
        
        if (key == 'intron'):
            for allele in an_alleles:
                features = allele.find('./Features')
                feature = [f for f in features.iter('Feature')]

                for feat in feature:
                    f_key = feat.get('Key')
                    if (f_key == key):
                        numb = feat.get('Number')
                
                if (MAX_INTRONS != int(numb)):
                    print('A AMOSTRA '+str(i)+' DO LOCUS '+str(dir)+' NÃO TEM O INTRON '+str(MAX_INTRONS))
                        

        else:
            for allele in an_alleles:
                features = allele.find('./Features')
                feature = [f for f in features.iter('Feature')]

                for feat in feature:
                    f_key = feat.get('Key')
                    if (f_key == key):
                        numb = feat.get('Number')
                
                if (MAX_EXONS != int(numb)):
                    print('A AMOSTRA '+str(i)+' DO LOCUS '+str(dir)+' NÃO TEM O EXON '+str(MAX_EXONS))
