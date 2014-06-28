#include "stdafx.h"
#include "Holder.h"
#include <thread>
#include <cmath>
#include <chrono>


class Helpers
{
	Holder * pHolder;

public:
	Helpers(Holder * _pHolder)
	{
		pHolder = _pHolder;
	}
	
	void EntityHide(std::string name)
	{
		Node * pSprite = pHolder -> GetEntityObjectByName(name);
		pSprite -> SetVisible(false);
		pSprite -> SetRespondable(false);
	}

	void EntityShow(std::string name)
	{
		Node * pSprite = pHolder -> GetEntityObjectByName(name);
		pSprite -> SetVisible(false);
		pSprite -> SetRespondable(false);
	}

	Node * GetEntityNamed(std::string name)
	{
		return pHolder -> GetEntityObjectByName(name);
	}

	void EntityFadeHide(std::string name, double t1 = 0.25, double t0 = 0)
	{
		Node * pSprite = pHolder -> GetEntityObjectByName(name);
		pSprite -> SetRespondable(false);

		std::thread entityfadehide_thread(FadeHideFunction, pSprite, t1, t0);
		entityfadehide_thread.detach();
	}
	void EntityFadeShow(std::string name, double t1 = 0.25, double t0 = 0)
	{
		Node * pSprite = pHolder -> GetEntityObjectByName(name);
		pSprite -> SetRespondable(true);

		std::thread entityfadeshow_thread(FadeShowFunction, pSprite, t1, t0);
		entityfadeshow_thread.detach();
	}
	void ChangeScaleX(std::string name, double scalex_begin, double scalex_end, double t1 = 0.25, double t0 = 0)
	{
		Node * pSprite = pHolder -> GetEntityObjectByName(name);
		pSprite -> SetRespondable(true);

		std::thread changescalex_thread(ChangeScaleXFunction, pSprite, scalex_begin, scalex_end, t1, t0);
		changescalex_thread.detach();
	}
	void ChangeScaleY(std::string name, double scalex_begin, double scalex_end, double t1 = 0.25, double t0 = 0)
	{
		Node * pSprite = pHolder -> GetEntityObjectByName(name);
		pSprite -> SetRespondable(true);

		std::thread changescalex_thread(ChangeScaleYFunction, pSprite, scalex_begin, scalex_end, t1, t0);
		changescalex_thread.detach();
	}

	void MoveTo(std::string name, int x, int y, double t1 = 0.25, double t0 = 0)
	{
		Node * pSprite = pHolder -> GetEntityObjectByName(name);
		std::thread MoveTo_thread(MoveToFunction, pSprite, x, y, t1, t0);
		MoveTo_thread.detach();
	}

	/*void ChangeScale(std::string name, double scalex_begin, double scalex_end, double t1 = 0.25, double t0 = 0)
	{
		Node * pSprite = pHolder -> GetEntityObjectByName(name);
		pSprite -> SetRespondable(true);

		std::thread changescalex_thread(ChangeScaleFunction, pSprite, scalex_begin, scalex_end, t1, t0);
		changescalex_thread.detach();
	}*/

private:
	static void FadeHideFunction(Node * pSprite, double t1, double t0)
	{
		double count_of_time = 0;
		int alpha = pSprite -> GetColorAlpha();
		while(true)
		{
			double ddelta = hge->Timer_GetDelta();
			std::this_thread::sleep_for (std::chrono::milliseconds(int(ddelta * 1000)));
			count_of_time = count_of_time + ddelta;

			if (count_of_time >= t0)
			{
				double dpersdt = (count_of_time - t0)/(t1 - t0);
				int inewalpha = ceil(alpha*(1 - dpersdt));
				pSprite -> SetAlpha(inewalpha);
			}

			if (count_of_time > t1)
			{
				return;
			}
		}
	}

	static void FadeShowFunction(Node * pSprite, double t1, double t0)
	{
		double count_of_time = 0;
		int alpha = pSprite -> GetColorAlpha();
		while(true)
		{
			double ddelta = hge->Timer_GetDelta();
			std::this_thread::sleep_for (std::chrono::milliseconds(int(ddelta * 1000)));
			count_of_time = count_of_time + ddelta;

			if (count_of_time >= t0)
			{
				double dpersdt = (count_of_time - t0)/(t1 - t0);
				int inewalpha = ceil((255 - alpha)*dpersdt + alpha);
				pSprite -> SetAlpha(inewalpha);
			}

			if (count_of_time > t1)
			{
				return;
			}
		}
	}
	static void ChangeScaleXFunction(Node * pSprite, double scalex_begin, double scalex_end, double t1, double t0)
	{
		float count_of_time = 0;
		float dScaleX = scalex_end - scalex_begin;

		while(true)
		{
			float ddelta = hge->Timer_GetDelta();
			std::this_thread::sleep_for (std::chrono::milliseconds(int(ddelta * 1000)));
			count_of_time = count_of_time + ddelta;
			
			if (count_of_time >= t0)
			{
				float dpersdt = (count_of_time - t0)/(t1 - t0);
				float fnewscale = dScaleX*dpersdt + scalex_begin;
				pSprite -> SetScaleX(fnewscale);
			}

			if (count_of_time > t1)
			{
				return;
			}
		}
	}
	static void ChangeScaleYFunction(Node * pSprite, double scalex_begin, double scalex_end, double t1, double t0)
	{
		float count_of_time = 0;
		float dScaleY = scalex_end - scalex_begin;

		while(true)
		{
			float ddelta = hge->Timer_GetDelta();
			std::this_thread::sleep_for (std::chrono::milliseconds(int(ddelta * 1000)));
			count_of_time = count_of_time + ddelta;
			
			if (count_of_time >= t0)
			{

				float dpersdt = (count_of_time - t0)/(t1 - t0);
				float fnewscale = dScaleY*dpersdt + scalex_begin;
				pSprite -> SetScaleY(fnewscale);
			}

			if (count_of_time > t1)
			{
				return;
			}
		}
	}

	static void MoveToFunction(Node * pSprite, int x, int y, double t1 = 0.25, double t0 = 0)
	{
		int x_start = pSprite -> GetScrX();
		int y_start = pSprite -> GetScrY();
		float l = sqrt((x_start - x)*(x_start - x) + (y_start - y)*(y_start - y));
		float count_of_time = 0;

		while(true)
		{
			float ddelta = hge->Timer_GetDelta();
			std::this_thread::sleep_for (std::chrono::milliseconds(int(ddelta * 1000)));
			count_of_time = count_of_time + ddelta;
			
			if (count_of_time >= t0)
			{
				float dpersdt = (count_of_time - t0)/(t1 - t0);
				float dl = l * dpersdt;

				int dx = dl * (x - x_start) / l + x_start; 
				int dy = (dl * (y - y_start) + y_start * l) / l;

				pSprite -> SetScrXY(dx, dy);
			}

			if (count_of_time > t1)
			{
				return;
			}
		}
	}

	/*static void ChangeScaleFunction(Node * pSprite, double scalex_begin, double scalex_end, double t1, double t0)
	{
		float count_of_time = 0;
		float dScale = abs(scalex_begin - scalex_end);

		while(true)
		{
			float ddelta = hge->Timer_GetDelta();
			std::this_thread::sleep_for (std::chrono::milliseconds(int(ddelta * 1000)));
			count_of_time = count_of_time + ddelta;
			
			if (count_of_time >= t0)
			{

				float dpersdt = (count_of_time - t0)/(t1 - t0);
				float fnewscale = ceil(dScale*dpersdt + scalex_begin);
				pSprite -> SetScale(fnewscale, fnewscale);
			}

			if (count_of_time >= t1)
			{
				return;
			}
		}
	}*/
};
