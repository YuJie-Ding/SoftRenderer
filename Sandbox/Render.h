#pragma once
#include "SR.h"
#include "windows.h"
#include <sstream>

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

SR::RenderObject objmt;
SR::RenderObject objCube;
SR::RenderObject objPlane;
SR::VertexShader vShader;
SR::FragmentShader fShader;

SR::Texture texture1;

void OnInit(HWND hWnd, LONG width, LONG height)
{
	// TODO: load model、texture，init renderer,
    SR::Renderer* render = SR::Renderer::Create();
    std::shared_ptr<SR::Camera> mainCamera(new SR::Camera());
    mainCamera->aspect = (float)width / height;
    render->SetCamera(mainCamera);
    render->Init(width, height);
    BITMAPINFO* bmpinfo;
    BYTE* data;

    loadBmp(".\\assets\\chess.bmp", bmpinfo, data);
    texture1.BufferData(data, bmpinfo->bmiHeader.biWidth, bmpinfo->bmiHeader.biHeight, bmpinfo->bmiHeader.biBitCount / 8);
    fShader.SetTexture(&texture1);
    {
        SR::Model_Obj modelCube = SR::LoadObjFromFile(".\\assets\\cube.obj");
        objCube.m_ib = modelCube.ib;
        objCube.m_vb = modelCube.vb;
        objCube.m_name = modelCube.name;

        SR::Translation cubeTranslation;
        cubeTranslation.m_position = { 0, 2, 7 };
        cubeTranslation.m_rotation = { 0, 0, 0 };
        cubeTranslation.m_scaling = { 1, 1, 1 };

        objCube.m_translation = cubeTranslation;
    }

    {
        SR::Model_Obj modelMt = SR::LoadObjFromFile(".\\assets\\mt2.obj");
        objmt.m_ib = modelMt.ib;
        objmt.m_vb = modelMt.vb;
        objmt.m_name = modelMt.name;

        SR::Translation mtTranslation;
        mtTranslation.m_position = { 0, 0, 3 };
        mtTranslation.m_rotation = { 0, 0, 0 };
        mtTranslation.m_scaling = { 1, 1, 1 };

        objmt.m_translation = mtTranslation;
    }

    {
        SR::Model_Obj modelMt = SR::LoadObjFromFile(".\\assets\\plane.obj");
        objPlane.m_ib = modelMt.ib;
        objPlane.m_vb = modelMt.vb;
        objPlane.m_name = modelMt.name;

        SR::Translation mtTranslation;
        mtTranslation.m_position = { 0, -1, 5 };
        mtTranslation.m_rotation = { 0, 0, 0 };
        mtTranslation.m_scaling = { 1, 1, 1 };

        objPlane.m_translation = mtTranslation;
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
    objCube.m_translation.m_rotation.x += timeInterval / 20.0f;
    objCube.m_translation.m_rotation.y += timeInterval / 9.0f;


    objmt.m_translation.m_rotation.x += timeInterval / 6.0f;
    objmt.m_translation.m_rotation.y += timeInterval / 25.0f;


    objPlane.m_translation.m_rotation.x += timeInterval / 6.0f;
    objPlane.m_translation.m_rotation.y += timeInterval / 25.0f;

    SR::Renderer::GetInstance()->GetCamera()->m_translation.m_rotation.z += timeInterval / 20.0f;
    SR::Renderer::GetInstance()->GetCamera()->ClearColor();
    SR::Renderer::GetInstance()->GetCamera()->ClearZBuffer();

    SR::Renderer::GetInstance()->OnRender(objmt, vShader, fShader);
    //SR::Renderer::GetInstance()->OnRender(objCube, vShader, fShader);
    //SR::Renderer::GetInstance()->OnRender(objPlane, vShader, fShader);

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