#include "player.h"

struct player * new_player(char * name) {
    struct player * p_player = (struct player *)malloc(sizeof(struct player));  /* Create new player */
    if (p_player == NULL) { return NULL; }

    struct card_stack * deck = new_card_stack(10);                              /* Create new deck */
    if (deck == NULL) { return NULL; }

    struct card_stack * hand = new_card_stack(5);                               /* Create new hand */
    if (hand == NULL) { return NULL; }

    struct card_stack * discard = new_card_stack(10);                           /* Create new discard pile */
    if (discard == NULL) { return NULL; }

    p_player->name = name;                                                      /* Set name */
    p_player->victory_points = 0;                                               /* VP initialized to 0 */
    p_player->deck = deck;                                                      /* set deck */
    p_player->hand = hand;                                                      /* set hand */
    p_player->discard = discard;                                                /* set discard */

    return p_player;
}
