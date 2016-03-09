//
// Created by giovanni on 08.03.16.
//
#ifndef HPCSE2_EX2_REORDER_H
#define HPCSE2_EX2_REORDER_H

void reorder(const int N, const vector<int>& keys, const vector<float> &x, const vector<float> &y, vector<float> &xsorted,
             vector<float> &ysorted)
{
  #pragma omp parallel for schedule(static) num_threads(NUM_THREADS)
    for(int i=0;i<N;i++){
        xsorted[i]=x[keys[i]];
        ysorted[i]=y[keys[i]];
    }
}

#endif //HPCSE2_EX2_REORDER_H
