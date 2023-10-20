#include<stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARD_TOTAL 52
#define SUITS 4
#define VALS 13


void shuffle(unsigned int pack[][VALS]);
void deal(unsigned int pack[][VALS], const char *num_face[], const char *suit[]);

int main ( void )
{
        srand(time(NULL));

        const char *num_face[VALS] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
        const char *suit[SUITS] = {"Spades", "Diamonds", "Clubs", "Hearts"};
        unsigned int deck[SUITS][VALS] = {0}; //needs to be initialized or subsequent shuffs will fail (deck already full)

        shuffle(deck);
        deal(deck, num_face, suit);
}

void shuffle(unsigned int pack[][VALS])
{
        for (size_t card = 0; card < CARD_TOTAL; ++card)
        {
                size_t row;
                size_t col;

                do 
                {
                        row = rand() % SUITS;
                        col = rand() % VALS;
                }
                while(pack[row][col] != 0);

                pack[row][col] = card;
        }
}

// char arr[] = array of chars (string) ; *char arr = array of char pointers (arr of strings)

void deal(unsigned int pack[][VALS], const char *num_face[], const char *suit[])
{
        for (size_t card = 0; card < CARD_TOTAL; ++card)
        {
                for (size_t row = 0; row < SUITS; ++row)
                {
                        for (size_t col = 0; col < VALS; ++col)
                        {
                                if (pack[row][col] == card) 
                                        printf("%s of %s\n", num_face[col], suit[row]);
                        }
                }
        }
}
