import os

# exemplo alterado de  EX_10.5.py para 10_5.py
for nome in os.listdir('./arquivos'):
    # alterar conforme sua necessidade de geração de nomes e layout de arquivos    
    dados = str(nome).split(".")
    numero = dados[0].split("_")[1]
    subnumero = dados[1]
    novo_nome = numero + "_" + subnumero + ".py"
    
    os.rename("./arquivos/"+nome, "./arquivos/"+novo_nome)
    print("arquivo " + nome + " alterado para " + novo_nome)
