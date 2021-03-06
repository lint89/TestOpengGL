#include <stdio.h>
#include <stdlib.h>

#define WindowWidth		400
#define WindowHeight	400

#define BMP_Header_Length 54

void grab(void)
{
	FILE* pDummyFile;
	FILE* pWritingFile;
	GLubyte* pPixelData;
	GLubyte BMP_Header[BMP_Header_Length];
	GLint i, j;
	GLint PixelDataLength;

	i = WindowWidth * 3;
	while (i % 4 != 0)
	{
		++i;
	}
	PixelDataLength = i * WindowHeight;

	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if (pPixelData == 0)
	{
		exit(0);
	}

	pDummyFile = fopen("dummy.bmp", "rb");
	if (pDummyFile == 0)
	{
		exit(0);
	}


	pWritingFile = fopen("grab.bmp", "wb");
	if (pWritingFile == 0)
	{
		exit(0);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, WindowWidth, WindowHeight, GL_BGR_EXT, 
		GL_UNSIGNED_BYTE, pPixelData);

	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET);
	i = WindowWidth;
	j = WindowHeight;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	fclose(pDummyFile);
	fclose(pWritingFile);

	free(pPixelData);
}
