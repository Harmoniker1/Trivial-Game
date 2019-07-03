// ------------------------------------------------------------
//
// (main) Trivial_Game.cpp
//
// Trivial Game v0.3.3
// A Simplified Version of SimCity
// Copyright © 2018-2019 Chenzhe Du, Jinghao Jiao, Zhiyu Sun, Jiayi Zheng.
//
// ------------------------------------------------------------

#include <cmath>

#include "left_click.h"      // left_click.h has Main_window.h included
#include "block_run.h"
#include "world_function.h"

using std::thread;

// The global variables *win and *wor are both defined in left_click.h

// ------------------------------------------------------------
// create main window

Main_window::Main_window(Point xy, int w, int h, const string& title)
	: Graph_lib::Window{ xy, w, h, title }
{

	create_grid();
	create_data_box();

	add(multiline_output);
	attach_text(output_box_text);

}

void apply_change_text_rate(Main_window& win) {
	win.plus_tax_rate = new Button{ Point { 1360 - 80,10 }, 20, 20, "+", [](void*, void* pw) { static_cast<Main_window*>(pw)->plus_tax_rate_function(*wor); } };
	win.attach(*win.plus_tax_rate);
	win.minus_tax_rate = new Button{ Point { 1360 - 60,10 }, 20, 20, "-",[](void*, void* pw) { static_cast<Main_window*>(pw)->minus_tax_rate_function(*wor); } };
	win.attach(*win.minus_tax_rate);

	win.change_tax_rate = new Text{ Point { win.x_max() - 195,24 }, "Change tax rate:" };
	win.attach_text(*win.change_tax_rate);
}

// ------------------------------------------------------------
// below are things related to pop-menu.

vector<Fl_Menu_Button*> G_menu;
Fl_Menu_Bar* menu = new Fl_Menu_Bar(0, 0, 940, 25);
void Menu_CB(Fl_Widget*, void*);

void set_G_menu(int i, int j) {
	for (i = 1; i <= 20; i++) {
		for (j = 1; j <= 30; j++) {
			G_menu.push_back(new Fl_Menu_Button(40 + (j - 1) * 30, 40 + (i - 1) * 30, 30, 30, "Set area"));
		}
	}
}

void apply_popup() {
	win->tooltip("When hovering above a block, click for pop-up menu...");
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j <= 30; j++) {
			G_menu[(i - 1) * 30 + j - 1]->type(Fl_Menu_Button::POPUP3);      // right-clicking triggers the menu
			G_menu[(i - 1) * 30 + j - 1]->add("Set to street      ", "^0", Menu_CB, 0);      // ctrl-0 hotkey
			G_menu[(i - 1) * 30 + j - 1]->add("Set as area/Set as residential area      ", "^1", Menu_CB, 0);      // ctrl-1 hotkey
			G_menu[(i - 1) * 30 + j - 1]->add("Set as area/Set as commercial area      ", "^2", Menu_CB, 0);      // ctrl-2 hotkey
			G_menu[(i - 1) * 30 + j - 1]->add("Set as area/Set as industrial area      ", "^3", Menu_CB, 0);      // ctrl-3 hotkey
			G_menu[(i - 1) * 30 + j - 1]->add("Set to public building/Set to hospital      ", "^4", Menu_CB, 0);      // ctrl-4 hotkey
			G_menu[(i - 1) * 30 + j - 1]->add("Set to public building/Set to school      ", "^5", Menu_CB, 0);      // ctrl-5 hotkey
			G_menu[(i - 1) * 30 + j - 1]->add("Set to public building/Set to police station      ", "^6", Menu_CB, 0);      // ctrl-6 hotkey
			G_menu[(i - 1) * 30 + j - 1]->add("Remove current construction or area      ", "^7", Menu_CB, 0);      // ctrl-7 hotkey
		}
	}
}

void Menu_CB(Fl_Widget*, void*) 
{
	for (int i = 1; i <= 20; i++) 
	{
		for (int j = 1; j <= 30; j++) 
		{
			Block& b = wor->world_block[i - 1][j - 1];
			const char *text = G_menu[(i - 1) * 30 + j - 1]->text();
			if (!text) 
			{
				continue;
			}
			if (strcmp(text, "Set to street      ") == 0) 
			{
				std::cout << "this is a test of the huidiaohanshu"<<std::endl;
				win->multiline_output->value("");
				//std::cout << "this is a test of the huidiaohanshu";
				try 
				{ 
					change_kind(4, b, *wor); 
				}
				catch (std::runtime_error &e) 
				{
					win->multiline_output->value(e.what());
				}
				
				continue;
			}
			if (strcmp(text, "Set as residential area      ") == 0) {
				win->multiline_output->value("");
				std::cout << "this is a test of the huidiaohanshu";
				try { change_kind(1, b, *wor); }
				catch (std::runtime_error &e) {
					win->multiline_output->value(e.what());
				}
				continue;
			}
			if (strcmp(text, "Set as commercial area      ") == 0) {
				win->multiline_output->value("");
				try { change_kind(2, b, *wor); }
				catch (std::runtime_error &e) {
					win->multiline_output->value(e.what());
				}
				continue;
			}
			if (strcmp(text, "Set as industrial area      ") == 0) {
				win->multiline_output->value("");
				try { build_a_factory(b, *wor); }
				catch (std::runtime_error &e) {
					win->multiline_output->value(e.what());
				}
				continue;
			}
			if (strcmp(text, "Set to hospital      ") == 0) {
				win->multiline_output->value("");
				try { build_a_public_building(11, b, *wor); }
				catch (std::runtime_error &e) {
					win->multiline_output->value(e.what());
				}
				continue;
			}
			if (strcmp(text, "Set to school      ") == 0) {
				win->multiline_output->value("");
				try { build_a_public_building(12, b, *wor); }
				catch (std::runtime_error &e) {
					win->multiline_output->value(e.what());
				}
				continue;
			}
			if (strcmp(text, "Set to police station      ") == 0) {
				win->multiline_output->value("");
				try { build_a_public_building(13, b, *wor); }
				catch (std::runtime_error &e) {
					win->multiline_output->value(e.what());
				}
				continue;
			}
			if (strcmp(text, "Remove current construction or area      ") == 0) {
				win->multiline_output->value("");
				if (b.kind != 6)
				{
					change_kind(0, b, *wor);
					return;
				}
				if (b.kind == 6)
				{
					change_kind(0, wor->world_block[b.mainplace[0]][b.mainplace[1]], *wor);
				}
				continue;
			}
		}
	}
}

// ------------------------------------------------------------
// below are things related to menu bar.

void Help_CB(Fl_Widget*, void*);
void About_CB(Fl_Widget*, void*);
void Quit_CB(Fl_Widget*, void*);
void Restart_CB(Fl_Widget*, void*);

void apply_menu_bar() {
	menu->add("Help", FL_CTRL + 'h', Help_CB);
	menu->add("Restart", FL_CTRL + 'r', Restart_CB);
	menu->add("About", FL_CTRL + 'a', About_CB);
	menu->add("Quit", FL_CTRL + 'q', Quit_CB);
}

void help_messagebox() {
	MessageBox(NULL, "This form provides you some useful tips on playing the game.\n\n"
		"This game is a (very) simplified version of the well-known game SimCity. "
		"In both of the games, the ultimate goal is to construct a development-sustainable city without letting it go out of your control (which means something gets terribly wrong with it).\n\n"
		"BEFORE PLAYING: look (and click) around to see what's implemented!\n\n"
		"Right-clicking on any of the grid box will trigger a pop-up menu, which is the direct way of modifying what's in the box.\n"
		"Beside the grid lie a data statistics box, which lists the very properties of the world, and also of a specific grid box if you left-click on it.\n"
		"Below it is an output box, where explanations of certain errors show up to inform you of things you shouldn't do during the game.\n\n"
        "WHEN PLAYING: you can design your city in whatever way you want!\n\n"
		"You must first build roads so that buildings can be set around them.\n"
		"Residential and commercial areas are both 1*1, and other buildings, including industrial areas, are 2*3. "
		"The program has already coded in flexible functions for you, so all you have to do is to right-click and select a building/area, and it can be built in the exact way you want it to.\n"
		"While building, you have to make sure you still have money, so that your city can maintain continuous and sustainable development.\n\n"
		"WHEN THE MONEY HAS ALL BEEN USED UP: oops, your game has come to an end, and you have to restart by clicking 'Restart' on the menu bar.\n\n"
		"Have fun!\n\n"
		"(This form will show again upon clicking 'Help' in the menu bar, and DON'T FORGET TO CLOSE THIS FORM BEFORE PLAYING, OTHERWISE THE PERFORMANCE WILL SHARPLY DECLINE)", "Welcome", MB_ICONINFORMATION | MB_OK);
}

void Help_CB(Fl_Widget*, void*) {
	help_messagebox();
}

void Restart_CB(Fl_Widget*, void*) {
	// pops up a message box ensuring the user's choice isn't by accident
	if (MessageBox(NULL, "Do you truly wish to reset the game?", "Warning", MB_ICONWARNING | MB_YESNO) == 6) {      // 6 means the user chooses "yes"
		for (int i = 1; i <= 20; i++) {
			for (int j = 1; j <= 30; j++) {
				Block& b = wor->world_block[i - 1][j - 1];
				block_reset(b);
				Graph_lib::Image* image = new Graph_lib::Image{ Point { 40 + (j - 1) * 30, 40 + (i - 1) * 30 }, "pictures/default_image.png" };
				win->attach(*image);
			}
		}
		apply_popup();      // re-apply pop-up menu
		win->detach_all_texts_in_data_box();
		wor->money = 500000;
		wor->GDP = 0;
		wor->total_glad = 0;
		wor->gameover = false;
	}
}


void About_CB(Fl_Widget*, void*) {
	MessageBox(NULL, "Trivial Game v0.3.3-build 20190116\n\n"
		"Inspiration & Model: SimCity(R)\n"
		"Developers: Chenzhe Du, Jinghao Jiao, Zhiyu Sun, Jiayi Zheng. "
		"(listed along surname's alphabetic sequence)", "About", MB_ICONINFORMATION | MB_OK);
}

void Quit_CB(Fl_Widget*, void*) {
	exit(0);
}

int residential, commercial, industrial, water_pump, park, hospital, school, police_station;

void calculate_result() {
	residential = num_of_residential(*wor);
	commercial = num_of_commercial(*wor);
	industrial = num_of_industrial(*wor);
	water_pump = num_of_water_pump(*wor);
	park = num_of_park(*wor);
	hospital = num_of_hospital(*wor);
	school = num_of_school(*wor);
	police_station = num_of_police_station(*wor);
}

void world_properties_timeout_function()
{
	if (wor->gameover == true) {
		return;
	}
	
	if (wor->money <= 0) {
		calculate_result();
		wor->gameover = true;
		std::stringstream ss;
		ss << "The game is over because you don't have money. The pop menus are now blocked. "
			<< "Press 'Restart' on the menu bar to start a new game, good luck this time.\n\n"
			<< "Your city has introduced " << residential << " residential area(s), " << commercial << " commercial area(s), "
			<< industrial << " industrial area(s), " << water_pump << " water pump(s), " << park << " park(s), "<< hospital << " hospital(s), "
			<< school << " school(s), " << police_station << " police station(s).";
		string ss_string{ ss.str() };
		LPCSTR s = ss_string.c_str();
		MessageBox(NULL, s, "Game Over", MB_ICONINFORMATION | MB_OK);
		for (int i = 1; i <= 20; i++) {
			for (int j = 1; j <= 30; j++) {
				G_menu[(i - 1) * 30 + j - 1]->clear();      // block pop-up menu
			}
		}
		return;
	}
	
	Text* money_text = new Text{ Point(win->x_max() - 370,140), "Money:" };
	Text* money_data = new Text{ Point(win->x_max() - 100,140), std::to_string(wor->money) };
	win->attach_text(*money_text); win->attach_text(*money_data);

	Text* GDP_text = new Text{ Point(win->x_max() - 370,165), "GDP:" };
	Text* GDP_data = new Text{ Point(win->x_max() - 100,165), std::to_string(wor->GDP) };
	win->attach_text(*GDP_text); win->attach_text(*GDP_data);

	Text* glad_text = new Text{ Point(win->x_max() - 370,190), "Rate of support:" };
	Text* glad_data = new Text{ Point(win->x_max() - 100,190), std::to_string(wor->total_glad) };
	win->attach_text(*glad_text); win->attach_text(*glad_data);

	Sleep(1000);
	win->detach(*money_text); win->detach(*money_data);
	win->detach(*GDP_text); win->detach(*GDP_data);
	win->detach(*glad_text); win->detach(*glad_data);
}

void world_properties_timeout_function_go()
{
	while (true)
	{
		world_properties_timeout_function();
	}
}

// ------------------------------------------------------------
// main function

int main(int argc, char *argv[])
{

	apply_change_text_rate(*win);

	// for pop-up menu:

	//wor->world_start = 1;

	thread worldrunning(worldgo, wor);
	worldrunning.detach();

	thread world_properties_text(world_properties_timeout_function_go);
	world_properties_text.detach();

	set_G_menu(20, 30);
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j <= 30; j++) {
			win->add(G_menu[(i - 1) * 30 + j - 1]);
			apply_popup();
		}
	}

	// for menu bar:

	win->add(*menu);
	apply_menu_bar();

	// for showing window:

	win->end();
	win->show();
	// draw_sim(wor);

	help_messagebox();

	blocks_run_add(wor, win);
	Fl::add_timeout(1. / 10., cb_timeout, win);

	thread starting(draw_s, wor);
	starting.detach();

	thread starting2(draw_i, wor);
	starting2.detach();

	thread starting3(draw_m, wor);
	starting3.detach();

	thread starting4(undraw_sim, wor);
	starting4.detach();

	return(Fl::run());

}