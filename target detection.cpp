#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    double threshold = 0.5 * 255;

    string inputFileName;

    std::cout << "Name of the picture file (exclude extension): ";
    std::cin >> inputFileName;

    ifstream image(inputFileName + ".ppm");
    ofstream binaryImage(inputFileName + "Binary.ppm");

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
            double valueCheck = r - 0.25 * g - 0.25 * b;

            if (valueCheck > threshold)
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

    delete[] luminosityData;
    delete[] maskData;

    std::cout << "pixel sorted";

    return 0;
}