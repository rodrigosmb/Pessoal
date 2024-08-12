lista_compras = []
ids = []

def gerador_id():
    i = 0
    while True:
        i += 1
        if i not in ids:
            ids.append(i)
            break
    ids.sort()
    return i

def menu_opcoes():
    while True:
        print('Menu de opções:')
        print('')
        print('1. Adicionar produto')
        print('2. Remover produto')
        print('3. Pesquisar produto')
        print('4. Sair do programa')
        print('')
        escolha = input('Digite sua escolha: ')
        if escolha not in ['1','2','3','4']:
            print('Escolha inválida, tente novamente.')
            continue
        else:
            return escolha

def adicionar_produto():
    unidades = ['Quilograma','Grama','Litro','Mililitro','Unidade','Metro','Centímetro']
    print('Qual é o produto a ser adicionado?')
    nome = input()
    while True:
        print('Escolha a unidade de medida do produto:')
        print('')
        print('1. Quilograma')
        print('2. Grama')
        print('3. Litro')
        print('4. Mililitro')
        print('5. Unidade')
        print('6. Metro')
        print('7. Centímetro')
        print('')
        unidade = input('Digite sua escolha: ')
        if unidade not in ['1','2','3','4','5','6','7']:
            print('Escolha inválida, tente novamente.')
            continue
        else:
            break
    unidade_atualizada = unidades[int(unidade) - 1]
    quantidade = float(input('Qual é a quantidade desse produto que você precisa: '))
    id = gerador_id()
    produto = {'ID' : id, 'Nome' : nome, 'Quantidade' : quantidade, 'Unidade' : unidade_atualizada}
    lista_compras.insert(id - 1, produto)
    

def remover_produto():
    ID_remover = int(input('Digite o ID do produto a ser removido: '))
    for produto in lista_compras:
        if produto['ID'] == ID_remover:
            lista_compras.remove(produto)
            ids.remove(ID_remover)
            break
    
def pesquisar_produto():
    print('Qual produto deseja pesquisar?')
    busca = input()
    produtos_encontrados = 0
    print()
    print('Os seguintes itens correspondem à pesquisa:')
    for produto in lista_compras:
        if busca.lower() in produto['Nome'].lower():
            produtos_encontrados += 1
            print(produto)
    print('O número de produtos encontrados foi: ', produtos_encontrados)
    print()

print('Olá!')
print('Essa é uma lista de compras simples.')
while True:
    a = 0
    print('Lista de compras:')
    while a < len(lista_compras):
        print(lista_compras[a])
        a += 1
    print()
    escolha = menu_opcoes()
    if escolha == '1':
        adicionar_produto()
    elif escolha == '2':
        remover_produto()
    elif escolha == '3':
        pesquisar_produto()
    else:
        break
        
