#include <stdio.h>

int damage;
int HP_Ryu;
int Ryu_damage;
int HP_Ken;
int Ken_damage;
int won = 0;
int Ryu_hits = 0;
int Ken_hits = 0;

int main() {

    scanf("%d", &HP_Ryu);
    scanf("%d", &HP_Ken);

    while (won == 0){  
        scanf("%d", &damage);

        if (damage > 0){
            Ryu_hits++;
            Ryu_damage = damage;
            HP_Ken = HP_Ken - Ryu_damage;
            if (HP_Ken < 0){
                HP_Ken = 0;
            }
            printf("RYU APLICOU UM GOLPE: %d\n", Ryu_damage);
            printf("HP RYU = %d\n", HP_Ryu);
            printf("HP KEN = %d\n", HP_Ken);
            if (HP_Ken == 0){
                printf("LUTADOR VENCEDOR: RYU\n");
                printf("GOLPES RYU = %d\n", Ryu_hits);
                printf("GOLPES KEN = %d\n", Ken_hits);
                won = 1;
            }
        }

        if (damage < 0){
            Ken_hits++;
            Ken_damage = -damage;
            HP_Ryu = HP_Ryu - Ken_damage;
            if (HP_Ryu < 0){
                HP_Ryu = 0;
            }
            printf("KEN APLICOU UM GOLPE: %d\n", Ken_damage);
            printf("HP RYU = %d\n", HP_Ryu);
            printf("HP KEN = %d\n", HP_Ken);
            if (HP_Ryu == 0){
                printf("LUTADOR VENCEDOR: KEN\n");
                printf("GOLPES RYU = %d\n", Ryu_hits);
                printf("GOLPES KEN = %d\n", Ken_hits);
                won = 1;
            }
        }
    }
    return 0;
}