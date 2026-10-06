#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// Define structures for the cards
struct Card {
    std::string suit;
    std::string rank;
    int value; // 2-14 (where 11=Jack, 12=Queen, 13=King, 14=Ace)
};

// Global arrays for building the deck
const std::string SUITS[] = { "Spade", "Heart", "Diamond", "Club" };
const std::string RANKS[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
const int VALUES[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

// Simple logic to check for a Flush or a Pair
std::string evaluateHand(const std::vector<Card>& hand) {
    bool isFlush = true;
    for (size_t i = 1; i < hand.size(); ++i) {
        if (hand[i].suit != hand[0].suit) {
            isFlush = false;
            break;
        }
    }
    if (isFlush) return "Flush";

    // Count identical ranks to look for a pair
    int pairs = 0;
    for (size_t i = 0; i < hand.size(); ++i) {
        for (size_t j = i + 1; j < hand.size(); ++j) {
            if (hand[i].rank == hand[j].rank) {
                pairs++;
            }
        }
    }

    if (pairs == 1) return "One Pair";
    if (pairs == 2) return "Two Pair";
    if (pairs >= 3) return "Three of a Kind (or better)";

    return "High Card (Nothing)";
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(0)));

    // 1. Create and fill a standard 52-card deck
    std::vector<Card> deck;
    for (int s = 0; s < 4; ++s) {
        for (int r = 0; r < 13; ++r) {
            deck.push_back({ SUITS[s], RANKS[r], VALUES[r] });
        }
    }

    // 2. Shuffle the deck manually
    for (size_t i = 0; i < deck.size(); ++i) {
        size_t j = i + std::rand() % (deck.size() - i);
        std::swap(deck[i], deck[j]);
    }

    // 3. Deal 5 cards to the player
    std::vector<Card> hand;
    for (int i = 0; i < 5; ++i) {
        hand.push_back(deck[i]);
    }

    // 4. Determine the actual correct hand strength
    std::string correctHandType = evaluateHand(hand);

    std::cout << "========================================\n";
    std::cout << "🃏 Welcome to the Poker Guessing Game! 🃏\n";
    std::cout << "========================================\n";
    std::cout << "Here is your 5-card hand:\n\n   ";

    for (const auto& card : hand) {
        std::cout << "[" << card.rank << card.suit << "] ";
    }
    std::cout << "\n\n========================================\n";
    std::cout << "What is the highest rank of this hand?\n";
    std::cout << "1. High Card (Nothing)\n";
    std::cout << "2. One Pair\n";
    std::cout << "3. Two Pair\n";
    std::cout << "4. Three of a Kind (or better)\n";
    std::cout << "5. Flush\n";
    std::cout << "----------------------------------------\n";

    int userChoice;
    std::cout << "Enter your guess (1-5): ";

    if (!(std::cin >> userChoice) || userChoice < 1 || userChoice > 5) {
        std::cout << "❌ Invalid input. Exiting game.\n";
        return 1;
    }

    // Map user menu selection to the underlying text string
    std::string userGuessStr;
    switch (userChoice) {
    case 1: userGuessStr = "High Card (Nothing)"; break;
    case 2: userGuessStr = "One Pair"; break;
    case 3: userGuessStr = "Two Pair"; break;
    case 4: userGuessStr = "Three of a Kind (or better)"; break;
    case 5: userGuessStr = "Flush"; break;
    }

    // 5. Check the user result
    if (userGuessStr == correctHandType) {
        std::cout << "\n🎉 Correct! You accurately read the hand context as a " << correctHandType << "!\n";
    }
    else {
        std::cout << "\n❌ Close, but wrong! Your hand was actually a: " << correctHandType << "\n";
    }

    return 0;
}
