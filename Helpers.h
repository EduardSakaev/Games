#include "stdafx.h"
#include "Holder.h"
#include <thread>
#include <cmath>


class Helpers
{
public:
	Helpers(Holder * _pHolder)
	{
		pHolder = _pHolder;
	}
	Holder * pHolder;
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

	void EntityFadeHide(double t0, double t1, std::string name)
	{
		Node * pSprite = pHolder -> GetEntityObjectByName(name);
		pSprite -> SetRespondable(false);

		std::thread thread_hide(Helpers::FadeHideFunction, t0, t1, pSprite);
	}

private:
	void FadeHideFunction(double t0, double t1, Node * pSprite)
	{
		double count_of_time = 0;
		while(true)
		{
			double ddelta = hge->Timer_GetDelta();
			count_of_time = count_of_time + ddelta;

			if (count_of_time >= t0)
			{
				double dpersdt = (count_of_time - t0)/(t1 - t0);
				int inewalpha = ceil(pSprite -> GetColorAlpha()*(1 - dpersdt));
				pSprite -> SetAlpha(inewalpha);
			}

			if (count_of_time >= t1)
			{
				return;
			}
		}
	}
};
