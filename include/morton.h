//
// Created by giovanni on 07.03.16.
//
#ifndef EX2_MORTON_H
#define EX2_MORTON_H
using uint=unsigned int;
#include<hpx/parallel/algorithms/for_each.hpp>
#include<vector>
using std::vector;

//takes array or coords and return array of square's label where the particle resides
void morton(const int N, const vector<float> &x, const vector<float> &y, const float xmin, const float ymin,
            const float ext, vector<int> &index);


#endif //EX2_MORTON_H
