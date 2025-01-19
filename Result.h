#pragma once
#include <iostream>
using namespace std;

template<class T>
class Result
{
private:
	double percentage;
	int num_votes;
	T choice;

public:
	Result() {
		percentage = 0;
		num_votes = 0;
	}

	Result(T choice, double percentage) {
		this->percentage = percentage;
		this->choice = choice;
		this->num_votes = num_votes;
	}

	Result(const Result& other) {
		this->percentage = other.percentage;
		this->num_votes = other.num_votes;
		this->choice = other.choice;
	}

	int getNumVotes() { return num_votes; }

	double getPercentage() { return percentage; }

	T getChoice() { return choice; }

	void setPercentage(double percentage) { this->percentage = percentage; }

	void setChoice(T& choice) { this->choice = choice; }

	void setNumVotes(int num_votes) { this->num_votes = num_votes; }

	friend ostream& operator<<(ostream& out, const Result<T>& obj) {
		out << "Choice: " << obj.choice << " | Percentage: " << obj.percentage << endl;

		return out;
	}
};