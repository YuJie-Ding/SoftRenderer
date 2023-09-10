#pragma once

void OnInit(HWND hWnd)
{
	// TODO: load model¡¢texture£¬init renderer,
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

    Rectangle(mdc, 100, 100, 200, 200);
    Rectangle(mdc, 300, 300, 200, 200);

    SR::Vector4f vec4(5, 6, 7, 8);
    float vec4Len = vec4.Magnitude();
    std::ostringstream text;
    text << vec4.ToString();
    std::string textStr = text.str();
    RECT textRect{ 10, 10, 100, 100 };
    DrawTextA(mdc, textStr.c_str(), textStr.size(), &textRect, DT_CENTER);

    BitBlt(hdc, 0, 0, width, height, mdc, 0, 0, SRCCOPY);
    SelectObject(mdc, oldBitmap);
    DeleteDC(mdc);
    DeleteObject(mdc);


	//TODO: set shader uniform and draw call
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