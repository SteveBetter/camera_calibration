#include <iostream>
#include <opencv2/opencv.hpp>

using std::vector;
using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char *argv[])
{
    cv::VideoCapture capture(0);
    if (!capture.isOpened()) {
        cout << "\nCouldn't open the camera\n";
        return -1;
    }
	
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
	
	cv::FileStorage fs;
		
	// EXAMPLE OF LOADING THESE MATRICES BACK IN:
    fs.open("intrinsics.xml", cv::FileStorage::READ);
    cout << "\nimage width: " << static_cast<int>(fs["image_width"]);
    cout << "\nimage height: " << static_cast<int>(fs["image_height"]);
    
    cv::Mat intrinsic_matrix_loaded, distortion_coeffs_loaded;
    cv::Size image_size;
    fs["camera_matrix"] >> intrinsic_matrix_loaded;
    fs["distortion_coefficients"] >> distortion_coeffs_loaded;
    fs["image_width"] >> image_size.width;
    fs["image_height"] >> image_size.height;
    
    cout << "\nintrinsic matrix:" << intrinsic_matrix_loaded;
    cout << "\ndistortion coefficients: " << distortion_coeffs_loaded << endl;

    // Build the undistort map which we will use for all
    // subsequent frames.
    //
    cv::Mat map1, map2;
    cv::initUndistortRectifyMap(intrinsic_matrix_loaded, distortion_coeffs_loaded,
                              cv::Mat(), intrinsic_matrix_loaded, image_size,
                              CV_16SC2, map1, map2);

    // Just run the camera to the screen, now showing the raw and
    // the undistorted image.
    //
    for (;;) {
        cv::Mat image, image0;
        capture >> image0;

        if (image0.empty()) {
            break;
        }
        cv::remap(image0, image, map1, map2, cv::INTER_LINEAR,
            cv::BORDER_CONSTANT, cv::Scalar());
        cv::imshow("Undistorted", image);
        if ((cv::waitKey(30) & 255) == 27) {
            break;
        }
    }

    return 0;
}
