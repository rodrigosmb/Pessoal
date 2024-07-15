# Leitura do tabuleiro
T = int(input())
tabuleiro = []
for _ in range(T):
    tabuleiro.append(input().split())

# Leitura da peça
P = int(input())
peca = []
for _ in range(P):
    peca.append(input().split())

# Processamento

zero = 0
noventa = 0
cent_oitenta = 0
duz_setenta = 0

def gira_dir(x):
  girada_90 = []
  contagem = len(x)
  for i in range(len(x[0])):
    linha = []
    for j in range(len(x)):
      contagem -= 1
      linha.append(peca[contagem][i])
    contagem = 0
    girada_90.append(linha)
  return girada_90

def cabe(i,j):
  for a in range(len(peca)):
    for b in range(len(peca[0])):
      if peca[a][b] == tabuleiro[i+a][j+b]:
        if peca[a][b] == "X" and tabuleiro[i+a][j+b] == "X":
          return False
  return True

for c in range(len(tabuleiro)-len(peca)+1):
  for d in range(len(tabuleiro[0])-len(peca[0])+1):
    if cabe(c,d) == True:
      zero += 1

peca = gira_dir(peca)
for e in range(len(tabuleiro)-len(peca)+1):
  for f in range(len(tabuleiro[0])-len(peca[0])+1):
    if cabe(e,f) == True:
      noventa += 1

peca = gira_dir(peca)
for g in range(len(tabuleiro)-len(peca)+1):
  for h in range(len(tabuleiro[0])-len(peca[0])+1):
    if cabe(g,h) == True:
      cent_oitenta += 1

peca = gira_dir(peca)
for o in range(len(tabuleiro)-len(peca)+1):
  for p in range(len(tabuleiro[0])-len(peca[0])+1):
    if cabe(o,p) == True:
      duz_setenta += 1

# Impressão do resultado
print(str(zero)+","+str(noventa)+","+str(cent_oitenta)+","+str(duz_setenta))