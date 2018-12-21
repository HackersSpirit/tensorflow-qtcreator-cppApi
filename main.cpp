#include <QCoreApplication>

#include <fstream>
#include <utility>
#include <vector>

#include <Windows.h>
#define COMPILER_MSVC
#define NOMINMAX

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDebug>

#include "tensorflow/core/public/session.h"
#include "tensorflow/core/platform/env.h"
#include "tensorflow/core/framework/tensor.h"

using namespace cv;
using namespace tensorflow;
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    vector<cv::String> fn;
    glob("path_to_image_folders\\*.jpeg", fn, false);
    size_t count = fn.size(); 
    int height = 256;
    int width = 256;
    cv::Size s(height,width);

    // initializing the graph
    tensorflow::GraphDef graph_def;

    // Location of model
    std::string graphFile = "path_to_tesorflow_model\\model.pb";

    tensorflow::Status graphLoadedStatus = ReadBinaryProto(tensorflow::Env::Default(),graphFile,&graph_def);
    if (!graphLoadedStatus.ok()){
        std::cout << graphLoadedStatus.ToString()<<std::endl;
        return 1;
    }
    std::unique_ptr<tensorflow::Session> session_inception(tensorflow::NewSession(tensorflow::SessionOptions()));
    tensorflow::Status session_create_status = session_inception->Create(graph_def);

    if (!session_create_status.ok()){
        return 1;
    }
    std::vector<tensorflow::Tensor> finalOutput;

    std::string InputName = "conv2d_1_input:0"; //Name of inputnode 
    std::string OutputName = "dense_2/Sigmoid:0"; //Name of outputnode

    for (size_t i=0; i<count; i++){
        cv::Mat Image;
        Mat readImage;
        readImage = imread(fn[i]);
        std::cerr << "resizing\n";
        cv::resize(readImage,Image,s,0,0,INTER_AREA);
        std::cerr << "success resizing\n";
        int depth = Image.channels();
        tensorflow::Tensor input_tensor(tensorflow::DT_FLOAT, tensorflow::TensorShape({1,height,width,depth}));
        auto input_tensor_mapped = input_tensor.tensor<float, 4>();

        Mat Image3;
        Image.convertTo(Image3, CV_32F, 1.0 / 255, 0);
        Image = Image3;

        const float * source_data = (float*) Image.data;
        // copying the data into the corresponding tensor
        for (int y = 0; y < height; ++y) {
            const float* source_row = source_data + (y * width * depth);
            for (int x = 0; x < width; ++x) {
                const float* source_pixel = source_row + (x * depth);
                const float* source_B = source_pixel + 0;
                const float* source_G = source_pixel + 1;
                const float* source_R = source_pixel + 2;

                input_tensor_mapped(0, y, x, 0) = *source_R;
                input_tensor_mapped(0, y, x, 1) = *source_G;
                input_tensor_mapped(0, y, x, 2) = *source_B;
            }
        }
        double t = (double)getTickCount();
        tensorflow::Status run_status  = session_inception->Run({{InputName,input_tensor}},{OutputName},{},&finalOutput);
        t = ((double)getTickCount() - t)/getTickFrequency();
        std::cout << "Times passed in seconds: " << t << std::endl;

        tensorflow::Tensor output = std::move(finalOutput.at(0));
        auto scores = output.flat<float>();
        cout<<"Image:"<<i<<" "<<"Score"<<scores<<endl;
    }
    return a.exec();
}
