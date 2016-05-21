
/////////////////////////////////////////////////////////////////////////////////
#include "pre_main.h"

// C++ stuff
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>  // Video write
#include <opencv2/videoio/videoio_c.h>  // Video write
#include <time.h>
#include <unistd.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
using namespace std;
using namespace cv;


//////////////////////////////////////////////////////////////////////////
string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://www.cplusplus.com/reference/clibrary/ctime/strftime/
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%m%d-%H%M%S", &tstruct);//"%Y-%m-%d-%H-%M-%S"

    return buf;
}

string recordVideo(){

    string outroot, outfile;

    char NPath[200];
    getcwd(NPath, 200);

    // By default write to same directory
    outroot = NPath;
    outroot = outroot + "/results/videos/";
    string videoFileName = currentDateTime();
    outfile = currentDateTime() + ".mp4";

    //webcam
    int device = 0;
    VideoCapture vCap;
    vCap = VideoCapture( device );
    vCap.set(CV_CAP_PROP_FRAME_WIDTH,640);
    vCap.set(CV_CAP_PROP_FRAME_HEIGHT,480);

    if( !vCap.isOpened() )
    {
        cout<<"camera couldn't be opened."<<endl;
    }

    Mat img;
    vCap >> img;
    cv::flip(img, img, 1);
    //    ellipse(img, Point(320, 240), Size(150, 120), 90.0, 0.0, 360, Scalar(0, 0, 255), 3);
    Mat rec_img=img(cv::Rect(0,0,640,480));

    boost::filesystem::path dir(outroot);
    boost::filesystem::create_directory(dir);

    string videoFilePath = outroot + outfile;

    // saving the videos
    cv::VideoWriter video_writer(videoFilePath, CV_FOURCC('D','I','V','X'), 24, rec_img.size(), true);

    time_t end,begin = time(0);
    int frameProc = 0;
    while(!img.empty())
    {
        //        namedWindow("rec",1);
        vCap >> img;
        cv::flip(img, img, 1);

        //qDebug()<<"size:"<<img.rows<<"*"<<img.cols<<endl;
        rec_img=img(cv::Rect(0,0,640,480));

        video_writer << rec_img;

        Mat tmpImg = rec_img.clone();
        ellipse(tmpImg, Point(320, 240), Size(150, 120), 90.0, 0.0, 360, Scalar(0, 0, 255), 3);
        imshow("rec", tmpImg);

        frameProc++;
        end = time(0);
        cout<<"Time:"<<end-begin<<"s,FrameCount:"<<frameProc-1<<endl;

        if(frameProc>180)//end-begin>10
        {
            break;
        }

        char c=cv::waitKey(1);
        if(c=='q')
        {
            break;
        }

    }

    return videoFilePath;

}
////////////////////////////////////////////////////////////////////////////////////////////

bool cmp_by_value(const pair<int, double>& lhs, const pair<int, double>& rhs){
    return abs(lhs.second) < abs(rhs.second);
}

int getFileNames(const string& dir, vector<string>& fileNames){
    boost::filesystem::path path(dir);
    if(!boost::filesystem::exists(path))
        cout<<"hahahahahahahahahahahahahahahaha"<<endl;

    boost::filesystem::directory_iterator end_iter;
    for(boost::filesystem::directory_iterator iter(path); iter!=end_iter; ++iter){
        if(boost::filesystem::is_regular_file(iter->status()))
            fileNames.push_back(iter->path().string());

        if(boost::filesystem::is_directory(iter->status()))
            getFileNames(iter->path().string(), fileNames);
    }
    return fileNames.size();
}

int main(){
    string outroot, outvideo, outimage, outtext;
    string mp4_file;


    char NPath[200];
    getcwd(NPath, 200);

    // By default write to same directory
    outroot = NPath; //	"/home/clark/Documents/Workspace/Glasses_PoseEstimation_SelectFrames/bin"
    outvideo =  outroot + "/results/TestData/videos/";
    outtext =  outroot + "/results/TestData/texts/";
    outimage = outroot + "/results/TestData/images/";

    vector<string> fileNames;
    int numVideos = getFileNames(outvideo, fileNames);
    cout<<numVideos<<endl;

    for(int n = 0; n < numVideos; ++n){
        string _currentDateTime = currentDateTime();
        mp4_file = fileNames[n];
//        mp4_file = 	"/home/clark/Documents/Workspace/Glasses_PoseEstimation_SelectFrames/bin/results/TestData/videos/videos/0511-104413.mp4";


        cout << "mp4_file: " << mp4_file << endl;

        cv::Mat captured_image;
        cv::VideoCapture m_VideoCapture(mp4_file);

        if( !m_VideoCapture.isOpened() )
        {
            std::cout << "Failed to open video source" << std::endl;
            abort();
        }

        m_VideoCapture >> captured_image;

        //    int numFrame = m_VideoCapture.get(CV_CAP_PROP_FRAME_COUNT);
        vector<Mat> imagesAll;
        int counter = 0;
        while(!captured_image.empty())
        {
            /// show image
            //        namedWindow("image",1);
            //        imshow("image", captured_image);
            Mat img = captured_image.clone();
            imagesAll.push_back(img);

            m_VideoCapture >> captured_image;
            //        cv::waitKey(33);
            counter++;
        }

        string line;
        float x, y, z, t;


        //  ===================== RQH
        string out_file = pre_main(mp4_file, outtext);

        if(out_file == "-1"){
            cout<<"hahahahahahaha"<<endl;
            continue;
        }

        ifstream stream(out_file);

        vector<int> imgIdxVec;
        vector<float> scaleVec;
        vector<CvPoint2D32f> midEyeVec;
        vector<glm::mat4> rotateMatrixVec;

        int imgIdx;
        float scale;
        CvPoint2D32f midEye;
        glm::mat4 rotateMatrix;

        int numOfImages = 0;
        int theBestImageIndex = 0;
        double tmp = 10.0;
        vector<double> data;

        map<int, double> tmp_map;

        while(getline(stream, line)){
            istringstream ss(line);
            ss >> imgIdx;
//            printf("%d\n", imgIdx);

            getline(stream, line);
            istringstream ss1(line);
            ss1 >> x >> y >> z >> t;
            rotateMatrix[0][0] = x;
            rotateMatrix[0][1] = y;
            rotateMatrix[0][2] = z;
            midEye.x = t;
//            printf("%.6f %.6f %.6f %.6f\n", x, y, z, t);

            getline(stream, line);
            istringstream ss2(line);
            ss2 >> x >> y >> z >> t;
            rotateMatrix[1][0] = x;
            rotateMatrix[1][1] = y;
            rotateMatrix[1][2] = z;
            midEye.y = t;
//            printf("%.6f %.6f %.6f %.6f\n", x, y, z, t);

            getline(stream, line);
            istringstream ss3(line);
            ss3 >> x >> y >> z >> t;
            rotateMatrix[2][0] = x;
            rotateMatrix[2][1] = y;
            rotateMatrix[2][2] = z;
            scale = t;
//            printf("%.6f %.6f %.6f %.6f\n", x, y, z, t);

            //        getline(stream, line);
            //        printf("0  0  0  1\n");

            getline(stream, line);
            istringstream ss4(line);
            ss4 >> x >> y >> z >> t;
            rotateMatrix[3][0] = x;
            rotateMatrix[3][1] = y;
            rotateMatrix[3][2] = z;
//            printf("%.6f %.6f %.6f 1\n", x, y, z);


            tmp_map[imgIdx] = rotateMatrix[3][1];

            if( rotateMatrix[3][1] < tmp){
                tmp = rotateMatrix[3][1];
                theBestImageIndex = imgIdx;
            }

            scaleVec.push_back(scale);
            imgIdxVec.push_back(imgIdx);
            midEyeVec.push_back(midEye);
            rotateMatrixVec.push_back(rotateMatrix);

            numOfImages++;
        }

        vector<pair<int, double> > tmp_vec(tmp_map.begin(), tmp_map.end());
        //    cout<<"===================Before Sort: "<<endl;
        //    for(int i = 0; i<tmp_vec.size(); ++i)
        //        cout<<tmp_vec[i].first<<", "<<tmp_vec[i].second<<endl;
        sort(tmp_vec.begin(), tmp_vec.end(), cmp_by_value);
//        cout<<"===================After Sort: "<<endl;
//        for(int i = 0; i<tmp_vec.size(); ++i)
//            cout<<tmp_vec[i].first<<", "<<tmp_vec[i].second<<endl;


        //    cout<<"theBestImageIndex: "<<theBestImageIndex<<endl;
        //    Mat img = imagesAll[theBestImageIndex];
        //    imshow("the Best Image", img);
        //    waitKey(0);



        //    outroot = outroot + "/images/";
        //    string videoFileName = currentDateTime();
        //    outfile = currentDateTime() + ".jpg";

        for(int i = 0; i<5; ++i){

            Mat img = imagesAll[tmp_vec[i].first];
            //save
            std::stringstream tmpss;
            tmpss<<i;
            string imgFileName = outimage + _currentDateTime + "_" + tmpss.str() + ".jpg";
            imwrite(imgFileName, img);
            imshow("clark", img);
            waitKey(1000);
        }
    }

    return 0;
}
