#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "checkin.h"
#include "debug.h"

// TODO: Hint! Add some global variables here.

/* Initialize the checkin system */
void init_checkin_system() {
  // TODO
  return;
}

/* Check in a new player. Block until there is no team on the field or the
 * player's team is on the field. Entering this function indicates that the
 * player is checking in. Returning from this function indicates that the
 * player has entered the field. */
void player_checkin(pthread_mutex_t *lock, player_t *player) {
  // TODO
  return;
}

/* Check out a player on the field. Block until all other players on the field
 * have also checked out. Entering this function indicates that the player is
 * checking out. Returning from this function indicates that the player has
 * exited the field. */
void player_checkout(pthread_mutex_t *lock, player_t *player) {
  // TODO
  return;
}

/* Return the name of the team that is currently playing on the field */
char *get_team_on_field(pthread_mutex_t *lock) {
  // TODO
  return NULL;
}
