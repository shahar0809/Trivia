#include "Question.h"

Question::Question()
{

}

Question::Question(std::string question, std::vector<std::string> possibleAnswers,int correctAnsIndex)
{
	m_question = question;
	for (int i = 0; i < NUM_OF_POSSIBLE_ANSWERS; i++)
	{
		pushAnswerWithRandomIndex(possibleAnswers[i]);
		if (i == correctAnsIndex)
		{
			m_correctAnswer = possibleAnswers[i];
			m_correctAnswerId = m_possibleAnswers.begin()->first;
		}
	}
}

std::string Question::getQuestion()
{
	return m_question;
}

std::map<unsigned int, std::string> Question::getPossibleAnswers()
{
	return this->m_possibleAnswers;
}

void Question::pushAnswerWithRandomIndex(std::string ans)
{
	srand(time(NULL));
	int randomNum;
	do
	{
		randomNum = rand() % 4 + 1;
	}
	while (m_possibleAnswers.find(randomNum) != this->m_possibleAnswers.end());

	m_possibleAnswers.insert(std::pair<unsigned int, std::string>(randomNum, ans));
}

std::string Question::getCorrectAnswer()
{
	return m_correctAnswer;
}

unsigned int Question::getCorrectAnswerId()
{
	return m_correctAnswerId;
}
void Question::addPossibleAnswer(std::string answer) 
{ 
	pushAnswerWithRandomIndex(answer);
}
void Question::setCorrectAnswer(std::string correctAns) 
{ 
	pushAnswerWithRandomIndex(correctAns);
	m_correctAnswer = correctAns; 
	this->m_correctAnswerId = this->m_possibleAnswers.begin()->first;
}
