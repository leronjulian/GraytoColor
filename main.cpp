//
//  main.cpp
//  Project
//
//  Created by Leron Julian on 10/17/16.
//  Copyright © 2016 Leron Julian. All rights reserved.
//
/*
 Use the surrounding pixels to see what the underlying color is to set equal to the grays and use different a's to see if they equal to one.
 52 = (.3)(r) + (.59)(g) + (.11)(b)
 60 = (.2)(r) + (.7)(g) + (.2)(b)
 60 = (.1)(r) + (.5)(g) + (.4)(b)
 
 */

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct RGBValues{
    int R,G,B;
};

ifstream& operator >>(ifstream &in,RGBValues &RGBV){
    in >> RGBV.R;
    in >> RGBV.G;
    in >> RGBV.B;
    return in;
}

void toBlack(RGBValues *data, int height2, int width2, int hue2);
void toColor(RGBValues *data2, int height3, int width3, int hue3);

int main() {
    ifstream originalPhoto;
    
    //User enters name of file
    string file_upload;
    char color_choice;
    cout << "Enter the name of the picture (Ex. Name.ppm): ";
    cin >> file_upload;
    originalPhoto.open(file_upload);
    cout << "Opening " << file_upload << "...." << endl;
    

    //Gets the height and width of the PPM File
    int width, height, hue;
    string temp;
    getline(originalPhoto, temp);
    getline (originalPhoto, temp);
    originalPhoto >> height;
    originalPhoto >> width;
    originalPhoto >> hue;
    

    const int num = width * height;
    RGBValues *RGB = new RGBValues[num];
    
    //Inputs the data into perspective color in structure
    if (originalPhoto.is_open())
    {
        //Gets the data from PPM file and puts in the structure
        string line;
        for(int i = 0; i < 4; i++){
            getline(originalPhoto, line);
        }
        int count = 0;
        while(count < (height * width)){
            originalPhoto >> RGB[count].R;
            originalPhoto >> RGB[count].G;
            originalPhoto >> RGB[count].B;
            count++;
        }
    }
    else cout << "Unable to open file" << endl;
    
    //Determines whether to convert to color or black/white
    do{
        cout << "Enter B to convert to black & white. C to convert to color: ";
        cin >> color_choice;
        tolower(color_choice);
    }while(color_choice != 'b' && color_choice != 'c');
    
    //Functions that handle converting images to color or black/white
    if(color_choice == 'b')
        toBlack(RGB, height, width, hue);
    else
        toColor(RGB, height, width, hue);
    return 0;
}

void toBlack(RGBValues *data, int height2, int width2, int hue2){
    for(int i = 0; i < (height2*width2 - 1); i++){
        int gray = (data[i].R * 0.3) + (data[i].G * 0.59) + (data[i].B * 0.11);
        data[i].R = gray;
        data[i].G = gray;
        data[i].B = gray;
    }
    ofstream blackWhitePhoto("Black&WhitePhoto.ppm");
    cout << "Converting to black & white..." << endl;
    blackWhitePhoto << "P3" << endl;
    blackWhitePhoto << "#Created by Leron Julian" << endl;
    blackWhitePhoto << height2 << " " << width2 << endl;
    blackWhitePhoto << hue2 << endl;
    
    for(int count = 0; count < (height2*width2 - 1); count++){
        blackWhitePhoto << data[count].R << " ";
        blackWhitePhoto << data[count].G << " ";
        blackWhitePhoto << data[count].B << " ";
    }
    cout << "Done..." << endl;
    cout << "File named Black&WhitePhoto.ppm" << endl;
    blackWhitePhoto.close();
}

void toColor(RGBValues *data, int height3, int width3, int hue3){
    
    int equation1;
    int equation2;
    int equation3;
    for(int index = 0; index < 20; index++){
        data[5].R - (.59*data[index].G) - (.11*data[index].B)/(.03)
        data[10].G = (.1*data[index].R) + (.8*data[index].G) + (.1*data[index].B);
        data[3].B = (.4*data[index].R) + (.3*data[index].G) + (.3*data[index].B);
    }
    
    for(int i = 0; i < (height3*width3); i++){
        int Red = (data[0].R - (.59*data[i].G) - (.11*data[i].B))/(.3);
        int Blue = (data[0].R - (.3*data[i].R) - .59*data[i].G)/(.11);
        int Green = (data[0].R - (.3*data[i].R) - .11*data[i].B)/(.59);

        data[i].R = Red;
        data[i].G = Green;
        data[i].B = Blue;
    }
    ofstream colorPhoto("ColorPhoto.ppm");
    cout << "Converting to color..." << endl;
    colorPhoto << "P3" << endl;
    colorPhoto << "#Created by Leron Julian" << endl;
    colorPhoto << height3 << " " << width3 << endl;
    colorPhoto << hue3 << endl;
    
    for(int count = 0; count < (height3*width3 - 1); count++){
        colorPhoto << data[count].R << " ";
        colorPhoto << data[count].G << " ";
        colorPhoto << data[count].B << " ";
    }
    cout << "Done..." << endl;
    cout << "File named ColorPhoto.ppm" << endl;
    colorPhoto.close();
}
