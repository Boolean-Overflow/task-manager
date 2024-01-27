#ifndef __TEAMS__
#define __TEAMS__
#include "../user/user.h"


typedef struct Team {
  User* manager, * members;
} Team;

#endif
