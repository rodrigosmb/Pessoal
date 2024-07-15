defesa = []
ataque = []
contagem1 = 0
breakar = False
prim_vitoria = True
vitoria_possivel = False

# Leitura das tropas de defesa

n = int(input())
for i in range(n):
    nov_def = int(input())
    defesa.append(nov_def)

# Leitura das tropas de ataque

m = int(input())
for j in range(m):
    nov_ata = int(input())
    ataque.append(nov_ata)

# Processamento da guerra

for elemento in defesa:
    if breakar == True:
        break
    derrotas = 0
    vitorias = 0
    contagem3 = 0
    time_def = defesa[contagem1:m + contagem1]
    posicao = contagem1 + 1
    contagem1 += 1
    if len(time_def) != m:
        break
    for l in time_def:
        ele_def = l
        contagem3 += 1
        for o in ataque:
            ele_ata = ataque[contagem3-1]
        if ele_ata > ele_def:
            vitorias += 1
        if ele_ata < ele_def:
            derrotas += 1

# Saída de dados
# ...
        if l == time_def[m-1] and vitorias > derrotas and prim_vitoria == True:
            print('Vitória posicionando as tropas a partir da posição', posicao)
            prim_vitoria = False
            vitoria_possivel = True
            break
            breakar = True
# ...
if vitoria_possivel == False:
    print('Derrota')
