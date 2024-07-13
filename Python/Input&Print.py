distancia_SpaceX = int(input())
vel_SpaceX = int(input())
intervalo = int(input())
distancia_BlueOrigin = int(input())
vel_BlueOrigin = int(input())

# Cálculo do tempo total gasto por cada espaçonave

tempo_SpaceX = distancia_SpaceX/vel_SpaceX
tempo_BlueOrigin = distancia_BlueOrigin/vel_BlueOrigin

# Impressão da resposta

print(tempo_SpaceX < (intervalo * 24) + tempo_BlueOrigin)