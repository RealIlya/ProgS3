#pragma once

#include <windows.h>
#include <string>

// Константы
const double PI = 3.14159265358979323846;

// Глобальные переменные
int squareSide;        // Сторона квадрата
int ellipseWidth;      // Ширина эллипса
int ellipseHeight;     // Высота эллипса
float scaleFactor;     // Масштабирование
float rotationAngle;   // Угол поворота в градусах
int currentFigure;     // Текущая фигура (0 - квадрат, 1 - эллипс)

// Функции
bool LoadParametersFromFile(const std::wstring& filename); // Загрузка параметров из файла
void DrawFigures(HDC hdc, RECT rect);                      // Рисование фигур
void SaveToEMF(HWND hwnd);                                  // Сохранение в EMF-файл
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); // Процедура обработки сообщений
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow); // Главная функция приложения
