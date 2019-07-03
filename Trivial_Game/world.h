// ------------------------------------------------------------
//
// world.h
//
// Trivial Game v0.3.3
// A Simplified Version of SimCity
// Copyright © 2018-2019 Chenzhe Du, Jinghao Jiao, Zhiyu Sun, Jiayi Zheng.
//
// ------------------------------------------------------------

#pragma once

#ifndef _WORLD_H
#define _WORLD_H

#include "blocks.h"
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

using std::string;

class world
{
public:
	world( int i, int j)
	    : world_block{ create_a_world(i, j) }, worldx{ i }, worldy{ j }
    {
	};
	world()
		: world_block{ create_a_world(1,1) }, worldx{ 1 }, worldy{ 1 }
	{
	};
    std::vector<Block> useless{ Block(0,0) };
    std::vector<std::vector<Block>> world_block{ useless };
	void money_add(double n);
	void money_use(double n);
	int worldx;
	int worldy;
    
    double GDP{0};
    double RGDP{0};
    double total_popularity{0};
    double total_glad{0};
	int world_stop{ 0 };
	int world_start{ 0 };
	double row_support{ 100 };
	double showed_support{ fmin(100.0,row_support) };
	double moneyleft();
		
	double tax_rate{ 0.08 };
	string tax_rate_string = std::to_string(tax_rate);

	int money{ 500000 };

	bool gameover{ false };

private:

	// ------------------------------------------------------------
	// create a world
	// ------------------------------------------------------------

	std::vector<std::vector<Block>> create_a_world(int hang, int lie)
	{
		std::vector<std::vector<Block>> w;
		for (size_t i = 0; i < hang; i++)
		{
			std::vector<Block> hang;
			for (size_t j = 0; j < lie; j++)
			{
				hang.push_back(Block(i, j));
			}
			w.push_back(hang);
		}
		return w;
	}
};

inline void world::money_add(double n)
{
	money += n;
}

inline void world::money_use(double n)
{
	money -= n;
}

inline double world::moneyleft()
{
	return money;
}

#endif