# Leitura do valor da hora
V = int(input())

# Leitura do numero de dias trabalhados na semana
D = int(input())

# Leitora e processamento dos periodos de trabalho de cada dia
f1 = 0
i1 = 0
f2 = 0
i2 = 0
f3 = 0
i3 = 0
f4 = 0
i4 = 0
f5 = 0
i5 = 0
f6 = 0
i6 = 0
f7 = 0
i7 = 0
horas_extrasD = 0
finais = 0
inicios = 0

for h in range(D):
    
    if h == 0 and D >= 1:
        P1 = int(input())
        for j in range(P1 * 2):
            ini_fin1 = int(input())
            if (j % 2) != 0:
                f1 += ini_fin1
            else:
                i1 += ini_fin1
            hd1 = f1 - i1
        if hd1 > 8:
            horas_extrasD += (hd1-8)

    if h == 1 and D >= 2:
        P2 = int(input())
        for j in range(P2 * 2):
            ini_fin2 = int(input())
            if (j % 2) != 0:
                f2 += ini_fin2
            else:
                i2 += ini_fin2
            hd2 = f2 - i2
        if hd2 > 8:
            horas_extrasD += (hd2-8)

    if h == 2 and D >= 3:
        P3 = int(input())
        for j in range(P3 * 2):
            ini_fin3 = int(input())
            if (j % 2) != 0:
                f3 += ini_fin3
            else:
                i3 += ini_fin3
            hd3 = f3 - i3
        if hd3 > 8:
            horas_extrasD += (hd3-8)

    if h == 3 and D >= 4:
        P4 = int(input())
        for j in range(P4 * 2):
            ini_fin4 = int(input())
            if (j % 2) != 0:
                f4 += ini_fin4
            else:
                i4 += ini_fin4
            hd4 = f4 - i4
        if hd4 > 8:
            horas_extrasD += (hd4-8)

    if h == 4 and D >= 5:
        P5 = int(input())
        for j in range(P5 * 2):
            ini_fin5 = int(input())
            if (j % 2) != 0:
                f5 += ini_fin5
            else:
                i5 += ini_fin5
            hd5 = f5 - i5
        if hd5 > 8:
            horas_extrasD += (hd5-8)

    if h == 5 and D >= 6:
        P6 = int(input())
        for j in range(P6 * 2):
            ini_fin6 = int(input())
            if (j % 2) != 0:
                f6 += ini_fin6
            else:
                i6 += ini_fin6
            hd6 = f6 - i6
        if hd6 > 8:
            horas_extrasD += (hd6-8)

    if h == 6 and D >= 7:
        P7 = int(input())
        for j in range(P7 * 2):
            ini_fin7 = int(input())
            if (j % 2) != 0:
                f7 += ini_fin7
            else:
                i7 += ini_fin7
            hd7 = f7 - i7
        if hd7 > 8:
            horas_extrasD += (hd7-8)
    
if D == 1:
    horas_trabalhadas = hd1
elif D == 2:
    horas_trabalhadas = hd1 + hd2
elif D == 3:
    horas_trabalhadas = hd1 + hd2 + hd3
elif D == 4:
    horas_trabalhadas = hd1 + hd2 + hd3 + hd4
elif D == 5:
    horas_trabalhadas = hd1 + hd2 + hd3 + hd4 + hd5
elif D == 6:
    horas_trabalhadas = hd1 + hd2 + hd3 + hd4 + hd5 + hd6
else:
    horas_trabalhadas = hd1 + hd2 + hd3 + hd4 + hd5 + hd6 + hd7
    
if horas_trabalhadas - horas_extrasD > 44:
    horas_extraS = horas_trabalhadas - horas_extrasD - 44
    horas_extras = horas_extraS + horas_extrasD

else:
    horas_extras = horas_extrasD

# Calculo do valor devido ao funcionário

valor = (horas_trabalhadas - horas_extras) * V + horas_extras * V * 1.5

# Impressão da saída

print("Horas trabalhadas:", horas_trabalhadas)
print("Horas extras:", horas_extras)
print("Valor devido: R$ {:0.2f}".format(valor))