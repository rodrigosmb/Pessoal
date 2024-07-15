# Leitura de dados
estoque = {}
contagem = 0
ped_compra = []
ped_venda = []

while True:
    entrada = input()

# Processamento

    if entrada == "FIM":
        break
    else:
        entradas = entrada.split()
        X = int(entradas[-1])
        inter = entradas[:-2]
        inter1 = str(inter).strip("[]")
        for i in "',":
            inter1 = inter1.replace(i, "")
        N = inter1
        if N in estoque.keys() and X >= 0:
            valor_anterior = estoque.pop(N)
            novo_valor = valor_anterior + X
            estoque[N] = novo_valor
            valor_anterior = 0
            novo_valor = 0
            ped_compra.append(N)
        elif N not in estoque.keys() and X >= 0:
            estoque[N] = X
            ped_compra.append(N)
        elif N in estoque.keys() and X < 0:
            valor_anteriorN = estoque.pop(N)
            if valor_anteriorN >= abs(X):
                novo_valorN = valor_anteriorN + X
                estoque[N] = novo_valorN
                ped_venda.append(N)
            elif valor_anteriorN < abs(X):
                estoque[N] = valor_anteriorN
                X = str(abs(X))
                # ...
                print("Quantidade indisponivel para a venda de " + X + " unidade(s) do produto " + N + ".")
            valor_anteriorN = 0
            novo_valorN = 0
        else:
            X = str(abs(X))
            # ...
            print("Quantidade indisponivel para a venda de " + X + " unidade(s) do produto " + N + ".")

keys = sorted(estoque)
# Impressão da saída
#...
for j in range(len(keys)):
    contagem += 1
    N = keys[contagem-1]
    E = str(estoque[keys[contagem-1]])
    C = str(ped_compra.count(N))
    V = str(ped_venda.count(N))
    print("Produto: " + N)
    print("Quantidade em Estoque: " + E)
    print("Pedidos de Compra: " + C)
    print("Pedidos de Venda: " + V)
