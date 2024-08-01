#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#include "position.h"

using namespace std;
using namespace std::chrono;

bool rSubGB(double r, double g, double b)
{
    double threshold = 0.45 * 255;
    double value = r - 0.3 * g - 0.3 * b;

    return (value > threshold) ? true : false;
}

bool test(double r, double g, double b)
{
    double threshold = 0.2 * 255;
    double value = r - 0.3 * g - 0.3 * b;

    return (value > threshold) ? true : false;
}

int* binarize(string name, bool (*functionRGB)(double, double, double), int &imageWidth, int &imageHeight)
{
    ifstream image(name + ".ppm");
    ofstream binaryImage(name + "Binary.ppm");

    if (!image.is_open())
    {
        return nullptr;
    }

    image.ignore(256, '\n');

    int maxValue;

    image >> imageWidth >> imageHeight >> maxValue;

    int imageSize = imageWidth * imageHeight;

    int* returnData = new int[imageSize];

    binaryImage << "P1" << endl << imageWidth << ' ' << imageHeight << endl;

    for (int i = 0; i < imageHeight; i++)
    {
        for (int j = 0; j < imageWidth; j++)
        {
            int r, g, b;

            image >> r >> g >> b;

            double valueCheck = r - 0.25 * g - 0.25 * b;

            int pixelValue;

            if (functionRGB(r, g, b))
            {
                pixelValue = 1;
            }

            else
            {
                pixelValue = 0;
            }

            binaryImage << pixelValue << ' ';
            returnData[i * imageWidth + j] = pixelValue;
        }
    }

    image.close();
    binaryImage.close();

    return returnData;
}

position* getTargetPosition(int* imageArray)
{


    return new position(0, 0);
}

int main()
{
    int imageWidth, imageHeight;

    auto start = high_resolution_clock::now();

    int* binaryImageArray = binarize("Blob_DetectionP3", test, imageWidth, imageHeight);

    if (binaryImageArray != nullptr)
    {
        getTargetPosition(binaryImageArray);

        delete[] binaryImageArray;
    }

    else
    {
        cout << "Failed to binarize the image." << endl;
    }

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Time taken: " << duration.count() << " ms" << endl;

    return 0;
}