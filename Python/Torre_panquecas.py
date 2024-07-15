# Leitura da torre de panquecas
torre = [int(panqueca) for panqueca in input().split()]
torre_ini = torre.copy()

# Leitura e processamento dos movimentos
while True:
    M = int(input())
    if M == 0:
        break
    torre_int = torre[:M]
    contagem = 0
    while contagem < M:
        torre.pop(0)
        contagem += 1
    torre.reverse()
    torre.extend(torre_int)
    torre.reverse()

# Impressão da saída
if sorted(torre_ini) != torre:
    print("Torre instavel")
else:
    print("Torre estavel")
