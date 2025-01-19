#pragma once
#include <iostream>
using namespace std;

class MaxChoicesExceeded : public exception
{
public:
	const char* what() const override {
		return "Max Choices Exceeded.. Cannot have more";
	}
};

class Voted : public exception
{
public:
	const char* what() const override {
		return "All choices are ranked";
	}
};

class NotEnoughChoices : public exception
{
public:
	const char* what() const override {
		return "Not Enough choices\n Cannot vote. Reduce number of choices or add more choices";
	}
};

class NumChoicesTooLow : public exception
{
public:
	const char* what() const override {
		return "You already have more choices. To remove choices, use removeChoice method";
	}
};

class NoChoices : public exception
{
public:
	const char* what() const override {
		return "There are no choices to remove";
	}
};

class RankInvalid : public exception
{
public:
	const char* what() const override {
		return "Rank assigned is invalid... Please try again";
	}
};

class IncompatibleVoteType : public exception
{
public:
	const char* what() const override {
		return "The Vote is incompatible with other votes as it has different choices";
	}
};