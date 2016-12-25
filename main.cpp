#include "ann_data.h"
#include "ann_net.h"
void getVecFromFile(string str, vector<double> &imgVec);

int main()
{
    AnnData data(16*32);
    data.getDataSet("./Train");

    AnnNet net(16*32, 10, 30);
    net.initNet();
    net.setMaxEpoch(200);
    net.setMinError(0.001);
    net.setLearningRate(0.1);

    net.train(data.sampleInput, data.targetLabel);


    //prdict
    string folderPath = "./Test/";
    DIR *dir = opendir(folderPath.c_str());
    struct dirent *ent;
    while((ent = readdir(dir)) != NULL)
    {
        if(ent->d_type & DT_REG)
        {
            if(string(ent->d_name).find(".bmp") == string::npos)
                continue;
            vector<double> in;
            vector<double> out;
            double conf;
            int lable;
            string str = folderPath + ent->d_name;

            getVecFromFile(str, in);
            net.predict(in, out, conf, lable);
            cout << str << ": predicted to " << lable << endl;
        }
    }
    closedir(dir);

    return 0;
}


void getVecFromFile(string str, vector<double> &imgVec)
{
    cv::Mat img = cv::imread(str, 0);
    //TODO(ww): convert to binary img
    cv::resize(img, img, cv::Size(16,32));
    for(int i = 0; i < img.rows; ++i)
    {
        uchar* data = img.ptr<uchar>(i);
        for(int j = 0; j < img.cols; ++j)
        {
            imgVec.push_back(data[j]/255.0);
        }
    }
}