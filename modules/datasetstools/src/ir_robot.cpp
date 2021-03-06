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

#include "opencv2/datasetstools/ir_robot.hpp"
#include "precomp.hpp"

namespace cv
{
namespace datasetstools
{

using namespace std;

class CV_EXPORTS IR_robotImp : public IR_robot
{
public:
    IR_robotImp() {}
    //IR_robotImp(const string &path);
    virtual ~IR_robotImp() {}

    virtual void load(const string &path);

private:
    void loadDataset(const string &path);
};

/*IR_robotImp::IR_robotImp(const string &path)
{
    loadDataset(path);
}*/

void IR_robotImp::load(const string &path)
{
    loadDataset(path);
}

void IR_robotImp::loadDataset(const string &path)
{
    train.push_back(vector< Ptr<Object> >());
    test.push_back(vector< Ptr<Object> >());
    validation.push_back(vector< Ptr<Object> >());

    vector<string> fileNames;
    getDirList(path, fileNames);
    for (vector<string>::iterator it=fileNames.begin(); it!=fileNames.end(); ++it)
    {
        Ptr<IR_robotObj> curr(new IR_robotObj);
        curr->name = *it;

        string pathScene(path + curr->name + "/");
        vector<string> sceneNames;
        getDirList(pathScene, sceneNames);
        int currImageNum = 0;
        for (vector<string>::iterator itScene=sceneNames.begin(); itScene!=sceneNames.end(); ++itScene)
        {
            string &fileName = *itScene;

            int imageNum = atoi( fileName.substr(3, 3).c_str() );
            //int pos = atoi( fileName.substr(6, 2).c_str() );
            if (imageNum != currImageNum)
            {
                curr->pos.push_back(cameraPos());
                currImageNum = imageNum;
            }

            curr->pos.back().images.push_back(fileName);
        }

        train.back().push_back(curr);
    }
}

Ptr<IR_robot> IR_robot::create()
{
    return Ptr<IR_robotImp>(new IR_robotImp);
}

}
}
