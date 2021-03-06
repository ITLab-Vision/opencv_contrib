/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2014, Itseez Inc, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Itseez Inc or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include "opencv2/datasetstools/ar_hmdb.hpp"
#include "precomp.hpp"

namespace cv
{
namespace datasetstools
{

using namespace std;

class CV_EXPORTS AR_hmdbImp : public AR_hmdb
{
public:
    AR_hmdbImp() {}
    //AR_hmdbImp(const string &path, int number = 0);
    virtual ~AR_hmdbImp() {}

    virtual void load(const string &path);

private:
    void loadDatasetSplit(const string &path, int number = 0);

    void loadDataset(const string &path);

    void loadAction(const string &fileName, vector<string> &train_, vector<string> &test_);
};

void AR_hmdbImp::loadAction(const string &fileName, vector<string> &train_, vector<string> &test_)
{
    ifstream infile(fileName.c_str());
    string video, label;
    while (infile >> video >> label)
    {
        if ("1"==label)
        {
            train_.push_back(video);
        } else
        if ("2"==label)
        {
            test_.push_back(video);
        }
    }
}

/*AR_hmdbImp::AR_hmdbImp(const string &path, int number)
{
    loadDataset(path, number);
}*/

void AR_hmdbImp::load(const string &path)
{
    loadDataset(path);
}

void AR_hmdbImp::loadDataset(const string &path)
{
    for (int i=0; i<3; ++i)
    {
        loadDatasetSplit(path, i);
    }
}

void AR_hmdbImp::loadDatasetSplit(const string &path, int number)
{
    // valid number [0,1,2]
    if (number<0 || number>2)
    {
        return;
    }

    train.push_back(vector< Ptr<Object> >());
    test.push_back(vector< Ptr<Object> >());
    validation.push_back(vector< Ptr<Object> >());

    string pathDataset(path + "hmdb51_org/");
    string pathSplit(path + "testTrainMulti_7030_splits/");

    vector<string> fileNames;
    getDirList(pathDataset, fileNames);
    for (vector<string>::iterator it=fileNames.begin(); it!=fileNames.end(); ++it)
    {
        Ptr<AR_hmdbObj> currTrain(new AR_hmdbObj);
        Ptr<AR_hmdbObj> currTest(new AR_hmdbObj);
        currTrain->name = *it;
        currTest->name = *it;

        train.back().push_back(currTrain);
        test.back().push_back(currTest);

        char tmp[2];
        sprintf(tmp, "%u", number+1);
        string fileName(pathSplit + currTrain->name + "_test_split" + tmp + ".txt");
        loadAction(fileName, currTrain->videoNames, currTest->videoNames);
    }
}

Ptr<AR_hmdb> AR_hmdb::create()
{
    return Ptr<AR_hmdbImp>(new AR_hmdbImp);
}

}
}
