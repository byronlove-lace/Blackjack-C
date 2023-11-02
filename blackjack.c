#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_HAND 12
#define MAX_CARD_NAME 22
#define DECK_TOTAL 52
#define SUIT_COUNT 4
#define NUM_COUNT 10
#define FACE_COUNT 3
#define MAX_PLAYERS 7
#define VAL_LEN 6

void assemble(const char const *suits[], const char const *nums[], const char const *faces[], char pack[][MAX_CARD_NAME]);
void shuffle(char pack[DECK_TOTAL][MAX_CARD_NAME]);
void deal_crd(char pack[DECK_TOTAL][MAX_CARD_NAME], char hand[MAX_HAND][MAX_CARD_NAME], unsigned int *nxt_crd, unsigned int *hand_count);

void deal_phase(char pack[DECK_TOTAL][MAX_CARD_NAME], char d_hand[MAX_HAND][MAX_CARD_NAME], char p_hand[MAX_HAND][MAX_CARD_NAME], unsigned int *nxt_crd, unsigned int *d_hand_count, unsigned int *p_hand_count);

void read_hands(char p_hand[MAX_HAND][MAX_CARD_NAME], unsigned int p_hand_count, char d_hand[MAX_HAND][MAX_CARD_NAME], unsigned int d_hand_count, unsigned int opening);

unsigned int eval_hand(char hand[MAX_HAND][MAX_CARD_NAME], unsigned int hand_count);

int main (void)
{
        srand(time(NULL));

        unsigned int top_crd = 0;
        char player_hand[MAX_HAND][MAX_CARD_NAME] = {0};
        char dealer_hand[MAX_HAND][MAX_CARD_NAME] = {0};

        unsigned int player_crd_count = 0;
        unsigned int dealer_crd_count = 0;

        const char *number_crd[NUM_COUNT] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten"};
        const char *face_crd[FACE_COUNT] = {"Jack", "Queen", "King"};
        const char *suit[SUIT_COUNT] = {"Spades", "Diamonds", "Clubs", "Hearts"};
        char deck[DECK_TOTAL][MAX_CARD_NAME] = {0};
        // can't use *dec[DECK_TOTAL] as this will create an array of objects of len(pointer)

        assemble(suit, number_crd, face_crd, deck);
        shuffle(deck);

        deal_phase(deck, dealer_hand, player_hand, &top_crd, &dealer_crd_count, &player_crd_count);
        // dealer_hand[0] is face down
        read_hands(player_hand, player_crd_count, dealer_hand, dealer_crd_count, 0);
        unsigned int real_val = eval_hand(player_hand, player_crd_count);
        printf("PLAYER HAND VALUE: %u\n", real_val);
}

void assemble(const char const *suits[], const char const *nums[], const char const *faces[], char pack[DECK_TOTAL][MAX_CARD_NAME])
{
        void mk_crd(const char *val, const char *suit, char *crd);
        char current_card[MAX_CARD_NAME];  

        unsigned int pos = 0;

        for (size_t s = 0; s < SUIT_COUNT/2; ++s)
        {
                for (size_t n = 0; n < NUM_COUNT; ++n)
                {
                        mk_crd(nums[n], suits[s], current_card);
                        strcpy(pack[pos], current_card);
                        // can't use pack[pos] = current_card here
                        // this would set the pointer pack[pos] to addy of current_card
                        // thre result would be that every object in pack would be the last value of current card
                        ++pos;
                }

                for (size_t f = 0; f < FACE_COUNT; ++f)
                {
                        mk_crd(faces[f], suits[s], current_card);
                        strcpy(pack[pos], current_card);
                        ++pos;
                }
        }

        for (size_t s = 2; s < SUIT_COUNT; ++s)
        {

                // int instead of size_t here:
                // > size_t is unsigned long long 
                // > when it reaches -1 (termination condition) it will be out of bounds
                // > gives garbage vals that cause infinite loop

                for (int f = (FACE_COUNT - 1); f >= 0; --f)
                {
                        mk_crd(faces[f], suits[s], current_card);
                        strcpy(pack[pos], current_card);
                        ++pos;
                }

                for (int n = (NUM_COUNT - 1); n >= 0; --n)
                {
                        mk_crd(nums[n], suits[s], current_card);
                        strcpy(pack[pos], current_card);
                        ++pos;
                }
        }
}

void mk_crd(const char *val, const char *suit, char *crd)
{
        const char of[5] = " of ";
        size_t i, j, k;
        i = j = k = 0;

        while (val[i] != '\0')
        {
                crd[i] = val[i];
                i++;
        }

        while (of[k] != '\0')
        {
                crd[i] = of[k];
                k++;
                i++;
        }

        while (suit[j] != '\0')
        {
                crd[i] = suit[j];
                i++;
                j++;
        }

        crd[i] = '\0';
}

void shuffle(char pack[DECK_TOTAL][MAX_CARD_NAME])
{
        int r; 
        char rand_card[MAX_CARD_NAME];  
        char hold_card[MAX_CARD_NAME];  

       for (size_t i = 0; i < DECK_TOTAL; ++i) 
               {
                       r = rand() % DECK_TOTAL;
                       strcpy(rand_card, pack[r]);
                       strcpy(hold_card, pack[i]);
                       strcpy(pack[i], rand_card);
                       strcpy(pack[r], hold_card);
               }
}

void deal_phase(char pack[DECK_TOTAL][MAX_CARD_NAME], char d_hand[MAX_HAND][MAX_CARD_NAME], char p_hand[MAX_HAND][MAX_CARD_NAME], unsigned int *nxt_crd, unsigned int *d_hand_count, unsigned int *p_hand_count)
{
        deal_crd(pack, p_hand, nxt_crd, p_hand_count);
        deal_crd(pack, d_hand, nxt_crd, d_hand_count);
        deal_crd(pack, p_hand, nxt_crd, p_hand_count);
        deal_crd(pack, d_hand, nxt_crd, d_hand_count);
}

void deal_crd(char pack[DECK_TOTAL][MAX_CARD_NAME], char hand[MAX_HAND][MAX_CARD_NAME], unsigned int *nxt_crd, unsigned int *hand_count)
{ 
        strcpy(hand[*hand_count], pack[*nxt_crd]);

        ++*nxt_crd; ++*hand_count;
}

void read_hands(char p_hand[MAX_HAND][MAX_CARD_NAME], unsigned int p_hand_count, char d_hand[MAX_HAND][MAX_CARD_NAME], unsigned int d_hand_count, unsigned int opening)
{
        if (opening > 1 || opening < 0)
        {
                puts("opening input is incorrect. Please change to 1 or 0");
        }

        if (opening == 0)
        {
                puts("Opening: \n");
                puts("Player: ");
                for (size_t i = 0; i < p_hand_count; ++i)
                {
                        printf("%s\n", p_hand[i]);
                }
                puts("");
                printf("Dealer:\n%s\n1 Facedown Card\n", d_hand[1]);
        }

        if (opening == 1)
        {
                puts("Player: ");
                for (size_t i = 0; i < p_hand_count; ++i)
                {
                        printf("%s\n", p_hand[i]);
                }
                puts("");

                puts("Dealer: ");

                for (size_t i = 0; i < d_hand_count; ++i)
                {
                        printf("%s\n", d_hand[i]);
                }
        }
}

unsigned int eval_hand(char hand[MAX_HAND][MAX_CARD_NAME], unsigned int hand_count) 
{
        unsigned int letter = 0;
        char val[VAL_LEN] = {0};
        unsigned int hand_val = 0;

                for (size_t i = 0; i < hand_count; ++i)
                {
                        while (hand[i][letter] != ' ')
                        {
                                val[letter] = hand[i][letter];
                                ++letter;
                        }
                        
                        letter = 0;

                        if (strcmp(val, "Ace") == 0)
                        {
                                if (hand_val > 10)
                                        hand_val += 1;
                                else
                                        hand_val += 11;
                        }

                        if (strcmp(val, "Two") == 0)
                        {
                                hand_val += 2;
                        }

                        if (strcmp(val, "Three") == 0)
                        {
                                hand_val += 3;
                        }

                        if (strcmp(val, "Four") == 0)
                        {
                                hand_val += 4;
                        }

                        if (strcmp(val, "Five") == 0)
                        {
                                hand_val += 5;
                        }

                        if (strcmp(val, "Six") == 0)
                        {
                                hand_val += 6;
                        }

                        if (strcmp(val, "Seven") == 0)
                        {
                                hand_val += 7;
                        }

                        if (strcmp(val, "Eight") == 0)
                        {
                                hand_val += 8;
                        }

                        if (strcmp(val, "Nine") == 0)
                        {
                                hand_val += 9;
                        }

                        if (strcmp(val, "Ten") == 0)
                        {
                                hand_val += 10;
                        }

                        if (strcmp(val, "Jack") == 0)
                        {
                                hand_val += 10;
                        }

                        if (strcmp(val, "Queen") == 0)
                        {
                                hand_val += 10;
                        }

                        if (strcmp(val, "King") == 0)
                        {
                                hand_val += 10;
                        }

                        memset(val, '\0', VAL_LEN * sizeof(char));
                }

        return hand_val;
}
