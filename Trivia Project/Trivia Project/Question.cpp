#include "Question.h"

Question::Question(std::string question, std::vector<std::string> possibleAnswers, int correctAnsId)
{
	m_question = question;
	m_possibleAnswers = possibleAnswers;
	m_correctAnswerId = correctAnsId;
}

std::string Question::getQuestion()
{
	return m_question;
}

std::map<unsigned int, std::string> Question::getPossibleAnswers()
{
	std::map<unsigned int, std::string> answers;

	for (int i = 0; i < NUM_OF_POSSIBLE_ANSWERS; i++)
	{
		answers.insert[i + 1] = m_possibleAnswers[i];
	}
	return answers;
}

std::string Question::getCorrectAnswer()
{
	return m_possibleAnswers[m_correctAnswerId];
}

unsigned int Question::getCorrectAnswerId()
{
	return m_correctAnswerId;
}