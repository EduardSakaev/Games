//
//#include "stdafx.h"
//#include <thread>
//
//class Timer
//{
//public:
//	Timer()
//	{
//      
//	}
//
//	void SetTimer(double time, void (*func)(void))
//	{
//		std::thread timer_thread(Add, time, func);
//		timer_thread.detach();
//	}
//
//	static void Add(double time, void (*func)(void))
//	{
//		while(true)
//		{
//			double ddelta = hge->Timer_GetDelta();
//			std::this_thread::sleep_for (std::chrono::milliseconds(int(ddelta * 1000)));
//			double count_of_time = count_of_time + ddelta;
//
//			if (count_of_time >= time)
//				func();
//		}
//	}
//
//	void ResetTimer()
//	{
//   
//	}
//};