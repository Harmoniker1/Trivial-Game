// ------------------------------------------------------------
//
// block_run.cpp
//
// Trivial Game v0.3.3
// A Very Simple Re-creation of SimCity
// Copyright © 2018-2019 Chenzhe Du, Jinghao Jiao, Zhiyu Sun, Jiayi Zheng.
//
// Disclaimer: This is only a course project, no commercial interest is involved.
// ------------------------------------------------------------

#include "block_run.h"

// ------------------------------------------------------------
// timego
// ------------------------------------------------------------

void timego(world * ww, Main_window* wwin)
{
	world& w = *ww;
	Main_window& win{ *wwin };
	for (size_t i = 0; i < w.worldx; i++)
	{
		for (size_t j = 0; j < w.worldy; j++)
		{
			Block& b{ w.world_block[i][j] };
			if ((b.kind == 0 || b.kind == 4 || b.kind == 6) && b.changing == 0)
			{
			}
			else if (b.changing == -1)
			{
				if (b.process != 0)
				{
					win.draw_block(b);
					b.process--;
				}
				else
				{
					b.assistant_kind = 0;
					b.level = 0;
					b.public_building = 0;
					win.draw_block(b);
					b.changing = 0;
					w.money_use(public_runcost[b.public_building]);
				}
			}
			else if (b.changing != 0)
			{
				// std::cout << b.x << 'm' << b.y <<'n'<<b.process<< std::endl;//test
				win.draw_block(b);
				std::cout << b.process;
				if (b.process != 0)
				{
					std::cout << b.process;
					b.process--;
					win.draw_block(b);
				}
				else
				{
					b.changing = 0;
					b.level = b.aim_level;
					b.kind = b.assistant_kind;
				}
			}
			else if (b.changing == 0 && b.level == 0 && b.kind != 0 && b.process != 0)
			{
				win.draw_block(b);
				b.process = 0;
			}
			else
			{
				popularity_go(b, w);
				glad_go(b, w);
				education_go(b, w);
				protection_go(b, w);
				important_water_go(b, w);
				patients_happy_go(b, w);
				aim_glad_go(b, w);
				w.money -= public_runcost[b.public_building];
				w.money += b.economy*w.tax_rate*0.1;

				if ((b.glad > 100 * b.level + 10) && b.level < 3 && (w.world_start == 1 || b.level == 0) && b.level == b.aim_level)
				{
					level_up(b, w);
				}
			}
		}
	}
}

void worldgo(world * wor)
{
	world& w{ *wor };
	while (true)
	{
		Sleep(1000);
		w.GDP=GDP(w);
		w.RGDP=RGDP(w);
		w.total_glad = total_glad(w);
		w.total_popularity = total_popularity(w);
	}
}

// ------------------------------------------------------------
// draw_go
// ------------------------------------------------------------

void draw_go(Main_window * win)
{
	while (true)
	{
		Sleep(150);
		win->redraw();
	}
}

/*
void landprice_go(Block & b, const world & w)
{
	double aim_landprice{ 0 };
	aim_landprice = 0;
	double need{ 0 };
	b.landprice = b.landprice + 0.1*(aim_landprice - b.landprice);
}
*/

// ------------------------------------------------------------
// blocks_run
// ------------------------------------------------------------

void blocks_run(world* w, Main_window* win)
{
	while (true)
	{
		//std::cout << b->x;//testing
		Sleep(500);
		//if ((b->kind > 0 && b->kind < 4) || b->changing != 0||b->kind==5)
		{
			timego(w, win);
		}
	}
}

// ------------------------------------------------------------
// blocks_run_add
// ------------------------------------------------------------

void blocks_run_add(world* w, Main_window* win)
{
	std::thread t(blocks_run, w, win);
	t.detach();
}

// ------------------------------------------------------------
// timeout
// ------------------------------------------------------------

void timeout(Main_window* win)
{
	win->redraw();
	Fl::repeat_timeout(1./10., cb_timeout, win);
}

// ------------------------------------------------------------
// world_properties_timeout_function
// ------------------------------------------------------------



// ------------------------------------------------------------
// popularity_go
// ------------------------------------------------------------

void popularity_go(Block& b, const world& w)
{
	if (b.kind == 1)
	{
		b.row_popularity += 0.4;
		b.row_popularity += need_for_this_house(b, w)*0.04;
		b.row_popularity -= std::fmax(0, (b.popularity - 10 * b.level * b.level) / 2);
		b.popularity = round(b.row_popularity);
		return;
	}
	if (b.kind == 2)
	{
		b.strange_popularity += 0.6;
		b.strange_popularity += need_for_this_trade(b, w)*0.06;
		b.strange_popularity -= std::fmax(0, (b.strange_popularity - 40 * b.level * b.level) / 2);
		return;
	}
	if (b.kind == 3)
	{
		b.strange_popularity += 0.5;
		b.strange_popularity += need_for_this_goods(b, w)*0.05;
		b.strange_popularity -= std::fmax(0, (b.strange_popularity - 30 * b.level * b.level) / 2);
		return;
	}
}

// ------------------------------------------------------------
// glad_go
// ------------------------------------------------------------

void glad_go(Block & b, const world & w)
{
	double good_thing{ 0 };

	if (b.kind == 1)
	{
		for (size_t i = std::fmax(0, b.x - 2); i < std::fmin(b.x + 3, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 2); j < std::fmin(w.worldy, b.y + 3); j++)
			{
				good_thing += need_for_this_house(w.world_block[i][j], w) / 4;
			}
		}
		for (size_t i = std::fmax(0, b.x - 5); i < std::fmin(b.x + 6, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 5); j < std::fmin(w.worldy, b.y + 6); j++)
			{
				if (w.world_block[i][j].kind == 3)
				{
					good_thing += need_for_this_house(w.world_block[i][j], w) / 8;
				}
			}
		}

		for (size_t i = std::fmax(0, b.x - 10); i < std::fmin(b.x + 11, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 10); j < std::fmin(w.worldy, b.y + 11); j++)
			{
				if (w.world_block[i][j].kind == 3)
				{
					good_thing += need_for_this_house(w.world_block[i][j], w) / 16;
				}
			}
		}
	}

	else if (b.kind == 2)
	{
		for (size_t i = std::fmax(0, b.x - 2); i < std::fmin(b.x + 3, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 2); j < std::fmin(w.worldy, b.y + 3); j++)
			{
				good_thing += need_for_this_trade(w.world_block[i][j], w) / 4;
			}
		}
		for (size_t i = std::fmax(0, b.x - 5); i < std::fmin(b.x + 6, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 5); j < std::fmin(w.worldy, b.y + 6); j++)
			{
				good_thing += need_for_this_trade(w.world_block[i][j], w) / 8;
			}
		}
		for (size_t i = std::fmax(0, b.x - 10); i < std::fmin(b.x + 11, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 10); j < std::fmin(w.worldy, b.y + 11); j++)
			{
				good_thing += need_for_this_trade(w.world_block[i][j], w) / 16;
			}
		}
	}

	else if (b.kind == 3)
	{
		for (size_t i = std::fmax(0, b.x - 2); i < std::fmin(b.x + 3, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 2); j < std::fmin(w.worldy, b.y + 3); j++)
			{
				good_thing += need_for_this_goods(w.world_block[i][j], w) / 4;
			}
		}
		for (size_t i = std::fmax(0, b.x - 5); i < std::fmin(b.x + 6, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 5); j < std::fmin(w.worldy, b.y + 6); j++)
			{
				if (w.world_block[i][j].kind == 3)
				{
					good_thing += need_for_this_goods(w.world_block[i][j], w) / 8;
				}
			}
		}
		for (size_t i = std::fmax(0, b.x - 10); i < std::fmin(b.x + 11, w.worldx); i++)
		{
			for (int j = std::fmax(0, b.y - 10); j < std::fmin(w.worldy, b.y + 11); j++)
			{
				good_thing += need_for_this_goods(w.world_block[i][j], w) / 16;
			}
		}
	}

	else
	{
		good_thing = 1;
	}

	if (good_thing > 3)
	{
		good_thing = 3;
	}
	else if (good_thing < 0)
	{
		good_thing = 0;
	}

	double bad_thing{ 0 };

	if (b.kind == 1)
	{
		bad_thing += std::fmax(0, (need_for_job(b, w) + need_for_trade(b, w)) / (b.popularity));
	}

	else if (b.kind == 3)
	{
		bad_thing += std::fmax(0, need_for_trade(b, w) + need_for_house(b, w));
	}

	else if (b.kind == 2)
	{
		bad_thing += std::fmax(0, need_for_goods(b, w) + need_for_house(b, w));
	}

	if (bad_thing > 3)
	{
		bad_thing = 3;
	}

	if (bad_thing < 0)
	{
		bad_thing = 0;
	}

	double unhappy{ w.tax_rate };
	unhappy = unhappy * 5;

	double the_max_support{ 100 };
	the_max_support = std::fmin(50 + 25 * (good_thing - bad_thing - unhappy), 100);
	b.glad += 0.005*the_max_support;
	b.glad += 0.002*(b.aim_glad - b.glad);
	if (b.glad < 0)
	{
		b.glad = 0;
	}
}

// ------------------------------------------------------------
// education_go
// ------------------------------------------------------------

void education_go(Block& b, const world& w)
{
	double local_schools{ 0 };
	for (size_t i = std::fmax(0, b.x - 2); i < std::fmin(b.x + 3, w.worldx); i++)
	{
		for (int j = std::fmax(0, b.y - 2); j < std::fmin(w.worldy, b.y + 3); j++)
		{
			if (w.world_block[i][j].kind == 5)
			{
				if (w.world_block[i][j].public_building == 12)
				{
					local_schools += 9;
				}
			}
		}
	}

	for (size_t i = std::fmax(0, b.x - 5); i < std::fmin(b.x + 6, w.worldx); i++)
	{
		for (int j = std::fmax(0, b.y - 5); j < std::fmin(w.worldy, b.y + 6); j++)
		{
			if (w.world_block[i][j].kind == 5)
			{
				if (w.world_block[i][j].public_building == 12)
				{
					local_schools += 6;
				}
			}
		}
	}

	for (size_t i = std::fmax(0, b.x - 10); i < std::fmin(b.x + 11, w.worldx); i++)
	{
		for (int j = std::fmax(0, b.y - 10); j < std::fmin(w.worldy, b.y + 11); j++)
		{
			if (w.world_block[i][j].kind == 5)
			{
				if (w.world_block[i][j].public_building == 12)
				{
					local_schools += 4;
				}
			}
		}
	}

	for (size_t i = std::fmax(0, b.x - 10); i < std::fmin(b.x + 11, w.worldx); i++)
	{
		for (int j = std::fmax(0, b.y - 10); j < std::fmin(w.worldy, b.y + 11); j++)
		{
			if (w.world_block[i][j].kind == 5)
			{
				if (w.world_block[i][j].public_building == 12)
				{
					local_schools += 4;
				}
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
	local_schools = local_schools * b.popularity / divide;
	b.education = 2 * local_schools;
	if (b.education > 1)
	{
		b.education = 10;
	}
}

// ------------------------------------------------------------
// protection_go
// ------------------------------------------------------------

void protection_go(Block& b, const world&w)
{
	double local_volunteers{ 0 };
	for (size_t i = std::fmax(0, b.x - 5); i < std::fmin(b.x + 6, w.worldx); i++)
	{
		for (int j = std::fmax(0, b.y - 5); j < std::fmin(w.worldy, b.y + 6); j++)
		{
			if (w.world_block[i][j].kind == 5)
			{
				if (w.world_block[i][j].public_building == 14 || w.world_block[i][j].public_building == 13)
				{
					local_volunteers += 2;
				}
			}
		}
	}

	for (size_t i = std::fmax(0, b.x - 10); i < std::fmin(b.x + 11, w.worldx); i++)
	{
		for (int j = std::fmax(0, b.y - 10); j < std::fmin(w.worldy, b.y + 11); j++)
		{
			if (w.world_block[i][j].kind == 5)
			{
				if (w.world_block[i][j].public_building == 14 || w.world_block[i][j].public_building == 13)
				{
					local_volunteers += 1;
				}
			}
		}
	}

	b.protection = local_volunteers;
	if (b.protection > 10)
	{
		b.protection = 10;
	}
}

// ------------------------------------------------------------
// important_water_go
// ------------------------------------------------------------

void important_water_go(Block& b, const world& w)
{
	for (size_t i = std::fmax(0, b.x - 10); i < std::fmin(b.x + 11, w.worldx); i++)
	{
		for (int j = std::fmax(0, b.y - 10); j < std::fmin(w.worldy, b.y + 11); j++)
		{
			if (w.world_block[i][j].kind == 5)
			{
				if (w.world_block[i][j].public_building == 1)
				{
					b.local_water = 1 + b.local_water / 2;
				}
			}
		}
	}
}

// ------------------------------------------------------------
// patients_happy_go
// ------------------------------------------------------------

void patients_happy_go(Block& b, const world& w)
{
	for (size_t i = std::fmax(0, b.x - 4); i < std::fmin(b.x + 5, w.worldx); i++)
	{
		for (int j = std::fmax(0, b.y - 4); j < std::fmin(w.worldy, b.y + 5); j++)
		{
			if (w.world_block[i][j].kind == 5)
			{
				if (w.world_block[i][j].public_building == 11)
				{
					if (b.health < 3)
					{
						b.health += 1;
					}
					else if (b.health >= 3)
					{
						b.health = 2 + b.local_water / 2;
					}
				}
			}
		}
	}
	for (size_t i = std::fmax(0, b.x - 9); i < std::fmin(b.x + 10, w.worldx); i++)
	{
		for (int j = std::fmax(0, b.y - 9); j < std::fmin(w.worldy, b.y + 10); j++)
		{
			if (w.world_block[i][j].kind == 5)
			{
				if (w.world_block[i][j].public_building == 11)
				{
					if (b.health < 3)
					{
						b.health += 0.75;
					}
					else if (b.health >= 3)
					{
						b.health = 2 + b.local_water / 2;
					}
				}
			}
		}
	}
	for (size_t i = std::fmax(0, b.x - 12); i < std::fmin(b.x + 13, w.worldx); i++)
	{
		for (int j = std::fmax(0, b.y - 12); j < std::fmin(w.worldy, b.y + 13); j++)
		{
			if (w.world_block[i][j].kind == 5)
			{
				if (w.world_block[i][j].public_building == 11)
				{
					if (b.health < 3)
					{
						b.health += 0.25;
					}
					else if (b.health >= 3)
					{
						b.health = 2 + b.local_water / 2;
					}
				}
			}
		}
	}
}

// ------------------------------------------------------------
// aim_glad_go
// ------------------------------------------------------------

void aim_glad_go(Block& b, const world& w)
{
	if (b.protection >= 4)
	{
		b.aim_glad = b.local_water * (b.health * 20 + (b.protection - 4) * 5 + b.education * 20);
	}
	else if (b.protection < 4) {
		b.aim_glad = b.local_water * (b.health * 30 + (b.protection - 4) * 20 + b.education * 10);
	}
}

// ------------------------------------------------------------
// block_reset
// ------------------------------------------------------------

void block_reset(Block& b)
{
	b.aim_glad = 0;
	b.aim_level = 0;
	b.assistant_kind = 0;
	b.changing = 0;
	b.crime = 10;
	b.economy = 0;
	b.education = 0;
	b.glad = 0;
	b.goods = 0;
	b.health = 0;
	b.kind = 0;
	b.landprice = 0;
	b.level = 0;
	b.local_water = 0;
	b.mainplace = { 0,0 };
	b.popularity = 1;
	b.process = 0;
	b.protection = 0;
	b.public_building = 0;
	b.roaddirection = 0;
	b.row_popularity = 1;
	b.strange_popularity = 0;
}

