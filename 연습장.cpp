#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void onMouse(int, int, int, int, void*); Point initialPoint(-1, -1); // initialPoint�� �ʱ���ġ ���庯��
void calculateAndShowHistogram(Mat&);
Mat img_return_10_10(const Mat&); // �̹����� 60,60���� �ڸ��� ȭ�鿡 ����ϸ鼭 �ڸ� �� ���� 
void displayPixelValues(const Mat& img);

int main(int argc, char** argv) {
    Mat img_BGR = imread("lena.jpg", IMREAD_COLOR); // �̹��� �о� MAT�� ���� + cv::Vec3b Ÿ������ �� �ȼ��� ����ȴ�. Vec3b�� 3���� 8-bit ��ȣ ���� ������ �̷���� ���� ��, unsigned char�� �̷����.  �� ��� -> B,G,R

    if (img_BGR.empty()) { cout << "Image Open Error!" << endl;        return -1; } //img�� �ȿ����� -1 ��ȯ

    //  cout << "�� ���" <<  img.rows << " �� ��� " << img.cols << " ���� ��� " << img.dims << "  ä�� �� ���   " << img.channels() << " ��� �� ��� " << img.size();

    Mat channels[3];   split(img_BGR, channels);    // �� ä���� �и�

    // imshow("Red Channel", channels[2]);    imshow("Green Channel", channels[1]);   imshow("Blue Channel", channels[0]); // R,G,B ä�� ǥ��

    Mat img_resized;    resize(img_BGR, img_resized, Size(10, 10)); // img ũ�� 10x10���� ����

    //cout << "this is mat for 10x10x3 \n " << resizedImg; // ��µǴ� ����� B G R B G R ... �� 30�� ; x 10�� ���� ��µȴ�. [ 1 2 3 4 5 6  ... ;  12 2 3 4 5 6 7 ... ; ...] ���⼭ 1 2 3 �� ���� B G R
    Mat img_gray;    cvtColor(img_BGR, img_gray, COLOR_BGR2GRAY);                     // img�� gray�� �ٲٱ�
    //Mat img_gray = 0.299 * channels[0] + 0.587 * channels[1] + 0.114 * channels[2];   //img�� gray�� �ٲٱ�_�Լ�����

    Rect regiontocrop(10, 10, 3, 3); //�߶� ���� ����(x,y, width, height)
    // Mat img_cropped = img_BGR(regiontocrop); //img���� ������ �߶�
    // imwrite("cropped_lena.jpg", img_cropped); // �߶� �̹��� ���� �������� ��ġ�� ����
    Mat img_gray_cropped = img_gray(regiontocrop);   imwrite("img_gray_cropped.jpg", img_gray_cropped); // img_gray�� �߶󳻾� ����
    //���� ���� �׸��� ���ھ���
    Mat img_draw = img_BGR;
    rectangle(img_draw, Point(100, 100), Point(200, 300), Scalar(0, 0, 255), 2);  // Point�� 2D��鿡���� ���� ��Ÿ���µ� ����, Scalar�� 4���� ���͸� ��Ÿ�� �� ���(�ִ� 4���� �Ǽ� ���� ����)
    putText(img_draw, "Hello i am mook", Point(100, 100), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2); // ������ 2�� ���� �β�
    cout << img_gray_cropped;
    //img ��� �� ���
    namedWindow("Original", WINDOW_AUTOSIZE);
    // imshow("Image out", img_draw); // display


    Mat originalImage = imread("lena.jpg", IMREAD_GRAYSCALE);

       // ȸ�� ��ȯ ��Ʈ���� ���� (��: �ð� �������� 30�� ȸ��)
    Mat rotationMatrix = getRotationMatrix2D(Point2f(originalImage.cols / 2, originalImage.rows / 2), 30.0, 1.0);

    // ������ ������ ���� ����ȯ ��Ʈ���� ����
    Mat inverseRotationMatrix;
    invertAffineTransform(rotationMatrix, inverseRotationMatrix);

    // ������ ���� ����
    Mat destinationImage;
    warpAffine(originalImage, destinationImage, inverseRotationMatrix, originalImage.size());



    /*
     Mat  img_a = img_BGR;
    imshow("Image drag to rectangle", img_a);
    setMouseCallback("Image drag to rectangle", onMouse, &img_a);  //�Լ� �����쿡 ���
    */    //���콺 �巡�׷� ���簢�� �׸���

    //waitKey(); // key ���
    //calculateAndShowHistogram(img_gray);

  //  return 0;


    /*  //  �������� openning
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        Mat erosion_result;     erode(img_gray, erosion_result, kernel);
        Mat dilation_result;    dilate(img_gray, dilation_result, kernel);
        vector<Mat> image_horizontal = { img_gray, erosion_result, dilation_result}; // vector�� Ȱ���Ͽ� Mat ��ü�� ��� �����迭�� ��Ÿ��
        // vector�����ø��� ���. � ������ �����͵� ������ �� �ִ� �����迭. vector�� Mat type�� ��ü�� ��� Ư�� ������ ���� �迭
        //���ʹ� ��Ұ� ���Եǰų� ������ �� �ڵ����� ũ�⸦ �����ϴ� ����� ���� ���� �迭,  �ش� ���� ������ �����̳ʿ� ���� �ڵ����� ó��
        //���� ��Ҵ� �ݺ��ڸ� ����Ͽ� �׼����ϰ� Ž���� �� �ֵ��� ���� ����ҿ� ��ġ
        Mat combined_result; hconcat(image_horizontal, combined_result); // inputarrayofarrays�� vector<Mat>�� ���� Mat�� �迭�� ����
        imshow("Combined_result", combined_result);
        waitKey(0);
        */


}

Mat img_return_10_10(const Mat& img) {
    Rect regiontocrop(30, 20, 10, 10);
    Mat img_10_10 = img(regiontocrop).clone();
    Mat img_resize;  resize(img_10_10, img_resize, Size(500, 500));
    return img_resize;
}

void displayPixelValues(const Mat& img) {
    Mat result = img.clone();

    for (int j = 0; j < img.rows; j++) {
        for (int i = 0; i < img.cols; i++) {
            // �ȼ� ���� ���ڿ��� ��ȯ
            string pixel_value_str = to_string(static_cast<int>(img.at<uchar>(j, i)));

            // �ȼ� �� ǥ��
            putText(result, pixel_value_str, Point(j * 500 / img.cols, i * 500 / img.rows), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 0, 0), 1);
        }
    }
    imshow("Image with Pixel Values", result);
    waitKey(0);
}



void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) { initialPoint = Point(x, y); }
    else if (event == EVENT_LBUTTONUP) {
        Mat img_a = *(Mat*)userdata;
        rectangle(img_a, initialPoint, Point(x, y), Scalar(0, 255, 0), 2);
        imshow("Image drag to rectangle", img_a);
        initialPoint = Point(-1, -1);
    }
}

/*
    cout <<"�̹���:\n"  << img<< endl; // 512x512x3 ���������, �̰ɷ� ����ϸ� 1���� ���ͷ� ��µ�
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            cout << "[";
            for (int c = 0; c < img.channels(); ++c) {
                cout << static_cast<int>(img.at<Vec3b>(i, j)[c]);  //static_cast<int> -> C++���� ����ȯ �����ϴ� ������. img.at<Vec3b>(i, j)[c]�� �� ��ü���� 'c'�ε����� �ش��ϴ� ��ü ������. 'c'�� ä�� �ǹ�
                if (c < img.channels() - 1) {
                    cout << ", ";
                }
            }
            cout << "] ";
        }
        cout << endl;
    }
  */

  /*
  void cv::calcHist(const Mat* images, // Histogram�� ����� �̹����鿡 ���� �迭�̴�.
      int           nimages, // images �迭�� ���Ե� �̹����� �����̴�.
      const int* channels, //Histogram�� ����� ä�� ��ȣ���� �迭�̴�.
      InputArray    mask, //Histogram�� ����� ������ ������ �� �ִ�.
      OutputArray   hist, //Histogram ������� �����Ѵ�.
      int           dims, //Histogram ������� ������ hist�� ������ ����Ų��.
      const int* histSize, //�� ������ bin����, �� �󵵼��� �з��� ĭ�� ������ �ǹ��Ѵ�.
      const float** ranges, //�� ������ �з� bin�� �ּҰ� �ִ밪�� �ǹ��Ѵ�.
      bool          uniform = true,
      bool          accumulate = false
  )
  */

void calculateAndShowHistogram(Mat& img) {
    if (img.empty()) { cout << "�̹����� �ҷ��� �� �����ϴ�." << endl;        return; }
    int histSize = 256; // ���� �� �ȼ��� ũ��� 256�̹Ƿ�
    int hist[256] = { 0 };

    for (int j = 0; j < img.cols; ++j) {
        for (int i = 0; i < img.rows; ++i) {
            int pixel_value = static_cast<int>(img.at<uchar>(j, i));
            hist[pixel_value]++;
        }
    }
    // ������׷� �ð�ȭ
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

    // ����ȭ
    int max_hist_value = *max_element(hist, hist + histSize);
    for (int i = 0; i < histSize; i++) {
        hist[i] = cvRound((double)hist[i] / max_hist_value * histImage.rows);
    }

    // ������׷� �׸���
    for (int i = 1; i < histSize; i++) {
        line(histImage, Point(bin_w * (i - 1), hist_h - hist[i - 1]),
            Point(bin_w * i, hist_h - hist[i]),
            Scalar(0, 0, 255), 2, 8, 0);
    }

    // �����쿡 �̹����� ������׷� ���
    namedWindow("Image", WINDOW_AUTOSIZE);
    imshow("Image", img);

    namedWindow("Histogram", WINDOW_AUTOSIZE);
    imshow("Histogram", histImage);

    waitKey(0);
}
