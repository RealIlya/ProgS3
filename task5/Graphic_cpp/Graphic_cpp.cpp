#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <iostream>

//#include "Graphic_cpp.h"

// Константа для числа Пи
const double PI = 3.14159265358979323846;

// Переменные для размеров фигур и трансформаций
int squareSide; // Сторона квадрата
int ellipseWidth; // Ширина эллипса
int ellipseHeight; // Высота эллипса
float scaleFactor = 1.0f; // Масштабирование
float rotationAngle = 0.0f; // Угол поворота в градусах

int currentFigure = 0; // Текущая фигура: 0 - квадрат, 1 - эллипс

// Функция для загрузки параметров из файла
bool LoadParametersFromFile(const std::wstring& filename) {
    std::wifstream file(filename);
    if (!file.is_open()) {
        MessageBox(NULL, L"Failed to open parameters file.", L"Error", MB_OK | MB_ICONERROR);
        return false; // Ошибка открытия файла
    }

    // Чтение размеров фигур из файла
    if (!(file >> squareSide >> ellipseWidth >> ellipseHeight)) {
        MessageBox(NULL, L"Invalid file format.", L"Error", MB_OK | MB_ICONERROR);
        return false; // Ошибка формата файла
    }

    // Проверка корректности данных
    if (squareSide <= 0 || ellipseWidth <= 0 || ellipseHeight <= 0) {
        MessageBox(NULL, L"Invalid figure dimensions.", L"Error", MB_OK | MB_ICONERROR);
        return false; // Ошибка в размерах фигур
    }

    file.close();
    return true; // Успешная загрузка параметров
}

// Функция для рисования фигур
void DrawFigures(HDC hdc, RECT rect) {
    // Центр окна
    int centerX = (rect.right - rect.left) / 2;
    int centerY = (rect.bottom - rect.top) / 2;

    // Применяем масштабирование
    XFORM xForm;
    SetGraphicsMode(hdc, GM_ADVANCED);
    xForm.eM11 = scaleFactor; // Масштаб по X
    xForm.eM22 = scaleFactor; // Масштаб по Y
    xForm.eM12 = 0.0f;
    xForm.eM21 = 0.0f;
    xForm.eDx = (1 - scaleFactor) * centerX; // Смещение по X
    xForm.eDy = (1 - scaleFactor) * centerY; // Смещение по Y
    SetWorldTransform(hdc, &xForm); // Установка трансформации

    // Применяем поворот
    xForm.eM11 = cos(rotationAngle * PI / 180); // Косинус угла
    xForm.eM12 = sin(rotationAngle * PI / 180); // Синус угла
    xForm.eM21 = -sin(rotationAngle * PI / 180); // Обратный синус
    xForm.eM22 = cos(rotationAngle * PI / 180); // Обратный косинус
    xForm.eDx = (1 - cos(rotationAngle * PI / 180)) * centerX + sin(rotationAngle * PI / 180) * centerY; // Смещение по X
    xForm.eDy = (1 - cos(rotationAngle * PI / 180)) * centerY - sin(rotationAngle * PI / 180) * centerX; // Смещение по Y
    ModifyWorldTransform(hdc, &xForm, MWT_RIGHTMULTIPLY); // Применение поворота

    // Рисование фигуры в зависимости от текущего выбора
    if (currentFigure == 0) {
        // Рисуем квадрат
        int squareLeft = centerX - squareSide / 2;
        int squareTop = centerY - squareSide / 2;
        Rectangle(hdc, squareLeft, squareTop, squareLeft + squareSide, squareTop + squareSide);
    }
    else if (currentFigure == 1) {
        // Рисуем эллипс
        int ellipseLeft = centerX - ellipseWidth / 2;
        int ellipseTop = centerY - ellipseHeight / 2;
        Ellipse(hdc, ellipseLeft, ellipseTop, ellipseLeft + ellipseWidth, ellipseTop + ellipseHeight);
    }
}

// Функция для сохранения рисунка в EMF-файл
void SaveToEMF(HWND hwnd) {
    HDC hdc = GetDC(hwnd);
    const wchar_t* fileName = L"output.emf"; // Имя файла для сохранения
    HDC hdcMeta = CreateEnhMetaFile(hdc, fileName, NULL, NULL); // Создаем EMF-файл

    // Получаем размеры клиентской области окна
    RECT rect;
    GetClientRect(hwnd, &rect);
    DrawFigures(hdcMeta, rect); // Рисуем фигуры в контексте EMF

    HENHMETAFILE hMetaFile = CloseEnhMetaFile(hdcMeta); // Закрываем EMF-файл
    DeleteEnhMetaFile(hMetaFile); // Удаляем метафайл
    ReleaseDC(hwnd, hdc); // Освобождаем контекст устройства

    // Выводим сообщение с полным путем к сохраненному файлу
    wchar_t buffer[MAX_PATH];
    GetFullPathName(fileName, MAX_PATH, buffer, NULL); // Получаем полный путь к файлу
    MessageBox(hwnd, buffer, L"Файл сохранен", MB_OK); // Показываем сообщение о сохранении
}

// Процедура обработки сообщений окна
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT: { // Обработка сообщения перерисовки окна
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps); // Начинаем рисование
        RECT rect;
        GetClientRect(hwnd, &rect); // Получаем размеры клиентской области
        // Очищаем фон перед рисованием
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255)); // Создаем кисть для фона
        FillRect(hdc, &rect, hBrush); // Заполняем фон
        DeleteObject(hBrush); // Удаляем кисть
        DrawFigures(hdc, rect); // Рисуем фигуры
        EndPaint(hwnd, &ps); // Завершаем рисование
        break;
    }
    case WM_KEYDOWN: { // Обработка нажатий клавиш
        switch (wParam) {
        case VK_UP:    scaleFactor += 0.1f; break; // Увеличиваем масштаб
        case VK_DOWN:  scaleFactor -= 0.1f; break; // Уменьшаем масштаб
        case VK_LEFT:  rotationAngle -= 5.0f; break; // Поворачиваем влево
        case VK_RIGHT: rotationAngle += 5.0f; break; // Поворачиваем вправо
        case 'S':      SaveToEMF(hwnd); break; // Сохраняем выбранную фигуру
        case 'R':      currentFigure = 0; break; // Устанавливаем текущую фигуру на квадрат
        case 'E':      currentFigure = 1; break; // Устанавливаем текущую фигуру на эллипс
        }
        InvalidateRect(hwnd, NULL, TRUE); // Перерисовываем окно
        break;
    }

    case WM_DESTROY: { // Обработка закрытия окна
        PostQuitMessage(0); // Завершаем приложение
        return 0;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam); // Обработка остальных сообщений
}

// Главная функция приложения
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    // Загружаем параметры из файла
    if (!LoadParametersFromFile(L"parameters.txt"))
        return 1; // Если не удалось загрузить параметры, завершаем приложение

    const wchar_t CLASS_NAME[] = L"Square and Ellipse Class"; // Имя класса окна
    WNDCLASS wc = {}; // Структура для описания класса окна
    wc.lpfnWndProc = WindowProc; // Указываем процедуру обработки сообщений
    wc.hInstance = hInstance; // Указываем экземпляр приложения
    wc.lpszClassName = CLASS_NAME; // Указываем имя класса окна

    RegisterClass(&wc); // Регистрируем класс окна

    // Создаем окно
    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Square and Ellipse", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
    if (hwnd == NULL) return 0; // Если окно не создано, завершаем приложение

    ShowWindow(hwnd, nCmdShow); // Показываем окно

    // Основной цикл обработки сообщений
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg); // Переводим сообщения (например, клавиатурные)
        DispatchMessage(&msg); // Передаем сообщение в процедуру обработки
    }
    return 0; // Завершаем приложение
}
