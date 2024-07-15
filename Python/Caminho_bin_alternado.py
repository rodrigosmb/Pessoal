"""
Essa função recebe como parâmetro uma matriz que representa o tabuleiro,
uma posição atual (linha_atual, coluna_atual) no tabuleiro, uma posição
final (linha_fim, coluna_fim) desejada e o parâmetro cor indica a cor da
última posição visitada no caminho.
O retorno esperado para a função é um valor booleano, com True indicando
que foi possível encontrar um caminho e False indicando que não existe um
caminho.
"""
tentouC = []
tentouB = []
tentouD = []
tentouE = []

def caminho(tabuleiro, linha_atual, coluna_atual, linha_fim, coluna_fim, cor):
    flag = False
    breakar = False
    if str(linha_atual)+str(coluna_atual) in tentouC or str(linha_atual)+str(coluna_atual) in tentouB\
            or str(linha_atual)+str(coluna_atual) in tentouD or str(linha_atual)+str(coluna_atual) in tentouE:
        flag = True
        breakar = True
    #CIMA
    if linha_atual > 0 and tabuleiro[linha_atual-1][coluna_atual] == 0 and cor == "preta" and\
            flag is False and str(linha_atual)+str(coluna_atual) not in tentouC:

        linha_atual -= 1
        flag = True
        tentouC.append(str(linha_atual)+str(coluna_atual))

    if linha_atual > 0 and tabuleiro[linha_atual - 1][coluna_atual] != 0 and cor == "branca" and \
            flag is False and str(linha_atual) + str(coluna_atual) not in tentouC:

        linha_atual -= 1
        flag = True
        tentouC.append(str(linha_atual) + str(coluna_atual))

    #BAIXO
    if linha_atual < L and tabuleiro[linha_atual+1][coluna_atual] == 0 and cor == "preta" and\
            flag is False and str(linha_atual)+str(coluna_atual) not in tentouB:

        linha_atual += 1
        flag = True
        tentouB.append(str(linha_atual)+str(coluna_atual))

    if linha_atual < L and tabuleiro[linha_atual + 1][coluna_atual] != 0 and cor == "branca" and \
            flag is False and str(linha_atual) + str(coluna_atual) not in tentouB:
        linha_atual += 1
        flag = True
        tentouB.append(str(linha_atual) + str(coluna_atual))

    #DIREITA
    if coluna_atual < len(tabuleiro[0]) - 1 and tabuleiro[linha_atual][coluna_atual + 1] == 0 and cor == "preta" and \
            flag is False and str(linha_atual) + str(coluna_atual) not in tentouD:
        coluna_atual += 1
        flag = True
        tentouD.append(str(linha_atual) + str(coluna_atual))

    if coluna_atual < len(tabuleiro[0]) - 1 and tabuleiro[linha_atual][coluna_atual + 1] != 0 and cor == "branca" and \
            flag is False and str(linha_atual) + str(coluna_atual) not in tentouD:
        coluna_atual += 1
        flag = True
        tentouD.append(str(linha_atual) + str(coluna_atual))

    #ESQUERDA
    if coluna_atual > 0 and tabuleiro[linha_atual][coluna_atual - 1] == 0 and cor == "preta" and \
            flag is False and str(linha_atual) + str(coluna_atual) not in tentouE:
        coluna_atual -= 1
        flag = True
        tentouE.append(str(linha_atual) + str(coluna_atual))

    if coluna_atual > 0 and tabuleiro[linha_atual][coluna_atual - 1] != 0 and cor == "branca" and \
            flag is False and str(linha_atual) + str(coluna_atual) not in tentouE:
        coluna_atual -= 1
        tentouE.append(str(linha_atual) + str(coluna_atual))

    if linha_atual == linha_fim and coluna_atual == coluna_fim:
        return True
    else:
        return [False, linha_atual, coluna_atual, breakar]

# Leitura dos dados

L = int(input())
tabuleiro = [input().split() for _ in range(L)]
l1, c1, l2, c2 = [int(i) for i in input().split()]

# Verificação se existe um caminho
linha_atual = l1
coluna_atual = c1
linha_fim = l2
coluna_fim = c2
if tabuleiro[l1][c1] == 0:
    cor = "branca"
else:
    cor = "preta"
while True:
    move = caminho(tabuleiro, linha_atual, coluna_atual, linha_fim, coluna_fim, cor)
    breakar = move[3]
    if breakar is True:
        print("caminho nao encontrado")
        break
    if move is True:
        print("caminho encontrado")
    else:
        linha_atual = move[1]
        coluna_atual = move[2]
        if tabuleiro[linha_atual][coluna_atual] == 0:
            cor = "branca"
        else:
            cor = "preta"
