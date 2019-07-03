// ------------------------------------------------------------
//
// world_function.h
//
// Trivial Game v0.3.3
// A Simplified Version of SimCity
// Copyright © 2018-2019 Chenzhe Du, Jinghao Jiao, Zhiyu Sun, Jiayi Zheng.
//
// ------------------------------------------------------------

#ifndef _world_FUNCTION_H
#define _world_FUNCTION_H

double GDP(const world&w);
int total_popularity(const world&w);
double area_landprice(const world&w,int r1,int r2,int l1,int l2);
double RGDP(const world&w);
double original_crime_rate(const world&w);
double total_glad(const world&w);

// Starting frame;

#endif

void crime_change(Block & bb, const world & w);

double basic_install_rate(const Block & b, const world & w);

void draw_s(world * w);

void draw_i(world * w);

void draw_m(world * w);

void undraw_sim(world* wor);

int num_of_residential(const world&w);

int num_of_commercial(const world&w);

int num_of_industrial(const world&w);

int num_of_water_pump(const world&w);

int num_of_park(const world&w);

int num_of_hospital(const world&w);

int num_of_school(const world&w);

int num_of_police_station(const world&w);
