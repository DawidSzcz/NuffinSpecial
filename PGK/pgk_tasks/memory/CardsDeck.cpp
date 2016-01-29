#include <vector>
#include <algorithm>
#include "CardsDeck.hpp"
using namespace std;

CardsDeck::CardsDeck(int height,int width)
: h(height), w(width), cards_left(height*width) {
	for(int i=0 ; i < h*w ; i++) {
		deck.push_back(new Card(i/2));
	}
}

Card* CardsDeck::at(int i,int j) const {
	return deck.at(i*w+j);
}

const vector<Card*>& CardsDeck::GetDeck() const {
	return deck;
}

void CardsDeck::RemoveCard(int i,int j) {
	if(i >= 0 && i < h && j >= 0 && j < w)
		if(deck.at(i*w+j) != NULL) {
			delete deck.at(i*w+j);
			deck.at(i*w+j) = NULL;
			cards_left--;
		}
}

int CardsDeck::GetHeight() const {
	return h;
}

int CardsDeck::GetWidth() const {
	return w;
}

int CardsDeck::GetCardsLeftNum() const {
	return cards_left;
}

void CardsDeck::Shuffle() {
	random_shuffle(deck.begin(),deck.end());
}

CardsDeck::~CardsDeck() {
	while(!deck.empty()) {
		Card* p = deck.back();
		if(p != NULL)
			delete p;

		deck.pop_back();
	}
}