#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#define HEIGHT 512
#define WIDTH 512

using namespace std;

typedef struct Point {
	int x;
	int y;
};

template<typename T> T** MemAlloc2D(int nHeight, int nWidth, int nInitVal)
{
	T** rtn = new T*[nHeight];
	for (int h = 0; h < nHeight; h++)
	{
		rtn[h] = new T[nWidth];
		memset(rtn[h], nInitVal, sizeof(T) * nWidth);
	}
	return rtn;
}

template<typename T> void MemFree2D(T** arr2D, int nHeight)
{
	for (int h = 0; h < nHeight; h++)
	{
		delete[] arr2D[h];
	}
	delete[] arr2D;
}

void FileRead(const char* strFilename, unsigned char** arr2D, int nHeight, int nWidth)
{
	FILE* fp_in = fopen(strFilename, "rb");
	for (int h = 0; h < nHeight; h++)
	{
		fread(arr2D[h], sizeof(unsigned char), nWidth, fp_in);
	}

	fclose(fp_in);
}

void FileWrite(const char* strFilename, unsigned char** arr2D, int nHeight, int nWidth)
{
	FILE* fp_out = fopen(strFilename, "wb");
	for (int h = 0; h < nHeight; h++)
	{
		fwrite(arr2D[h], sizeof(unsigned char), nWidth, fp_out);
	}

	fclose(fp_out);
}



void main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// File Open & Memory Allocation

	unsigned char** arr2D = MemAlloc2D<unsigned char>(HEIGHT, WIDTH, 0);
	
	FileRead("lena256.raw", arr2D, HEIGHT, WIDTH);

	FileWrite("lena256_out.raw", arr2D, HEIGHT, WIDTH);

}
