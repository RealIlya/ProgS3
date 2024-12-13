#pragma once

#include <windows.h>
#include <string>

// ���������
const double PI = 3.14159265358979323846;

// ���������� ����������
int squareSide;        // ������� ��������
int ellipseWidth;      // ������ �������
int ellipseHeight;     // ������ �������
float scaleFactor;     // ���������������
float rotationAngle;   // ���� �������� � ��������
int currentFigure;     // ������� ������ (0 - �������, 1 - ������)

// �������
bool LoadParametersFromFile(const std::wstring& filename); // �������� ���������� �� �����
void DrawFigures(HDC hdc, RECT rect);                      // ��������� �����
void SaveToEMF(HWND hwnd);                                  // ���������� � EMF-����
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); // ��������� ��������� ���������
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow); // ������� ������� ����������
