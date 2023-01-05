#pragma once
#define NONE         "\033[m"
#define RED          "\033[0;32;31m"
#define LIGHT_RED    "\033[1;31m"
#define GREEN        "\033[0;32;32m"
#define LIGHT_GREEN  "\033[1;32m"
#define BLUE         "\033[0;32;34m"
#define LIGHT_BLUE   "\033[1;34m"
#define DARY_GRAY    "\033[1;30m"
#define CYAN         "\033[0;36m"
#define LIGHT_CYAN   "\033[1;36m"
#define PURPLE       "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN        "\033[0;33m"
#define YELLOW       "\033[1;33m"
#define LIGHT_GRAY   "\033[0;37m"
#define WHITE        "\033[1;37m"

#define DELAY  8
#define NUM_BLOCK 100
#define BASE_ATK_RANGE  3
#define COL_MAX 30                  //֧����ʾ������ͼ��Χ
#define ROW_MAX 30
#define SPECIAL_DAMAGE 1.5          //�������ʱ��ɵ��˺�ϵ��
#define CRIT_DAMAGE 2               //�����˺�
#define CHEAPEST_SOLDIER 75         //���ʿ���۸�
#define BOWMAN_PRICE 100
#define FOOTMAN_PRICE 75
#define KNIGHT_PRICE 125
#define GENERATE_RANGE 5 //���ؿ�������ʿ���ķ�Χ
#define uchar unsigned char
#define uint unsigned int

//extern int atk_bowman_num, atk_footman_num, atk_knight_num;//atk��ʿ������
//extern int def_bowman_num, def_footman_num, def_knight_num;//def��ʿ������
//���������ƶ���Ԥ����(y,x)y:pos[0],x:pos[1]
//#define MOVE_LEFT  {s[pos[0]][pos[1]-1]=s[pos[0]][pos[1]];s[pos[0]][pos[1]]=empty1;pos[1]--;if(display_count<DELAY){display_count++}if(&&Keyboard::isKeyPressed(Keyboard::A){display_count=0;s[pos[0]][pos[1]]->soldierSprite.move(-33.33333333f,0.f);}else{display_count++;}}
//#define MOVE_RIGHT {s[pos[0]][pos[1]+1]=s[pos[0]][pos[1]];s[pos[0]][pos[1]]=empty1;pos[1]++;if(display_count>DELAY){display_count=0;s[pos[0]][pos[1]]->soldierSprite.move(33.33333333f,0.f);}else{display_count++;}}
//#define MOVE_UP    {s[pos[0]-1][pos[1]]=s[pos[0]][pos[1]];s[pos[0]][pos[1]]=empty1;pos[0]--;if(display_count>DELAY){display_count=0;s[pos[0]][pos[1]]->soldierSprite.move(0.f,-33.33333333f);}else{display_count++;}}
//#define MOVE_DOWN  {s[pos[0]+1][pos[1]]=s[pos[0]][pos[1]];s[pos[0]][pos[1]]=empty1;pos[0]++;if(display_count>DELAY){display_count=0;s[pos[0]][pos[1]]->soldierSprite.move(0.f,33.33333333f);}else{display_count++;}}

#define MOVE_LEFT  {s[pos[0]][pos[1]-1]=s[pos[0]][pos[1]];s[pos[0]][pos[1]]=empty1;pos[1]--;s[pos[0]][pos[1]]->soldierSprite.move(-33.33333333f,0.f);}
#define MOVE_RIGHT {s[pos[0]][pos[1]+1]=s[pos[0]][pos[1]];s[pos[0]][pos[1]]=empty1;pos[1]++;s[pos[0]][pos[1]]->soldierSprite.move(33.33333333f,0.f);}
#define MOVE_UP    {s[pos[0]-1][pos[1]]=s[pos[0]][pos[1]];s[pos[0]][pos[1]]=empty1;pos[0]--;s[pos[0]][pos[1]]->soldierSprite.move(0.f,-33.33333333f);}
#define MOVE_DOWN  {s[pos[0]+1][pos[1]]=s[pos[0]][pos[1]];s[pos[0]][pos[1]]=empty1;pos[0]++;s[pos[0]][pos[1]]->soldierSprite.move(0.f,33.33333333f);}

//#define MOVE_LEFT  {s[pos[0]][pos[1]-1]=s[pos[0]][pos[1]];s[pos[0]][pos[1]]=empty1;pos[1]--;for(double i=0;i<33.33333333;i=i+0.001)if(Keyboard::isKeyPressed(Keyboard::A)){{s[pos[0]][pos[1]]->soldierSprite.move(-i,0.f);}}}
//#define MOVE_RIGHT {s[pos[0]][pos[1]+1]=s[pos[0]][pos[1]];s[pos[0]][pos[1]]=empty1;pos[1]++;for(double i=0;i<33.33333333;i=i+0.001)if(Keyboard::isKeyPressed(Keyboard::A)){{s[pos[0]][pos[1]]->soldierSprite.move(i,0.f);}}}
//#define MOVE_UP    {s[pos[0]-1][pos[1]]=s[pos[0]][pos[1]];s[pos[0]][pos[1]]=empty1;pos[0]--;for(double i=0;i<33.33333333;i=i+0.001){if(Keyboard::isKeyPressed(Keyboard::A)){s[pos[0]][pos[1]]->soldierSprite.move(0.f,-i);}}}
//#define MOVE_DOWN  {s[pos[0]+1][pos[1]]=s[pos[0]][pos[1]];s[pos[0]][pos[1]]=empty1;pos[0]++;for(double i=0;i<33.33333333;i=i+0.001){if(Keyboard::isKeyPressed(Keyboard::A)){s[pos[0]][pos[1]]->soldierSprite.move(0.f,i);}}}
//����ʾ��ͼ
//  0 1 2 3 4 5 6 7 8 9 ������pos[1]
// 0
// 1�� ��  �� ��  ��  ��  ��  �� ��
// 2�� ��  �� ��  ��  ��  ��  �� ��
// 3�� ��  �� ��  ��  ��  ��  �� ��
// 4�� ��  �� ��  ��  ��  ��  �� ��
// 5�� ��  �� ��  ��  ��  ��  �� ��
// 6�� ��  �� ��  ��  ��  ��  �� ��
// ������
// pos[0]
typedef enum
{
    normal, bowman, footman, knight, base,super //���ؾ���һ���������ƶ���ʿ��
}soldier_type;
//ս��˫�����壬Ĭ��Ϊmid
typedef enum
{
    mid, def, atk
}war_side;