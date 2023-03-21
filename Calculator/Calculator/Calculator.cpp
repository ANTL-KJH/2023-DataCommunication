/*
* Project Name : Calculator
* Program's purpose and basic function :
* - cauculation of expression
* Program First Author : JH KIM
* Date of First Write : 2023.03.21
* ======================================================================================
* Source Code Modification History
*  ======================================================================================
* Author				Date				Ver				Modification details
* JH KIM				2023.03.21			v1.0			First Write
*/
// Calculator.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 유일한 애플리케이션 개체입니다.

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // MFC를 초기화합니다. 초기화하지 못한 경우 오류를 인쇄합니다.
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: 여기에 애플리케이션 동작을 코딩합니다.
            wprintf(L"심각한 오류: MFC 초기화 실패\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: 여기에 애플리케이션 동작을 코딩합니다.
            CString str;                    // CString object
            char buffer[100];               // input buffer
            int operatorPos;
            double Lnum, Rnum, result = 0.0;
            _tsetlocale(LC_ALL, _T(""));    // Korean printout setting
            _tprintf(_T("사칙연산 수식을 입력하시오:\n"));
            cin.getline(buffer, 100);       // input expression from user
            str = buffer;
            str.Replace(_T(" "), NULL);     // replace " " to NULL
            //_tprintf(_T("%s\n"), str);    // printout input string
            operatorPos = str.FindOneOf(_T("+-*/"));    // return Operator Pos
            //_tprintf(_T("%d\n"), operatorPos);        // printout operator position
            Lnum = _wtof(str.Left(operatorPos));        // Left num
            Rnum = _wtof(str.Right(str.GetLength() - (operatorPos + 1)));   // Right num
            //_tprintf(_T("%lf\n"), Lnum);
            //_tprintf(_T("%lf\n"), Rnum);
            
            if (str.FindOneOf(_T("+")) == operatorPos)          // add
                result = Lnum + Rnum;
            else if (str.FindOneOf(_T("-")) == operatorPos)     // subtraction
                result = Lnum - Rnum;
            else if (str.FindOneOf(_T("*")) == operatorPos)     // multiply
                result = Lnum * Rnum;
            else if (str.FindOneOf(_T("/")) == operatorPos)     // division
                result = Lnum / Rnum;
            _tprintf(_T("%lf\n"), result);                      // printout result 
        }
    }
    else
    {
        // TODO: 오류 코드를 필요에 따라 수정합니다.
        wprintf(L"심각한 오류: GetModuleHandle 실패\n");
        nRetCode = 1;
    }

    return nRetCode;
}
