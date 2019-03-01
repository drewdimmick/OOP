#ifndef DECK_H_
#define DECK_H_

#include <vector>
#include <algorithm> // for random_shuffle

enum Suit { // Suit of the card
    Spades, Clubs, Hearts, Diamonds
};
Suit suit;

enum Rank { // Rank of the card
    two, three, four, five, six, seven, eight, nine, ten,
    jack, queen, king, ace
};
Rank rank;

// Vectors to hold the enum values in.
// Used for easy iteration when creating the deck
const std::vector<Suit> suitVector{Suit::Spades, Suit::Clubs, Suit::Hearts, Suit::Diamonds};
const std::vector<Rank> rankVector{Rank::two, Rank::three, Rank::four, Rank::five, Rank::six, 
                                    Rank::seven, Rank::eight, Rank::nine, Rank::ten,
                                    Rank::jack, Rank::queen, Rank::king, Rank::ace};

struct Card {
    Suit suit;
    Rank rank;
};

class Deck {
    public:

    std::vector<Card> cards;
        Deck();
};

// Create a deck of 52 unique cards and shuffle it
Deck::Deck() {

    for(auto & s : suitVector) {
        for(auto & r: rankVector) {
            Card newCard;
            newCard.suit = s;
            newCard.rank = r;
            cards.push_back(newCard);
        }
    }

    // Shuffle Deck
    std::random_shuffle(cards.begin(), cards.end());
}

#endif //DECK_H_