// ------------------------------------------------------------
//
// function.h
//
// Trivial Game
// A Simplified Version of SimCity
// Copyright © 2018-2019 Chenzhe Du, Jinghao Jiao, Zhiyu Sun, Jiayi Zheng.
//
// ------------------------------------------------------------

#pragma once

#ifndef _FUNCTION_H
#define _FUNCTION_H

#include "world.h"
#include "statics.h"
#include <Windows.h>
#include <string>
#include <sstream>
#include <exception>

void change_kind(int n, Block& b, world& w);      // 0: non-kind; 1: residential; 2: commercial; 3: industrial; 4: road; 5: infrastructure (sub-kind needed)
void build_a_factory ( Block& b, world& w);
void build_a_public_building(int n, Block& b, world& w);	//1: water pump; 2: park; 11: hospital; 12: school; 13:police station
void level_up(Block& b, world& w);
double need_for_house(const Block& b, const world& w);      // the block's need for residential area
double need_for_trade(const Block& b, const world& w);      // the block's need for commercial area
double need_for_goods(const Block& b,const world& w);      // the block's need for industrial area
double need_for_job(const Block& b, const world& w);      // the block's need for work
double need_for_this_house(const Block& b, const world& w);      // need (of the area around the block) for this block to be residential
double need_for_this_trade(const Block& b, const world& w);      // need (of the area around the block) for this block to be commercial
double need_for_this_goods(const Block &b, const world& w);      // need (of the area around the block) for this block to be industrial
int next_to_road(const Block& b,const world& w);

int empty(Block& b, const world& w);      // whether a 2*3 building can be placed
int traffic(const Block& b, const world& w);

#endif