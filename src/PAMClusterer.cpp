//
// PAMClusterer.cpp
//
// Copyright (c) 2017 Shion Hosoda
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "include/PAMClusterer.hpp"

// PAMClusterer::PAMClusterer()//{{{
//     :numberOfClusters_(3),
//     medoidIndices_(3),
//     metric_(JSD)
// {
//     this->initializeMedoids();
// }//}}}

// PAMClusterer::PAMClusterer(unsigned int numberOfClusters, unsigned int metric)//{{{
//     :numberOfClusters_(numberOfClusters),
//     medoidIndices_(numberOfClusters),
//     metric_(static_cast<Metric>(metric))
// {
//     this->initializeMedoids();
// }//}}}

PAMClusterer::PAMClusterer(unsigned int numberOfClusters)//{{{
    :numberOfClusters_(numberOfClusters),
    medoidIndices_(numberOfClusters),
    metric_(JSD)
{
}//}}}

void PAMClusterer::initializeMedoids(){//{{{
    medoidIndices_ = choiceRandomItems(numberOfClusters_, 0, data_.size()-1);
}//}}}

double PAMClusterer::calculateDistance(unsigned int index1, unsigned int index2){//{{{
    switch(metric_){
        case JSD:
            return calculateJSD(data_[index1], data_[index2]);
            break;
        case EUCLID:
            return calculateEuclidDistance(data_[index1], data_[index2]);
            break;
    }
}//}}}

void PAMClusterer::assignRecordsToClusters(){//{{{
    for(int i=0; i<data_.size(); i++){
        double maxSimilarity = 0.0;
        unsigned int maxIndex = 0;
        for(int j=0; j<numberOfClusters_; j++){
            double thisSimilarity = 1/this->calculateDistance(i, medoidIndices_[j]);
            if(thisSimilarity > maxSimilarity){
                maxSimilarity = thisSimilarity;
                maxIndex = j;
            }
        }
        clusters_[i] = maxIndex;
    }
}//}}}

void PAMClusterer::decideMedoids(){//{{{
    for(int i=0; i<numberOfClusters_; i++){
        double maxSumSimilarity = 0.0;
        unsigned int maxIndex = 0;
        for(int j=0; j<data_.size(); j++){
            if(clusters_[j] == i){
                double thisSumDistance = 0.0;
                for(int k=0; k<data_.size(); k++){
                    if(clusters_[k] == i){
                        thisSumDistance += this->calculateDistance(j, k);
                    }
                }
                double thisSumSimilarity = 1.0/thisSumDistance;
                if(thisSumSimilarity > maxSumSimilarity){
                    maxSumSimilarity = thisSumSimilarity;
                    maxIndex = j;
                }
            }
        }
        medoidIndices_[i] = maxIndex;
    }
}//}}}

bool PAMClusterer::IsConvergence(std::vector<unsigned int> medoids){//{{{
    bool isCorresponding = true;
    for(int i=0; i<medoidIndices_.size(); i++){
        if(medoidIndices_[i] != medoids[i]){
            isCorresponding = false;
            break;
        }
    }
    return isCorresponding;
}//}}}

py::list PAMClusterer::fitToData(const py::list &data){//{{{
    data_ = convertListToVector2D(data);
    clusters_.assign(data_.size(),0);
    this->initializeMedoids();
    int count = 0;
    while(1){
        std::vector<unsigned int> previousMedoids = medoidIndices_;
        this->assignRecordsToClusters();
        this->decideMedoids();
        if(this->IsConvergence(previousMedoids))break;
        count++;
    }
    std::cout<<count<<" iterations."<<std::endl;
    return convertVectorToList1D(clusters_);
}//}}}

BOOST_PYTHON_MODULE(libclustering){//{{{
	py::class_<PAMClusterer>("pam", py::init<unsigned int>())
    .def("fit", &PAMClusterer::fitToData);
}//}}}
