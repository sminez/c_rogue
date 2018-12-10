#include "colors.h"
#include "mob.h"


Mob* mob_new_goblin(int level) {
    return mob_new('g', "goblin", FADED_GREEN, 1, 1, 1, 1, 5, 5);
}