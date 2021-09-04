#pragma once
#include "IRule.h"
template <class T>
class IRuleEvaluator
{
public:
	virtual void addRule(const T& rule) = 0;
	virtual bool delRule(const T& rule) = 0;
	virtual ~IRuleEvaluator() {}
};