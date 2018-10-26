#include "player.h"

player * new_player(char * name) {
    player * p_player = (player *)malloc(sizeof(player));  /* Create new player */
    if (p_player == NULL) { return NULL; }

    card_stack * deck = new_card_stack(10);     /* Create new deck */
    if (deck == NULL) { return NULL; }

    card_stack * hand = new_card_stack(5);      /* Create new hand */
    if (hand == NULL) { return NULL; }

    card_stack * discard = new_card_stack(10);  /* Create new discard pile */
    if (discard == NULL) { return NULL; }

    card_stack * play_area = new_card_stack(5); /* Create new discard pile */
    if (play_area == NULL) { return NULL; }

    int8_t i;
    for (i = 0; i < 8; ++i) {
        p_player->name[i] = name[i];
    }
    p_player->name[i] = '\0';

    p_player->victory_points = 0;     /* VP initialized to 0 */
    p_player->actions = 1;            /* Actions initialized to 1 */
    p_player->buys = 1;               /* Buys initialized to 1 */
    p_player->deck = deck;            /* set deck */
    p_player->hand = hand;            /* set hand */
    p_player->discard = discard;      /* set discard */
    p_player->play_area = play_area;  /* set play_area */

    return p_player;
}
