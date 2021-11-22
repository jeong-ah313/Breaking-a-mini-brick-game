#include <Windows.h>
#include <stdio.h>
#include <conio.h>

#define BALL_SIZE 20       // 볼의 크기 상수를 정의
#define BAR_HOR_SIZE  50  // 바의 수평 크기 상수를 정의 
#define BAR_VER_SIZE  10  // 바의 수직 크기 상수를 정의
#define BLOCK_HOR_SIZE 50   // 블록의 수평 크기 상수를 정의
#define BLOCK_VER_SIZE 25   // 블록의 수직 크기 상수를 정의
#define BAR_MOVE_STEP 5  // 바의 수형 이동 크기 상수를 정의
#define MOVE_STEP 5       // 볼의 이동 간격 상수를 정의
#define _B 523.2511
#define _S 987.7666

int main(void)
{
    int bar_x = 250;   // 막대의 시점의 x,y 좌표
    int bar_y = 200;

    int ball_x = 300;   // 볼의 시점의 x,y 좌표 
    int ball_y = 200;

    int block_x = 40;  // 블록의 시점의 x,y 좌표
    int block_y = 70;

    int dx = MOVE_STEP;  // 시작시 x좌표의 이동 값
    int dy = MOVE_STEP;  // 시작시 y좌표의 이동 값

    int i;  //블록을 6개 만들어주기 위해 필요한 변수

    int meet = 0;
    int meet0 = 0; //block과 ball이 만나는 값
    int meet1 = 0;
    int meet2 = 0;
    int meet3 = 0;
    int meet4 = 0;
    int meet5 = 0;

    char c; // 키 입력 저장 변수

    HWND    hwnd = GetForegroundWindow(); // 현재 윈도우의  핸들을 구한다. 
    HDC hdc = GetWindowDC(hwnd);          // 윈도우의 디바이스 컨테스트(Device context)의 핸들을 구하여 윈도우에 접근한다. 

     // 배경을 흰색으로 설정
    SelectObject(hdc, CreatePen(PS_SOLID, 1, RGB(255, 255, 255)));
    SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
    Rectangle(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

    // 그리는 펜의 테두리 색은 파란색, 채우는 색은 흰색으로 설정
    SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(0, 0, 255)));
    SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));

    // 파란색 테두리를 갖는 사각형을 그린다. 바탕색은 흰색
    Rectangle(hdc, 30, 40, 500, 400 + BALL_SIZE + MOVE_STEP);

    TextOut(hdc, 200, 450, L"BAR X control : j,J,k,K", 23); // 화면 아래에 문자열 출력


    // 블록을 그린다.
    for (i = 0; i <= 5; i++)
    {
        // 그리는 펜의 테두리 색은 검정색, 채우는 색은 고동색으로 설정
        SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(0, 0, 0)));
        SelectObject(hdc, CreateSolidBrush(RGB(103, 0, 0)));
        Rectangle(hdc, block_x + 80 * i, block_y, block_x + BLOCK_HOR_SIZE + 80 * i, block_y + BLOCK_VER_SIZE);
    }

    while (meet < 6)
    {
        // 그리는 펜의 테두리 색은 파란색, 채우는 색은 빨강색으로 설정
        SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(0, 0, 255)));
        SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));

        // 원을 그린다. 
        Ellipse(hdc, ball_x, ball_y, ball_x + BALL_SIZE, ball_y + BALL_SIZE);

        // 바를 그린다. 
        Rectangle(hdc, bar_x, 400, bar_x + BAR_HOR_SIZE, 400 + BAR_VER_SIZE);



        Sleep(30); // 시간 지연

        // 그리는 펜의 색은 흰색, 채우는 색은 흰색
        SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(255, 255, 255)));
        SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));

        // 바탕색(흰색)으로 원을 그려서 원을 지운다. 
        Ellipse(hdc, ball_x, ball_y, ball_x + BALL_SIZE, ball_y + BALL_SIZE);

        // 바를 지운다. 
        Rectangle(hdc, bar_x, 400, bar_x + BAR_HOR_SIZE, 400 + BAR_VER_SIZE);



        // 이동하는 위치의 x,y 좌표 값으로 변경하기 위해 좌표 값을 dx,dy만큼 이동

        if (_kbhit())  // 키가 눌러졌는지 검사
        {

            c = _getch();   // 키가 눌러진 경우 입력 문자 값을 얻는다.     
            if (c == 'j' || c == 'J') bar_x = bar_x - BAR_MOVE_STEP; // j, J가 입력된 경우 x좌표 값은 dx만큼 감소
            if (c == 'k' || c == 'K') bar_x = bar_x + BAR_MOVE_STEP; // k, K가 입력된 경우 x좌표 값은 dx만큼 증가
        } //if

        // 충돌 검사, 볼의 x좌표가 바의 x좌표와 크기 범위 안에 위치하는가
        // 볼의 y 좌표가 볼의 크기를 고려한 바의 y좌표와 바의 수직 두께 좌표 범위 안에 있는가
        if (bar_x <= ball_x && ball_x <= (bar_x + BAR_HOR_SIZE))
            if ((400 - BALL_SIZE) <= ball_y && ball_y <= (400 + BAR_VER_SIZE))
            {
                dy = -MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
            }


        ball_x = ball_x + dx;
        ball_y = ball_y + dy;

        // 바의 좌측, 우측 경계 값 검사 및 설정
        if (bar_x >= (500 - (BAR_HOR_SIZE + MOVE_STEP)))
        {
            // x 좌표 값의 우측 경계를 만난 경우 x 좌표 값 제한
            bar_x = 500 - (BAR_HOR_SIZE + MOVE_STEP);

            // 부딪히면 소리 발생
            Beep(_B, 20);
            Beep(_S, 20);
        }
        if (bar_x <= 30 + MOVE_STEP)
        {
            // x 좌표 값의 좌측 경계를 만난 경우 x 좌표 값 제한
            bar_x = 30 + MOVE_STEP;

            // 부딪히면 소리 발생
            Beep(_B, 20);
            Beep(_S, 20);
        }


        // 볼의 좌측, 우측 경계 값 검사 및 설정
        if (ball_x >= (500 - (BALL_SIZE + MOVE_STEP)))
        {
            // x 좌표 값의 우측 경계를 만난 경우 x 좌표 값 제한
            dx = -MOVE_STEP;

            // 부딪히면 소리 발생
            Beep(_B, 20);
            Beep(_S, 20);
        }

        if (ball_x <= 30 + MOVE_STEP)
        {   // x 좌표 값의 좌측 경계를 만난 경우 x 좌표 값 제한
            dx = +MOVE_STEP;

            // 부딪히면 소리 발생
            Beep(_B, 20);
            Beep(_S, 20);
        }

        if (ball_y >= 400)            // 볼이 바닥에 닿은 경우, 볼의 시작 위치 x,y 좌표를 를 초기화
        {
            ball_y = 200;
            ball_x = 300;

            // 부딪히면 소리 발생
            Beep(_B, 20);
            Beep(_S, 20);
        }

        if (ball_y <= (40 + MOVE_STEP))
        {
            // y 좌표 값이 위측 경계를 만난 경우 y좌표 값 제한
            dy = +MOVE_STEP;

            // 부딪히면 소리 발생
            Beep(_B, 20);
            Beep(_S, 20);
        }


        /////////////////////////////////////////////////////////
        // ball이 block과 만나는 경우
        // ball이 block과 만나는 경우1
        if ((((ball_y <= block_y + BLOCK_VER_SIZE) && (ball_y >= block_y)) && ((ball_x >= block_x + 80 * 0) && (ball_x <= (block_x + BLOCK_HOR_SIZE + 80 * 0)))))
        {

            if (meet0 == 0)
            {
                dx = +MOVE_STEP;
                dy = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
                meet0++;
                meet++;
            }
        } //if

        if (meet0 > 0)
        {
            if (ball_x <= 30 + MOVE_STEP)
            {   // x 좌표 값의 좌측 경계를 만난 경우 x 좌표 값 제한
                dx = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
            }
            if (ball_y <= (40 + MOVE_STEP))
            {
                // y 좌표 값이 위측 경계를 만난 경우 y좌표 값 제한
                dy = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
            }
        }

        // ball이 block과 만나는 경우2
        if ((((ball_y <= block_y + BLOCK_VER_SIZE) && (ball_y >= block_y)) && ((ball_x >= block_x + 80 * 1) && (ball_x <= (block_x + BLOCK_HOR_SIZE + 80 * 1)))))
        {
            if (meet1 == 0)
            {
                dx = +MOVE_STEP;
                dy = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
                meet1++;
                meet++;
            }

        } //if
        if (meet1 > 0)
        {
            if (ball_x <= 30 + MOVE_STEP)
            {   // x 좌표 값의 좌측 경계를 만난 경우 x 좌표 값 제한
                dx = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
            }
            if (ball_y <= (40 + MOVE_STEP))
            {
                // y 좌표 값이 위측 경계를 만난 경우 y좌표 값 제한
                dy = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
            }
        }

        // ball이 block과 만나는 경우3
        if ((((ball_y <= block_y + BLOCK_VER_SIZE) && (ball_y >= block_y)) && ((ball_x >= block_x + 80 * 2) && (ball_x <= (block_x + BLOCK_HOR_SIZE + 80 * 2)))))
        {
            if (meet2 == 0)
            {
                dx = +MOVE_STEP;
                dy = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
                meet2++;
                meet++;
            }
        } //if

        if (meet2 > 0)
        {
            if (ball_x <= 30 + MOVE_STEP)
            {   // x 좌표 값의 좌측 경계를 만난 경우 x 좌표 값 제한
                dx = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
            }
            if (ball_y <= (40 + MOVE_STEP))
            {
                // y 좌표 값이 위측 경계를 만난 경우 y좌표 값 제한
                dy = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
            }
        }

        // ball이 block과 만나는 경우4
        if ((((ball_y <= block_y + BLOCK_VER_SIZE) && (ball_y >= block_y)) && ((ball_x >= block_x + 80 * 3) && (ball_x <= (block_x + BLOCK_HOR_SIZE + 80 * 3)))))
        {
            if (meet3 == 0)
            {
                dx = +MOVE_STEP;
                dy = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
                meet3++;
                meet++;
            }
        } //if

        if (meet3 > 0)
        {
            if (ball_x <= 30 + MOVE_STEP)
            {   // x 좌표 값의 좌측 경계를 만난 경우 x 좌표 값 제한
                dx = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
            }
            if (ball_y <= (40 + MOVE_STEP))
            {
                // y 좌표 값이 위측 경계를 만난 경우 y좌표 값 제한
                dy = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
            }
        }

        // ball이 block과 만나는 경우5
        if ((((ball_y <= block_y + BLOCK_VER_SIZE) && (ball_y >= block_y)) && ((ball_x >= block_x + 80 * 4) && (ball_x <= (block_x + BLOCK_HOR_SIZE + 80 * 4)))))
        {
            if (meet4 == 0)
            {
                dx = +MOVE_STEP;
                dy = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
                meet4++;
                meet++;
            }
        } //if

        if (meet4 > 0)
        {
            if (ball_x <= 30 + MOVE_STEP)
            {   // x 좌표 값의 좌측 경계를 만난 경우 x 좌표 값 제한
                dx = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
            }
            if (ball_y <= (40 + MOVE_STEP))
            {
                // y 좌표 값이 위측 경계를 만난 경우 y좌표 값 제한
                dy = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
            }
        }

        // ball이 block과 만나는 경우6
        if ((((ball_y <= block_y + BLOCK_VER_SIZE) && (ball_y >= block_y)) && ((ball_x >= block_x + 80 * 5) && (ball_x <= (block_x + BLOCK_HOR_SIZE + 80 * 5)))))
        {
            if (meet5 == 0)
            {
                dx = +MOVE_STEP;
                dy = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
                meet5++;
                meet++;
            }
        } //if

        if (meet5 > 0)
        {
            if (ball_x <= 30 + MOVE_STEP)
            {   // x 좌표 값의 좌측 경계를 만난 경우 x 좌표 값 제한
                dx = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
            }
            if (ball_y <= (40 + MOVE_STEP))
            {
                // y 좌표 값이 위측 경계를 만난 경우 y좌표 값 제한
                dy = +MOVE_STEP;

                // 부딪히면 소리 발생
                Beep(_B, 20);
                Beep(_S, 20);
            }
        }


        ////////////////////////////////////////////////////
        //블록에 공이 닿으면 블록을 지워줌
        if ((ball_y <= block_y + BLOCK_VER_SIZE) && (ball_y >= block_y) && (ball_x >= block_x + 80 * 0) && (ball_x <= (block_x + BLOCK_HOR_SIZE + 80 * 0)))
        {
            //흰색으로 BLOCK을 지워줌(첫번째 블록)
            SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(255, 255, 255)));
            SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
            Rectangle(hdc, block_x + 80 * 0, block_y, block_x + BLOCK_HOR_SIZE + 80 * 0, block_y + BLOCK_VER_SIZE);
        }

        if ((ball_y <= block_y + BLOCK_VER_SIZE) && (ball_y >= block_y) && (ball_x >= block_x + 80 * 1) && (ball_x <= (block_x + BLOCK_HOR_SIZE + 80 * 1)))
        {
            //흰색으로 BLOCK을 지워줌(두번째 블록)
            SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(255, 255, 255)));
            SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
            Rectangle(hdc, block_x + 80 * 1, block_y, block_x + BLOCK_HOR_SIZE + 80 * 1, block_y + BLOCK_VER_SIZE);
        }

        if ((ball_y <= block_y + BLOCK_VER_SIZE) && (ball_y >= block_y) && (ball_x >= block_x + 80 * 2) && (ball_x <= (block_x + BLOCK_HOR_SIZE + 80 * 2)))
        {
            //흰색으로 BLOCK을 지워줌(세번째 블록)
            SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(255, 255, 255)));
            SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
            Rectangle(hdc, block_x + 80 * 2, block_y, block_x + BLOCK_HOR_SIZE + 80 * 2, block_y + BLOCK_VER_SIZE);
        }

        if ((ball_y <= block_y + BLOCK_VER_SIZE) && (ball_y >= block_y) && (ball_x >= block_x + 80 * 3) && (ball_x <= (block_x + BLOCK_HOR_SIZE + 80 * 3)))
        {
            //흰색으로 BLOCK을 지워줌(네번째 블록)
            SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(255, 255, 255)));
            SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
            Rectangle(hdc, block_x + 80 * 3, block_y, block_x + BLOCK_HOR_SIZE + 80 * 3, block_y + BLOCK_VER_SIZE);
        }

        if ((ball_y <= block_y + BLOCK_VER_SIZE) && (ball_y >= block_y) && (ball_x >= block_x + 80 * 4) && (ball_x <= (block_x + BLOCK_HOR_SIZE + 80 * 4)))
        {
            //흰색으로 BLOCK을 지워줌(다섯번째 블록)
            SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(255, 255, 255)));
            SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
            Rectangle(hdc, block_x + 80 * 4, block_y, block_x + BLOCK_HOR_SIZE + 80 * 4, block_y + BLOCK_VER_SIZE);
        }

        if ((ball_y <= block_y + BLOCK_VER_SIZE) && (ball_y >= block_y) && (ball_x >= block_x + 80 * 5) && (ball_x <= (block_x + BLOCK_HOR_SIZE + 80 * 5)))
        {
            //흰색으로 BLOCK을 지워줌(여섯번째 블록)
            SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(255, 255, 255)));
            SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
            Rectangle(hdc, block_x + 80 * 5, block_y, block_x + BLOCK_HOR_SIZE + 80 * 5, block_y + BLOCK_VER_SIZE);
        }
    } //while
    return 0;
} //main