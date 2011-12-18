#ifndef _DATE_H
#define _DATE_H 1

#include "types.h"

bool anneeBissextile(const DATE date);
short joursMois(const DATE date);
bool datePassee(const DATE date);
bool dateValide(const DATE date);
short age(const DATE date);

#endif
