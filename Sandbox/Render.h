#pragma once
#include "SR.h"

SR::Renderer renderer;
SR::RenderObject objCube;
SR::VertexShader vShader;

void OnInit(HWND hWnd)
{
	// TODO: load model、texture，init renderer,
    SR::Model_Obj modelCube = SR::LoadObjFromFile(".\\assets\\cube.obj");
    objCube.m_ib = modelCube.ib;
    objCube.m_vb = modelCube.vb;
    objCube.m_name = modelCube.name;

    SR::Translation cubeTranslation;
    cubeTranslation.m_position = { 0.5, 0.5, -3.0 };
    cubeTranslation.m_rotation = { 0.0, 0.0, 0.0 };
    cubeTranslation.m_scaling = { 1.0f, 1.0f, 1.0f };

    objCube.m_translation = cubeTranslation;

}


unsigned char* backBuffer = nullptr;

void setPixel(unsigned x, unsigned y, unsigned width, unsigned char r, unsigned char g, unsigned char b, unsigned int a)
{
    backBuffer[(y * width + x) * 4] = b;
    backBuffer[(y * width + x) * 4 + 1] = g;
    backBuffer[(y * width + x) * 4 + 2] = r;
    backBuffer[(y * width + x) * 4 + 3] = a;
}

void OnWinPaint(HDC hdc, unsigned long long timeNow, unsigned long long lastTime, int width, int height)
{
	std::cout << 1000.0 / (timeNow - lastTime) << std::endl;

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
    bitmapInfo.bmiHeader.biSizeImage = width * height * 4;


    for (unsigned int i = 0; i < width; i++)
    {
        for (unsigned int j = 0; j < height; j++)
        {
            setPixel(i, j, width, 128, 100, 200, 0);
        }
    }

    StretchDIBits(mdc,
        0, 0, width, height,
        0, height, width, -height,
        backBuffer,
        &bitmapInfo,
        DIB_RGB_COLORS,
        SRCCOPY);
    vShader.model_Mat = SR::Matrix4x4f::Translation(objCube.m_translation.m_position);
    vShader.view_Mat = SR::Matrix4x4f::Indentity();
    vShader.proj_Mat = SR::GetProjMatrix(1.0, 60);
    std::vector<SR::Vertex> vertexes = renderer.OnRender(objCube, vShader);

    for (auto& vertex : vertexes)
    {
        float x = (vertex.position.x + 1.0) / 2 * height;
        float y = (vertex.position.y + 1.0) / 2 * height;
        std::cout << "(" << x << "," << y << ")" << " ";
        std::cout << vertex.position.ToString() << std::endl;
        Rectangle(mdc, x - 5, y - 5, x + 5, y + 5);
    }
    //std::cout << std::endl;

    //Rectangle(mdc, 100, 100, 200, 200);
    //Rectangle(mdc, 300, 300, 200, 200);

    SR::Vector4f vec4(5, 6, 7, 8);
    float vec4Len = vec4.Magnitude();
    std::ostringstream text;
    text << vec4.ToString();
    std::string textStr = text.str();
    RECT textRect{ 10, 10, 100, 100 };
    //DrawTextA(mdc, textStr.c_str(), textStr.size(), &textRect, DT_CENTER);

    BitBlt(hdc, 0, 0, width, height, mdc, 0, 0, SRCCOPY);
    SelectObject(mdc, oldBitmap);
    DeleteDC(mdc);
    DeleteObject(mdc);

    
}

void OnWindowSize()
{
	// TODO: update paint rect
}

void OnTimer(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	InvalidateRect(hWnd, &rect, FALSE);
	UpdateWindow(hWnd);
}