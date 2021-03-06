// Copyright (C) 2015 by Jiecao Chen (chenjiecao@gmail.com)

#include "../include/streamcc_headers/CountMin_basic.hpp"
#include "../include/streamcc_headers/Hash.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <functional>


SccAux::CountMin_basic::CountMin_basic(int _m, int _d) :
        m(_m), d(_d) {
    srand(time(NULL));
    for (int i = 0; i < d; ++i) {
        d_buf.push_back(Buffer(m));
        seeds.push_back(rand());
    }
}


void SccAux::CountMin_basic::processItem(const int &item, double weight) {
    for (int i = 0; i < d; ++i) {
        int p = murmurhash(&item, seeds[i]) % m;
        d_buf[i][p] += weight;
    }
}

double SccAux::CountMin_basic::estTotWeight(const int &item) {
    double values[d];
    for (int i = 0; i < d; ++i) {
        int p = murmurhash(&item, seeds[i]) % m;
        values[i] = d_buf[i][p];
    }
    return *std::min_element(values, values + d);
}

















