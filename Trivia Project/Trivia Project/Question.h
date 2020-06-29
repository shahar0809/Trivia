#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <time.h>

#define NUM_OF_POSSIBLE_ANSWERS 4

class Question
{
public:
	Question(std::string question, std::vector<std::string> possibleAnswers, int correctAnsId);
	std::string getQuestion();
	std::map<unsigned int, std::string> getPossibleAnswers();
	std::string getCorrectAnswer();
	unsigned int getCorrectAnswerId();
	void pushAnswerWithRandomIndex(std::map<unsigned int, std::string>* answers, std::string ans);

private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	int m_correctAnswerId;
};

