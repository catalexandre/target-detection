#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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

int* binarize(string name, bool (*functionRGB)(double, double, double))
{
    ifstream image(name + ".ppm");
    ofstream binaryImage(name + "Binary.ppm");

    if (!image.is_open())
    {
        return nullptr;
    }

    image.ignore(256, '\n');

    int maxValue, width, height;

    image >> width >> height >> maxValue;

    int imageSize = width * height;

    int* returnData = new int[imageSize + 2];

    returnData[0] = width;
    returnData[1] = height;

    binaryImage << "P1" << endl << width << ' ' << height << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
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
            returnData[i * width + j + 2] = pixelValue;
        }
    }

    image.close();
    binaryImage.close();

    return returnData;
}

int main()
{
    int* binaryImageArray = binarize("Blob_DetectionP3", test);

    if (binaryImageArray != nullptr)
    {
        int imageWidth = binaryImageArray[0];
        int imageHeight = binaryImageArray[1];
        int imageSize = imageWidth * imageHeight;

        // Allocate a new array for the actual binary image data
        int* binaryImageData = new int[imageSize];

        // Copy data from old array to new array
        for (int i = 0; i < imageSize; i++)
        {
            binaryImageData[i] = binaryImageArray[2 + i];
        }

        // Deallocate the old array
        delete[] binaryImageArray;

        // Print the binary image data
        for (int i = 0; i < imageHeight; i++)
        {
            for (int j = 0; j < imageWidth; j++)
            {
                cout << binaryImageData[i * imageWidth + j] << ' ';
            }
            cout << endl;
        }

        // Deallocate the new array
        delete[] binaryImageData;
    }

    else
    {
        cout << "Failed to binarize the image." << endl;
    }

    return 0;
}