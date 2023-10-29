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

#define PLAYERS 2

void assemble(const char const *suits[], const char const *nums[], const char const *faces[], char pack[][MAX_CARD_NAME]);
void shuffle(char pack[DECK_TOTAL][MAX_CARD_NAME]);
void deal(int, size_t);

int main ( void )
{
        srand(time(NULL));

        int card_count;
        int hand[MAX_HAND];
        int hand_value;

        const char *number_card[NUM_COUNT] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten"};
        const char *face_card[FACE_COUNT] = {"Jack", "Queen", "King"};
        const char *suit[SUIT_COUNT] = {"Spades", "Diamonds", "Clubs", "Hearts"};
        char deck[DECK_TOTAL][MAX_CARD_NAME] = {0};
        // can't use *dec[DECK_TOTAL] as this will create an array of objects of len(pointer)

        char *hands[PLAYERS][MAX_HAND];

        assemble(suit, number_card, face_card, deck);
        shuffle(deck);

        for (size_t i = 0; i < DECK_TOTAL; ++i)
                printf("%s\n", deck[i]);
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

