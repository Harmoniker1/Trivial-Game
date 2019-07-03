// ------------------------------------------------------------
//
// blocks.h
//
// Trivial Game
// A Simplified Version of SimCity®
// Copyright © 2018-2019 Chenzhe Du, Jinghao Jiao, Zhiyu Sun, Jiayi Zheng. All Rights Reserved.
//
// ------------------------------------------------------------

#pragma once

#ifndef _BLOCKS_H
#define _BLOCKS_H

#include <iostream>
#include <vector>
#include <algorithm>

 // --------------------------------
 // the definition of the class "Block"
 // --------------------------------

class Block
{
	public:
		Block(int xx, int yy)
			:x{ xx }, y{ yy }
		{
		};
		Block()
			:x{ 0 }, y{ 0 }
		{
		};

		// FUNDAMENTAL
			// what
		int kind{ 0 };
		int assistant_kind{ 0 };
		int public_building{ 0 };
		int ppublicbuilding{ 0 };
		int roaddirection{ 0 };
			// where
		int x;
		int y;
			// detail
		int level{ 0 };
		int aim_level{ 0 };
		
		// residental
		int popularity{ 1 };
		double row_popularity{ 1 };

		double strange_popularity{ 0 };
		
		double economy{ 0 };
		double goods{ 0 };
		double landprice{ 0 };
		int crime{ 10 };

		double glad{ 0 };
		double aim_glad{ 0 };

		// construcing state
		int changing{ 0 };
		int process{ 0 };

		// assistant block
		std::vector<int> mainplace{0, 0};

		double education{ 0 };
		double protection{ 0 };
		double local_water{ 0 };
		double health{ 0 };
};

#endif