#pragma once
#include <iostream>
#include "Exceptions.h"
using namespace std;

template<class T>
class Choices
{
protected:
	T* choices_list;
	int num_choices;
	int current_choices;

public:
	T* getChoices_List() { return choices_list; }

	int getNum_Choices() const { return num_choices; }

	int getCurrent_Choices() { return current_choices; }

	Choices() {
		num_choices = 0;
		current_choices = 0;

		choices_list = new T[num_choices];
	}

	Choices(int num_choices) {
		this->num_choices = num_choices;
		current_choices = 0;

		choices_list = new T[num_choices];
	}

	Choices(const Choices<T>& other) {
		this->num_choices = other.num_choices;
		this->current_choices = other.current_choices;

		choices_list = new T[num_choices];

		for (int i = 0; i < current_choices; i++) {
			choices_list[i] = other.choices_list[i];
		}
	}

	Choices<T>& operator=(const Choices<T>& other) {
		if (this != &other) {
			this->num_choices = other.num_choices;
			this->current_choices = other.current_choices;

			delete[]this->choices_list;
			this->choices_list = new T[num_choices];

			for (int i = 0; i < current_choices; i++) {
				this->choices_list[i] = other.choices_list[i];
			}
		}
		return *this;
	}

	Choices(Choices<T>&& other) {
		this->num_choices = other.num_choices;
		this->current_choices = other.current_choices;

		choices_list = other.choices_list;
		other.choices_list = NULL;
	}

	Choices<T>& operator=(Choices<T>&& other) noexcept {
		if (this != &other) {
			this->num_choices = other.num_choices;
			this->current_choices = other.current_choices;

			choices_list = other.choices_list;
			other.choices_list = NULL;
		}
		return *this;
	}

	~Choices() {
		delete[]choices_list;
	}

	void setMaxChoice(int num_choices) {
		if (current_choices > num_choices) {
			throw NumChoicesTooLow();
		}

		this->num_choices = num_choices;
	}

	void addChoice(T choice) {
		if (current_choices >= num_choices)
		{
			throw MaxChoicesExceeded();
		}

		choices_list[current_choices] = choice;
		current_choices++;
	}

	void displayChoices() {
		for (int i = 0; i < current_choices; i++) {
			cout << choices_list[i] << endl;
		}
	}

	void removeChoice(T choice) {

		if (current_choices == 0) { throw NoChoices(); }

		int index = 0;
		for (int i = 0; i < current_choices; i++) {
			if (choice == choices_list[i]) { index = i; }
		}

		T* new_choices = new T[num_choices - 1];
		current_choices--;

		for (int i = 0; i < current_choices; i++) {
			if (i < index) {
				new_choices[i] = choices_list[i];
			}
			else {
				new_choices[i] = choices_list[i - 1];
			}
		}

		delete[]choices_list;
		choices_list = new_choices;

	}

	friend bool operator==(const Choices<T>& ch1, const Choices<T>& ch2) {
		if (ch1.num_choices != ch2.num_choices) { return false; }

		for (int i = 0; i < ch1.num_choices; i++) {
			int flag = 0;
			for (int i = 0; i < ch2.num_choices; i++) {
				if (ch1.choices_list[i] == ch2.choices_list[i]) { flag++; }
			}
			if (flag == 0) { return false; }
		}

		return true;
	}
};