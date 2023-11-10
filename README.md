# BlackJack

Classic Blackjack made in C

## Description 
1. This program uses nested functions to create card strings and assemble them into an array of strings in the order of a new pack of cards
2. The shuffle function iterates through the pack and swaps card[i] with another random card
2. The deal function uses a combination of strcpy and counters to deal the cards in the correct order
3. Read hands  function takes a flag for the opening turn. If on the opening, the dealers first card is face down 
4. The program checks to see if either player has a natural
5. If neither player has a natural, the game starts.
6. Player chooses how to play / The dealer will always hit if below 17
7. Game loops until bust or natural win

## Progress
* Need to debug dealer AI
* Need to debug natural check
* Need to add split check

## Background
I did this project to learn about pointers in C
