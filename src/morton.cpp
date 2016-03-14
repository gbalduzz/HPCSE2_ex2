//
// Created by giovanni on 12.03.16.
//
#include "../include/morton.h"

uint   interleave(uint x,uint y);
inline uint integer_mantissa(float x,float xmin,float xmax);

void morton(const int N, const vector<float> &x, const vector<float> &y, const float xmin, const float ymin,
   const float ext, vector<int> &index)
{
    hpx::parallel::for_each( hpx::parallel::v1::parallel_execution_policy(),
            std::begin(index),std::end(index),
            [&](int& idx)
            {
                int i=&idx-&index[0];//std::distance(idx,std::begin(index));
                idx=interleave(integer_mantissa(x[i],xmin,ext+xmin),integer_mantissa(y[i],ymin,ext+ymin));
            }
    );

}

uint   interleave(uint x,uint y)
{
    // Interleave lower 16 bits of x and y, so the bits of x
    // are in the even positions and bits from y in the odd;
    // z gets the resulting 32-bit Morton Number.
    // x and y must initially be less than 65536.
    //From  https://graphics.stanford.edu/~seander/bithacks.html#InterleaveBMN
    static const unsigned int B[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF};
    static const unsigned int S[] = {1, 2, 4, 8};

    x = (x | (x << S[3])) & B[3];
    x = (x | (x << S[2])) & B[2];
    x = (x | (x << S[1])) & B[1];
    x = (x | (x << S[0])) & B[0];

    y = (y | (y << S[3])) & B[3];
    y = (y | (y << S[2])) & B[2];
    y = (y | (y << S[1])) & B[1];
    y = (y | (y << S[0])) & B[0];

    return x | (y << 1);
}

inline uint integer_mantissa(float x,float xmin,float xmax){
    //map x,y from [x/ymin,x/ymin+ext] to [0, 65536)
    return static_cast<uint>( (x-xmin)/(xmax-xmin)*65535 );
}
