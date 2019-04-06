#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion

#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O

using namespace std;
using namespace cv;


static void help()
{
    cout
        << "------------------------------------------------------------------------------" << endl
        << "This program shows how to read a video file with OpenCV. In addition, it "
        << "tests the similarity of two input videos first with PSNR, and for the frames "
        << "below a PSNR trigger value, also with MSSIM."                                   << endl
        << "Usage:"                                                                         << endl
        << "./video-input-psnr-ssim <referenceVideo> <useCaseTestVideo> <PSNR_Trigger_Value> <Wait_Between_Frames> " << endl
        << "--------------------------------------------------------------------------"     << endl
        << endl;
}


int main(int argc, char *argv[])
{
    help();
    if (argc != 2)
    {
	cout << argc;
	cout << argv;	
        cout << "Not enough parameters" << endl;
        return -1;
    }
    stringstream conv;

    const string sourceReference = argv[1];// sourceCompareWith = argv[2];
    int psnrTriggerValue, delay;
    conv << argv[3] << endl << argv[4];       // put in the strings
    //conv >> psnrTriggerValue >> delay;        // take out the numbers
    
    int frameNum = -1;          // Frame counter

    VideoCapture captRefrnc(sourceReference);// captUndTst(sourceCompareWith);

    if (!captRefrnc.isOpened())
    {
        cout  << "Could not open reference " << sourceReference << endl;
        return -1;
    }
    //if (!captUndTst.isOpened())
    //{
    //   cout  << "Could not open case test " << sourceCompareWith << endl;
    //    return -1;
    //}
    Size refS = Size((int) captRefrnc.get(CAP_PROP_FRAME_WIDTH),
                     (int) captRefrnc.get(CAP_PROP_FRAME_HEIGHT));
    //     uTSi = Size((int) captUndTst.get(CAP_PROP_FRAME_WIDTH),
    //                 (int) captUndTst.get(CAP_PROP_FRAME_HEIGHT));
    //if (refS != uTSi)
    //{
    //    cout << "Inputs have different size!!! Closing." << endl;
    //    return -1;
    //}

    //const char* WIN_UT = "Under Test";
    const char* WIN_RF = "Reference";

    // Windows
    namedWindow(WIN_RF, WINDOW_NORMAL);
    //namedWindow(WIN_UT, WINDOW_AUTOSIZE);
    moveWindow(WIN_RF, 400       , 0);
    resizeWindow(WIN_RF, 640, 480);        //750,  2 (bernat =0)
    //moveWindow(WIN_UT, refS.width, 0);         //1500, 2

    cout << "Reference frame resolution: Width=" << refS.width << "  Height=" << refS.height
         << " of nr#: " << captRefrnc.get(CAP_PROP_FRAME_COUNT) << endl;
    cout << "PSNR trigger value " << setiosflags(ios::fixed) << setprecision(3)
         << psnrTriggerValue << endl;

    Mat frameReference, frameUnderTest;
    double psnrV;
    Scalar mssimV;

    for(;;) //Show the image captured in the window and repeat
    {
        captRefrnc >> frameReference;
        //captUndTst >> frameUnderTest;
        //if (frameReference.empty() || frameUnderTest.empty())
        //{
        //    cout << " < < <  Game over!  > > > ";
        //    break;
        //}
        ++frameNum;
        cout << "Frame: " << frameNum << "# ";
        //psnrV = getPSNR(frameReference,frameUnderTest);
        //cout << setiosflags(ios::fixed) << setprecision(3) << psnrV << "dB";
        //if (psnrV < psnrTriggerValue && psnrV)
        //{
        //    mssimV = getMSSIM(frameReference, frameUnderTest);
        //    cout << " MSSIM: "
 //               << " R " << setiosflags(ios::fixed) << setprecision(2) << mssimV.val[2] * 100 << "%"
//                << " G " << setiosflags(ios::fixed) << setprecision(2) << //mssimV.val[1] * 100 << "%"
//                << " B " << setiosflags(ios::fixed) << setprecision(2) << //mssimV.val[0] * 100 << "%";
//        }

        cout << endl;

        imshow(WIN_RF, frameReference);
//        imshow(WIN_UT, frameUnderTest);

        char c = (char)waitKey(delay);
        if (c == 27) break;
    }
    return 0;
}

