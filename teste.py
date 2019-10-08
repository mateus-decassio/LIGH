import lxml.etree as ET

archive = "/home/mateus/Downloads/HLA-DPB1/49934-sg.xml"




read_file = open(archive, "r")
tree = ET.parse(read_file)
root = tree.getroot()

s = root.xpath("./Samples/Sample/Name")
sample = s[0].text
print(sample)

l = root.xpath("./Samples/Sample/Loci/Locus/Name")
locus = l[0].text
print(locus)


regions = root.find("./Samples/Sample/Loci/Locus/AlleleDB/Regions")
regions = [f for f in regions.iter('Region')]
counter_regions = len(regions);
#print(counter_regions)
for region in regions:
    ID = region.get('ID')
    begin = region.get('begin')
    end = region.get('end')
    #print(ID, begin, end)


haplotypes = root.find("./Samples/Sample/Loci/Locus/Haplotypes")
haplotypes = [f for f in haplotypes.iter('Haplotype')]
counter_haplotypes = len(haplotypes)
#print(counter_haplotypes)
for haplotype in haplotypes:
        ID = haplotype.get('ID')
        begin = haplotype.get('begin')
        end = haplotype.get('end')
        sequence = haplotype.text
        #print(ID, begin, end, sequence)


matches = root.find("./Samples/Sample/Loci/Locus/Matching/Matches")
matches = [f for f in matches.iter('Match')]
counter_matches = len(matches)
print("matches encontrados = ", counter_matches)
for match in matches:
        ID = match.get('ID')
        print(ID)
        combinations = match.find("./HaplotypeCombination")
        combinations = [f for f in combinations.iter('HaplotypeID')]
        counter_combinations = len(combinations)
        print("combinações para esse match = ", counter_combinations)
        for combination in combinations:
            haplo = combination.text
