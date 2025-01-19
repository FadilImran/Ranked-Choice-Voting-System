#pragma once
#include <iostream>
#include "Vote.h"
#include "Choices.h"
using namespace std;

template<class T>
class Votes
{
private:
	Vote<T>* votes_list;
	Choices<T> choices;
	bool voted;

public:

	Vote<T>* getVote() { return votes_list; }

	Choices<T> getChoices() { return choices; }

	int getNum_Choices() const { return choices.getNum_Choices(); }

	Votes() {
		voted = 0;

		votes_list = new Vote<T>[getNum_Choices()];
	}

	Votes(Choices<T>& choices) {
		this->choices = choices;
		votes_list = new Vote<T>[getNum_Choices()];
	}

	Votes(const Votes<T>& other) {
		this->choices = other.choices;
		this->voted = other.voted;

		votes_list = new Vote<T>[other.getNum_Choices()];

		if (voted) {
			for (int i = 0; i < other.getNum_Choices(); i++) {
				votes_list[i] = other.votes_list[i];
			}
		}
	}

	Votes<T>& operator=(const Votes<T>& other) {
		if (this != &other) {
			this->choices = other.choices;
			this->voted = other.voted;

			delete[]votes_list;

			votes_list = new Vote<T>[choices.getNum_Choices()];

			if (voted) {
				for (int i = 0; i < choices.getNum_Choices(); i++) {
					votes_list[i] = other.votes_list[i];
				}
			}
		}
		return *this;
	}

	Votes(Votes<T>&& other) noexcept {
		this->choices = move(other.choices);
		this->voted = other.voted;

		votes_list = other.votes_list;
		other.votes_list = NULL;
	}

	Votes<T>& operator=(Votes<T>&& other) {
		if (this != &other) {
			this->choices = move(other.choices);
			this->voted = other.voted;

			votes_list = other.votes_list;
			other.votes_list = NULL;
		}

		return *this;
	}

	~Votes() {
		delete[]votes_list;
	}

	void register_vote() {

		if (choices.getCurrent_Choices() != choices.getNum_Choices()) {
			throw NotEnoughChoices();
		}

		if (voted) {
			throw Voted();
		}

		choices.displayChoices();

		cout << "For each of the choices above, assign a number from 1 to " << choices.getNum_Choices()
			<< ". 1 being most prefferd and " << choices.getNum_Choices() << " being least preferred." << endl;

		for (int i = 0; i < choices.getNum_Choices(); i++) {
			int rank = 0;
			cout << choices.getChoices_List()[i] << " Rank: ";
			cin >> rank;

			if (rank <= 0 || rank > choices.getNum_Choices()) { throw RankInvalid(); }

			for (int j = 0; j < i; j++) {
				if (votes_list[j].getRank() == rank) { throw RankInvalid(); }
			}

			Vote<T> vote(choices.getChoices_List()[i], rank);

			votes_list[i] = vote;
		}


		voted = 1;

	}

	void clearVote() {
		delete[]votes_list;
		votes_list = new Vote<T>[choices.getNum_Choices()];
		voted = 0;
	}


	friend bool operator==(const Votes<T>& vl1, const Votes<T>& vl2) {
		if (vl1.voted != vl2.voted) { return false; }

		else if (vl1.choices.getNum_Choices() != vl2.choices.getNum_Choices()) { return false; }

		for (int i = 0; i < vl1.choices.getNum_Choices(); i++) {
			int flag = 0;
			for (int i = 0; i < vl1.choices.getNum_Choices(); i++) {
				if (vl1.votes_list[i] == vl2.votes_list[i]) { flag++; }
			}
			if (flag == 0) { return false; }
		}

		return true;
	}

	friend ostream& operator<<(ostream& out, const Votes<T>& other) {
		for (int i = 0; i < other.getNum_Choices(); i++) {
			out << other.votes_list[i] << endl;
		}
		return out;
	}
};