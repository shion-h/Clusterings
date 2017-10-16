//
// pyutils.hpp
//
// Copyright (c) 2017 Shion Hosoda
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include <boost/python.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
namespace py = boost::python;
std::vector<std::vector<double> > convertListToVector2D(py::list list){//{{{
    std::vector<std::vector<double> > vector(len(list));
    for(int i=0; i<vector.size(); i++)vector[i].assign(len(list[0]),0);
    for(int i=0; i<len(list); i++){
        for(int j=0; j<len(list[0]); j++){
            py::list listBuf = py::extract<py::list>(list[i]);
            vector[i][j] = py::extract<double>(listBuf[j]);
        }
    }
    return vector;
}//}}}

py::list convertVectorToList2D(std::vector<std::vector<unsigned int> > vector){//{{{
    py::list list;
    for(int i=0; i<vector.size(); i++){
        py::list oneDlist;
        for(int j=0; j<vector[i].size(); j++){
            oneDlist.append(vector[i][j]);
        }
        list.append(oneDlist);
    }
    return list;
}//}}}

py::list convertVectorToList1D(std::vector<unsigned int> vector){//{{{
    py::list list;
    for(int i=0; i<vector.size(); i++){
        list.append(vector[i]);
    }
    return list;
}//}}}

double calculateJSD(const std::vector<double> vector1, const std::vector<double> vector2){//{{{
    double JSD = 0.0;
    for(int i=0; i<vector1.size(); i++){
        JSD += 0.5 * (vector1[i]*log(vector1[i]/vector2[i]) + vector2[i]*log(vector2[i]/vector1[i]));
    }
    if(JSD == 0.0){
        for(int i=0; i<vector1.size(); i++){
        }
    }
    return JSD;
}//}}}

double calculateEuclidDistance(std::vector<double> vector1, std::vector<double> vector2){//{{{
    double euclidDistance = 0.0;
    for(int i=0; i<vector1.size(); i++){
        double diff = vector1[i]-vector2[i];
        euclidDistance += diff * diff;
    }
    return euclidDistance;
}//}}}

std::vector<unsigned int> choiceRandomItems(const size_t size, int randMin, int randMax){//{{{
    if(randMin > randMax) std::swap(randMin, randMax);
    const size_t maxMinDiff = static_cast<size_t>(randMax - randMin + 1);
    if(maxMinDiff < size) throw std::runtime_error("augument error");

    std::vector<unsigned int> tmp;
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<int> distribution(randMin, randMax);

    const size_t makeSize = static_cast<size_t>(size*1.2);

    while(tmp.size() < size){
        while(tmp.size() < makeSize) tmp.push_back(distribution(mt));
        std::sort(tmp.begin(), tmp.end());
        auto uniqueEnd = std::unique(tmp.begin(), tmp.end());

        if(size < std::distance(tmp.begin(), uniqueEnd)){
            uniqueEnd = std::next(tmp.begin(), size);
        }
        tmp.erase(uniqueEnd, tmp.end());
    }

    std::shuffle(tmp.begin(), tmp.end(), mt);
    return tmp;
}//}}}
