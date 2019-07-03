// ------------------------------------------------------------
//
// world_function.cpp
//
// Trivial Game
// A Simplified Version of SimCity®
// Copyright © 2018-2019 Chenzhe Du, Jinghao Jiao, Zhiyu Sun, Jiayi Zheng. All Rights Reserved.
//
// ------------------------------------------------------------

#include "world.h"
#include "blocks.h"
#include "function.h"
#include "world_function.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <Windows.h>

using std::vector;

// ------------------------------------------------------------
// GDP
// ------------------------------------------------------------

double GDP(const world&w)
{
    double sum{0};
    for(int i=0; i<w.worldx; ++i){
        double sum_per_row{0};
        for(int j=0; j<w.worldy; ++j){
            sum_per_row += w.world_block[i][j].economy;
        }
        sum += sum_per_row;
    }
    return sum;
}

// ------------------------------------------------------------
// total popularity
// ------------------------------------------------------------

int total_popularity(const world&w){
    int sum{0};
    for(int i=0; i<w.worldx; ++i){
        int sum_per_row{0};
        for(int j=0; j<w.worldy; ++j){
            sum_per_row += w.world_block[i][j].popularity;
        }
        sum += sum_per_row;
    }
    return sum;
}

// ------------------------------------------------------------
// landprice
// ------------------------------------------------------------

double area_landprice(const world&w,int r1,int r2,int l1,int l2){
    double sum{0};
    for(int i=r1; i<= std::fmax(r1,r2); ++i){
        double sum_per_row{0};
        for(int j=l1; j<=std::fmax(l1,l2); ++j){
            sum_per_row += w.world_block[i][j].landprice;
        }
        sum +=sum_per_row;
    }
    return sum;
}

double total_landprice(const world&w){
    return area_landprice(w,0,w.worldx,0,w.worldy);
}

// ------------------------------------------------------------
// RGDP
// ------------------------------------------------------------

double RGDP(const world&w){
    return GDP(w)/total_popularity(w);
}

// ------------------------------------------------------------
// original crime rate, considering the levels of residential area only
// ------------------------------------------------------------

double original_crime_rate(const world&w){
    int sum1{0};
    int sum2{0};
    int sum3{0};
    int sum4{0};
    for(int i=0;i<w.worldx;++i){
        int a{0};
        int b{0};
        int c{0};
        int d{0};
        for(int j=0;j<w.worldy;++j){
            if(w.world_block[i][j].kind==1){
                switch(w.world_block[i][j].level){
                    case 0:
                        ++a;
                        break;
                    case 1:
                        ++b;
                        break;
                    case 2:
                        ++c;
                        break;
                    case 3:
                        ++d;
                        break;
                }
            }
        }
        sum1+=a;
        sum2+=b;
        sum3+=c;
        sum4+=d;
    }
    double s1{double(sum1)/(sum1+sum2+sum3+sum4)};
    double s2{double(sum2)/(sum1+sum2+sum3+sum4)};
    double s3{double(sum3)/(sum1+sum2+sum3+sum4)};
    double s4{double(sum4)/(sum1+sum2+sum3+sum4)};
    double rate{0};
    rate=(10*s1+8*s2+3*s3+1*s4)*10;
    return rate;
}

// ------------------------------------------------------------
// glad
// ------------------------------------------------------------

vector<int> used(const world&w){
    vector<int>v(4,0);
    for(int i=0;i<w.worldx;++i){
        for(int j=0;j<w.worldy;++j){
            switch(w.world_block[i][j].kind){
                case 1:      // residential
                    ++v[0];
                    break;
                case 2:      // commercial
                    ++v[1];
                    break;
                case 3:      // industrial
                    ++v[2];
                    break;
                case 5:      // infrastructure
                    ++v[3];
                    break;
            }
        }
    }
    return v;
}

vector<double> dif_kind_rate(const world&w){
    int sum{0};
    vector<int> v1=used(w);
    for(int i=0;i<v1.size();++i){
        sum+=v1[i];
    }
    vector<double> v2;
    for(int j=0;j<=3;++j){
		double a{ 0 };
		if (sum != 0)
		{
			a = v1[j] / sum;
		}
        v2.push_back(a);
    }
    return v2;
}

vector<double> each_kind_glad(const world&w){
    vector<double> each_glad(4,0);
    for(int i=0;i<w.worldx;++i){
        for(int j=0;j<w.worldy;++j){
            switch(w.world_block[i][j].kind){
                case 1://residential
                    each_glad[0]+=w.world_block[i][j].glad;
                    break;
                case 2://commercial
                    each_glad[1]+=w.world_block[i][j].glad;
                    break;
                case 3://industrial
                    each_glad[2]+=w.world_block[i][j].glad;
                    break;
                case 5://infrastructure
                    each_glad[3]+=w.world_block[i][j].glad;
                    break;
            }
        }
    }
    return each_glad;
}

double total_glad(const world&w){
    double glad{0};
    vector<double>assistant1 = dif_kind_rate(w);
    vector<double>assistant2 = each_kind_glad(w);
    glad = assistant1[0]*assistant2[0]+assistant1[1]*assistant2[1]+assistant1[2]*assistant2[2]+assistant1[3]*assistant2[3];
    return glad;
}

void print_each_glad(const world&w){
    vector<double>v = each_kind_glad(w);
    std::cout<<"residential : "<<v[0]<<'\t'
    <<"commercial : "<<v[1]<<'\t'
    <<"industrial : "<<v[2]<<'\t'
    <<"infrastructure : "<<v[3]<<'\t';
}

int covering_station_num(const Block&b,const world&w){
    int sum{0};
    for (size_t i = std::fmax(0, b.x - 15); i < std::fmin(b.x + 15, w.worldx); i++){
        for(size_t j = std::fmax(0, b.y - 15); j < std::fmin(w.worldy, b.y + 15); j++){
            if(w.world_block[i][j].public_building==13){//scanning police station,13 is police station
                ++sum;
            }
        }
    }
    return sum;
}

int covering_school_num(const Block&b,const world&w){
    int sum{0};
    for (size_t i = std::fmax(0, b.x - 10); i < std::fmin(b.x + 10, w.worldx); i++){
        for(size_t j = std::fmax(0, b.y - 10); j < std::fmin(w.worldy, b.y + 10); j++){
            if(w.world_block[i][j].public_building==12){//scanning school,12 is school
                ++sum;
            }
        }
    }
    return sum;
}

int covering_hospital_num(const Block&b,const world&w){
    int sum{0};
    for (size_t i = std::fmax(0, b.x - 10); i < std::fmin(b.x + 10, w.worldx); i++){
        for(size_t j = std::fmax(0, b.y - 10); j < std::fmin(w.worldy, b.y + 10); j++){
            if(w.world_block[i][j].public_building==11){//scanning hospital,13 is hospital
                ++sum;
            }
        }
    }
    return sum;
}

void crime_change(Block&bb,const world&w){
    bb.crime-=covering_station_num(bb, w)*1;
    if(bb.crime<0){
        bb.crime=0;
    }
}

double basic_install_rate(const Block&b,const world&w){
    int sum{0};
    sum=covering_station_num(b, w)+covering_school_num(b, w)+covering_hospital_num(b, w);
    double rate{0};
    rate=double(sum)/225;
    return rate;
}

void draw_s(world* wor){
	world& w{ *wor };
    for(int i1=8;i1>=3;--i1){
		Sleep(300);
		change_kind(1,w.world_block[5][i1],w);
    }
    for(int i2=6;i2<=8;++i2){
		Sleep(300);
		change_kind(1,w.world_block[i2][3],w);
    }
    for(int i3=4;i3<=8;++i3){
		Sleep(300);
		change_kind(1,w.world_block[8][i3],w);
    }
    for(int i4=9;i4<=11;++i4){
		Sleep(300);
		change_kind(1,w.world_block[i4][8],w);
    }
    for(int i5=7;i5>=3;--i5){
		Sleep(300);
		change_kind(1,w.world_block[11][i5],w);
    }
}

void draw_i(world* wor) {
	world& w{ *wor };
	for (int i1 = 13; i1 <= 15; ++i1)
	{
		Sleep(300);
		change_kind(2, w.world_block[5][i1], w);
	}
	for (int i2 = 6; i2 <= 10; ++i2)
	{
		Sleep(300);
		change_kind(2, w.world_block[i2][14], w);
	}
	for (int i3 = 13; i3 <= 15; ++i3)
	{
		Sleep(300);
		change_kind(2, w.world_block[11][i3], w);
	}
}

void draw_m(world* wor) {
	world& w{ *wor };
	for (int i1 = 5; i1 <= 11; ++i1)
	{
		Sleep(300);
		change_kind(1, w.world_block[i1][20], w);
	}
	for (int i2 = 1; i2 <= 3; ++i2)
	{
		Sleep(300);
		change_kind(1, w.world_block[5 + i2][20 + i2], w);
	}
	for (int i3 = 1; i3 <= 3; ++i3)
	{
		Sleep(300);
		change_kind(1, w.world_block[8 - i3][23 + i3], w);
	}
	for (int i4 = 6; i4 <= 11; ++i4)
	{
		Sleep(300);
		change_kind(1, w.world_block[i4][26], w);
	}
}

void undraw_sim(world* wor){
	Sleep(23000);
	for(int i=0;i<wor->worldx;++i)
	{
        for(int j=0;j<wor->worldy;++j){
			change_kind(0,wor->world_block[i][j],*wor);
        }
    }
	wor->world_start = 1;
}

int num_of_residential(const world&w){
    int sum{0};
    for(int i=0;i<w.worldx;++i){
        for(int j=0;j<w.worldy;++j){
            if(w.world_block[i][j].kind==1){
                ++sum;
            }
        }
    }
    return sum;
}

int num_of_commercial(const world&w){
    int sum{0};
    for(int i=0;i<w.worldx;++i){
        for(int j=0;j<w.worldy;++j){
            if(w.world_block[i][j].kind==2){
                ++sum;
            }
        }
    }
    return sum;
}

int num_of_industrial(const world&w){
    int sum{0};
    for(int i=0;i<w.worldx;++i){
        for(int j=0;j<w.worldy;++j){
            if(w.world_block[i][j].kind==3){
                ++sum;
            }
        }
    }
    return sum;
}

int num_of_water_pump(const world&w){
    int sum{0};
    for(int i=0;i<w.worldx;++i){
        for(int j=0;j<w.worldy;++j){
            if(w.world_block[i][j].public_building==1){
                ++sum;
            }
        }
    }
    return sum;
}

int num_of_park(const world&w){
    int sum{0};
    for(int i=0;i<w.worldx;++i){
        for(int j=0;j<w.worldy;++j){
            if(w.world_block[i][j].public_building==2){
                ++sum;
            }
        }
    }
    return sum;
}

int num_of_hospital(const world&w){
    int sum{0};
    for(int i=0;i<w.worldx;++i){
        for(int j=0;j<w.worldy;++j){
            if(w.world_block[i][j].public_building==11){
                ++sum;
            }
        }
    }
    return sum;
}

int num_of_school(const world&w){
    int sum{0};
    for(int i=0;i<w.worldx;++i){
        for(int j=0;j<w.worldy;++j){
            if(w.world_block[i][j].public_building==12){
                ++sum;
            }
        }
    }
    return sum;
}

int num_of_police_station(const world&w){
    int sum{0};
    for(int i=0;i<w.worldx;++i){
        for(int j=0;j<w.worldy;++j){
            if(w.world_block[i][j].public_building==13){
                ++sum;
            }
        }
    }
    return sum;
}
