#pragma once

#include "IRule.h"

template <typename T>
class RuleImpl : public IRule<T>
{
private:
	T answer;
public:
	RuleImpl(T answer);
	void execute(T challenge);
	bool isMatch();
};

template <class T>
RuleImpl<T>::RuleImpl(T answer)
{
	this->answer = answer;
}

template <class T>
void RuleImpl<T>::execute(T challenge)
{
	this->bExecuteResult = (challenge == answer);
}

template <class T>
bool RuleImpl<T>::isMatch()
{
	return this->bExecuteResult;
}