// ------------------------------------------------------------
//
// block_run.h
//
// Trivial Game
// A Simplified Version of SimCity®
// Copyright © 2018-2019 Chenzhe Du, Jinghao Jiao, Zhiyu Sun, Jiayi Zheng. All Rights Reserved.
//
// ------------------------------------------------------------

#pragma once

#ifndef _BLOCK_RUN_H
#define _BLOCK_RUN_H

#include "blocks.h"
#include "world.h"
#include "Main_window.h"
#include "world_function.h"

#include <Windows.h>

// ------------------------------------------------------------
// every block refreshes itself after every second
// ------------------------------------------------------------

void timego(world* w, Main_window* win);

void worldgo(world* wor);

void draw_go(Main_window* win);

void blocks_run(world* w, Main_window* win);

void blocks_run_add(world* w, Main_window* win);

void timeout(Main_window* wor);


static void cb_timeout(void* pw)
{
	timeout(static_cast<Main_window*>(pw));
}


void test(int i,int j,int k);

void landprice_go(Block& b, const world& w);

// residental

void working_state_go(Block& b, const world& w);

void popularity_go(Block& b, const world& w);

void glad_go(Block& b, const world& w);

void education_go(Block& b, const world& w);

void protection_go(Block& b, const world& w);

void important_water_go(Block& b, const world& w);

void patients_happy_go(Block& b, const world& w);

void aim_glad_go(Block& b, const world& w);

void block_reset(Block& b);

#endif