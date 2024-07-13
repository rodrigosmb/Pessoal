# leitura da sequência de compras e vendas

estoque = 0
contagem = 0
vendas_indisponiveis = []

while True:
    inp = int(input())

    if inp == 0:
        break
    if inp < 0:
        if abs(inp) > estoque:
            vendas_indisponiveis.append(inp)
        else:
            estoque += inp
            contagem += 1
    else:
        estoque += inp

# impressão da saída

for i in vendas_indisponiveis:
    print("Quantidade indisponível para a venda de", abs(i), "unidades.")

print("Quantidade de vendas realizadas:", contagem)
print("Quantidade em estoque:", estoque)