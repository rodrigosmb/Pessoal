votos = {}
tot_votos = []
candidatos = []
cont_brancos = 0
cont_nulos = 0

# Leitura de dados
while True:
    voto = input()

    if voto == "0":
        break
    if voto != "Nulo" and voto != "Branco":
        if voto not in tot_votos:
            candidatos.append(voto)
    if voto == "Branco":
        cont_brancos += 1
    elif voto == "Nulo":
        cont_nulos += 1
    else:
        tot_votos.append(voto)

for j in range(len(candidatos)):
    votos[tot_votos.count(candidatos[j])] = candidatos[j]
votos_organizados = list(votos.keys())
votos_organizados.sort(reverse=True)

# Saída de dados
for k in range(len(candidatos)):
    print(votos[votos_organizados[k]], str(votos_organizados[k]))
print("Brancos", str(cont_brancos))
print("Nulos", str(cont_nulos))