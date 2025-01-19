#include <iostream>
#include "Exceptions.h"
#include "Election.h"
#include <string>
#include <vector>
using namespace std;

const int NUM_VOTES = 3;
const int NUM_CHOICES = 5;

int main() {

	try {

		Choices<string> choices(NUM_CHOICES);

		choices.addChoice("Trump");
		choices.addChoice("Biden");
		choices.addChoice("Kamala");
		choices.addChoice("Bernie");
		choices.addChoice("Vivek");

		vector<Votes<string>> partcipant_votes;

		for (int i = 0; i < NUM_VOTES; i++) {
			Votes<string> vote(choices);

			vote.register_vote();

			partcipant_votes.push_back(vote);
		}

		Election<string> election_1(NUM_CHOICES);

		for (int i = 0; i < NUM_VOTES; i++) {
			election_1.addVote(partcipant_votes[i]);
		}

		cout << endl;

		election_1.calculateResults();

		election_1.displayResults();
	}

	catch (exception& e) {
		cout << e.what() << endl;
	}

	return 0;
}