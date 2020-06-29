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
	void setQuestion(std::string question) { m_question = question; };
	std::map<unsigned int, std::string> getPossibleAnswers();
	std::string getCorrectAnswer();
	unsigned int getCorrectAnswerId();
	void addPossibleAnswer(std::string answer) { m_possibleAnswers.push_back(answer); };
	void pushAnswerWithRandomIndex(std::map<unsigned int, std::string>* answers, std::string ans);

private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	int m_correctAnswerId;
};

