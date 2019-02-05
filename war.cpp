#include <iostream>
#include <vector>
#include <string>

#include "deck.h"

void PlayGame(Deck deck1, Deck deck2, int &p1, int &p2);

int main() {

    // The two shuffled decks for playing the game
    Deck deck1;
    Deck deck2;

    // Scores for each player
    int player1 = 0;
    int player2 = 0;

    PlayGame(deck1, deck2, player1, player2);

    //std::cout << "player1: " << player1 << " , player2: " << player2 << std::endl;
    
    return 0;
}

void PlayGame(Deck deck1, Deck deck2, int &p1, int &p2) {

    for(int i = deck1.cards.size() - 1; i > -1; i--) {

        // strings to represent the enums for rank and suit
        std::string rankString1;
        std::string suitString1;
        std::string rankString2;
        std::string suitString2;

        // Convert enum to string for output
        switch(deck1.cards[i].rank) {
            case two:
                rankString1 = "Two";
                break;
            case three:
                rankString1 = "Three";
                break;
            case four:
                rankString1 = "Four";
                break;
            case five:
                rankString1 = "Five";
                break;
            case six:
                rankString1 = "Six";
                break;
            case seven:
                rankString1 = "Seven";
                break;
            case eight:
                rankString1 = "Eight";
                break;
            case nine:
                rankString1 = "Nine";
                break;
            case ten:
                rankString1 = "Ten";
                break;
            case jack:
                rankString1 = "Jack";
                break;
            case queen:
                rankString1 = "Queen";
                break;
            case king:
                rankString1 = "King";
                break;
            case ace:
                rankString1 = "Ace";
                break;
        }

        switch(deck1.cards[i].suit) {
            case Spades:
                suitString1 = "Spades";
                break;
            case Clubs:
                suitString1 = "Clubs";
                break;
            case Hearts:
                suitString1 = "Hearts";
                break;
            case Diamonds:
                suitString1 = "Diamonds";
                break;
        }

        switch(deck2.cards[i].rank) {
            case two:
                rankString2 = "Two";
                break;
            case three:
                rankString2 = "Three";
                break;
            case four:
                rankString2 = "Four";
                break;
            case five:
                rankString2 = "Five";
                break;
            case six:
                rankString2 = "Six";
                break;
            case seven:
                rankString2 = "Seven";
                break;
            case eight:
                rankString2 = "Eight";
                break;
            case nine:
                rankString2 = "Nine";
                break;
            case ten:
                rankString2 = "Ten";
                break;
            case jack:
                rankString2 = "Jack";
                break;
            case queen:
                rankString2 = "Queen";
                break;
            case king:
                rankString2 = "King";
                break;
            case ace:
                rankString2 = "Ace";
                break;
        }

        switch(deck2.cards[i].suit) {
            case Spades:
                suitString2 = "Spades";
                break;
            case Clubs:
                suitString2 = "Clubs";
                break;
            case Hearts:
                suitString2 = "Hearts";
                break;
            case Diamonds:
                suitString2 = "Diamonds";
                break;
        }

        std::cout << "Player 1's card: " << rankString1 << " of " << suitString1 << "  |    WAR    |  " << "Player 2's card: " << rankString2 << " of " << suitString2 << std::endl << std::endl;

        // if player1's card is higher then they win
        if(deck1.cards[i].rank > deck2.cards[i].rank) {
            deck1.cards.push_back(deck2.cards[i];
            std::cout << "Player 1 wins this round!" << std::endl << std::endl;
        }
        else if(deck1.cards[i].rank < deck2.cards[i].rank) {
            p2++;
            std::cout << "Player 2 wins this round!" << std::endl << std::endl;
        }
        else {
            std::cout << "It's a draw!" << std::endl << std::endl;
        }
    }  
}

