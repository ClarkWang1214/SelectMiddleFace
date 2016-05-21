/////////////////////////////////////////////////////////////////////////////////
#include "pre_main.h"
// OpenCV stuff   opencv2/
#include <core/core.hpp>
#include <objdetect.hpp>
#include <calib3d.hpp>
#include <imgcodecs.hpp>
#include <imgproc.hpp>
#include <highgui/highgui.hpp>
#include <videoio/videoio.hpp>  // Video write  opencv2/
#include <videoio/videoio_c.h>  // Video write  opencv2/
//#include <viz/vizcore.hpp> ///*opencv2/*/

// IplImage stuff (get rid of it? TODO)
#include <core/core_c.h>
#include <imgproc/imgproc_c.h>

// C++ stuff
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>  // Video write
#include <opencv2/videoio/videoio_c.h>  // Video write
#include <time.h>
#include <unistd.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
using namespace std;
using namespace cv;

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
        //qDebug()<<"size:"<<img.rows<<"*"<<img.cols<<endl;
        rec_img=img(cv::Rect(0,0,640,480));

        video_writer << rec_img;

        imshow("rec", rec_img);

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

//int main (int argc, char **argv)
//{
//    string mp4_file = recordVideo();
//    std::cout << "mp4_file: " << mp4_file << endl;
////    cv::String mp4_file = "/home/ren/MyGit/CLM_Server_Upload/GlassesData/identify/test.mp4";
////    std::cout << "1" << std::endl;
//    char out_file[1024] = {0};
//    strcpy(out_file, pre_main(mp4_file.c_str()));
//    cout<<"out: "<<out_file<<endl;

//    return 0;
//}

