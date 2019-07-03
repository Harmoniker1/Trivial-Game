// ------------------------------------------------------------
//
// Main_window.h
//
// Trivial Game
// A Simplified Version of SimCity®
// Copyright © 2018-2019 Chenzhe Du, Jinghao Jiao, Zhiyu Sun, Jiayi Zheng.
//
// ------------------------------------------------------------

#pragma once

#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <thread>
#include <windows.h>

#include "GUI.h"
#include "Graph.h"
#include "Vector_ref.h"
#include "Window.h"

#include "function.h"
#include "blocks.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/fl_message.H>
#include <stdlib.h>
#include <string.h>

using std::string;
using std::vector;

using Graph_lib::Point;
using Graph_lib::Line_style;
using Graph_lib::Vector_ref;
using Graph_lib::Color;
using Graph_lib::Text;
using Graph_lib::Font;
using Graph_lib::Button;

// ------------------------------------------------------------
// Main_window class
// ------------------------------------------------------------

class Main_window : public Graph_lib::Window {
public:
	Main_window(Point xy, int w, int h, const string& title);      // construction of Main_window

	Fl_Multiline_Output* multiline_output = new Fl_Multiline_Output(980, 560, 340, 80, "");

	void attach_text(Text& t);

	void draw_block(const Block& b);

	int handle(int event) override;
	bool handle_mousepush(int button, int ex, int ey);

	// ------------------------------------------------------------
	// below modifies the value of tax rate.

	Button* plus_tax_rate;
	Button* minus_tax_rate;

	void plus_tax_rate_function(world& w);
	void minus_tax_rate_function(world& w);

	// texts about tax rate is defined in private.
	Text* change_tax_rate;

	Text* popularity_text; Text* popularity_data;      // for residential area only
	Text* goods_text; Text* goods_data;      // for commercial area only
	Text* economy_text; Text* economy_data;      // for all areas
	Text* landprice_text; Text* landprice_data;      // for residential and commercial area
	Text* glad_text; Text* glad_data;      // for residential and commercial area
	Text* need_for_house_text; Text* need_for_house_data;      // for commercial and industrial area
	Text* need_for_trade_text; Text* need_for_trade_data;      // for residential and industrial area
	Text* need_for_goods_text; Text* need_for_goods_data;      // for commercial area only
	Text* need_for_job_text; Text* need_for_job_data;      // for residential area only
	Text* need_for_this_house_text; Text* need_for_this_house_data;      // for each block
	Text* need_for_this_trade_text; Text* need_for_this_trade_data;      // for each block
	Text* need_for_this_goods_text; Text* need_for_this_goods_data;      // for each block

	void detach_all_texts_in_data_box() {
		detach(*popularity_text); detach(*popularity_data);
		detach(*goods_text); detach(*goods_data);
		detach(*economy_text); detach(*economy_data);
		detach(*landprice_text); detach(*landprice_data);
		detach(*glad_text); detach(*glad_data);
		detach(*need_for_house_text); detach(*need_for_house_data);
		detach(*need_for_trade_text); detach(*need_for_trade_data);
		detach(*need_for_goods_text); detach(*need_for_goods_data);
		detach(*need_for_job_text); detach(*need_for_job_data);
		detach(*need_for_this_house_text); detach(*need_for_this_house_data);
		detach(*need_for_this_trade_text); detach(*need_for_this_trade_data);
		detach(*need_for_this_goods_text); detach(*need_for_this_goods_data);
	}

private:

	// ------------------------------------------------------------
	// below defines the exact coordinate of each block.
	// In create_grid(), a block is set to be in row number i and column number j.

	Vector_ref<Graph_lib::Image>
		vrow1, vrow2, vrow3, vrow4, vrow5,
		vrow6, vrow7, vrow8, vrow9, vrow10,
		vrow11, vrow12, vrow13, vrow14, vrow15,
		vrow16, vrow17, vrow18, vrow19, vrow20;
	vector<Vector_ref<Graph_lib::Image>> vwhole
	{ vrow1,vrow2,vrow3,vrow4,vrow5,
	  vrow6,vrow7,vrow8,vrow9,vrow10,
	  vrow11,vrow12,vrow13,vrow14,vrow15,
	  vrow16,vrow17,vrow18,vrow19,vrow20 };

	// ------------------------------------------------------------
	// below lists the members of the data box.

	Graph_lib::Rectangle rect{ Point(x_max() - 380,40), 340, 450 };

	Text summary{ Point(x_max() - 370,65), "Data analysis:" };
	Text line{ Point(x_max() - 370, 90), "--------------------" };

	Text tax_rate_text{ Point(x_max() - 370,115), "Tax Rate:" };
	Text tax_rate_data{ Point(x_max() - 100,115), std::to_string(0.08)};

	Text line2{ Point(x_max() - 370, 215), "--------------------" };

	// ------------------------------------------------------------
	// below lists the members of the output box.

	Text output_box_text{ Point(980, 550), "Output box:" };
	// (the output box itself is defined in the "public" section)

	// ------------------------------------------------------------
	// below are create functions.

	void create_grid();
	void create_data_box();
};

#endif