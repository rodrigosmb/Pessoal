# Programa para calcular valor do ingresso no cinema

dia_semana = int(input())
hora_inicio = input()
minuto_inicio = input()
estudante = input()
metodo = input()

horario = int(hora_inicio + minuto_inicio)

if horario < 1830:
    periodo = "diurno"
else:
    periodo = "noturno"


# valor do ingresso inteiro

if dia_semana == 1:
    ingresso_ini = 30
    if metodo == "C":
        ingresso_int = ingresso_ini * 0.7
    else:
        ingresso_int = ingresso_ini

if dia_semana == 2 and periodo == "diurno":
    ingresso_ini = 15
    if metodo == "C":
        ingresso_int = ingresso_ini * 0.5
    else:
        ingresso_int = ingresso_ini

if dia_semana == 2 and periodo == "noturno":
    ingresso_ini = 20
    if metodo == "C":
        ingresso_int = ingresso_ini * 0.5
    else:
        ingresso_int = ingresso_ini

if dia_semana == 3 and periodo == "diurno":
    ingresso_ini = 15
    if metodo == "C":
        ingresso_int = ingresso_ini * 0.5
    else:
        ingresso_int = ingresso_ini

if dia_semana == 3 and periodo == "noturno":
    ingresso_ini = 20
    if metodo == "C":
        ingresso_int = ingresso_ini * 0.5
    else:
        ingresso_int = ingresso_ini

if dia_semana == 4 and periodo == "diurno":
    ingresso_ini = 15
    if metodo == "C":
        ingresso_int = ingresso_ini * 0.5
    else:
        ingresso_int = ingresso_ini

if dia_semana == 4 and periodo == "noturno":
    ingresso_ini = 30
    if metodo == "C":
        ingresso_int = ingresso_ini * 0.5
    else:
        ingresso_int = ingresso_ini

if dia_semana == 5 and periodo == "diurno":
    ingresso_ini = 20
    if metodo == "C":
        ingresso_int = ingresso_ini * 0.5
    else:
        ingresso_int = ingresso_ini

if dia_semana == 5 and periodo == "noturno":
    ingresso_ini = 30
    if metodo == "C":
        ingresso_int = ingresso_ini * 0.5
    else:
        ingresso_int = ingresso_ini

if dia_semana == 6 and periodo == "diurno":
    ingresso_ini = 20
    if metodo == "C":
        ingresso_int = ingresso_ini * 0.5
    else:
        ingresso_int = ingresso_ini

if dia_semana == 6 and periodo == "noturno":
    ingresso_ini = 40
    if metodo == "C":
        ingresso_int = ingresso_ini * 0.7
    else:
        ingresso_int = ingresso_ini

if dia_semana == 7 and periodo == "diurno":
    ingresso_ini = 30
    if metodo == "C":
        ingresso_int = ingresso_ini * 0.8
    else:
        ingresso_int = ingresso_ini

if dia_semana == 7 and periodo == "noturno":
    ingresso_ini = 40
    if metodo == "C":
        ingresso_int = ingresso_ini * 0.8
    else:
        ingresso_int = ingresso_ini

# valor a pagar

if estudante == "S":
    ingresso = ingresso_ini * 0.5
else:
    ingresso = ingresso_int

# saída do valor do ingresso
print('Valor do ingresso: R$', format(ingresso, '.2f').replace('.', ','))