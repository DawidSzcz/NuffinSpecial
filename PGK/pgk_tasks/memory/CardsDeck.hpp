#ifndef CARDSDECK_HPP
#define CARDSDECK_HPP

#include <vector>
#include "Card.hpp"
using namespace std;

class CardsDeck {
public:
	CardsDeck(int height,int width);
	virtual Card* at(int i,int j) const;
	const vector<Card*>& GetDeck() const;
	virtual void Shuffle();
	virtual void RemoveCard(int i,int j);
	virtual int GetHeight() const;
	virtual int GetWidth() const;
	virtual int GetCardsLeftNum() const;
	virtual ~CardsDeck();
protected:
	vector<Card*> deck;
	int h,w;
	int cards_left;
};

#endif