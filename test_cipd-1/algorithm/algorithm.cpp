#include <vector>
#include <QDebug>
#include "algorithm.h"
#include <string>

namespace algorithm {

std::string test_permutation()
{
    std::vector<std::vector<int> > res;
    std::vector<int> nums={1,1,2};
    algorithm::permutation(nums,0,res);
    std::string s;
    for(size_t i=0;i<res.size();i++) {
        s.push_back('[');
        for(size_t j=0;j<res[i].size();j++) {
            s+=std::to_string(res[i][j]);
            if(j<res[i].size()-1) s.push_back(' ');
        }
        s.push_back(']');
        if(i<res.size()-1) s.push_back(',');
    }
    return s;
}

}

