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
	Question();
	Question(std::string question, std::vector<std::string> possibleAnswers, int correctAns);

	std::string getQuestion();
	void setQuestion(std::string question) { m_question = question; };
	void addPossibleAnswer(std::string answer);
	void setCorrectAnswer(std::string correctAns); 

	std::map<unsigned int, std::string> getPossibleAnswers();
	std::string getCorrectAnswer();
	unsigned int getCorrectAnswerId();
	void pushAnswerWithRandomIndex(std::string ans);

private:
	std::string m_correctAnswer;
	std::string m_question;
	std::map<unsigned int,std::string> m_possibleAnswers;
	int m_correctAnswerId;
};

