#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_HAND 12
#define MAX_CARD_NAME 22
#define DECK_TOTAL 52
#define SUITS 4
#define NUMS 10
#define FACES 3

#define PLAYERS 2

void dec_ins_sort(int *arr, size_t);
void assemble(const char const *suits[], const char const *nums[], const char const *faces[], char *deck[]);
char *mk_crd(const char *val, const char *suit, char *crd);
void shuffle(int, size_t);
void deal(int, size_t);

int main ( void )
{

        int card_count;
        int hand[MAX_HAND];
        int hand_value;

        const char *number_card[NUMS] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten"};
        const char *face_card[FACES] = {"Jack", "Queen", "King"};
        const char *suit[SUITS] = {"Spades", "Diamonds", "Clubs", "Hearts"};
        char *deck[DECK_TOTAL] = {0};

        char *hands[PLAYERS][MAX_HAND];

        assemble(suit, number_card, face_card, deck);

        printf("%s", deck[1]);

        for (size_t i = 0; i < DECK_TOTAL; ++i)
                printf("%s", deck[1]);
                
}

void assemble(const char const *suits[], const char const *nums[], const char const *faces[], char *deck[])
{
        char current_card[MAX_CARD_NAME];  

        unsigned int pos = 0;
        for (size_t s = 0; s < SUITS/2; ++s)
        {
                for (size_t n = 0; n < NUMS; ++n)
                {
                        deck[pos] = mk_crd(nums[n], suits[s], current_card);
                        ++pos;
                }

                for (size_t f = 0; f < FACES; ++f)
                {
                        deck[pos] = mk_crd(faces[f], suits[s], current_card);
                        ++pos;
                }
        }

        for (size_t s = 2; s < SUITS; ++s)
        {

                // int instead of size_t here:
                // > size_t is unsigned long long 
                // > when it reaches -1 (termination condition) it will be out of bounds
                // > gives garbage vals that cause infinite loop

                for (int f = (FACES - 1); f >= 0; --f)
                {
                        deck[pos] = mk_crd(faces[f], suits[s], current_card);
                        ++pos;
                }

                for (int n = (NUMS - 1); n >= 0; --n)
                {
                        deck[pos] = mk_crd(nums[n], suits[s], current_card);
                        ++pos;
                }
        }
}

char *mk_crd(const char *val, const char *suit, char *crd)
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
        return crd;
}
