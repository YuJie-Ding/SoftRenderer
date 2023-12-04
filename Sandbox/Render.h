#pragma once
#include "SR.h"
#include "windows.h"
#include <sstream>
#include <fstream>

int loadBmp(std::string bmpPath, BITMAPINFO*& pbmi, BYTE*& pBits)
{
    BITMAPFILEHEADER bmfh;
    FILE* fpi;
    BOOL bSuccess;
    DWORD dwInfoSize, dwBytesRead;
    using namespace std;
    fpi = fopen(bmpPath.c_str(), "rb");
    if (fpi == NULL)
    {
        cout << "Failed to open file";
        exit(EXIT_FAILURE);
    }
    // 读取文件头
    fread(&bmfh, sizeof(tagBITMAPFILEHEADER), 1, fpi);
    if (bmfh.bfType != 0x4d42)
    {
        cout << "Not bmp file";
        exit(EXIT_FAILURE);
    }
    // showBmpHead(strHead);
    pbmi = new BITMAPINFO;
    //读取信息头
    fread(pbmi, 40, 1, fpi);
    // 跳过调色板直接读取像素信息
    int offset = bmfh.bfOffBits - 54;
    fseek(fpi, offset, SEEK_CUR);
    pBits = new BYTE[pbmi->bmiHeader.biWidth * pbmi->bmiHeader.biHeight * 3];
    int n = fread(pBits, bmfh.bfSize - bmfh.bfOffBits, 1, fpi);
    fclose(fpi);
    return 1;
}

SR::RenderObject objCube;
SR::RenderObject objPlane;
SR::RenderObject objCylinder;
SR::RenderObject objCat;
SR::RenderObject objTorus;
SR::RenderObject objRock;
SR::RenderObject objSpot;

SR::VertexShader* LightVertexShader;
SR::FragmentShader* LightFragmentShader;

SR::VertexShader* UnlitVertexShader;
SR::FragmentShader* UnlitFragmentShader;

SR::Texture texture1;
SR::Texture rock_Texture;
SR::Texture spot_Texture;
SR::Texture GIS_Texture;

std::vector<std::string> SplitString(std::string srcString, char splitChar);

void LoadGISImage(void** data, int& width, int& height)
{
    std::string filePath = "E:\\CodeData\\GIS\\bi-image_end.txt";
    std::ifstream fileStream;
    fileStream.open(filePath, std::ios::in);
    std::string line;
    width = 480;
    height = 360;
    char* _data = new char[width * height];
    int row = 0;
    while (std::getline(fileStream, line))
    {
        auto splitLine = SplitString(line, ',');
        for (int i = 0; i < splitLine.size(); i++)
        {
            _data[row * width + i] = atoi(splitLine[i].c_str());
        }
        row++;
    }
    *data = _data;
}

void OnInit(HWND hWnd, LONG width, LONG height)
{
    char* dataOfGis;
    int widthOfData, heightOfData;
    //LoadGISImage((void**) & dataOfGis, widthOfData, heightOfData);
    LightVertexShader = new SR::Light_VShader;
    LightFragmentShader = new SR::Light_FShader;

    UnlitVertexShader = new SR::VertexShader;
    UnlitFragmentShader = new SR::FragmentShader;

    SR::Renderer* render = SR::Renderer::Create();
    std::shared_ptr<SR::Camera> mainCamera(new SR::Camera());
    mainCamera->m_transform.m_position = { 0, 0, 0 };
    mainCamera->aspect = (float)width / height;
    render->SetCamera(mainCamera);
    render->Init(width, height);
    BITMAPINFO* bmpinfo;
    BYTE* data;

    loadBmp(".\\assets\\chess.bmp", bmpinfo, data);
    texture1.BufferData(data, bmpinfo->bmiHeader.biWidth, bmpinfo->bmiHeader.biHeight, bmpinfo->bmiHeader.biBitCount / 8);
    LightFragmentShader->SetTexture(&texture1);
    UnlitFragmentShader->SetTexture(&texture1);

    loadBmp(".\\assets\\rock.bmp", bmpinfo, data);
    rock_Texture.BufferData(data, bmpinfo->bmiHeader.biWidth, bmpinfo->bmiHeader.biHeight, bmpinfo->bmiHeader.biBitCount / 8);

    loadBmp(".\\assets\\spot_texture.bmp", bmpinfo, data);
    spot_Texture.BufferData(data, bmpinfo->bmiHeader.biWidth, bmpinfo->bmiHeader.biHeight, bmpinfo->bmiHeader.biBitCount / 8);

    //GIS_Texture.BufferData(dataOfGis, widthOfData, heightOfData, 1);

    {
        SR::Model_Obj modelCube = SR::LoadObjFromFile(".\\assets\\cube2.obj");
        objCube.m_ib = modelCube.ib;
        objCube.m_vb = modelCube.vb;
        objCube.m_name = modelCube.name;

        SR::Transform cubeTranslation;
        cubeTranslation.m_position = { 0, 0, 7 };
        cubeTranslation.m_rotation = { 45, 45, 0 };
        cubeTranslation.m_scaling = { 1, 1, 1 };

        objCube.m_transform = cubeTranslation;
    }

    {
        SR::Model_Obj modelPlane = SR::LoadObjFromFile(".\\assets\\plane.obj");
        objPlane.m_ib = modelPlane.ib;
        objPlane.m_vb = modelPlane.vb;
        objPlane.m_name = modelPlane.name;

        SR::Transform PlaneTranslation;
        PlaneTranslation.m_position = { 0, 0, 3 };
        PlaneTranslation.m_rotation = { 90, 0, 0 };
        PlaneTranslation.m_scaling = { 1, 1, 1 };

        objPlane.m_transform = PlaneTranslation;
    }

    {

        SR::Model_Obj modelCylinder = SR::LoadObjFromFile(".\\assets\\cylinder2.obj");
        objCylinder.m_ib = modelCylinder.ib;
        objCylinder.m_vb = modelCylinder.vb;
        objCylinder.m_name = modelCylinder.name;

        SR::Transform CylinderTranslation;
        CylinderTranslation.m_position = { 0, 0, 7 };
        CylinderTranslation.m_rotation = { 45, 45, 10 };
        CylinderTranslation.m_scaling = { 1, 1, 1 };

        objCylinder.m_transform = CylinderTranslation;
    }

    {

        SR::Model_Obj modelCat = SR::LoadObjFromFile(".\\assets\\cat2.obj");
        objCat.m_ib = modelCat.ib;
        objCat.m_vb = modelCat.vb;
        objCat.m_name = modelCat.name;

        SR::Transform CatTranslation;
        CatTranslation.m_position = { 0, 0, 4 };
        CatTranslation.m_rotation = { 0, 45, 0 };
        CatTranslation.m_scaling = { 1, 1, 1 };

        objCat.m_transform = CatTranslation;
    }

    {
        SR::Model_Obj modelTorus= SR::LoadObjFromFile(".\\assets\\torus2.obj");
        objTorus.m_ib = modelTorus.ib;
        objTorus.m_vb = modelTorus.vb;
        objTorus.m_name = modelTorus.name;

        SR::Transform TorusTranslation;
        TorusTranslation.m_position = { 0, 0, 4 };
        TorusTranslation.m_rotation = { 45, 0, 45 };
        TorusTranslation.m_scaling = { 1, 1, 1 };

        objTorus.m_transform = TorusTranslation;
    }

    {
        SR::Model_Obj modelRock = SR::LoadObjFromFile(".\\assets\\rock.obj");
        objRock.m_ib = modelRock.ib;
        objRock.m_vb = modelRock.vb;
        objRock.m_name = modelRock.name;

        SR::Transform RockTranslation;
        RockTranslation.m_position = { 0, 0, 7 };
        RockTranslation.m_rotation = { 30, 0, 30 };
        RockTranslation.m_scaling = { 1, 1, 1 };

        objRock.m_transform = RockTranslation;
    }

    {
        SR::Model_Obj modelSpot = SR::LoadObjFromFile(".\\assets\\spot.obj");
        objSpot.m_ib = modelSpot.ib;
        objSpot.m_vb = modelSpot.vb;
        objSpot.m_name = modelSpot.name;

        SR::Transform SpotTranslation;
        SpotTranslation.m_position = { 0, 0, 3 };
        SpotTranslation.m_rotation = { 0, 45, 0 };
        SpotTranslation.m_scaling = { 1, 1, 1 };

        objSpot.m_transform = SpotTranslation;
    }
}

// for displaying FPS
int FPS = 0;
int count_FPS = 0;
unsigned long long timeBegin = 0;
unsigned long long timeEnd = 0;

void OnWinPaint(HDC hdc, unsigned long long timeNow, unsigned long long lastTime, int width, int height)
{
    HDC mdc = CreateCompatibleDC(hdc);
    HBITMAP hbmp;
    hbmp = CreateCompatibleBitmap(hdc, width, height);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(mdc, hbmp);

    BITMAPINFO bitmapInfo;
    ZeroMemory(&bitmapInfo, sizeof(BITMAPINFO));
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = width;
    bitmapInfo.bmiHeader.biHeight = height;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;


    float timeInterval = timeNow - lastTime;
    objCube.m_transform.m_rotation.x += timeInterval / 20.0f;
    objCube.m_transform.m_rotation.y += timeInterval / 9.0f;


    //objmt.m_translation.m_rotation.x += timeInterval / 6.0f;
    //objmt.m_translation.m_rotation.y += timeInterval / 10.0f;


    //objPlane.m_translation.m_rotation.x += timeInterval / 6.0f;
    //objPlane.m_translation.m_rotation.y += timeInterval / 25.0f;


    //objCylinder.m_translation.m_rotation.x += timeInterval / 5.0f;
    //objCylinder.m_translation.m_rotation.y += timeInterval / 10.0f;


    //objCat.m_translation.m_rotation.y += timeInterval / 10.0f;


    objRock.m_transform.m_rotation.x += timeInterval / 15.0f;
    objRock.m_transform.m_rotation.y += timeInterval / 10.0f;


    objTorus.m_transform.m_rotation.y += timeInterval / 10.0f;


    objSpot.m_transform.m_rotation.y += timeInterval / 10.0f;

    //SR::Renderer::GetInstance()->GetCamera()->m_transform.m_rotation.z += timeInterval / 20.0f;
    SR::Renderer::GetInstance()->GetCamera()->ClearColor();
    SR::Renderer::GetInstance()->GetCamera()->ClearZBuffer();
    //LightFragmentShader->SetTexture(&texture1);
    //UnlitFragmentShader->SetTexture(&texture1);
    //UnlitFragmentShader->SetTexture(&rock_Texture);
    //UnlitFragmentShader->SetTexture(&GIS_Texture);
    // Unlit 
    {
        //SR::Renderer::GetInstance()->OnRender(objmt, *LightVertexShader, *LightFragmentShader);
        //SR::Renderer::GetInstance()->OnRender(objCube, *UnlitVertexShader, *UnlitFragmentShader);
        //SR::Renderer::GetInstance()->OnRender(objCylinder, *UnlitVertexShader, *UnlitFragmentShader);
        //SR::Renderer::GetInstance()->OnRender(objPlane, *UnlitVertexShader, *UnlitFragmentShader);
        //SR::Renderer::GetInstance()->OnRender(objCat, *UnlitVertexShader, *UnlitFragmentShader);
        //SR::Renderer::GetInstance()->OnRender(objTorus, *UnlitVertexShader, *UnlitFragmentShader);
        //SR::Renderer::GetInstance()->OnRender(objRock, *UnlitVertexShader, *UnlitFragmentShader);
        //SR::Renderer::GetInstance()->OnRender(objSpot, *UnlitVertexShader, *UnlitFragmentShader);
    }
    // Lit
    {
        //SR::Renderer::GetInstance()->OnRender(objCube, *UnlitVertexShader, *UnlitFragmentShader);
        //SR::Renderer::GetInstance()->OnRender(objCube, *LightVertexShader, *LightFragmentShader);
        //SR::Renderer::GetInstance()->OnRender(objCylinder, *LightVertexShader, *LightFragmentShader);
        //SR::Renderer::GetInstance()->OnRender(objPlane, *LightVertexShader, *LightFragmentShader);
        //SR::Renderer::GetInstance()->OnRender(objCat, *LightVertexShader, *LightFragmentShader);
        //SR::Renderer::GetInstance()->OnRender(objTorus, *LightVertexShader, *LightFragmentShader);
        //LightFragmentShader->SetTexture(&rock_Texture);
        //UnlitFragmentShader->SetTexture(&rock_Texture);
        //SR::Renderer::GetInstance()->OnRender(objRock, *LightVertexShader, *LightFragmentShader);

        LightFragmentShader->SetTexture(&spot_Texture);
        //UnlitFragmentShader->SetTexture(&spot_Texture);
        SR::Renderer::GetInstance()->OnRender(objSpot, *LightVertexShader, *LightFragmentShader);
    }
    auto frameBuffer = SR::Renderer::GetInstance()->GetCamera()->GetFrameBuffer();
    const void* backColorData = frameBuffer->GetColorData();

    if (backColorData != nullptr)
    {
        StretchDIBits(mdc,
            0, 0, width, height,
            0, height, width, -height,
            backColorData,
            &bitmapInfo,
            DIB_RGB_COLORS,
            SRCCOPY);
    }

    const void* centerColorData = frameBuffer->GetCenterColorData();
    BITMAPINFO bitmapInfo2;
    ZeroMemory(&bitmapInfo2, sizeof(BITMAPINFO));
    bitmapInfo2.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo2.bmiHeader.biWidth = frameBuffer->GetCenterWidth();
    bitmapInfo2.bmiHeader.biHeight = frameBuffer->GetCenterHeight();
    bitmapInfo2.bmiHeader.biPlanes = 1;
    bitmapInfo2.bmiHeader.biBitCount = 32;
    bitmapInfo2.bmiHeader.biCompression = BI_RGB;

    if (centerColorData != nullptr)
    {
        StretchDIBits(mdc,
            0, 0, bitmapInfo2.bmiHeader.biWidth, height,
            0, 0, bitmapInfo2.bmiHeader.biWidth, height,
            centerColorData,
            &bitmapInfo2,
            DIB_RGB_COLORS,
            SRCCOPY);
    }


    // display FPS
    {
        if (count_FPS++ == 6)
        {
            timeEnd = GetTickCount64();
            FPS = 1000.0 / ((timeEnd - timeBegin) / 7.0);
            count_FPS = 0;
            timeBegin = GetTickCount64();
        }

        std::stringstream s;
        s << "FPS: " << FPS;
        RECT rect1 = { 0, 0, 100, 100 };
        DrawTextA(mdc, s.str().c_str(), s.str().size(), &rect1, DT_VCENTER);
    }


    BitBlt(hdc, 0, 0, width, height, mdc, 0, 0, SRCCOPY);
    SelectObject(mdc, oldBitmap);
    DeleteDC(mdc);
    DeleteObject(hbmp);
    DeleteObject(oldBitmap);
}

void OnWindowSize(int width, int height)
{
    SR::Renderer::GetInstance()->GetCamera()->aspect = (float)width / height;
    SR::Renderer::GetInstance()->ReSize(width, height);
}

void OnTimer(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, const RECT& rect)
{
	InvalidateRect(hWnd, &rect, FALSE);
	UpdateWindow(hWnd);
}