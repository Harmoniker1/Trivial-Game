// ------------------------------------------------------------
//
// function.cpp
//
// Trivial Game
// A Simplified Version of SimCity
// Copyright © 2018-2019 Chenzhe Du, Jinghao Jiao, Zhiyu Sun, Jiayi Zheng.
//
// ------------------------------------------------------------

#include "function.h"
#include <cmath>

// ------------------------------------------------------------
// change_kind
// ------------------------------------------------------------

void change_kind(int n, Block& b, world& w)
{
	// std::cout << b.kind << n;
	if (b.assistant_kind == n)
	{
		//throw std::runtime_error{ "This block already has the type of construction/area you've chosen." };
		return;
	}
	if (n==0)
	{
		//std::cout << 8888888888888;
		b.assistant_kind = b.kind;
		//b.public_building = 0;
		b.kind = 0;
		b.changing = -1;
		if (b.level==0&&b.assistant_kind!=6)
		{
			b.process = 1;
		}
		else
		{
			b.process = 4;
		}
		b.popularity = 0;
		b.row_popularity = 0;
		if ((b.assistant_kind==5&&b.public_building>=10)||b.assistant_kind==3)
		{
			int m{ b.roaddirection };
			// std::cout << m;
			if (m == 1)
			{
				for (int i = 0; i < 2; i++)
				{
					for (int j = -1; j < 2; j++)
					{
						if (i != 0 || j != 0)
						{
							change_kind(0, w.world_block[b.x + j][b.y + i], w);
							w.world_block[b.x + j][b.y + i].mainplace[0] = 0;
							w.world_block[b.x + j][b.y + i].mainplace[1] = 0;
						}
					}
				}
				return;
			}
			if (m == 2)
			{
				for (size_t i = 0; i < 2; i++)
				{
					for (int j = -1; j < 2; j++)
					{
						if (i != 0 || j != 0)
						{
							change_kind(0, w.world_block[b.x + i][b.y + j], w);
							w.world_block[b.x + i][b.y + j].mainplace[0] = 0;
							w.world_block[b.x + i][b.y + j].mainplace[1] = 0;
						}
					}
				}
				return;
			}
			if (m == 3)
			{
				for (size_t i = 0; i < 2; i++)
				{
					for (int j = -1; j < 2; j++)
					{
						if (i != 0 || j != 0)
						{
							change_kind(0, w.world_block[b.x + j][b.y - i], w);
							w.world_block[b.x + j][b.y - i].mainplace[0] = 0;
							w.world_block[b.x + j][b.y - i].mainplace[1] = 0;
						}
					}
				}
				return;
			}
			if (m == 4)
			{
				for (int i = 0; i < 2; i++)
				{
					for (int j = -1; j < 2; j++)
					{
						if (i != 0 || j != 0)
						{
							change_kind(0, w.world_block[b.x - i][b.y + j], w);
							w.world_block[b.x - i][b.y + j].mainplace[0] = 0;
							w.world_block[b.x - i][b.y + j].mainplace[1] = 0;
						}
					}
				}
				return;
			}
			b.roaddirection = 0;
		}
		return;
	}
	if (b.kind != 0)
	{
		throw std::runtime_error{ "Please remove the current construction/area you've set first." };
		return;
	}
	if (n==4)
	{
		b.level = 1;
		b.aim_level = 1;
		b.assistant_kind = n;
		w.money_use(block_cost[n]);
		b.changing = 1;
		b.process = 4;
		return;
	}
	if (n==6)
	{
		b.assistant_kind = 6;
		b.kind = 6;
		//std::cout << "mmmmmmmmmmm";
		return;
	}
	if (next_to_road(b, w) == 0&&w.world_start==1)
	{
		throw std::runtime_error{ "road required" };
	}
	if ((next_to_road(b, w) != 0||w.world_start==0) && n != 5)
	{
		b.level = 0;
		b.kind = n;
		b.assistant_kind = n;
		b.process = 1;
		if (n == 1)
		{
			b.popularity = 1;
			b.row_popularity = 1;
		}
		w.money_use(block_cost[n]);
		return;
	}
	if (n == 5 && b.public_building != 0)
	{
		b.level = 1;
		b.aim_level = 1;
		b.assistant_kind = 5;
		b.changing = 1;
		b.process = 4;
		return;
	}
	return;
}

void build_a_factory(Block & b, world & w)
{
	int m{ empty(b,w) };
	b.roaddirection = m;
	//std::cout << m;
	if (m == 0)
	{
		throw std::runtime_error{ "Enough space is required to build." };
		return;
	}
	if (m == 1)
	{
		for (size_t i = 0; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (i != 0 || j != 0)
				{
					change_kind(6, w.world_block[b.x + j][b.y + i], w);
					w.world_block[b.x + j][b.y + i].mainplace[0] = b.x;
					w.world_block[b.x + j][b.y + i].mainplace[1] = b.y;
				}
			}
		}
		change_kind(3, b, w);
		w.money_use(public_buildcost[3]);
		return;
	}
	if (m == 2)
	{
		for (size_t i = 0; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (i != 0 || j != 0)
				{
					change_kind(6, w.world_block[b.x + i][b.y + j], w);
					w.world_block[b.x + i][b.y + j].mainplace[0] = b.x;
					w.world_block[b.x + i][b.y + j].mainplace[1] = b.y;
				}
			}
		}
		change_kind(3, b, w);
		w.money_use(public_buildcost[3]);
		return;
	}
	if (m == 3)
	{
		for (size_t i = 0; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (i != 0 || j != 0)
				{
					change_kind(6, w.world_block[b.x + j][b.y - i], w);
					w.world_block[b.x + j][b.y - i].mainplace[0] = b.x;
					w.world_block[b.x + j][b.y - i].mainplace[1] = b.y;
				}
			}
		}
		change_kind(3, b, w);
		w.money_use(public_buildcost[3]);
		return;
	}
	if (m == 4)
	{
		for (size_t i = 0; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (i != 0 || j != 0)
				{
					change_kind(6, w.world_block[b.x - i][b.y + j], w);
					w.world_block[b.x - i][b.y + j].mainplace[0] = b.x;
					w.world_block[b.x - i][b.y + j].mainplace[1] = b.y;
				}
			}
		}
		change_kind(3, b, w);
		w.money_use(public_buildcost[3]);
		return;
	}
}

//void use_change_kind(int n, Block& b, world& w)
//{
	//std::thread t(change_kind, n, b, w);
	//t.detach();
//}

// ------------------------------------------------------------
// build_a_public_building
// ------------------------------------------------------------

void build_a_public_building(int n, Block& b, world& w)
{
	// std::cout << n;
	b.ppublicbuilding = n;
	b.public_building = n;
	if (n < 10)
	{
		change_kind(5, b, w);
		if (b.assistant_kind != 5)
		{
			//b.public_building = 0;
		}
		else
		{
			w.money_use(public_buildcost[n]);
		}
	}
	else
	{
		// std::cout << n;
		int m{ empty(b,w) };
		b.roaddirection = m;
		// std::cout << m;
		if (m==0)
		{
			b.public_building = 0;
			throw std::runtime_error{ "Enough space is required to build." };
			return;
		}
		if (m == 1)
		{
			for (int i = 0; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					if (i != 0 || j != 0)
					{
						change_kind(6, w.world_block[b.x + j][b.y + i], w);
						w.world_block[b.x + j][b.y + i].mainplace[0] = b.x;
						w.world_block[b.x + j][b.y + i].mainplace[1] = b.y;
					}
				}
			}
			change_kind(5, b, w);
			w.money_use(public_buildcost[n]);
			return;
		}
		if (m == 2)
		{
			for (int i = 0; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					if (i != 0 || j != 0) 
					{
						change_kind(6, w.world_block[b.x + i][b.y + j], w);
						w.world_block[b.x + i][b.y + j].mainplace[0] = b.x;
						w.world_block[b.x + i][b.y + j].mainplace[1] = b.y;
					}
				}
			}
			change_kind(5, b, w);
			w.money_use(public_buildcost[n]);
			return ;
		}
		if (m == 3)
		{
			for (size_t i = 0; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					if (i != 0 || j != 0)
					{
						change_kind(6, w.world_block[b.x + j][b.y - i], w);
						w.world_block[b.x + j][b.y - i].mainplace[0] = b.x;
						w.world_block[b.x + j][b.y - i].mainplace[1] = b.y;
					}
				}
			}
			change_kind(5, b, w);
			w.money_use(public_buildcost[n]);
			return;
		}
		if (m == 4)
		{
			for (int i = 0; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					if (i != 0 || j != 0)
					{
						change_kind(6, w.world_block[b.x - i][b.y + j], w);
						w.world_block[b.x - i][b.y + j].mainplace[0] = b.x;
						w.world_block[b.x - i][b.y + j].mainplace[1] = b.y;
					}
				}
			}
			change_kind(5, b, w);
			w.money_use(public_buildcost[n]);
			return;
		}
	}
}

// ------------------------------------------------------------
// level_up
// ------------------------------------------------------------

void level_up(Block& b, world& w)
{
	b.aim_level = b.level + 1;
	b.changing = 1;
	b.process = 4;
	w.money_use(block_level_up_cost[b.kind]);
	w.money_use(public_level_up_cost[b.public_building]);
}

// ------------------------------------------------------------
// need_for_house
// ------------------------------------------------------------

double need_for_house(const Block& b, const world& w)
{
	if (b.kind == 0)
	{
		return 0;
	}
	if (b.kind == 1)
	{
		return 0;
	}
	if (b.kind == 2)
	{
		int total = b.level * 50;
		int now{ 0 };
		for (size_t i = std::fmax(0, b.x - 2); i < std::fmin(b.x + 3, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 2); j < std::fmin(w.worldy, b.y + 3); j++)
			{
				if (w.world_block[i][j].kind == 1)
				{
					now += w.world_block[i][j].popularity;
				}
			}
		}
		int divide{ 0 };
		for (size_t i = std::fmax(0, b.x - 2); i < std::fmin(b.x + 3, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 2); j < std::fmin(w.worldy, b.y + 3); j++)
			{
				if (w.world_block[i][j].kind == 2)
				{
					divide += w.world_block[i][j].level;
				}
			}
		}
		if(divide==0)
        {
            return 0;
        }
		return total - b.level * now / divide;
	}
	if (b.kind == 3)
	{
		int total = b.level * 40;
		int now{ 0 };
		for (size_t i = std::fmax(0, b.x - 4); i < std::fmin(b.x + 5, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 4); j < std::fmin(w.worldy, b.y + 5); j++)
			{
				if (w.world_block[i][j].kind == 1)
				{
					now += w.world_block[i][j].popularity;
				}
			}
		}
		int divide{ 0 };
		for (size_t i = std::fmax(0, b.x - 4); i < std::fmin(b.x + 5, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 4); j < std::fmin(w.worldy, b.y + 5); j++)
			{
				if (w.world_block[i][j].kind == 3)
				{
					divide += w.world_block[i][j].strange_popularity;
				}
			}
		}
		if(divide==0)
        {
            return 0;
        }
		return total - b.strange_popularity * now / divide;
	}
	return 0.0;
}

// ------------------------------------------------------------
// need_for_trade
// ------------------------------------------------------------

double need_for_trade(const Block& b, const world& w)
{
	if (b.kind == 0)
	{
		return 0;
	}
	if (b.kind == 2)
	{
		return 0;
	}
	if (b.kind == 1)
	{
		int total = (1 + b.level / 10)*(1 / 50)*(b.popularity) ;
		int now{ 0 };
		for (size_t i = std::fmax(0, b.x - 3); i < std::fmin(b.x + 4, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 3); j < std::fmin(w.worldy, b.y + 4); j++)
			{
				if (w.world_block[i][j].kind == 2)
				{
					now += w.world_block[i][j].level;
				}
			}
		}
		int divide{ 0 };
		for (size_t i = std::fmax(0, b.x - 3); i < std::fmin(b.x + 4, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 3); j < std::fmin(w.worldy, b.y + 4); j++)
			{
				if (w.world_block[i][j].kind == 1)
				{
					divide += w.world_block[i][j].popularity;
				}
			}
		}
		if(divide==0)
        {
            return 0;
        }
		return total - b.popularity * now / divide;
	}
	if (b.kind == 3)
	{
		int total = b.level * 2;
		int now{ 0 };
		for (size_t i = std::fmax(0, b.x - 10); i < std::fmin(b.x + 11, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 10); j < std::fmin(w.worldy, b.y + 10); j++)
			{
				if (w.world_block[i][j].kind == 2)
				{
					now += w.world_block[i][j].level;
				}
			}
		}
		int divide{ 0 };
		for (size_t i = std::fmax(0, b.x - 10); i < std::fmin(b.x + 11, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 10); j < std::fmin(w.worldy, b.y + 11); j++)
			{
				if (w.world_block[i][j].kind == 3)
				{
					divide += w.world_block[i][j].level;
				}
			}
		}
		if(divide==0)
        {
            return 0;
        }
		return total - b.level * now / divide;
	}
	return 0.0;
}

// ------------------------------------------------------------
// need_for_goods
// ------------------------------------------------------------

double need_for_goods(const Block& b, const world& w)
{
	if (b.kind == 0)
	{
		return 0;
	}
	if (b.kind == 3)
	{
		return 0;
	}
	if (b.kind == 1)
	{
		return 0;
	}
	if (b.kind == 2)
	{
		int total = b.level / 2;
		int now{ 0 };
		for (size_t i = std::fmax(0, b.x - 10); i < std::fmin(b.x + 11, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 10); j < std::fmin(w.worldy, b.y + 11); j++)
			{
				if (w.world_block[i][j].kind == 3)
				{
					now += w.world_block[i][j].level;
				}
			}
		}
		int divide{ 0 };
		for (size_t i = std::fmax(0, b.x - 10); i < std::fmin(b.x + 11, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 10); j < std::fmin(w.worldy, b.y + 11); j++)
			{
				if (w.world_block[i][j].kind == 2)
				{
					divide += w.world_block[i][j].level;
				}
			}
		}
		if(divide==0)
        {
            return 0;
        }
		return total - b.level * now / divide;
	}
	return 0.0;
}

// ------------------------------------------------------------
// need_for_job
// ------------------------------------------------------------

double need_for_job(const Block& b, const world& w)
{
	if (b.kind == 1)
	{
		double total{ b.popularity*0.4 };
		int now{ 0 };
		for (size_t i = std::fmax(0, b.x - 8); i < std::fmin(b.x + 9, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 8); j < std::fmin(w.worldy, b.y + 9); j++)
			{
				if (w.world_block[i][j].kind == 3)
				{
					now += w.world_block[i][j].level * 40;
				}
				if (w.world_block[i][j].kind == 2)
				{
					now += w.world_block[i][j].level * 30;
				}
			}
		}
		int divide{ 0 };
		for (size_t i = std::fmax(0, b.x - 8); i < std::fmin(b.x + 9, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 8); j < std::fmin(w.worldy, b.y + 9); j++)
			{
				if (w.world_block[i][j].kind == 1)
				{
					divide += w.world_block[i][j].popularity;
				}
			}
		}
		if(divide==0)
        {
            return 0;
        }
		return total - now * b.popularity / divide;
	}
	return 0.0;
}

double need_for_this_house(const Block & b, const world & w)
{
	double now{ 10 };
	for (size_t i = std::fmax(0, b.x - 2); i < std::fmin(b.x + 3, w.worldx); i++)
	{
		for (int j = std::fmax(0, b.y - 2); j < std::fmin(w.worldy, b.y + 3); j++)
		{
			now += need_for_house(w.world_block[i][j],w);
		}
	}
	for (size_t i = std::fmax(0, b.x - 10); i < std::fmin(b.x + 11, w.worldx); i++)
	{
		for (int j = std::fmax(0, b.y - 10); j < std::fmin(w.worldy, b.y + 11); j++)
		{
			if (w.world_block[i][j].kind==3)
			{
				now += need_for_house(w.world_block[i][j], w)/5;
			}
		}
	}
	return now;
}

double need_for_this_trade(const Block & b, const world & w)
{
	double now{ 10 };
	for (size_t i = std::fmax(0, b.x - 3); i < std::fmin(b.x + 4, w.worldx); i++)
	{
		for (int j = std::fmax(0, b.y - 3); j < std::fmin(w.worldy, b.y + 4); j++)
		{
			now += need_for_trade(w.world_block[i][j], w);
		}
	}
	for (size_t i = std::fmax(0, b.x - 10); i < std::fmin(b.x + 11, w.worldx); i++)
	{
		for (int j = std::fmax(0, b.y - 10); j < std::fmin(w.worldy, b.y + 11); j++)
		{
			if (w.world_block[i][j].kind == 3)
			{
				now += need_for_trade(w.world_block[i][j], w) / 5;
			}
		}
	}
	return now;
}

double need_for_this_goods(const Block & b, const world & w)
{
	double now{10 };
	for (size_t i = std::fmax(0, b.x - 10); i < std::fmin(b.x + 11, w.worldx); i++)
	{
		for (int j = std::fmax(0, b.y - 10); j < std::fmin(w.worldy, b.y + 11); j++)
		{
			now += need_for_house(w.world_block[i][j], w);
		}
	}
	return now;
}

// ------------------------------------------------------------
// next_to_road
// ------------------------------------------------------------

int next_to_road(const Block& b, const world& w)
{
	int road(0);
	if (w.world_block[b.x][b.y - 1].kind == 4)
	{
		return 1;
	}
	if (w.world_block[b.x - 1][b.y].kind == 4)
	{
		return 2;
	}
	if (w.world_block[b.x][b.y + 1].kind == 4)
	{
		return 3;
	}
	if (w.world_block[b.x + 1][b.y].kind == 4)
	{
		return 4;
	}
	return road;
}

// ------------------------------------------------------------
// bool empty
// ------------------------------------------------------------

int empty(Block& b, const world& w)
{
	int kong{ 0 };
	int n = next_to_road(b, w);
	// std::cout << n;
	if (n == 0)
	{
		b.public_building = 0;
		throw std::runtime_error{ "Road required" };
		return kong;
	}
	else if (n == 1)
	{
		kong = 1;
		for (size_t i = 0; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (!(w.world_block[b.x + j][b.y + i].kind==0))
				{
					return 0;
				}
			}
		}
		return kong;
	}
	else if (n == 2)
	{
		kong = 2;
		// std::cout << kong;
		for (size_t i = 0; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (!(w.world_block[b.x + i][b.y + j].kind==0))
				{
					kong = 0;
				}
			}
		}
		// std::cout << kong;
		return kong;
	}
	else if (n == 3)
	{
		kong = 3;
		for (size_t i = 0; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (!(w.world_block[b.x + j][b.y - i].kind ==0))
				{
					kong = 0;
				}
			}
		}
		return kong;
	}
	else if (n == 4)
	{
		kong = 4;
		for (size_t i = 0; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (!(w.world_block[b.x - i][b.y + j].kind==0))
				{
					kong = 0;
				}
			}
		}
		return kong;
	}
	return kong;
}

// ------------------------------------------------------------
// int traffic
// ------------------------------------------------------------

int traffic(const Block& b, const world& w)
{
	int n{ 0 };
	for (size_t i = std::fmax( b.x - 1,0 ); i < std::fmin(b.x + 2,w.worldx) ; i++)
	{
		for (int j = std::fmax(b.y - 1,0); j < std::fmin(b.y + 2,w.worldy) ; j++)
		{
			if (w.world_block[i][j].kind == 4)
			{
				n += w.world_block[i][j].level;
			}
		}
	}
	return n;
}