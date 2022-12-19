#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <string>
namespace algorithm {

template<class T> void permutation(std::vector<T> &vec,int cursor,std::vector<std::vector<T> > &res)
{
    if(size_t(cursor)==vec.size()) {
        res.push_back(vec);
    }
    bool ok;
    for(size_t i=size_t(cursor);i<vec.size();i++) {
        ok=true;
        for(size_t j=i+1;j<vec.size();j++) {
            if(vec[j]==vec[i]) {
                ok=false;
                break;
            }
        }
        if(!ok) {
            continue;
        }
        std::swap(vec[cursor],vec[i]);
        permutation(vec,cursor+1,res);
        std::swap(vec[cursor],vec[i]);
    }
}
extern std::string test_permutation();
}

#endif // ALGORITHM_H
