#include "Question.h"

Question::Question()
{

}

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

	pushAnswerWithRandomIndex(&answers, m_possibleAnswers[0]);
	m_correctAnswerId = answers.begin()->first;

	for (int i = 1; i < NUM_OF_POSSIBLE_ANSWERS; i++)
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

void Question::setQuestion(std::string question)
{
	this->m_question = question;
}