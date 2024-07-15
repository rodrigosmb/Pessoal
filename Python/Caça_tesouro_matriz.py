contagem = 0

# Leitura da matriz

n = int(input())
matriz = [input().split() for _ in range(n)]

# Leitura e processamento dos caminhos
N = 0
S = 0
L = 0
O = 0
prim_time = input()
nº_jogadas = int(input())
X = 0
Y = 0

for i in range(nº_jogadas):
    movimentos = input()
    for j in range(len(movimentos)):
        movimento = movimentos[contagem]
        contagem += 1
        if movimento == "N":
            N += 1
        elif movimento == "S":
            S += 1
        elif movimento == "O":
            O += 1
        elif movimento == "L":
            L += 1
        linha = 0 - N + S
        coluna = 0 + L - O
        posicao = matriz[linha][coluna]

        if prim_time == "azul" and (i % 2) == 0:
            if posicao == "*":
                X += 1
        if prim_time != "azul" and (i % 2) != 0:
            if posicao == "*":
                X += 1
        if prim_time == "vermelho" and (i % 2) == 0:
            if posicao == "*":
                Y += 1
        if prim_time != "vermelho" and (i % 2) != 0:
            if posicao == "*":
                Y += 1
        if posicao == "*":
            matriz[linha][coluna] = "."
    contagem = 0
    linha = 0
    coluna = 0
    N = 0
    S = 0
    L = 0
    O = 0

# Impressão da saída
print("Tesouros encontrados pelo time azul:", X)
print("Tesouros encontrados pelo time vermelho:", Y)
if X > Y:
    print("Vitoria do time azul")
elif X < Y:
    print("Vitoria do time vermelho")
else:
    print("Empate")
