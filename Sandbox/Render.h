#pragma once
#include "SR.h"
#include "windows.h"


SR::RenderObject objCube;
SR::VertexShader vShader;

void OnInit(HWND hWnd, LONG width, LONG height)
{
	// TODO: load model、texture，init renderer,
    SR::Renderer* render = SR::Renderer::Create();
    render->Init(width, height);


    SR::Model_Obj modelCube = SR::LoadObjFromFile(".\\assets\\mt.obj");
    objCube.m_ib = modelCube.ib;
    objCube.m_vb = modelCube.vb;
    objCube.m_name = modelCube.name;

    for (unsigned int i = 0; i < objCube.m_ib->GetCount(); i++)
    {
        unsigned int index = objCube.m_ib->GetIndex(i);
        const float* pObjPosition = (const float*)objCube.m_vb->GetVertexData(index, 0);
        SR::Vector4f ObjPosition = { pObjPosition[0], pObjPosition[1], pObjPosition[2], 1.0f };
    }

    SR::Translation cubeTranslation;
    cubeTranslation.m_position = { 0, 0, 3 };
    cubeTranslation.m_rotation = { 45, 25, 15 };
    cubeTranslation.m_scaling = { .01, .01, .01 };

    objCube.m_translation = cubeTranslation;

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


    float timeIntetval = timeNow - lastTime;
    objCube.m_translation.m_rotation.x += timeIntetval / 20.0f;
    objCube.m_translation.m_rotation.y += timeIntetval / 9.0f;

    SR::Matrix4x4f model_Mat = SR::Matrix4x4f::Translation(objCube.m_translation.m_position) *
        SR::Matrix4x4f::Rotation(objCube.m_translation.m_rotation.z, SR::Axis::Axis_Z) *
        SR::Matrix4x4f::Rotation(objCube.m_translation.m_rotation.y, SR::Axis::Axis_Y) *
        SR::Matrix4x4f::Rotation(objCube.m_translation.m_rotation.x, SR::Axis::Axis_X) *
        SR::Matrix4x4f::Scale(objCube.m_translation.m_scaling);
    SR::Matrix4x4f view_Mat = SR::Matrix4x4f::Indentity();
    SR::Matrix4x4f proj_Mat = SR::GetProjMatrix(1.0, 60);
    vShader.SetMVP(model_Mat, view_Mat, proj_Mat);

    auto frameBuffer = SR::Renderer::GetInstance()->OnRender(objCube, vShader);
    const void* colorData = frameBuffer->GetColorData();

    if (colorData != nullptr)
    {
        StretchDIBits(mdc,
            0, 0, width, height,
            0, height, width, -height,
            colorData,
            &bitmapInfo,
            DIB_RGB_COLORS,
            SRCCOPY);
    }


    BitBlt(hdc, 0, 0, width, height, mdc, 0, 0, SRCCOPY);
    SelectObject(mdc, oldBitmap);
    DeleteDC(mdc);
    DeleteObject(hbmp);
    DeleteObject(oldBitmap);
}

void OnWindowSize(int width, int height)
{
    SR::Renderer::GetInstance()->ReSize(width, height);
}

void OnTimer(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, const RECT& rect)
{
	InvalidateRect(hWnd, &rect, FALSE);
	UpdateWindow(hWnd);
}