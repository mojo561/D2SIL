#pragma once
template <class ...Args>
class IRule
{
protected:
	bool bExecuteResult;
public:
	virtual void execute(Args...) = 0;
	virtual bool isMatch() = 0;

	virtual ~IRule() {}
};