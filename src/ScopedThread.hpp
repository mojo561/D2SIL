#pragma once

/*
references:
https://leimao.github.io/blog/CPP-Ensure-Join-Detach-Before-Thread-Destruction/
https://www.geeksforgeeks.org/g-fact-93/
*/

/*
need this to make the compiler happy (undefined)
*/
template< class >
class ScopedThread;

template<class fn, class ...Args>
class ScopedThread<fn(Args...)>
{
private:
	std::atomic_bool isDestructing;
	std::function<fn(Args...)> fnCallback;
public:
	explicit ScopedThread(std::function<fn(Args...)> func) : isDestructing(false)
	{
		fnCallback = std::function<fn(Args...)>(func);
	}

	inline void start(Args&&... args)
	{
		if (!isDestructing)
		{
			std::thread t = std::thread([this, &args...]() {
				(fnCallback)(std::forward<Args>(args)...);
			});

			t.detach();
		}
	}

	inline void startRepeated(Args&&... args)
	{
		if (!isDestructing)
		{
			std::thread t = std::thread([this, &args...]() {
				while (!isDestructing)
				{
					(fnCallback)(std::forward<Args>(args)...);
				}
			});

			t.detach();
		}
	}

	~ScopedThread()
	{
		isDestructing = true;
	}
};