#pragma once
#include <vector>
#include <string.h>
#include <boost/optional.hpp>
#include <iostream>

using namespace std;

class Fixture
{
public:
	Fixture();
	~Fixture();

//private:
	string make;
	string file;
	string name;
	int fixture_type;
	boost::optional<int> user_type;
	int metric;
	int match;
	int num_sim_files;
	float chuck_width;
	float gb_depth;
	float gb_pullback_dist;

	string file_path;
	int check_sum;
};

