#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#include "checkin.h"
#include "player.h"

#define USEC_TO_SEC 1000000

pthread_mutex_t lock;

typedef struct player_schedule {
  player_t *player;
  unsigned int arrival_time; /* Time before a player arrives and checks in */
  unsigned int play_time; /* Time that a player plays on the field */
} player_schedule_t;

void simulate_player(player_schedule_t *player_schedule) {
  // Player has not arrived at the field yet.
  usleep(player_schedule->arrival_time);

  // Player checks in and waits to enter the field.
  pthread_mutex_lock(&lock);
  printf("%s player checking in!\n", player_schedule->player->team);
  player_checkin(&lock, player_schedule->player);
  printf("%s player entered field!\n", player_schedule->player->team);
  pthread_mutex_unlock(&lock);

  // Player plays on the field.
  usleep(player_schedule->play_time);

  pthread_mutex_lock(&lock);
  // SANITY CHECK: Verify that the player's team is still on the field.
  char *team = get_team_on_field(&lock);
  if (team == NULL || strcmp(team, player_schedule->player->team)) {
    printf("Something went wrong! %s (expected team) is not equal to %s (actual team).\n",
        player_schedule->player->team, team);
    exit(1);
  }

  // Player checks out and exits the field when their teammates have also checked out.
  printf("%s player checking out!\n", player_schedule->player->team);
  player_checkout(&lock, player_schedule->player);  
  printf("%s player exited field!\n", player_schedule->player->team);
  pthread_mutex_unlock(&lock);
}

void *run_simulation(void *arg) {
  player_schedule_t *player_schedule = (player_schedule_t *) arg;
  simulate_player(player_schedule);

  free(player_schedule->player);
  free(player_schedule);
  return NULL;
}

void create_new_player(pthread_t *thread, char *team, double arrival_time, double play_time) {
  player_schedule_t *player_schedule = malloc(sizeof(player_schedule_t));
  player_schedule->player = malloc(sizeof(player_t));
  player_schedule->player->team = team;
  player_schedule->arrival_time = (unsigned int) arrival_time * USEC_TO_SEC;
  player_schedule->play_time = (unsigned int) play_time * USEC_TO_SEC;
  pthread_create(thread, NULL, run_simulation, (void *) player_schedule);
}

void manual_test() {
  // TODO: Modify this to run more complex tests.
  int num_players = 3;
  pthread_t *threads = malloc(num_players * sizeof(pthread_t));

  create_new_player(&threads[0], "Gryffindor", 0, 0);
  create_new_player(&threads[1], "Gryffindor", 0.5, 0);
  create_new_player(&threads[2], "Slytherin", 1, 0.5);

  for (int i = 0; i < num_players; i++) {
    pthread_join(threads[i], NULL);
  }

  free(threads);
}

int main() {
  pthread_mutex_init(&lock, NULL);

  // Initialize the checkin system.
  init_checkin_system();

  // Simulate players arriving and playing.
  manual_test();
}
