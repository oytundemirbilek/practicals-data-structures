#ifndef PCH_H
#define PCH_H

#endif

#include <iostream>
#include <stdio.h>

//DEFINING STRUCTS OF STACKS
struct table {
	int card;
	table * next;
};
struct player1 {
	int card;
	player1 * next;
};
struct player2 {
	int card;
	player2 * next;
};
struct bin {
	int card;
	bin * next;
};
struct func {
	int turns;
	int tableDeckCount, playerDeckCount;
	int nextcard, removedcard;
	int binDeckCount;
	int p1cards, p2cards;
	
	//DEFINING STACKS AND THEIR ROOT, ITERATOR POINTERS
	player1 * head1;
	player2 * head2;
	table * head3;
	bin * head4;

	player1 * iter1;
	player2 * iter2;
	table * iter3;
	bin * iter4;

	void createDecks(FILE * fp) {
		
		fscanf(fp, "%d %d", &tableDeckCount, &playerDeckCount);
		p1cards = playerDeckCount;
		p2cards = playerDeckCount;
		//CREATING TABLE DECK
		for (int i = 0; i < tableDeckCount; i++) {
			fscanf(fp, "%d", &nextcard);
			iter3->card = nextcard;
			iter3->next = new table;
			if(i != tableDeckCount - 1)iter3 = iter3->next;
		}
		iter3->next = NULL;
		iter3 = head3;
		
		//CREATING PLAYERS DECK
		for (int i = 0; i < playerDeckCount; i++) {
			fscanf(fp, "%d", &nextcard);
			iter1->card = nextcard;
			iter1->next = new player1;
			if (i != playerDeckCount - 1)iter1 = iter1->next;
		}
		iter1->next = NULL;
		iter1 = head1;

		for (int i = 0; i < playerDeckCount; i++) {
			fscanf(fp, "%d", &nextcard);
			iter2->card = nextcard;
			iter2->next = new player2;
			if (i != playerDeckCount - 1)iter2 = iter2->next;
		}
		iter2->next = NULL;
		iter2 = head2;
	}
	void startGame() {
		if (turns % 2 == 1) {
			//TURN OF FIRST PLAYER
			while (iter3->next != NULL)iter3 = iter3->next;
			if (iter3->card < 0) {
				iter3->card = iter3->card * (-1);
				//printf("First player needs to give %d cards\n", iter3->card);
				for (int i = 0; i < iter3->card; i++) {
					removeCards(iter1);
					addCards(iter2, removedcard);
					p1cards--;
					if (head1 == NULL)break;
				}
			}
			else {
				//printf("First player needs to take %d cards\n", iter3->card);
				for (int i = 0; i < iter3->card; i++) {
					removeCards(iter2);
					addCards(iter1, removedcard);
					p2cards--;
					if (head2 == NULL)break;
				}
			}
			iter3 = head3;
			removeCards(iter3);
		}
		else {
			//TURN OF SECOND PLAYER
			while (iter3->next != NULL)iter3 = iter3->next;
			if (iter3->card < 0) {
				iter3->card = iter3->card * (-1);
				//printf("Second player needs to give %d cards\n", iter3->card);
				for (int i = 0; i < iter3->card; i++) {
					removeCards(iter2);
					addCards(iter1, removedcard);
					p2cards--;
					if (head2 == NULL)break;
				}
			}
			else {
				//printf("Second player needs to take %d cards\n", iter3->card);
				for (int i = 0; i < iter3->card; i++) {
					removeCards(iter1);
					addCards(iter2, removedcard);
					p1cards--;
					if (head1 == NULL)break;
				}
			}
			iter3 = head3;
			removeCards(iter3);
		}
	}

	void addCards(player1 *, int card) {
		if (head1 == NULL) {
			head1 = new player1;
			head1->card = card;
			head1->next = NULL;
			p1cards++;
		}
		else {
			while (iter1->next != NULL)iter1 = iter1->next;
			if (iter1->card < card) {
				//PLAYER TAKES THE CARD
				//printf("%d > %d is true -> Card %d is given\n", card, iter1->card, card);
				iter1->next = new player1;
				iter1->next->card = card;
				iter1->next->next = NULL;
				iter1 = head1;
				p1cards++;
			}
			else {
				//CARD GOES TO THE BIN
				if (head4 != NULL) {
					while (iter4->next != NULL)iter4 = iter4->next;
					iter4->next = new bin;
					iter4->next->card = card;
					iter4->next->next = NULL;
				}
				else {
					head4 = new bin;
					head4->card = card;
					head4->next = NULL;
				}
				binDeckCount++;
				iter4 = head4;
				//printf("%d > %d is false -> Card %d is thrown away\n", card, iter1->card, card);
			}
		}
		iter1 = head1;
	}
	void addCards(player2 *, int card) {
		if (head2 == NULL) {
			head2 = new player2;
			head2->card = card;
			head2->next = NULL;
			p2cards++;
		}
		else {
			while (iter2->next != NULL)iter2 = iter2->next;
			if (iter2->card < card) {
				//PLAYER TAKES THE CARD
				//printf("%d > %d is true -> Card %d is given\n", card, iter2->card, card);
				iter2->next = new player2;
				iter2->next->card = card;
				iter2->next->next = NULL;
				iter2 = head2;
				p2cards++;
			}
			else {
				//CARD GOES TO THE BIN
				if (head4 != NULL) {
					while (iter4->next != NULL)iter4 = iter4->next;
					iter4->next = new bin;
					iter4->next->card = card;
					iter4->next->next = NULL;
				}
				else {
					head4 = new bin;
					head4->card = card;
					head4->next = NULL;
				}
				binDeckCount++;
				iter4 = head4;
				//printf("%d > %d is false -> Card %d is thrown away\n", card, iter2->card, card);
			}
		}
		iter2 = head2;
	}

	void removeCards(player1 *) {
		if (head1 == NULL) {}
		else if (head1->next == NULL) {
			//LAST CARD REMOVED
			iter1 = head1;
			removedcard = iter1->card;
			delete iter1;
			head1 = NULL;
			iter1 = head1;
		}
		else {
			//CARD REMOVED
			if(iter1->next != NULL) while (iter1->next->next != NULL)iter1 = iter1->next;
			removedcard = iter1->next->card;
			delete iter1->next;
			iter1->next = NULL;
			iter1 = head1;
		}
	}
	void removeCards(player2 *) {
		if (head2 == NULL) {}
		else if (head2->next == NULL) {
			//LAST CARD REMOVED
			iter2 = head2;
			removedcard = iter2->card;
			delete iter2;
			head2 = NULL;
			iter2 = head2;
		}
		else {
			//CARD REMOVED
			while (iter2->next->next != NULL)iter2 = iter2->next;
			removedcard = iter2->next->card;
			delete iter2->next;
			iter2->next = NULL;
			iter2 = head2;
		}
	}
	void removeCards(table *) {
		if (head3 == NULL) {}
		else if (head3->next == NULL) {
			//LAST CARD REMOVED
			iter3 = head3;
			removedcard = iter3->card;
			delete iter3;
			head3 = NULL;
			iter3 = head3;
		}
		else {
			//CARD REMOVED
			while (iter3->next->next != NULL)iter3 = iter3->next;
			removedcard = iter3->next->card;
			delete iter3->next;
			iter3->next = NULL;
			iter3 = head3;
		}
	}
};

struct func * funcPoint;

int main(int argc, char **argv)
{
	//GETTING INPUT FILE AND CREATING DECKS OF CARDS
	func * funcPoint = new func;
	FILE * fp = fopen(argv[1], "r");
	funcPoint->head1 = new player1;
	funcPoint->head2 = new player2;
	funcPoint->head3 = new table;
	funcPoint->head4 = NULL;
	funcPoint->iter1 = funcPoint->head1;
	funcPoint->iter2 = funcPoint->head2;
	funcPoint->iter3 = funcPoint->head3;
	funcPoint->iter4 = funcPoint->head4;
	funcPoint->turns = 0;
	funcPoint->binDeckCount = 0;
	funcPoint->createDecks(fp);
	fclose(fp);
	
	//LOOP OF EVERY TURN
	while (funcPoint->tableDeckCount != 0) {
		funcPoint->turns++;
		if (funcPoint->head1 == NULL) {
		std::cout << funcPoint->binDeckCount << std::endl;

			break;
		}
		if (funcPoint->head2 == NULL) {
			std::cout << funcPoint->binDeckCount << std::endl;

			break;
		}
		//printf("\n--turn %d begins\n", funcPoint->turns);
		//funcPoint->printDecks();
		funcPoint->startGame();		
		funcPoint->tableDeckCount--;
	}
	//RESULTS
	if (funcPoint->tableDeckCount == 0 && funcPoint->p1cards > funcPoint->p2cards)std::cout << funcPoint->binDeckCount << std::endl;

	if (funcPoint->tableDeckCount == 0 && funcPoint->p2cards > funcPoint->p1cards)std::cout << funcPoint->binDeckCount << std::endl;

	if (funcPoint->tableDeckCount == 0 && funcPoint->p2cards == funcPoint->p1cards)std::cout << funcPoint->binDeckCount << std::endl;



	return 0;
}
