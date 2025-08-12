#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define DEFENSE_BOOST 2
#define MAX_HEALTH 100

enum ACTIONS {
    ATTACK = 1, DEFEND, REST
};

typedef struct {
    char name[20];
    float health;
    float damage;
    float defense;
    int cures;
} Entity;

void printUI(Entity *player, Entity *enemy);

void printInstructions();

void sortAction(Entity *actioner, Entity *target, const int *action, int *invalid);

void attack(Entity *attacker, Entity *target);

void defend(Entity *target);

void heal(Entity *target);

int main() {
    srand(time(NULL));

    Entity player = {"Player", MAX_HEALTH, 25.2f, 3.2f, 3};
    Entity enemy = {"Enemy", MAX_HEALTH, 27.8f, 5.3f, 4};
    int gameOver = 0, currentTurn = 0, action = 0, isActionInvalid = 0;
    char *winner = malloc(sizeof(char) * 20);

    while (!gameOver) {
        system("clear");
        printUI(&player, &enemy);

        if (currentTurn % 2 == 0) {
            // player's turn
            printInstructions();
            scanf("%d", &action);

            sortAction(&player, &enemy, &action, &isActionInvalid);
        } else {
            // enemy's turn
            printf("%s's turn...", enemy.name);
            sleep(1);
            action = rand() % (3 + 1 - 1) + 1;

            sortAction(&enemy, &player, &action, &isActionInvalid);
        }

        if (!isActionInvalid) {
            currentTurn++;
        }

        isActionInvalid = 0;

        if (player.health <= 0) {
            gameOver = 1;
            strcpy(winner, enemy.name);
        } else if (enemy.health <= 0) {
            gameOver = 1;
            strcpy(winner, player.name);
        }

        sleep(2);
    }

    system("clear");
    printf("%s wins!", winner);
    free(winner);
    return 0;
}

void printUI(Entity *player, Entity *enemy) {
    printf("Player:\t\tEnemy:\n"
           "Health: %.1f\tHealth: %.1f\n"
           "Damage: %.1f\tDamage: %.1f\n"
           "Defense: %.1f\tDefense: %.1f\n"
           "Cures: %d\tCures: %d\n",
           player->health, enemy->health,
           player->damage, enemy->damage,
           player->defense, enemy->defense,
           player->cures, enemy->cures);
}

void printInstructions() {
    puts("Your turn...");
    printf("Instructions:\n"
        "1) Attack "
        "2) Defend "
        "3) Rest\n"
    );
}

void sortAction(Entity *actioner, Entity *target, const int *action, int *invalid) {
    switch (*action) {
        default:
            puts("Invalid action.");
            *invalid = 1;
            break;
        case ATTACK:
            attack(actioner, target);
            break;
        case DEFEND:
            defend(actioner);
            break;
        case REST:
            heal(actioner);
            break;
    }
}

void attack(Entity *attacker, Entity *target) {
    printf("\n%s attacks %s\n", attacker->name, target->name);
    target->health -= attacker->damage - target->defense;
}

void defend(Entity *target) {
    printf("\n%s defends himself\n", target->name);
    target->defense += DEFENSE_BOOST;
}

void heal(Entity *target) {
    if (target->cures == 0) {
        printf("\n%s cannot heal anymore\n", target->name);
        return;
    }

    if (target->health == MAX_HEALTH) {
        puts("\nAlready max health");
        return;
    }

    printf("\n%s rests\n", target->name);
    target->health += 10;

    if (target->health > MAX_HEALTH) {
        float healthOver = MAX_HEALTH - target->health;
        target->health -= healthOver;
    }
    target->cures--;
}
