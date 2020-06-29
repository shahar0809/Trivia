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
		//answers.insert[i + 1] = m_possibleAnswers[i];
		pushAnswerWithRandomIndex(&answers, m_possibleAnswers[i]);
	}
	return answers;
}

void Question::pushAnswerWithRandomIndex(std::map<unsigned int, std::string>* answers, std::string ans)
{
	srand(time(NULL));
	int randomNum;
	do
	{
		randomNum = rand() % 4 + 1;
	}
	while (answers->find(randomNum) != answers->end());

	answers->insert(std::pair<unsigned int, std::string>(randomNum, ans));
}

std::string Question::getCorrectAnswer()
{
	return m_possibleAnswers[m_correctAnswerId];
}

unsigned int Question::getCorrectAnswerId()
{
	return m_correctAnswerId;
}