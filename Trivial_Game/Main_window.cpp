// ------------------------------------------------------------
//
// Main_window.cpp
//
// Trivial Game
// A Simplified Version of SimCity®
// Copyright © 2018-2019 Chenzhe Du, Jinghao Jiao, Zhiyu Sun, Jiayi Zheng. All Rights Reserved.
//
// ------------------------------------------------------------

#include "Main_window.h"

using Graph_lib::Color;
using Graph_lib::Font;

// ------------------------------------------------------------
// create grid
// ------------------------------------------------------------

void Main_window::create_grid()
{
	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 30; ++j) {
			Vector_ref<Graph_lib::Image>& v = vwhole[i];
			v.push_back(new Graph_lib::Image{ Point { 40 + j * 30, 40 + i * 30 }, "pictures/default_image.png" });
			attach(v[v.size() - 1]);
		}
	}
}

// ------------------------------------------------------------
// create data box
// ------------------------------------------------------------

void Main_window::create_data_box()
{
	// attach box
	rect.set_color(Color::black);
	rect.set_style(Line_style{ Line_style::solid, 1 });
	rect.set_fill_color(Color::white);
	attach(rect);

	// attach summary text (using bold font)
	summary.set_font(Font::times_bold);
	summary.set_font_size(15);
	summary.set_color(Color::black);
	attach(summary);

	// attach line & line 2
	attach_text(line);
	attach_text(line2);

	// attach texts of tax rate
    attach_text(tax_rate_text);
	attach_text(tax_rate_data);
}

// ------------------------------------------------------------
// plus/minus_tax_rate_function
// ------------------------------------------------------------

void Main_window::plus_tax_rate_function(world& w) {
	// clear multiline output
	multiline_output->value("");

	// add tax rate
	w.tax_rate += 0.001;
	w.tax_rate_string = std::to_string(w.tax_rate);

	// detach the original one
	detach(tax_rate_data);

	// re-define and attach tax rate data
	tax_rate_data.set_label(w.tax_rate_string);
	attach_text(tax_rate_data);
}

void Main_window::minus_tax_rate_function(world& w) {
	if (w.tax_rate <= 0.001) {
		multiline_output->value("Cannot make the tax rate negative.\n");
		return;
	}

	w.tax_rate -= 0.001;
	w.tax_rate_string = std::to_string(w.tax_rate);

	detach(tax_rate_data);

	tax_rate_data.set_label(w.tax_rate_string);
	attach_text(tax_rate_data);
}

// ------------------------------------------------------------
// attach_text
// ------------------------------------------------------------

void Main_window::attach_text(Text& t) {
	t.set_font(Font::times);
	t.set_font_size(15);
	t.set_color(Color::black);
	attach(t);
}

// ------------------------------------------------------------
// draw_block
// ------------------------------------------------------------

void Main_window::draw_block(const Block& b)
{
	if (b.assistant_kind==6)
	{
		return;
	}
	if (b.assistant_kind != 3 && b.public_building < 10 && b.level == b.aim_level)
	{
		std::stringstream ss;
		ss << "pictures/" << b.assistant_kind << "_" << b.public_building << "_";
		if (b.changing == 1 && b.assistant_kind != 4)
		{
			ss << (-1)*b.process + 5 << "-" << b.level;
		}
		if (b.changing == 1 && b.assistant_kind == 4)
		{
			ss << (-1)*b.process + 5 << "-" << b.level;
		}
		if (b.changing == -1)
		{
			ss << b.process << "-" << b.level;
		}
		ss << ".png";
		std::string s;
		ss >> s;
		Graph_lib::Image* i = new Graph_lib::Image{ Point{40 + b.y * 30,40 + b.x * 30},s };
		std::cout << s;
		this->attach(*i);
	}
	else if (b.assistant_kind != 3 && b.public_building < 10 && b.level != b.aim_level)
	{
		std::stringstream ss;
		ss << "pictures/" << b.assistant_kind << "_" << b.public_building << "_";
		if (b.changing == 1)
		{
			ss << (-1)*b.process + 5 << "-" << b.aim_level;
		}
		if (b.changing == -1)
		{
			ss << b.process << "-" << b.level;
		}
		std::string s;
		ss << ".png";
		ss >> s;
		Graph_lib::Image* i = new Graph_lib::Image{ Point{40 + b.y * 30,40 + b.x * 30},s };
		this->attach(*i);
	}
	else if ((b.assistant_kind == 3 || b.public_building >= 10) && b.level == b.aim_level)
	{

		if (b.roaddirection == 0)
		{
			return;
		}
		std::stringstream ss;
		ss << "pictures/" << b.assistant_kind << "_" << b.public_building << "_";
		int left{ 0 };
		int up{ 0 };
		int road{ b.roaddirection };
		if (road == 1)
		{
			left = 0;
			up = 1;
		}
		else if (road == 2)
		{
			left = 1;
			up = 0;
		}
		else if (road == 3)
		{
			left = 1;
			up = 1;
		}
		else if (road == 4)
		{
			left = 1;
			up = 1;
		}
		if (b.changing == 1)
		{
			ss << (-1)*b.process + 5 << "-" << b.level << "-" << road;
		}
		if (b.changing == -1)
		{
			ss << b.process << "-" << b.level << "-" << road;
		}
		ss << ".png";
		std::string s;
		ss >> s;
		Graph_lib::Image* i = new Graph_lib::Image{ Point{40 + (b.y - left) * 30,40 + (b.x - up) * 30},s };
		this->attach(*i);
	}
	else if ((b.assistant_kind == 3 || b.public_building >= 10) && b.level != b.aim_level)
	{
		if (b.roaddirection == 0)
		{
			return;
		}
		std::stringstream ss;
		ss << "pictures/" << b.assistant_kind << "_" << b.public_building << "_";
		int left{ 0 };
		int up{ 0 };
		int road{ b.roaddirection };
		if (road == 1)
		{
			left = 0;
			up = 1;
		}
		else if (road == 2)
		{
			left = 1;
			up = 0;
		}
		else if (road == 3)
		{
			left = 1;
			up = 1;
		}
		else if (road == 4)
		{
			left = 1;
			up = 1;
		}
		if (b.changing == 1)
		{
			ss << (-1)*b.process + 5 << "-" << b.aim_level << "-" << road;
		}
		if (b.changing == -1)
		{
			ss << b.process << "-" << b.level << "-" << road;
		}
		ss << ".png";
		std::string s;
		ss >> s;
		Graph_lib::Image* i = new Graph_lib::Image{ Point{40 + (b.y - left) * 30,40 + (b.x - up) * 30},s };
		this->attach(*i);
	}
	// this->redraw();
}