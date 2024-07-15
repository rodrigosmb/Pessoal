# leitura da imagem
_ = input()  # P2 - linha a ser ignorada

m, n = [int(x) for x in input().split()]

_ = input()  # 255 - linha a ser ignorada

imagem_original = []
for i in range(n):
    linha = [int(x) for x in input().split()]
    imagem_original.append(linha)

def imprimir_imagem(imagem):
    print("P2")
    print(len(imagem[0]), len(imagem))
    print("255")
    for i in range(len(imagem)):
        print(" ".join(str(int(x)) for x in imagem[i]))

def expansao(imagem_original):
    expandida = []
    contL = 0
    contC = 0
    for i in range(2*n - 1):
        linha = []
        for j in range(2*m - 1):
            linha.append(0)
        expandida.append(linha)

    for k in range(2*n - 1):
        for l in range(2*m - 1):
            if k % 2 == 0 and l % 2 == 0:
                if contC == m:
                    contC = 0
                    contL += 1
                expandida[k][l] = imagem_original[contL][contC]
                contC += 1
    for a in range(2*n - 1):
        for b in range(2*m - 1):
            if b != 0 and a % 2 == 0 and b % 2 == 0:
                expandida[a][b - 1] = int((expandida[a][b] + ult_valor)/2)
            if a % 2 == 0 and b % 2 == 0:
                ult_valor = expandida[a][b]
    for c in range(2*n - 3):
        for d in range(2*m - 1):
            if c % 2 == 0 and d % 2 == 0:
                expandida[c + 1][d] = int((expandida[c][d] + expandida[c + 2][d])/2)
    for e in range(2*n - 1):
        for f in range(2*m - 1):
            if f != 0 and e % 2 != 0 and f % 2 == 0:
                expandida[e][f - 1] = int((expandida[e][f] + expandida[e][f - 2])/2)
    return expandida

def retracao(imagem_original):
    contC = 0
    contL = 0
    reduzida = []

    if n % 2 == 0 and m % 2 == 0:
        for i in range(int(n/2)):
            linha = []
            for j in range(int(m/2)):
                linha.append(0)
            reduzida.append(linha)
        for a in range(int(n/2)):
            for b in range(int(m/2)):
                if contC == m:
                    contC = 0
                    contL += 2
                reduzida[a][b] = int((imagem_original[contL][contC] + imagem_original[contL + 1][contC]
                                     + imagem_original[contL][contC + 1] + imagem_original[contL + 1][contC + 1])/4)
                contC += 2
    elif n % 2 != 0 and m % 2 == 0:
        for i in range(int(n/2) + 1):
            linha = []
            for j in range(int(m/2)):
                linha.append(0)
            reduzida.append(linha)
        for c in range(int(n/2)):
            for d in range(int(m/2)):
                if contC == m:
                    contC = 0
                    contL += 2
                reduzida[c][d] = int((imagem_original[contL][contC] + imagem_original[contL + 1][contC]
                                     + imagem_original[contL][contC + 1] + imagem_original[contL + 1][contC + 1])/4)
                contC += 2
        contC = 0
        for d in range(int(m/2)):
            reduzida[-1][d] = int((imagem_original[-1][contC] + imagem_original[-1][contC + 1])/2)
            contC += 2
    elif m % 2 != 0 and n % 2 == 0:
        for i in range(int(n/2)):
            linha = []
            for j in range(int(m/2) + 1):
                linha.append(0)
            reduzida.append(linha)
        for e in range(int(n/2)):
            for f in range(int(m/2)):
                if contC == m-1:
                    contC = 0
                    contL += 2
                reduzida[e][f] = int((imagem_original[contL][contC] + imagem_original[contL + 1][contC]
                                     + imagem_original[contL][contC + 1] + imagem_original[contL + 1][contC + 1])/4)
                contC += 2
        contL = 0
        for g in range(int(n/2)):
            reduzida[g][-1] = int((imagem_original[contL][-1] + imagem_original[contL + 1][-1])/2)
            contL += 2

    elif n % 2 != 0 and m % 2 != 0:
        for i in range(int(n/2) + 1):
            linha = []
            for j in range(int(m/2) + 1):
                linha.append(0)
            reduzida.append(linha)
        for h in range(int(n/2)):
            for k in range(int(m/2)):
                if contC == m-1:
                    contC = 0
                    contL += 2
                reduzida[h][k] = int((imagem_original[contL][contC] + imagem_original[contL + 1][contC]
                                     + imagem_original[contL][contC + 1] + imagem_original[contL + 1][contC + 1])/4)
                contC += 2
        contC = 0
        for l in range(int(m/2)):
            reduzida[-1][l] = int((imagem_original[-1][contC] + imagem_original[-1][contC + 1])/2)
            contC += 2
        contL = 0
        for o in range(int(n / 2)):
            reduzida[o][-1] = int((imagem_original[contL][-1] + imagem_original[contL + 1][-1])/2)
            contL += 2
        reduzida[-1][-1] = imagem_original[-1][-1]
    return(reduzida)

# leitura do tipo de redimensionamento
tipo = input()

# impressão da imagem final
if tipo == "expansao":
    imagem = expansao(imagem_original)
    imprimir_imagem(imagem)
if tipo == "retracao":
    imagem = retracao(imagem_original)
    imprimir_imagem(imagem)

