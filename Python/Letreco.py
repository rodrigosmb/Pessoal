acertou = False

# Leitura da palavra
palavra = input()

# Leitura dos palpites e impressão do resultado para cada palpite
for i in range(6):
    tentativa = input()
    for j in range(len(tentativa)):
        if tentativa[j] == palavra[j]:
            print(tentativa[j].upper(), end="")
        elif tentativa[j] in palavra:
            print(tentativa[j], end="")
        else:
            print("_", end="")
    print("")

# Impressão da linha final
# ...
    if tentativa == palavra:
        acertou = True
        print("PARABÉNS!!!")
        print("Resposta correta")
        break
# ...
if acertou == False:
    print("Mais sorte da próxima vez!")
    print("Palavra correta:", palavra)
