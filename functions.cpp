#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;


int energy(const Pixel *const*image, int col, int row, int width, int height)
{
  int totalsum = 0;
      int i = col;
      int j = row;
      int sum;
      if(i == 0){
        if(j ==0){
          sum = pow(image[width -1][0].r - image[1][0].r, 2) + pow(image[width -1][0].g - image[1][0].g, 2) + pow(image[width -1][0].b - image[1][0].b, 2) + pow(image[0][height -1].r - image[0][1].r, 2) + pow(image[0][height -1].g - image[0][1].g, 2) + pow(image[0][height -1].b - image[0][1].b, 2);
        }
        else if (j == height -1){
          sum = pow(image[width -1][j].r - image[1][j].r, 2) + pow(image[width -1][j].g - image[1][j].g, 2) + pow(image[width -1][j].b - image[1][j].b, 2) + pow(image[i][0].r - image[i][j-1].r, 2) + pow(image[0][0].g - image[0][j-1].g, 2) + pow(image[0][0].b - image[0][j-1].b, 2);
        }
        else{
          sum = pow(image[width - 1][j].r - image[1][j].r, 2) + pow(image[width -1][j].g - image[1][j].g, 2) + pow(image[width -1][j].b - image[1][j].b, 2) + pow(image[0][j+1].r - image[0][j -1].r, 2) + pow(image[0][j+1].g - image[0][j-1].g, 2) + pow(image[0][j+1].b - image[0][j-1].b, 2);
        }
      }
      else if(j==0){
        if(i == width - 1){
          sum = pow(image[0][0].r - image[i - 1][0].r, 2) + pow(image[0][0].g - image[i-1][0].g, 2) + pow(image[0][0].b - image[i - 1][0].b, 2) + pow(image[i][1].r - image[i][height -1].r, 2) + pow(image[i][1].g - image[i][height -1].g, 2) + pow(image[i][height -1].b - image[i][1].b, 2);
        }
        else{
          sum = pow(image[i][height - 1].r - image[i][1].r, 2) + pow(image[i][height -1].g - image[i][1].g, 2) + pow(image[i][height -1].b - image[i][1].b, 2) + pow(image[i+1][0].r - image[i-1][0].r, 2) + pow(image[i+1][0].g - image[i-1][0].g, 2) + pow(image[i+1][0].b - image[i-1][0].b, 2);
        }
      }
      else if (j == height - 1){
        if(i == width -1){
          sum = pow(image[i][0].r - image[i][j-1].r, 2) + pow(image[i][0].g - image[i][j-1].g, 2) + pow(image[i][j-1].b - image[i][0].b, 2) + pow(image[0][j].r - image[i-1][j].r, 2) + pow(image[0][j].g - image[i-1][j].g, 2) + pow(image[0][j].b - image[i-1][j].b, 2) ;
        }
        else{
          sum = pow(image[i][0].r - image[i][j-1].r, 2) + pow(image[i][0].g - image[i][j-1].g, 2) + pow(image[i][j-1].b - image[i][0].b, 2) + pow(image[i +1][j].r - image[i-1][j].r, 2) + pow(image[i+1][j].g - image[i-1][j].g, 2) + pow(image[i+1][j].b - image[i-1][j].b, 2) ;
        }
      }
      else if(i == width - 1){
        sum = pow(image[0][j].r - image[i-1][j].r, 2) + pow(image[0][j].g - image[i-1][j].g, 2) + pow(image[0][j].b - image[i-1][j].b, 2) + pow(image[i][j+1].r - image[i][j-1].r, 2) + pow(image[i][j+1].g - image[i][j-1].g, 2) + pow(image[i][j+1].b - image[i][j-1].b, 2) ;
      }
      else{
        sum = pow(image[i+1][j].r - image[i-1][j].r, 2) + pow(image[i+1][j].g - image[i-1][j].g, 2) + pow(image[i+1][j].b - image[i-1][j].b, 2) + pow(image[i][j+1].r - image[i][j-1].r, 2) + pow(image[i][j+1].g - image[i][j-1].g, 2) + pow(image[i][j+1].b - image[i][j-1].b, 2);
      }
      totalsum += sum;
  return totalsum;
}


int getVerticalSeam(const Pixel *const*image, int start_col, int width, int height, int* seam)
{
  int col1 = start_col;
  int x = energy(image, start_col, 0, width, height);
  seam[0] = start_col;
  int total_energy = x;
  for(int i = 1; i < height; i ++){
    int opt1;
    int opt2;
    int opt3;
    if(width - 1 == col1){
      opt1 = energy(image, col1, i, width, height);
      opt2 = energy(image, col1 - 1, i, width, height);
      opt3 = opt1+1;
    }
    else if(col1 == 0){
      opt1 = energy(image, col1, i, width, height);
      opt2 = opt1 +1;
      opt3 = energy(image, col1 +1, i, width, height);
    }
    else{
      opt1 = energy(image, col1, i, width, height);
      opt2 = energy(image, col1 - 1, i, width, height);
      opt3 = energy(image, col1 +1, i, width, height);
    }
    if(opt1 <= opt2){
      if(opt1 <= opt3){
        seam[i] = col1;
        total_energy += opt1;
      }
      else{
        total_energy += opt3;
        if(col1 == width - 1){
          seam[i] = 0;
          col1 = 0;
        }
        else{
          seam[i] = col1 +1;
          col1 +=1;
        }
      }
    }
    else{
      if(opt2 < opt3){
        total_energy += opt2;
        if(col1 == 0){
          col1 = width - 1;
          seam[i] = width -1;
        }
        else{
          seam[i] = col1 -1;
          col1 -=1;
        }
      }
      else{
        total_energy += opt3;
        if(col1 == width - 1){
          seam[i] = 0;
          col1 = 0;
        }
        else{
          seam[i] = col1 +1;
          col1 +=1;
        }
      }
    }


  }
  
  return total_energy;
}

void removeVerticalSeam(Pixel **image, int& width, int height, int *verticalSeam)
{
  for(int i = 0; i < height; i ++){
    for(int j = verticalSeam[i]; j < width; j++){
        if(j == width - 1){
          continue;
        }
        else{
          int x = j + 1;
          image[j][i] = image[x][i];
          //image[j][i].g = image[x][i].g;
          //image[j][i].b = image[x][i].b;
        }
    }
  }
  width -=1;
}

// TODO Write this function for extra credit
int getHorizontalSeam(const Pixel *const*image, int start_row, int width, int height, int* seam)
{
  return 0;
}

// TODO Write this function for extra credit
void removeHorizontalSeam(Pixel **image, int width, int& height, int *horizontalSeam)
{
  
}

int *findMinVerticalSeam(const Pixel *const*image, int width, int height)
{
  // initialize minSeam and minDistance to seam starting at first col (index 0)
  int *minSeam = new int[height]{0};
  int minDist = getVerticalSeam(image, 0, width, height, minSeam);

  int *candidateSeam = new int[height]{0};
  int candidateDistance = -1; // invalid distance

  // start at second col (index 1) since we initialized with first col (index 0)
  for (int col = 1; col < width; ++col)
  {
    candidateDistance = getVerticalSeam(image, col, width, height, candidateSeam);

    if (candidateDistance < minDist)
    { // new min
      //  swap min & candidate
      minDist = candidateDistance;
      int* temp = candidateSeam;
      candidateSeam = minSeam;
      minSeam = temp;
    }
  }

  // clean up 
  delete [] candidateSeam;

  return minSeam;
}

int *findMinHorizontalSeam(const Pixel *const*image, int width, int height)
{
  // initialize minSeam and minDistance to seam starting at first row (index 0)
  int *minSeam = new int[width]{0};
  int minDistance = getHorizontalSeam(image, 0, width, height, minSeam);

  int *candidateSeam = new int[width]{0};
  int candidateDistance = -1; // invalid distance

  // start at second row (index 1) since we initialized with first row (index 0)
  for (int row = 1; row < height; ++row)
  {
    candidateDistance = getHorizontalSeam(image, row, width, height, candidateSeam);

    if (candidateDistance < minDistance)
    { // new minimum
      //  swap min and candidate seams
      minDistance = candidateDistance;
      int* temp = candidateSeam;
      candidateSeam = minSeam;
      minSeam = temp;
    }
  }

    // clean up 
  delete [] candidateSeam;

  return minSeam;
}

Pixel **createImage(int width, int height)
{
  cout << "Start createImage... " << endl;

  // Create a one dimensional array on the heap of pointers to Pixels
  //    that has width elements (i.e. the number of columns)
  Pixel **image = new Pixel *[width] {}; // initializes to nullptr

  for (int col = 0; col < width; ++col)
  { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    try
    {
      image[col] = new Pixel[height];
    }
    catch (std::bad_alloc &e)
    {
      // clean up already allocated arrays
      for (int i = 0; i < col; ++i)
      {
        delete[] image[i];
      }
      delete[] image;
      // rethrow
      throw e;
    }
  }

  // initialize cells
  // cout << "Initializing cells..." << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = {0, 0, 0};
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel **image, int width)
{
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i = 0; i < width; ++i)
  {
    delete[] image[i];
  }
  delete[] image;
  image = nullptr;
  cout << "End deleteImage..." << endl;
}

bool isValidColor(int colorVal)
{
  if (colorVal < 0 || colorVal > 255)
  {
    return false;
  }
  return true;
}

Pixel ** loadImage(string filename, int &width, int &height)
{
  cout << "Start loadImage..." << endl;
  // remove
  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    throw std::invalid_argument("Failed to open input file (" + filename + ")");
  }

  string type;
  ifs >> type; // should be P3
  if (toupper(type.at(0)) != 'P' || type.at(1) != '3')
  {
    throw std::domain_error("Not PPM type P3 (" + type + ")");
  }
  ifs >> width;
  // cout << "w and h: " << w << " " << h << endl;
  if (ifs.fail())
  {
    throw std::domain_error("Read non-integer value for width");
  }
  if (width <= 0)
  {
    ostringstream oss;
    oss << "Width in file must be greater than 0 (" << width << ")";
    throw std::domain_error(oss.str());
  }

  ifs >> height;
  if (ifs.fail())
  {
    cout << "Read non-integer value for height" << endl;
  }
  if (height <= 0)
  {
    ostringstream oss;
    oss << "Height in file must be greater than 0 (" << height << ")";
    throw std::domain_error(oss.str());
  }

  int colorMax = 0;
  ifs >> colorMax;
  if (ifs.fail())
  {
    throw std::domain_error("Read non-integer value for max color value");
  }
  if (colorMax != 255)
  {
    ostringstream oss;
    oss << "Max color value must be 255 (" << colorMax << ")";
    throw std::domain_error(oss.str());
  }

  // load image throws exceptions but we will let them pass through
  Pixel **image = createImage(width, height);

  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "Pixel(" << col << ", " << row << ")" << endl;
      ifs >> image[col][row].r;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for red");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for red (" << image[col][row].r << ")";
        throw std::domain_error(oss.str());
      }

      ifs >> image[col][row].g;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for green");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for green (" << image[col][row].r + ")";
        throw std::domain_error(oss.str());
      }

      ifs >> image[col][row].b;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for blue");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for blue (" << image[col][row].r + ")";
        throw std::domain_error(oss.str());
      }
    }
  }
  cout << "End loadImage..." << endl;
  return image;
}

void outputImage(string filename, const Pixel *const *image, int width, int height)
{
  cout << "Start outputImage..." << endl;
  // remove code
  // declare/define and open output file stream with filename
  ofstream ofs(filename);
  // ensure file is open
  if (!ofs.is_open())
  {
    throw std::invalid_argument("Error: failed to open output file - " + filename);
  }
  ofs << "P3" << endl;
  ofs << width << " " << height << endl;
  ofs << 255 << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      ofs << image[col][row].r << " ";
      ofs << image[col][row].g << " ";
      ofs << image[col][row].b << " ";
    }
    ofs << endl;
  }
  cout << "End outputImage..." << endl;
}
