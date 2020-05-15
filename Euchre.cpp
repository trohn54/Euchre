// Euchre.cpp : This file contains the 'main' function. Program execution begins and ends there.
//code written by Thomas Rohn for the 2020 spring Cpp2 class at Columbia College Chicago, instructed by Karl Statz

#include <iostream>
#include <vector>
#include <string>

enum Value { Nine, Ten, Jack, Queen, King, Ace };
enum Suit { Diamonds, Clubs, Hearts, Spades };


struct Card
{
	Value value; Suit suit;
};

//determine red or black to be trump. Thankfully suits are ordered in such a way where it goes red, black, red, black, as in even, odd, even, odd.
int getTrumpColor(const Card& trump)
{
	return trump.suit % 2;
}
//The main attraction!
//In order to get an accurate algorithm, me and some friends played a ton of euchre and recorded what cards were in everybodys hand and who won how many tricks.
//based on results I decided to assign points to each card, giving each hand a point total. Players with more points were more likely to win the trick.
//programming the algorithm was then about how to best reflect the point system I had created.
//points are as follows: righty 25, lefty 18, tr. ace 16, tr. king 14, tr. queen 12, tr. ten 10, tr. nine 8
//non trump numbers: ace 7, king 5, queen 3, jack 1, ten and nine zero
float Rank(std::vector<Card>* hand, const Card& trump)
{	
	int points = 0;
			
	int trumpColor = getTrumpColor(trump);

	//set points
	for (int i = 0; i < hand->size(); i++)
	{
		//check for trump suit
		if (hand->at(i).suit == trump.suit) 
		{
			//check for righty
			if (hand->at(i).value == 2)
			{
				points += 25;
			}
			//check for trump 9 and 10
			else if (trump.value < 2)
			{
				points += 6 + (2 * hand->at(i).value);
			}
			//any other trump cards
			else
			{
				points += 6 + (2 * hand->at(i).value);
			}
		}

		//add non-trump points
		else
		{
			//check for lefty:
			if ((hand->at(i).value == 2) && (hand->at(i).suit % 2 == trumpColor))
			{
				points += 18;
			}			
			//check the rest
			else if ((hand->at(i).value > 1))
			{
				points += 2 * (hand->at(i).value) - 3;
			}
		}
		std::cout << points << " ";
	}	
	
	//most possible points is 85, so we divide points by that.
	return (points/85.0);    
}

int main()
{
	//TODO: make a deck and randomly pull 5 cards from it. Hardcoding is inneficient. Utilize map containers.
	std::vector<Card> best(0); //we know a hand will have exactly 5 cards, so we set aside precisely that much memory
	best.push_back({ Ace, Spades });
	best.push_back({ King, Spades });
	best.push_back({ Queen, Spades });
	best.push_back({ Jack, Spades });
	best.push_back({ Jack, Clubs });

	std::vector<Card> worst(0); //we know a hand will have exactly 5 cards, so we set aside precisely that much memory
	worst.push_back({ Nine, Hearts });
	worst.push_back({ Nine, Diamonds });
	worst.push_back({ Nine, Clubs });
	worst.push_back({ Ten, Hearts });
	worst.push_back({ Ten, Diamonds });

	Card trump = { Nine,Spades };

	float bestRank = Rank(&best, trump) * 100;	
	std::cout << "wins " << bestRank << "% of tricks.\n";

	float worstRank = Rank(&worst, trump) * 100;
	std::cout << "wins " << worstRank << "% of tricks.\n";
	return 0; 
}