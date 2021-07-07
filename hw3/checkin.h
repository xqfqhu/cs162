#ifndef CHECKIN_H
#define CHECKIN_H

#include <pthread.h>
#include "list.h"
#include "player.h"

// TODO: Hint! Define a struct here.

void init_checkin_system();

void player_checkin(pthread_mutex_t *lock, player_t *player);

void player_checkout(pthread_mutex_t *lock, player_t *player);

char *get_team_on_field(pthread_mutex_t *lock);

#endif // CHECKIN_H
