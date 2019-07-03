// ------------------------------------------------------------
//
// left_click.h
//
// Trivial Game
// A Simplified Version of SimCity
// Copyright © 2018-2019 Chenzhe Du, Jinghao Jiao, Zhiyu Sun, Jiayi Zheng.
//
// ------------------------------------------------------------

#pragma once

#include "Main_window.h"

using std::to_string;

Main_window* win = new Main_window{ Point{8, 10}, 1360, 680, "Trivial Game" };
world* wor = new world(20, 30);

// ------------------------------------------------------------
// below are things related to left-click.
// the data box itself is defined in Main_window.h, along with the declaration of the Text*s and detach_all_texts_in_data_box().

int Main_window::handle(int event)
{
	int ret{ Fl_Window::handle(event) };
	if (ret == 1) {
		return ret;
	}
	switch (event) {
	case FL_FOCUS:
	case FL_UNFOCUS:
		ret = 1;
		break;
	case FL_PUSH:
		if (handle_mousepush(Fl::event_button(), Fl::event_x(), Fl::event_y())) {
			ret = 1;
		}
		break;
	}
	return ret;
}

bool Main_window::handle_mousepush(int button, int ex, int ey)
{
	if (button != FL_LEFT_MOUSE) {
		return false;
	}

	detach_all_texts_in_data_box();

	if (ex < 40 || ex > 939 || ey < 40 || ey > 639) {
		//redraw();
		return true;
	}
	double ey_double = ey;
	double ex_double = ex;      // so that they can do the devision in the way of doubles
	int i = floor((ey_double - 40.0) / 30.0);
	int j = floor((ex_double - 40.0) / 30.0);
	Block b = wor->world_block[i][j];

	const string popularity_string = "This residential area's popularity is";
	const string goods_string = "Goods given to this commercial area";
	const string economy_string = "The economic aggregate of this area is";
	const string landprice_string = "The landprice of this area is";
	const string glad_string = "The happiness quotient of this area is";
	const string need_for_house_string = "The need for residential area of this area is";
	const string need_for_trade_string = "The need for commercial area of this area is";
	const string need_for_goods_string = "The need for goods is";
	const string need_for_job_string = "The need for job of this residential area is";
	const string need_for_this_house_string = "The need for this block to be residential is";
	const string need_for_this_trade_string = "The need for this block to be commercial is";
	const string need_for_this_goods_string = "The need for this block to be industrial is";

	string popularity_data_string = to_string(b.popularity);
	string goods_data_string = to_string(b.goods);
	string economy_data_string = to_string(b.economy);
	string landprice_data_string = to_string(b.landprice);
	string glad_data_string = to_string(b.glad);
	string need_for_house_data_string = to_string(need_for_house(b, *wor));
	string need_for_trade_data_string = to_string(need_for_trade(b, *wor));
	string need_for_goods_data_string = to_string(need_for_goods(b, *wor));
	string need_for_job_data_string = to_string(need_for_job(b, *wor));
	string need_for_this_house_data_string = to_string(need_for_this_house(b, *wor));
	string need_for_this_trade_data_string = to_string(need_for_this_trade(b, *wor));
	string need_for_this_goods_data_string = to_string(need_for_this_goods(b, *wor));

	if (b.kind != 1 && b.kind != 2 && b.kind != 3) {      // need text for need for this house, need for this trade, need for this goods
		{
			need_for_this_house_text = new Text{ Point{ x_max() - 370,250 }, need_for_this_house_string }; attach_text(*need_for_this_house_text);
			need_for_this_house_data = new Text{ Point{ x_max() - 100,250 }, need_for_this_house_data_string }; attach_text(*need_for_this_house_data);
		}
		{
			need_for_this_trade_text = new Text{ Point{ x_max() - 370,275 }, need_for_this_trade_string }; attach_text(*need_for_this_trade_text);
			need_for_this_trade_data = new Text{ Point{ x_max() - 100,275 }, need_for_this_trade_data_string }; attach_text(*need_for_this_trade_data);
		}
		{
			need_for_this_goods_text = new Text{ Point{ x_max() - 370,300 }, need_for_this_goods_string }; attach_text(*need_for_this_goods_text);
			need_for_this_goods_data = new Text{ Point{ x_max() - 100,300 }, need_for_this_goods_data_string }; attach_text(*need_for_this_goods_data);
		}
		//redraw();
		return true;
	}

	if (b.kind == 1) {      // need text for popularity, economy, landprice, glad, need for trade, need for job, need for this house, need for this trade, need for this goods
		{
			popularity_text = new Text{ Point{ x_max() - 370,250 }, popularity_string }; attach_text(*popularity_text);
			popularity_data = new Text{ Point{ x_max() - 100,250 }, popularity_data_string }; attach_text(*popularity_data);
		}
		{
			economy_text = new Text{ Point{ x_max() - 370,275 }, economy_string }; attach_text(*economy_text);
			economy_data = new Text{ Point{ x_max() - 100,275 }, economy_data_string }; attach_text(*economy_data);
		}
		{
			landprice_text = new Text{ Point{ x_max() - 370,300 }, landprice_string }; attach_text(*landprice_text);
			landprice_data = new Text{ Point{ x_max() - 100,300 }, landprice_data_string }; attach_text(*landprice_data);
		}
		{
			glad_text = new Text{ Point{ x_max() - 370,325 }, glad_string }; attach_text(*glad_text);
			glad_data = new Text{ Point{ x_max() - 100,325 }, glad_data_string }; attach_text(*glad_data);
		}
		{
			need_for_trade_text = new Text{ Point{ x_max() - 370,350 }, need_for_trade_string }; attach_text(*need_for_trade_text);
			need_for_trade_data = new Text{ Point{ x_max() - 100,350 }, need_for_trade_data_string }; attach_text(*need_for_trade_data);
		}
		{
			need_for_job_text = new Text{ Point{ x_max() - 370,375 }, need_for_job_string }; attach_text(*need_for_job_text);
			need_for_job_data = new Text{ Point{ x_max() - 100,375 }, need_for_job_data_string }; attach_text(*need_for_job_data);
		}
		{
			need_for_this_house_text = new Text{ Point{ x_max() - 370,400 }, need_for_this_house_string }; attach_text(*need_for_this_house_text);
			need_for_this_house_data = new Text{ Point{ x_max() - 100,400 }, need_for_this_house_data_string }; attach_text(*need_for_this_house_data);
		}
		{
			need_for_this_trade_text = new Text{ Point{ x_max() - 370,425 }, need_for_this_trade_string }; attach_text(*need_for_this_trade_text);
			need_for_this_trade_data = new Text{ Point{ x_max() - 100,425 }, need_for_this_trade_data_string }; attach_text(*need_for_this_trade_data);
		}
		{
			need_for_this_goods_text = new Text{ Point{ x_max() - 370,450 }, need_for_this_goods_string }; attach_text(*need_for_this_goods_text);
			need_for_this_goods_data = new Text{ Point{ x_max() - 100,450 }, need_for_this_goods_data_string }; attach_text(*need_for_this_goods_data);
		}

		//redraw();
		return true;
	}

	if (b.kind == 2) {      // need text for goods, economy, landprice, glad, need for house, need for goods, need for this house, need for this trade, need for this goods
		{
			goods_text = new Text{ Point{ x_max() - 370,250 }, goods_string }; attach_text(*goods_text);
			goods_data = new Text{ Point{ x_max() - 100,250 }, goods_data_string }; attach_text(*goods_data);
		}
		{
			economy_text = new Text{ Point{ x_max() - 370,275 }, economy_string }; attach_text(*economy_text);
			economy_data = new Text{ Point{ x_max() - 100,275 }, economy_data_string }; attach_text(*economy_data);
		}
		{
			landprice_text = new Text{ Point{ x_max() - 370,300 }, landprice_string }; attach_text(*landprice_text);
			landprice_data = new Text{ Point{ x_max() - 100,300 }, landprice_data_string }; attach_text(*landprice_data);
		}
		{
			glad_text = new Text{ Point{ x_max() - 370,325 }, glad_string }; attach_text(*glad_text);
			glad_data = new Text{ Point{ x_max() - 100,325 }, glad_data_string }; attach_text(*glad_data);
		}
		{
			need_for_house_text = new Text{ Point{ x_max() - 370,350 }, need_for_house_string }; attach_text(*need_for_house_text);
			need_for_house_data = new Text{ Point{ x_max() - 100,350 }, need_for_house_data_string }; attach_text(*need_for_house_data);
		}
		{
			need_for_goods_text = new Text{ Point{ x_max() - 370,375 }, need_for_goods_string }; attach_text(*need_for_goods_text);
			need_for_goods_data = new Text{ Point{ x_max() - 100,375 }, need_for_goods_data_string }; attach_text(*need_for_goods_data);
		}
		{
			need_for_this_house_text = new Text{ Point{ x_max() - 370,400 }, need_for_this_house_string }; attach_text(*need_for_this_house_text);
			need_for_this_house_data = new Text{ Point{ x_max() - 100,400 }, need_for_this_house_data_string }; attach_text(*need_for_this_house_data);
		}
		{
			need_for_this_trade_text = new Text{ Point{ x_max() - 370,425 }, need_for_this_trade_string }; attach_text(*need_for_this_trade_text);
			need_for_this_trade_data = new Text{ Point{ x_max() - 100,425 }, need_for_this_trade_data_string }; attach_text(*need_for_this_trade_data);
		}
		{
			need_for_this_goods_text = new Text{ Point{ x_max() - 370,450 }, need_for_this_goods_string }; attach_text(*need_for_this_goods_text);
			need_for_this_goods_data = new Text{ Point{ x_max() - 100,450 }, need_for_this_goods_data_string }; attach_text(*need_for_this_goods_data);
		}

		//redraw();
		return true;
	}

	if (b.kind == 3) {      // need text for economy, need for this house, need for this trade, need for this goods
		{
			economy_text = new Text{ Point{ x_max() - 370,250 }, economy_string }; attach_text(*economy_text);
			economy_data = new Text{ Point{ x_max() - 100,250 }, economy_data_string }; attach_text(*economy_data);
		}
		{
			need_for_this_house_text = new Text{ Point{ x_max() - 370,275 }, need_for_this_house_string }; attach_text(*need_for_this_house_text);
			need_for_this_house_data = new Text{ Point{ x_max() - 100,275 }, need_for_this_house_data_string }; attach_text(*need_for_this_house_data);
		}
		{
			need_for_this_trade_text = new Text{ Point{ x_max() - 370,300 }, need_for_this_trade_string }; attach_text(*need_for_this_trade_text);
			need_for_this_trade_data = new Text{ Point{ x_max() - 100,300 }, need_for_this_trade_data_string }; attach_text(*need_for_this_trade_data);
		}
		{
			need_for_this_goods_text = new Text{ Point{ x_max() - 370,325 }, need_for_this_goods_string }; attach_text(*need_for_this_goods_text);
			need_for_this_goods_data = new Text{ Point{ x_max() - 100,325 }, need_for_this_goods_data_string }; attach_text(*need_for_this_goods_data);
		}

		//redraw();
		return true;
	}

	return true;
}