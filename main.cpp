#include <iostream>
#include <easyx.h>
#include <vector>
#include <random>
#include <time.h>
#include <string>
#include <conio.h>

void DrawBackground() {
    setlinecolor(RGB(187, 173, 160));
    rectangle(50, 150, 450, 550);
    for (int i = 1; i <= 3; i++) {
        line(50, 150 + 100 * i, 450, 150 + 100 * i); // 画横线
        line(50 + 100 * i, 150, 50 + 100 * i, 550); // 画竖线
    }
    settextcolor(BLUE);
    setbkmode(TRANSPARENT);
    settextstyle(100, 50, _T("宋体"));
    outtextxy(150, 30, _T("2048"));
}

std::wstring IntToWString(int x) {
    return std::to_wstring(x);
}

void DrawNumbers(int nums[4][4]) {
    settextcolor(BLACK);
    for (int x = 0;x < 4;x++) {
        for (int y = 0;y < 4;y++) {
            if (nums[x][y] != 0) {
                std::wstring numStr = IntToWString(nums[x][y]);
                if (nums[x][y] < 10) {
                    if (nums[x][y] == 2) {
                        setfillcolor(RGB(238, 228, 218));
                    }
                    else if (nums[x][y] == 4) {
                        setfillcolor(RGB(237, 224, 200));
                    }
                    else {
                        setfillcolor(RGB(242, 177, 121));
                    }
                    solidrectangle(50 + 100 * x, 150 + 100 * y, 150 + 100 * x, 250 + 100 * y);
                    settextstyle(75, 0, _T("宋体"));
                    outtextxy(82 + x * 100, 162 + 100 * y, numStr.c_str());
                }
                else if (nums[x][y] < 100) {
                    if (nums[x][y] == 16) {
                        setfillcolor(RGB(244, 150, 99));
                    }
                    else if (nums[x][y] == 32) {
                        setfillcolor(RGB(246, 124, 95));
                    }
                    else {
                        setfillcolor(RGB(246, 94, 59));
                    }
                    solidrectangle(50 + 100 * x, 150 + 100 * y, 150 + 100 * x, 250 + 100 * y);
                    settextstyle(60, 0, _T("宋体"));
                    outtextxy(70 + x * 100, 168 + 100 * y, numStr.c_str());
                }
                else if (nums[x][y] < 1000) {
                    setfillcolor(RGB(237, 204, 97));
                    solidrectangle(50 + 100 * x, 150 + 100 * y, 150 + 100 * x, 250 + 100 * y);
                    settextstyle(55, 0, _T("宋体"));
                    outtextxy(57 + x * 100, 173 + 100 * y, numStr.c_str());
                }
                else {
                    setfillcolor(RGB(237, 204, 97));
                    solidrectangle(50 + 100 * x, 150 + 100 * y, 150 + 100 * x, 250 + 100 * y);
                    settextstyle(40, 0, _T("宋体"));
                    outtextxy(60 + x * 100, 178 + 100 * y, numStr.c_str());
                }
            }
            setlinestyle(0, 15);
            setlinecolor(RGB(187, 173, 160));
            rectangle(50 + 100 * x, 150 + 100 * y, 150 + 100 * x, 250 + 100 * y);
        }
    }
}
void DrawScore(int score,int highscore) {
    settextcolor(RED);
    settextstyle(40, 0, _T("宋体"));
    std::wstring numStr = IntToWString(score);
    outtextxy(0, 5, _T("Score:"));
    outtextxy(120, 5, numStr.c_str());
    std::wstring numStr2 = IntToWString(highscore);
    outtextxy(320, 5, _T("Best:"));
    outtextxy(420, 5, numStr2.c_str());
}

enum class Direction {
    up, down, left, right
};

void Merge(int nums[4][4], int dir, int& score) {
    // 合并逻辑
    int flag_0 = 0;
    switch (dir) {
    case 0:
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int k = j + 1;
                while (k < 4) {
                    if (nums[i][k] != 0) {
                        break;
                    }
                    k++;
                }
                if (k <= 3) {
                    if (nums[i][j] == nums[i][k]) {
                        nums[i][j] += nums[i][k];
                        nums[i][k] = 0;
                        score += nums[i][j];
                    }
                }
            }
        }
        break;
    case 1:
        for (int i = 0; i < 4; i++) {
            for (int j = 3; j >= 0; j--) {
                int k = j - 1;
                while (k >= 0) {
                    if (nums[i][k] != 0) {
                        break;
                    }
                    k--;
                }
                if (k >= 0) {
                    if (nums[i][j] == nums[i][k]) {
                        nums[i][j] += nums[i][k];
                        nums[i][k] = 0;
                        score += nums[i][j];
                    }
                }
            }
        }
        break;
    case 2:
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                int k = i + 1;
                while (k < 4) {
                    if (nums[k][j] != 0) {
                        break;
                    }
                    k++;
                }
                if (k <= 3) {
                    if (nums[i][j] == nums[k][j]) {
                        nums[i][j] += nums[k][j];
                        nums[k][j] = 0;
                        score += nums[i][j];
                    }
                }
            }
        }
        break;
    case 3:
        for (int j = 0; j < 4; j++) {
            for (int i = 3; i >= 0; i--) {
                int k = i - 1;
                while (k >= 0) {
                    if (nums[k][j] != 0) {
                        break;
                    }
                    k--;
                }
                if (k >= 0) {
                    if (nums[i][j] == nums[k][j]) {
                        nums[i][j] += nums[k][j];
                        nums[k][j] = 0;
                        score += nums[i][j];
                    }
                }
            }
        }
        break;
    }
}

void Slide(int nums[4][4], int dir) {
    switch (dir) {
    case 0://上
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int k = j - 1;
                while (k >= 0) {
                    if (nums[i][k] != 0) {
                        break;
                    }
                    k--;
                }
                if (k != (j - 1)) {
                    nums[i][k + 1] = nums[i][j];
                    nums[i][j] = 0;
                }
            }
        }
        break;
    case 1://下
        for (int i = 0; i < 4; i++) {
            for (int j = 3; j >= 0; j--) {
                int k = j + 1;
                while (k < 4) {
                    if (nums[i][k] != 0) {
                        break;
                    }
                    k++;
                }
                if (k != (j + 1)) {
                    nums[i][k - 1] = nums[i][j];
                    nums[i][j] = 0;
                }
            }
        }
        break;
    case 2://左
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                int k = i - 1;
                while (k >= 0) {
                    if (nums[k][j] != 0) {
                        break;
                    }
                    k--;
                }
                if (k != (i - 1)) {
                    nums[k + 1][j] = nums[i][j];
                    nums[i][j] = 0;
                }
            }
        }
        break;
    case 3://右
        for (int j = 0; j < 4; j++) {
            for (int i = 3; i >= 0; i--) {
                int k = i + 1;
                while (k < 4) {
                    if (nums[k][j] != 0) {
                        break;
                    }
                    k++;
                }
                if (k != (i + 1)) {
                    nums[k - 1][j] = nums[i][j];
                    nums[i][j] = 0;
                }
            }
        }
        break;
    }
}

void ChangeState(Direction dir, int nums[4][4], int& score) {
    switch (dir) {
    case Direction::up:
        Merge(nums, 0, score);
        Slide(nums, 0);
        break;
    case Direction::down:
        Merge(nums, 1, score);
        Slide(nums, 1);
        break;
    case Direction::left:
        Merge(nums, 2, score);
        Slide(nums, 2);
        break;
    case Direction::right:
        Merge(nums, 3, score);
        Slide(nums, 3);
        break;
    }
}

bool isFull(int nums[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (nums[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool isEnd(int nums[4][4]) {
    if (!isFull(nums)) {
        return false;
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (nums[i][j] == nums[i][j + 1]) return false;
        }
    }
    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 3; ++i) {
            if (nums[i][j] == nums[i + 1][j]) return false;
        }
    }
    return true;
}
void DrawEnd(int score, int highscore) {
    cleardevice();
    setbkcolor(RGB(205, 193, 180));  // 背景颜色
    cleardevice();

    // 标题 "游戏结束"
    settextstyle(40, 0, _T("宋体"));
    settextcolor(RGB(255, 87, 34));  // 鲜艳的红色
    outtextxy(160, 100, _T("游戏结束"));

    // 本次得分
    settextstyle(30, 0, _T("宋体"));
    settextcolor(RGB(33, 150, 243));  // 蓝色
    std::wstring scoreStr = IntToWString(score);
    outtextxy(130, 200, _T("本次得分:"));
    outtextxy(280, 200, scoreStr.c_str());

    // 历史最高得分
    settextstyle(30, 0, _T("宋体"));
    settextcolor(RGB(76, 175, 80));  // 绿色
    std::wstring highscoreStr = IntToWString(highscore);
    outtextxy(130, 250, _T("历史最高得分:"));
    outtextxy(320, 250, highscoreStr.c_str());

    // 提示按键
    settextstyle(25, 0, _T("宋体"));
    settextcolor(RGB(255, 87, 34));  // 使用对比色进行提示
    outtextxy(130, 320, _T("按ENTER重新开始"));
    outtextxy(130, 370, _T("按Esc退出"));

    // 添加简单的框架（可选）
    setlinecolor(RGB(0, 0, 0));  // 黑色边框
    setlinestyle(PS_SOLID, 3);  // 边框样式
    rectangle(100, 180, 400, 460);  // 外部框架
}

int main() {
    int nums[4][4] = {};
    int x, y;
    const int num_2 = 2;
    const int num_4 = 4;
    int score = 0;
    int flag1;
    int highscore = 0;
    Direction dir;
    initgraph(500, 600);
    setbkcolor(RGB(205, 193, 180));
    cleardevice();
    srand((unsigned int)time(NULL));
    DrawBackground();
    DrawNumbers(nums);
    DrawScore(score,highscore);
    while (true) {
        if (!isFull(nums)) {
            x = rand() % 4;
            y = rand() % 4;
            while (nums[x][y] != 0) {
                x = rand() % 4;
                y = rand() % 4;
            }
            flag1 = rand() % 2;
            if (flag1 == 0) {
                nums[x][y] = num_2;
            }
            else {
                nums[x][y] = num_4;
            }
        }
        cleardevice();
        DrawBackground();
        DrawNumbers(nums);
        DrawScore(score,highscore);
        while (true) {
            if (_kbhit()) {
                char ch = _getch();
                if (ch == 72 || ch == 'w' || ch == 'W') {
                    dir = Direction::up;
                    break;
                }
                else if (ch == 80 || ch == 'S' || ch == 's') {
                    dir = Direction::down;
                    break;
                }
                else if (ch == 75 || ch == 'a' || ch == 'A') {
                    dir = Direction::left;
                    break;
                }
                else if (ch == 77 || ch == 'd' || ch == 'D') {
                    dir = Direction::right;
                    break;
                }
                else if (ch == 27) {
                    exit(0);
                }
            }
        }
        cleardevice();
        ChangeState(dir, nums, score);
        DrawBackground();
        DrawNumbers(nums);
        DrawScore(score,highscore);
        if (isEnd(nums)) {
            std::cout << "End Game" << std::endl;
            Sleep(1000);
            if (score >= highscore) {
                highscore = score;
            }
            DrawEnd(score,highscore);
            while (true) {
                if (_kbhit()) {
                    char ch = _getch();
                    if (ch == 13) {
                        cleardevice();
                        for (int i = 0;i < 4;i++) {
                            for (int j = 0;j < 4;j++) {
                                nums[i][j] = 0;
                            }
                        }
                        score = 0;
                        break;
                    }
                    else if (ch == 27) {
                        exit(0);
                    }
                }
            }
        }
        Sleep(50);
    }
    closegraph();
    return 0;
}
