#include "../include/extent.h"
#include <hpx/parallel/algorithms/minmax.hpp>
using pairf=std::pair<float,float>;

pairf bracket_MinMax(const vector<float> &x, const int start, const int end);

void extent(const int N, const vector<float>& x,const vector<float>& y,float& xmin,float& ymin,float& ext)
{
    auto policy=hpx::parallel::par.with(hpx::parallel::static_chunk_size(100000));
    auto x_mm=hpx::parallel::minmax_element(policy,x.begin(),x.end());
    auto y_mm=hpx::parallel::minmax_element(policy,y.begin(),y.end());

    xmin=*(x_mm.first);
    ymin=*(y_mm.first);
    float  dx(*(x_mm.second)-xmin);
    float  dy(*(y_mm.second)-ymin);
    ext= dx>dy ? dx : dy;
}