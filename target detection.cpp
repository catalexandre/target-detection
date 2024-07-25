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

int binarize(string name, bool (*functionRGB)(double, double, double))
{
    ifstream image(name + ".ppm");
    ofstream binaryImage(name + "Binary.ppm");

    if (!image.is_open())
    {
        cout << "Encountered an error when opening the input file. Terminating the program" << endl;
        return 1;
    }

    image.ignore(256, '\n');

    int width, height, maxValue;

    image >> width >> height >> maxValue;

    std::cout << width << ' ' << height << ' ' << maxValue << endl;

    binaryImage << "P1" << endl << width << ' ' << height << endl;

    double* luminosityData = new double[width * height];
    int* maskData = new int[width * height];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r, g, b;

            image >> r >> g >> b;

            //this is the value that is compared to threshold. 0 <= valueCheck <= 1

            if (functionRGB(r, g, b))
            {
                binaryImage << 0 << ' ';
            }


            else
            {
                binaryImage << 1 << ' ';
            }
        }
    }

    image.close();
    binaryImage.close();
}

int main()
{

    string inputFileName;

    std::cout << "Name of the picture file (exclude extension): ";
    std::cin >> inputFileName;

    binarize("Blob_DetectionP3", *rSubGB);

    delete[] maskData;

    std::cout << "pixel sorted";

    return 0;
}