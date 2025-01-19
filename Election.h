#pragma once
#include <iostream>
#include <vector>
#include "Votes.h"
#include "Result.h"
using namespace std;

template<class T>
class Election
{
private:
	Votes<T>* allvotes;
	vector<Result<T>> results;
	int num_votes;
	int num_choices;

public:
	Election() {
		num_votes = 0;
		num_choices = 0;
	}

	Election(int num_choices) {
		this->num_votes = 0;
		this->num_choices = num_choices;

		allvotes = new Votes<T>[num_votes];

	}

	Election(const Election<T>& other) {
		this->num_votes = other.num_votes;
		this->num_choices = other.num_choices;

		allvotes = new Votes<T>[num_votes];

		for (int i = 0; i < num_votes; i++) {
			allvotes[i] = other.allvotes[i];
		}
	}

	Election(Election<T>&& other) {
		this->num_votes = other.num_votes;
		this->num_choices = other.num_choices;
		this->results = other.results;

		allvotes = other.allvotes;
		other.allvotes = NULL;
	}

	Election<T>& operator=(const Election<T>& other) {
		if (this != &other) {
			this->num_votes = other.num_votes;
			this->num_choices = other.num_choices;
			this->results = other.results;

			delete[]allvotes;

			allvotes = new Votes<T>[num_votes];

			for (int i = 0; i < num_votes; i++) {
				allvotes[i] = other.allvotes[i];
			}

		}
		return *this;
	}

	Election<T>& operator=(Election<T>&& other) {
		if (this != &other) {
			this->num_votes = other.num_votes;
			this->num_choices = other.num_choices;
			this->results = other.results;

			allvotes = other.allvotes;
			other.allvotes = NULL;
		}
	}

	~Election() {
		delete[]allvotes;
	}

	void addVote(Votes<T>& other) {

		if (num_votes == 0) {
			this->num_choices = other.getNum_Choices();
		}

		else if (num_votes > 0) {
			for (int i = 0; i < num_votes; i++) {
				if (!(allvotes[i].getChoices() == other.getChoices())) {
					throw IncompatibleVoteType();
				}
			}
		}
		Votes<T>* allvotes_new = new Votes<T>[num_votes + 1];

		for (int i = 0; i < num_votes; i++) {
			allvotes_new[i] = allvotes[i];
		}

		allvotes_new[num_votes] = other;

		delete[]allvotes;

		allvotes = allvotes_new;
		num_votes++;
	}

	void deleteVote(const Vote<T>& other) {
		Votes<T>* allvotes_new = new Votes<T>[num_votes - 1];

		int index = 0;
		for (int i = 0; i < num_votes; i++) {
			if (allvotes[i] == other) { index = i; }
		}

		for (int i = 0; i < num_votes - 1; i++) {
			if (i < index) {
				allvotes_new[i] == allvotes[i];
			}
			else {
				allvotes_new[i] == allvotes[i - 1];
			}
		}

		delete[]allvotes;

		allvotes = allvotes_new;
		num_votes--;
	}

	void calculateResults() {
		Choices<T> choices = allvotes[0].getChoices();
		bool have_winner = false;
		bool have_tie = false;

		for (int i = 0; i < num_choices; i++) {
			double num_votes_per_choice = 0;
			for (int j = 0; j < num_votes; j++) {
				for (int k = 0; k < num_choices; k++) {
					
					Vote<T> vote = allvotes[j].getVote()[k];
					if (vote.getChoice() == choices.getChoices_List()[i] && vote.getRank() == 1) 
					{ num_votes_per_choice++; }
				}
			}

			Result<T> result;
			result.setChoice(choices.getChoices_List()[i]);
			result.setNumVotes(num_votes_per_choice);
			result.setPercentage((num_votes_per_choice / num_votes) * 100);

			results.push_back(result);
		}

		do {

			int min_num_votes_index = 0;
			Result<T> min_result = results[0];

			for (int i = 0; i < num_choices; i++) {
				if (results[i].getPercentage() > 50) {
					have_winner = true;
					break;
				}

				else if (results.size() == 2 && results[i].getPercentage() == 50) {
					have_tie = true;
					break;
				}

				else if (results[i].getNumVotes() < min_result.getNumVotes()) {
					min_num_votes_index = i;
					min_result = results[i];
				}
			}

			if (!(have_winner || have_tie)) {
				results.erase(results.begin() + min_num_votes_index);
				int rank_to_be_considered = 2;

				for (int i = 0; i < results.size(); i++) {
					double num_votes_per_choice = 0;
					for (int j = 0; j < num_votes; j++) {
						int flag = 0;
						for (int k = 0; k < num_choices; k++) {
							Vote<T> vote = allvotes[j].getVote()[k];
							if (vote.getRank() == 1 && vote.getChoice() == min_result.getChoice()) { flag++; }
							if (vote.getRank() == rank_to_be_considered && vote.getChoice() == results[i].getChoice()) { flag++; }
							if (flag == 2) { num_votes_per_choice++; }
						}
					}
					results[i].setNumVotes(results[i].getNumVotes() + num_votes_per_choice);
					results[i].setPercentage((results[i].getNumVotes() / num_votes) * 100);
				}

				rank_to_be_considered++;
			}
			

		} while (!(have_winner || have_tie));

	}

	void displayResults() {
		for (int i = 0; i < results.size(); i++) {
			cout << results[i] << endl;
		}
	}

	void display_votes() {
		for (int i = 0; i < num_votes; i++) {
			cout << allvotes[i] << endl;
		}
	}
};