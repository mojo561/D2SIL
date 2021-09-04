#pragma once

#include "IRuleEvaluator.h"
#include "RuleImpl.hpp"

template <typename T>
class RuleEvaluatorImpl : public IRuleEvaluator<RuleImpl<T>>
{
public:
	bool evaluate(T foo) const;
	void addRule(const RuleImpl<T>& rule);
	bool delRule(const RuleImpl<T>& rule);
	void delRules(void) noexcept;
private:
	std::unordered_map<uintptr_t, std::unique_ptr<RuleImpl<T>>> rules;
	std::unique_ptr<RuleImpl<T>> clone(const RuleImpl<T>& rule);
};

template <class T>
inline bool RuleEvaluatorImpl<T>::evaluate(T foo) const
{
	for (auto itor = rules.begin(); itor != rules.end(); ++itor)
	{
		itor->second->execute(foo);
		if (itor->second->isMatch())
		{
			return true;
		}
	}
	return false;
}

/*
Copies 'rule'.
*/
template <class T>
inline void RuleEvaluatorImpl<T>::addRule(const RuleImpl<T>& rule)
{
	uintptr_t nKey = std::hash<uintptr_t>{}( reinterpret_cast<uintptr_t>( &rule ) );
	auto x = std::make_pair(nKey, std::move(clone(rule)));
	rules.insert(std::move(x));
}

/*
returns true when erasure from internal storage is successful.
*/
template <class T>
inline bool RuleEvaluatorImpl<T>::delRule(const RuleImpl<T>& rule)
{
	uintptr_t nKey = std::hash<uintptr_t>{}( reinterpret_cast<uintptr_t>( &rule ) );
	return static_cast<bool>( rules.erase(nKey) );
}

/*
remove all rule elements from internal storage.
*/
template <class T>
inline void RuleEvaluatorImpl<T>::delRules(void) noexcept
{
	rules.clear();
}

template <class T>
inline std::unique_ptr<RuleImpl<T>> RuleEvaluatorImpl<T>::clone(const RuleImpl<T>& rule)
{
	return std::unique_ptr<RuleImpl<T>>(new RuleImpl<T>(rule));
}