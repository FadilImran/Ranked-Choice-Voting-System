#pragma once
#include <iostream>
using namespace std;

template<class T>
class Vote
{
private:
	int rank;
	T choice;

public:
	Vote() {
		int rank = 0;
	}

	Vote(T choice, int rank) {
		this->rank = rank;
		this->choice = choice;
	}

	int getRank() { return rank; }

	T getChoice() { return choice; }

	void setRank(int rank) { this->rank = rank; }

	void setChoice(T choice) { this->choice = choice; }

	friend bool operator==(const Vote<T>& vote1, const Vote<T>& vote2) {
		return (vote1.choice == vote2.choice) && (vote1.rank == vote2.rank);
	}

	friend ostream& operator<<(ostream& out, const Vote<T>& obj) {
		out << "Choice: " << obj.choice << " | Rank: " << obj.rank << endl;

		return out;
	}
};