//
// PAMClusterer.hpp
//
// Copyright (c) 2017 Shion Hosoda
//
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php
//

#include "pyutils.hpp"

enum Metric{//{{{
    JSD, EUCLID,
};//}}}

class PAMClusterer{//{{{
    private:
        unsigned int numberOfClusters_;
        Metric metric_;
        std::vector<std::vector<double> > data_;
        // medoid index records
        std::vector<unsigned int> medoidIndices_;
        std::vector<unsigned int> clusters_;
    public:
        // PAMClusterer();
        // PAMClusterer(unsigned int numberOfClusters, unsigned int metric);
        PAMClusterer(unsigned int numberOfClusters);
        void initializeMedoids();
        double calculateDistance(unsigned int index1, unsigned int index2);
        void assignRecordsToClusters();
        void decideMedoids();
        bool IsConvergence(std::vector<unsigned int> medoids);
        py::list fitToData(const py::list &data);
};//}}}
