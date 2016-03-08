//
// Created by giovanni on 08.03.16.
//
#ifndef HPCSE2_EX2_REORDER_H
#define HPCSE2_EX2_REORDER_H

void reorder(const int N, const int* const keys, const float * const x,const float * const y,float *xsorted,float *ysorted)
{
  #pragma omp parallel for
    for(int i=0;i<N;i++){
        xsorted[i]=x[keys[i]];
        ysorted[i]=y[keys[i]];
    }
}

#endif //HPCSE2_EX2_REORDER_H
