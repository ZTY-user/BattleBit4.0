#pragma once
#include<iostream>
#include"define.h"
//#include"BattleBit_Control.h"
#include<thread>
#include"BattleBit_View.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
using namespace std;
using namespace sf;

//int display_count=0;

//class BattleBit_View;

    class Soldier {
    public:
        soldier_type type;
        war_side side;
        uchar price;
        uchar attack;
        uchar defence;
        uchar crit_rate;
        uchar hp;
        uchar attack_range;
        uchar move_range;
        uchar is_moved;
        int view_range;
        int generate_footman_rate, generate_bowman_rate, generate_knight_rate;
        int total_footman_num, total_bowman_num, total_knight_num;
        int min_generate_row, min_generate_col, max_generate_row, max_generate_col;
        int min_atk_row, min_atk_col, max_atk_row, max_atk_col;
        int pos[2];//����
        char move_tag;
       
        Texture soldierTex;
        Sprite soldierSprite;

         //BattleBit_View** observers;//�۲�������
        //int observer_num;//�۲��ߵĸ���

        int g_nearest_row, g_nearest_col, g_step, g_min_distance;



        //��̬���ʹ�ã�ֻ�ܴ���һ�������ʵ����
        Soldier();
        static Soldier& getinstance() {
            static Soldier  instance;
            return instance;
        }

        virtual void move(Soldier***& s,int row, int col, Soldier* empty1, Soldier*& atk_base, Soldier*& def_base);        //ʿ���ƶ��麯��
        virtual int atk_enemy(Soldier***& s,int row, int col, Soldier* empty1,Soldier* &atk_base, Soldier*& def_base);    //ʿ�������麯��
        int find_nearest_enemy(Soldier***& s,int row, int col, Soldier*&atk_base,Soldier*&def_base);   //Ѱ������ĵ���/��������
         virtual void generate_soldier(Soldier***& s, int row, int col, Soldier* empty1);//���ذ������������ʿ��

      //  void registerObserver(BattleBit_View* o);
        //void removeObserver(BattleBit_View* o);
        //void notifyObservers(Soldier* atk_base, Soldier* def_base);

    };
    /*extern Soldier* empty1;//Ĭ������ȫ��
    extern Soldier* block;//���赲�ĵط���������//�費��Ҫ���ã�
    extern Soldier* atk_base;
    extern Soldier* def_base;
    extern int g_nearest_row, g_nearest_col, g_step, g_min_distance;
    */

     //Soldier *empty1;
    //Soldier *block;
    //Soldier* atk_base;
   // Soldier* def_base;
    //Soldier*** s;
 


    



    class Base : public Soldier {
    public://���ؿ������ɵ�ʿ����Χ

        Base() {}
        Base(soldier_type c_type, war_side c_side, int c_pos[]);
        virtual void move(Soldier***& s,int row, int col) ;    //�պ���ʲôҲ����    //��base��move()�̶�ס����base���ƶ�
        // virtual void generate_soldier(Soldier***& s,int row,int col);
             //��һ����Χ�ڣ�1-10����������ҷ�ʿ��
        virtual int atk_enemy(Soldier***& s,int row, int col, Soldier* empty1,Soldier*& atk_base, Soldier*& def_base);//�������Լ��Ĺ���ģʽ
        virtual void generate_soldier(Soldier***& s, int row, int col, Soldier* empty1);
      
    };
    void Base::move(Soldier***& s, int row, int col) {}

    class Footman : public Soldier //����
    {
    public:
        Footman() {}
        Footman(soldier_type c_type, war_side c_side, int c_pos[]);

    };

    class Super_soldier : public Soldier //����ʿ��
    {
    public:
        Super_soldier() {}
        Super_soldier(soldier_type c_type, war_side c_side, int c_pos[]);
        virtual int atk_enemy(Soldier***& s, int row, int col, Soldier* empty1, Soldier*& atk_base, Soldier*& def_base);
        virtual void move(Soldier***& s, int row, int col, Soldier* empty1, Soldier*& atk_base, Soldier*& def_base);

    };

    class Bowman :public Soldier {//������
    public:
        Bowman() {}
        Bowman(soldier_type c_type, war_side c_side, int c_pos[]);
        virtual int atk_enemy(Soldier***& s,int row, int col, Soldier* empty1,Soldier*& atk_base, Soldier* &def_base);//�����ֹ�����Χ�㣬���Լ��Ĺ�����ʽ
    };
    class Knight : public Soldier //���
    {
    public:
        Knight() {}
        Knight(soldier_type c_type, war_side c_side, int c_pos[]);
        virtual void move(Soldier***& s,int row, int col, Soldier* empty1, Soldier*& atk_base, Soldier*& def_base);//����ƶ��ٶȿ죬���Լ����ƶ���ʽ
    };


    

    void Soldier::move(Soldier***& s,int row, int col, Soldier* empty1,Soldier*&atk_base,Soldier*&def_base) {
        int i = 0, j = 0, k = 0;
        if (is_moved == 1) { return; }//�Ѿ��ƶ��ˣ��������ƶ�
        if (atk_enemy(s,row, col, empty1, atk_base,  def_base)) {//��������˵��ˣ�Ҳ���ܶ�
            return;
        }
        else
        {
            find_nearest_enemy(s,row, col,atk_base,def_base);
            if (g_nearest_row < pos[0])     //����������Ϸ�
            {
                if ((pos[0] != 0) && s[pos[0] - 1][pos[1]] == empty1)   //�����һ���ǿյģ����Ƶ���һ��
                    MOVE_UP

                else if (g_nearest_col < pos[1])         //�����һ��Ϊ�գ���������ĵ�������ߣ���ô˵���������Ѿ�
                {
                    if ((pos[1] != 0) && s[pos[0]][pos[1] - 1] == empty1)   //��߿յģ����Ƶ����
                        MOVE_LEFT
                    //else if ((pos[1] != 0) && s[pos[0]][pos[1] +1] == empty1)   //�ұ߿յģ����Ƶ����
                           // MOVE_RIGHT
                }
                else if ((pos[1] != col - 1) && s[pos[0]][pos[1] + 1] == empty1)  //���ұ߿��ţ����Ƶ��ұ�
                    MOVE_RIGHT
            }
            else if (g_nearest_row > pos[0])  //����������·�
            {
                if ((pos[0] != row - 1) && s[pos[0] + 1][pos[1]] == empty1)   //�����һ���ǿյģ����Ƶ���һ��
                {

                    MOVE_DOWN

                }
                else if (g_nearest_col < pos[1])         //�����һ��Ϊ�գ����ҵ�������ߣ�˵����һ�����Ѿ�
                {
                    if ((pos[1] != 0) && s[pos[0]][pos[1] - 1] == empty1)   //��߿յģ����Ƶ����
                        MOVE_LEFT
                }
                else if ((pos[1] != col - 1) && s[pos[0]][pos[1] + 1] == empty1)  //���ұ߿��ţ����Ƶ��ұ�
                    MOVE_RIGHT
            }
            else if (g_nearest_row == pos[0])     //�����ͬһ��
            {
                if (g_nearest_col < pos[1])
                {
                    if ((pos[1] != 0) && s[pos[0]][pos[1] - 1] == empty1)   //��߿յģ����Ƶ����
                        MOVE_LEFT
                    else if ((pos[0] != 0) && s[pos[0] - 1][pos[1]] == empty1)   //�ϱ߿յģ����Ƶ��ϱ�
                        MOVE_UP
                    else if ((pos[0] != row - 1) && s[pos[0] + 1][pos[1]] == empty1)   //�±߿յģ����Ƶ��±�
                        MOVE_DOWN
                }
                else if (g_nearest_col > pos[1])
                {
                    if ((pos[1] != col - 1) && s[pos[0]][pos[1] + 1] == empty1)   //�ұ߿յģ����Ƶ��ұ�
                        MOVE_RIGHT
                    else if ((pos[0] != 0) && s[pos[0] - 1][pos[1]] == empty1)   //�ϱ߿յģ����Ƶ��ϱ�
                        MOVE_UP
                    else if ((pos[0] != row - 1) && s[pos[0] + 1][pos[1]] == empty1)   //�±߿յģ����Ƶ��±�
                        MOVE_DOWN
                }
            }
            is_moved = 1;
        }
        atk_enemy(s,row, col, empty1, atk_base, def_base);
    }

    //�����Լ�����Ұ��Χ��Ѱ������ĵ���
    int Soldier::find_nearest_enemy(Soldier***& s,int row, int col,Soldier*&atk_base, Soldier* &def_base)
    {
        int i = 0, j = 0, min_distance = 60, min_distance_row = 30, min_distance_col = 30;
        int nearest_i = 0, nearest_j = 0;//���벻����б�ߣ�ֻ�ܺ��ź�������
        int is_atk_find_def_soldier = 0;
        int is_def_find_atk_soldier = 0;
        if (s[pos[0]][pos[1]]->side == atk)
        {
            int imin, imax;
            int jmin, jmax;
            if ((imin = pos[0] - s[pos[0]][pos[1]]->view_range) < 0)
            {
                imin = 0;
            }
            if ((imax = pos[0] + s[pos[0]][pos[1]]->view_range) >=row)
            {
                imax = row-1;
            }
            if ((jmin = pos[1] - s[pos[0]][pos[1]]->view_range) < 0)
            {
                jmin = 0;
            }
            if ((jmax = pos[1] + s[pos[0]][pos[1]]->view_range) >= col)
            {
                jmax = col - 1;
            }
            
            for (i = imin; i <=imax; ++i)
            {
             
                for (j = jmin; j <=jmax; ++j)
                {
                    
                    if (s[i][j]->side == def && (abs(i - pos[0]) + abs(j - pos[1])) < min_distance)
                    {
                        is_atk_find_def_soldier = 1;
                        nearest_i = i;
                        nearest_j = j;
                        min_distance = abs(i - pos[0]) + abs(j - pos[1]);
                    }

                }
            }
            if (is_atk_find_def_soldier == 0) {
                nearest_i = def_base->pos[0];
                nearest_j = def_base->pos[1];
                min_distance = abs(i - def_base->pos[0]) + abs(j - def_base->pos[1]);
            }
        }
        else if (s[pos[0]][pos[1]]->side == def)
        {
            int imin, imax;
            int jmin, jmax;
            if ((imin = pos[0] - s[pos[0]][pos[1]]->view_range )< 0)
            {
                imin = 0;
            }
            if ((imax = pos[0] + s[pos[0]][pos[1]]->view_range )>= row)
            {
                imax = col - 1;
            }
            if ((jmin = pos[1] - s[pos[0]][pos[1]]->view_range) < 0)
            {
                jmin = 0;
            }
            if ((jmax = pos[1] + s[pos[0]][pos[1]]->view_range) >= col)
            {
                jmax = col - 1;
            }
            for (i = imin; i <=imax; ++i)
            {
                for (j = jmin; j <=jmax; ++j)
                {
                    if (s[i][j]->side == atk && (abs(i - pos[0]) + abs(j - pos[1])) < min_distance)
                    {
                        is_def_find_atk_soldier = 1;
                        nearest_i = i;
                        nearest_j = j;
                        min_distance = abs(i - pos[0]) + abs(j - pos[1]);
                    }


                }
            }
            if (is_def_find_atk_soldier == 0) {
                nearest_i = atk_base->pos[0];
                nearest_j = atk_base->pos[1];
                min_distance = abs(i - atk_base->pos[0]) + abs(j - atk_base->pos[1]);
            }
        }
        g_nearest_row = nearest_i;        //��������˵����괫������
        g_nearest_col = nearest_j;
        g_min_distance = min_distance;
        return 0;
    }
    //�Ƿ񱩻� 
    uchar whether_crit(uchar rate)
    {
        srand(time(NULL));
        if ((rand() % 100 + 1) <= rate)
            return CRIT_DAMAGE;
        else
            return 1;
    }
    //�����˺��������������������
    uchar damage_calculate(Soldier* be_atk, Soldier* atk)
    {
        uchar damage = 0;
        if ((be_atk->type == bowman && atk->type == knight) || (be_atk->type == footman && \
            atk->type == bowman) || (be_atk->type == knight && atk->type == footman))
        {
            damage = (atk->attack - be_atk->defence) * SPECIAL_DAMAGE * whether_crit(atk->crit_rate);
        }//��˵ı��ֻ����������˺������ҹ����и��ʻ��������Ч��
        else
            damage = (atk->attack - be_atk->defence) * whether_crit(atk->crit_rate);
        return damage;
    }

    //�ҳ���ΧѪ�����ٵ�ʿ���������������ɹ�����1���޵��˷���0
    int Soldier::atk_enemy(Soldier***& s,int row, int col, Soldier* empty1, Soldier*&atk_base, Soldier*&def_base)
    {
        uchar damage;
        uchar min_hp = 230, min_x = 30, min_y = 30, can_atk = 0;
      /*  if (s[pos[0]][pos[1]]->type == bowman) {
            find_nearest_enemy(s, row, col, atk_base, def_base);

            if (g_min_distance <= 3)
            {
                if ((damage = damage_calculate(s[g_nearest_row][g_nearest_col], s[pos[0]][pos[1]])) > s[g_nearest_row][g_nearest_col]->hp)
                {
                    s[g_nearest_row][g_nearest_col] = empty1;
                    s[g_nearest_row][g_nearest_col]->soldierSprite.setPosition(Vector2f(1000.0f, 1000.0f));
                }
                else
                {
                    s[g_nearest_row][g_nearest_col]->hp -= damage;
                }
                return 1;
            }
            else
                return 0;
        }
        else {*/

            if ((pos[0] != 0) && (s[pos[0] - 1][pos[1]]->side != side) && (s[pos[0] - 1][pos[1]]->side != mid))//�����һ���ǵ���
            {
                min_hp = s[pos[0] - 1][pos[1]]->hp;
                min_x = pos[0] - 1;
                min_y = pos[1];
                can_atk = 1;
            }
            if ((pos[1] != 0) && (s[pos[0]][pos[1] - 1]->side != side) && (s[pos[0]][pos[1] - 1]->side != mid))//�������ǵ���
            {
                can_atk = 1;
                if (s[pos[0]][pos[1] - 1]->hp < min_hp)
                {
                    min_hp = s[pos[0]][pos[1] - 1]->hp;
                    min_x = pos[0];
                    min_y = pos[1] - 1;
                }
            }
            if ((pos[1] != col - 1) && (s[pos[0]][pos[1] + 1]->side != side) && (s[pos[0]][pos[1] + 1]->side != mid))//�������ǵ���
            {
                can_atk = 1;
                if (s[pos[0]][pos[1] + 1]->hp < min_hp)
                {
                    min_hp = s[pos[0]][pos[1] + 1]->hp;
                    min_x = pos[0];
                    min_y = pos[1] + 1;
                }
            }
            if ((pos[0] != row - 1) && (s[pos[0] + 1][pos[1]]->side != side) && (s[pos[0] + 1][pos[1]]->side != mid))//�����һ���ǵ���
            {
                can_atk = 1;
                if (s[pos[0] + 1][pos[1]]->hp < min_hp)
                {
                    min_hp = s[pos[0] + 1][pos[1]]->hp;
                    min_x = pos[0] + 1;
                    min_y = pos[1];
                }
            }
            if (can_atk)         //�����ʿ���ڹ�����Χ��
            {
                if ((damage = damage_calculate(s[min_x][min_y], s[pos[0]][pos[1]])) > min_hp)
                {
                    s[min_x][min_y] = empty1;//����ֱ������
                    s[min_x][min_y]->soldierSprite.setPosition(Vector2f(1000.0f, 1000.0f));
                }
                else
                {
                    s[min_x][min_y]->hp -= damage;//��������������һ����Ѫ��
                    if (s[min_x][min_y]->side == def) {
                        s[min_x][min_y]->soldierSprite.setColor(Color::Red);
                    }
                    else if (s[min_x][min_y]->side == atk) {
                        s[min_x][min_y]->soldierSprite.setColor(Color::Blue);
                    }
                }
                return 1;
            }
            else
                return 0;
        }
    void Super_soldier::move(Soldier***& s, int row, int col, Soldier* empty1, Soldier*& atk_base, Soldier*& def_base) {
        if (is_moved == 1||move_tag=='Q'||move_tag=='q') { return; }//�Ѿ��ƶ��ˣ��������ƶ�
        if ((move_tag=='a'||move_tag=='A' )&& s[pos[0]][pos[1] - 1] == empty1 && (pos[0]) < ROW_MAX && (pos[1] - 1) < COL_MAX && (pos[0]) >= 0 && (pos[1] - 1) >= 0) {

            MOVE_LEFT
               // soldierSprite.move(-33.33333333f, 0.f);
            is_moved = 1;


        }
        else if ((move_tag == 'd' || move_tag == 'D') && s[pos[0]][pos[1] + 1] == empty1 && (pos[0]) < ROW_MAX && (pos[1] + 1) < COL_MAX && (pos[0]) >= 0 && (pos[1] + 1) >= 0) {

            MOVE_RIGHT
              //  soldierSprite.move(33.33333333f, 0.f);
            is_moved = 1;

        }
        else if ((move_tag == 'w' || move_tag == 'W') && s[pos[0] - 1][pos[1]] == empty1 && (pos[0] - 1) < ROW_MAX && pos[1] < COL_MAX && (pos[0] - 1) >= 0 && pos[1] >= 0) {

            MOVE_UP
               // soldierSprite.move(0.f, -33.33333333f);
            is_moved = 1;

        }
        else if ((move_tag == 's' || move_tag == 'S') && s[pos[0] + 1][pos[1]] == empty1 && (pos[0] + 1) < ROW_MAX && pos[1] < COL_MAX && (pos[0] + 1) >= 0 && pos[1] >= 0) {

            MOVE_DOWN
               // soldierSprite.move(0.f, 33.33333333f);
            is_moved = 1;
        }
        
        is_moved = 1;
        Super_soldier::atk_enemy(s, row, col, empty1, atk_base, def_base);
    }

    int Super_soldier::atk_enemy(Soldier***& s, int row, int col, Soldier* empty1, Soldier*& atk_base, Soldier*& def_base) {
        int is_atk=0;
        int i, j;
        int damage;
        if (s[pos[0]][pos[1]]->side == atk)
        {
            int imin, imax;
            int jmin, jmax;
            if ((imin = pos[0] - s[pos[0]][pos[1]]->attack_range) < 0)
            {
                imin = 0;
            }
            if ((imax = pos[0] + s[pos[0]][pos[1]]->attack_range) >= row)
            {
                imax = row - 1;
            }
            if ((jmin = pos[1] - s[pos[0]][pos[1]]->attack_range) < 0)
            {
                jmin = 0;
            }
            if ((jmax = pos[1] + s[pos[0]][pos[1]]->attack_range) >= col)
            {
                jmax = col - 1;
            }

            for (i = imin; i <= imax; ++i)
            {

                for (j = jmin; j <= jmax; ++j)
                {
                    if (s[i][j]->side == def) {
                        is_atk = 1;
                        if ((damage = damage_calculate(s[i][j], s[pos[0]][pos[1]])) > s[i][j]->hp)
                        {
                            s[i][j] = empty1;//����ֱ������
                            s[i][j]->soldierSprite.setPosition(Vector2f(1000.0f, 1000.0f));
                        }
                        else
                        {
                            s[i][j]->hp -= damage;//��������������һ����Ѫ��
                            if (s[i][j]->side == def) {
                                s[i][j]->soldierSprite.setColor(Color::Red);
                            }
                            else if (s[i][j]->side == atk) {
                                s[i][j]->soldierSprite.setColor(Color::Blue);
                            }
                        }
                    }
                }
            }
        }
        else if (s[pos[0]][pos[1]]->side == def)
        {
            int imin, imax;
            int jmin, jmax;
            if ((imin = pos[0] - s[pos[0]][pos[1]]->attack_range) < 0)
            {
                imin = 0;
            }
            if ((imax = pos[0] + s[pos[0]][pos[1]]->attack_range) >= row)
            {
                imax = col - 1;
            }
            if ((jmin = pos[1] - s[pos[0]][pos[1]]->attack_range) < 0)
            {
                jmin = 0;
            }
            if ((jmax = pos[1] + s[pos[0]][pos[1]]->attack_range) >= col)
            {
                jmax = col - 1;
            }
            for (i = imin; i <= imax; ++i)
            {
                for (j = jmin; j <= jmax; ++j)
                {
                    if (s[i][j]->side == atk) {
                        is_atk = 1;
                        if ((damage = damage_calculate(s[i][j], s[pos[0]][pos[1]])) > s[i][j]->hp)
                        {
                            s[i][j] = empty1;//����ֱ������
                            s[i][j]->soldierSprite.setPosition(Vector2f(1000.0f, 1000.0f));
                        }
                        else
                        {
                            s[i][j]->hp -= damage;//��������������һ����Ѫ��
                            if (s[i][j]->side == def) {
                                s[i][j]->soldierSprite.setColor(Color::Red);
                            }
                            else if (s[i][j]->side == atk) {
                                s[i][j]->soldierSprite.setColor(Color::Blue);
                            }
                        }
                    }
                }
            }
        }
        return is_atk;
    }

    //������ƶ������õݹ鴦��ʵ���ƶ�����
    void Knight::move(Soldier***& s,int row, int col, Soldier* empty1, Soldier*& atk_base, Soldier*& def_base)
    {
        if (is_moved == 1)
            return;

        if (atk_enemy(s,row, col,empty1, atk_base, def_base))
        {
            is_moved = 1;
            return;
        }
        if (g_step == 3)
        {
            is_moved = 1;
            return;
        }
        else
        {
            find_nearest_enemy(s,row, col,atk_base,def_base);
            if (g_nearest_row < pos[0])     //����������Ϸ�
            {
                if ((pos[0] != 0) && s[pos[0] - 1][pos[1]] == empty1) //�����һ���ǿյģ����Ƶ���һ��
                {
                    MOVE_UP
                        g_step++;
                    move(s,row, col, empty1, atk_base, def_base);

                }
                else if (g_nearest_col < pos[1])         //�����һ�����Ѿ�
                {
                    if ((pos[1] != 0) && s[pos[0]][pos[1] - 1] == empty1)   //��߿յģ����Ƶ����
                    {
                        MOVE_LEFT
                            g_step++;
                        move(s,row, col, empty1, atk_base, def_base);
                    }
                }
                else if ((pos[1] != col - 1) && s[pos[0]][pos[1] + 1] == empty1)  //���ұ߿��ţ����Ƶ��ұ�
                {
                    MOVE_RIGHT
                        g_step++;
                    move(s,row, col, empty1, atk_base, def_base);
                }
            }
            else if (g_nearest_row > pos[0])  //����������·�
            {
                if ((pos[0] != row - 1) && s[pos[0] + 1][pos[1]] == empty1)   //�����һ���ǿյģ����Ƶ���һ��
                {
                    MOVE_DOWN
                        g_step++;
                    move(s,row, col, empty1, atk_base, def_base);
                }
                else if (g_nearest_col < pos[1])         //�����һ�����Ѿ�
                {
                    if ((pos[1] != 0) && s[pos[0]][pos[1] - 1] == empty1)   //��߿յģ����Ƶ����
                    {
                        MOVE_LEFT
                            g_step++;
                        move(s,row, col, empty1, atk_base, def_base);
                    }
                }
                else if ((pos[1] != col - 1) && s[pos[0]][pos[1] + 1] == empty1)  //���ұ߿��ţ����Ƶ��ұ�
                {
                    MOVE_RIGHT
                        g_step++;
                    move(s,row, col, empty1, atk_base, def_base);
                }
            }
            else if (g_nearest_row == pos[0])     //�����ͬһ��
            {
                if (g_nearest_col < pos[1])         //
                {
                    if ((pos[1] != 0) && s[pos[0]][pos[1] - 1] == empty1)   //��߿յģ����Ƶ����
                    {
                        MOVE_LEFT
                            g_step++;
                        move(s,row, col, empty1, atk_base, def_base);
                    }
                    else if ((pos[0] != 0) && s[pos[0] - 1][pos[1]] == empty1)   //�ϱ߿յģ����Ƶ��ϱ�
                    {
                        MOVE_UP
                            g_step++;
                        move(s,row, col, empty1, atk_base, def_base);
                    }
                    else if ((pos[0] != row - 1) && s[pos[0] + 1][pos[1]] == empty1)   //�±߿յģ����Ƶ��±�
                    {
                        MOVE_DOWN
                            g_step++;
                        move(s,row, col, empty1, atk_base, def_base);
                    }
                }
                else if (g_nearest_col > pos[1])
                {
                    if ((pos[1] != col - 1) && s[pos[0]][pos[1] + 1] == empty1)   //�ұ߿յģ����Ƶ��ұ�
                    {
                        MOVE_RIGHT
                            g_step++;
                        move(s,row, col, empty1, atk_base, def_base);
                    }
                    else if ((pos[0] != 0) && s[pos[0] - 1][pos[1]] == empty1)   //�ϱ߿յģ����Ƶ��ϱ�
                    {
                        MOVE_UP
                            g_step++;
                        move(s,row, col, empty1, atk_base, def_base);
                    }
                    else if ((pos[0] != row - 1) && s[pos[0] + 1][pos[1]] == empty1)   //�±߿յģ����Ƶ��±�
                    {
                        MOVE_DOWN
                            g_step++;
                        move(s,row, col, empty1, atk_base, def_base);
                    }
                }
            }
            //        if(g_step==3)
            //            atk_enemy(s,row,col);

        }
        g_step = 0;
    }

    //�����ֹ���������������Χ1~3
    int Bowman::atk_enemy(Soldier***& s,int row, int col, Soldier* empty1, Soldier*&atk_base, Soldier*&def_base)
    {
        uchar damage;
        find_nearest_enemy(s,row, col, atk_base, def_base);
       // cout << g_min_distance<<endl;
        if (g_min_distance <= 3)
        {
            //cout << damage_calculate(s[g_nearest_row][g_nearest_col], s[pos[0]][pos[1]]) << endl;
            if ((damage = damage_calculate(s[g_nearest_row][g_nearest_col],  s[pos[0]][pos[1]])) > s[g_nearest_row][g_nearest_col]->hp)
            {

                s[g_nearest_row][g_nearest_col] = empty1;
                s[g_nearest_row][g_nearest_col]->soldierSprite.setPosition(Vector2f(1000.0f, 1000.0f));
            }
            else
            {
                s[g_nearest_row][g_nearest_col]->hp -= damage;
                if (s[g_nearest_row][g_nearest_col]->side == def) {
                    s[g_nearest_row][g_nearest_col]->soldierSprite.setColor(Color::Red);
                }else
                  if (s[g_nearest_row][g_nearest_col]->side == atk) {
                        s[g_nearest_row][g_nearest_col]->soldierSprite.setColor(Color::Blue);
                    }
            }
            return 1;
        }
        else
            return 0;
    }



    void Soldier::generate_soldier(Soldier***& s,int row, int col, Soldier* empty1) {
        //��ʾ���صĿ�������ʿ���ķ�Χ
        if ((min_generate_row = (pos[0] - GENERATE_RANGE)) <= 0) {
            min_generate_row = 0;
        }
        if ((min_generate_col = (pos[1] - GENERATE_RANGE)) <= 0) {
            min_generate_col = 0;
        }
        if ((max_generate_row = (pos[0] + GENERATE_RANGE)) >= ROW_MAX - 1) {
            max_generate_row = ROW_MAX - 1;
        }
        if ((max_generate_col = (pos[1] + GENERATE_RANGE)) >= COL_MAX - 1) {
            max_generate_col = COL_MAX - 1;
        }
        srand(time(NULL));
        int tag;
        //char pos1[2];
        int pos1[2];
        for (int i = min_generate_row; i <= max_generate_row; i++) {
            for (int j = min_generate_col; j <= max_generate_col; j++) {
                if (s[i][j] != s[pos[0]][pos[1]]) {//��������غ�
                    if (s[i][j] == empty1) {

                        if (rand() % 20== 1) {//��empty�����ɸõ�ĸ�����5%
                            pos1[0] = i; pos1[1] = j;
                            if (total_bowman_num > 0 || total_footman_num > 0 || total_knight_num > 0) {

                                generate_bowman_rate = 100 * (total_bowman_num) / (total_bowman_num + total_footman_num + total_knight_num);
                                generate_footman_rate = generate_bowman_rate + 100 * (total_footman_num) / (total_bowman_num + total_footman_num + total_knight_num);
                                generate_knight_rate = generate_footman_rate + 100 * (total_knight_num) / (total_bowman_num + total_footman_num + total_knight_num);

                                tag = rand() % generate_knight_rate + 1;

                                if (tag > 0 && tag <= generate_bowman_rate) {

                                    s[i][j] = new Bowman(bowman, this->side, pos1);
                                    total_bowman_num--;
                                }
                                else if (tag > generate_bowman_rate && tag <= generate_footman_rate) {

                                    s[i][j] = new Footman(footman, this->side, pos1);
                                    total_footman_num--;

                                }
                                else if (tag > generate_footman_rate && tag <= generate_knight_rate) {

                                    s[i][j] = new Knight(knight, this->side, pos1);
                                    total_knight_num--;

                                }


                            }
                        }



                    }
                }
            }
        }
    }
    void Base::generate_soldier(Soldier***& s, int row, int col, Soldier* empty1) {
        //��ʾ���صĿ�������ʿ���ķ�Χ


        if ((min_generate_row = (pos[0] - GENERATE_RANGE)) <= 0) {
            min_generate_row = 0;
        }
        if ((min_generate_col = (pos[1] - GENERATE_RANGE)) <= 0) {
            min_generate_col = 0;
        }
        if ((max_generate_row = (pos[0] + GENERATE_RANGE)) >= ROW_MAX - 1) {
            max_generate_row = ROW_MAX - 1;
        }
        if ((max_generate_col = (pos[1] + GENERATE_RANGE)) >= COL_MAX - 1) {
            max_generate_col = COL_MAX - 1;
        }
        srand(time(NULL));
        int tag;
        //char pos1[2];
        int pos1[2];
        for (int i = min_generate_row; i <= max_generate_row; i++) {
            for (int j = min_generate_col; j <= max_generate_col; j++) {
                if (s[i][j] != s[pos[0]][pos[1]]) {//��������غ�
                    if (s[i][j] == empty1) {
                   
                        if (rand() % 20== 1) {//��empty�����ɸõ�ĸ�����5%
                            pos1[0] = i; pos1[1] = j;
                            if (total_bowman_num > 0 || total_footman_num > 0 || total_knight_num > 0) {

                                generate_bowman_rate = 100 * (total_bowman_num) / (total_bowman_num + total_footman_num + total_knight_num);
                                generate_footman_rate = generate_bowman_rate + 100 * (total_footman_num) / (total_bowman_num + total_footman_num + total_knight_num);
                                generate_knight_rate = generate_footman_rate + 100 * (total_knight_num) / (total_bowman_num + total_footman_num + total_knight_num);

                                tag = rand() % generate_knight_rate + 1;

                                if (tag > 0 && tag <= generate_bowman_rate) {

                                    s[i][j] = new Bowman(bowman, this->side, pos1);
                                    total_bowman_num--;
                                
                                        
                                }
                                else if (tag > generate_bowman_rate && tag <= generate_footman_rate) {

                                    s[i][j] = new Footman(footman, this->side, pos1);
                                    total_footman_num--;
                                   
                                }
                                else if (tag > generate_footman_rate && tag <= generate_knight_rate) {

                                    s[i][j] = new Knight(knight, this->side, pos1);
                                    total_knight_num--;
                        
                                }


                            }
                        }



                    }
                }
            }
        }
    }
    int Base::atk_enemy(Soldier***& s,int row, int col, Soldier* empty1, Soldier*&atk_base, Soldier*&def_base) {
        //��ʾ���ؿ��Թ����ķ�Χ
        if ((min_atk_row = (pos[0] - BASE_ATK_RANGE)) <= 0) {
            min_atk_row = 0;
        }
        if ((min_atk_col = (pos[1] - BASE_ATK_RANGE)) <= 0) {
            min_atk_col = 0;
        }
        if ((max_atk_row = (pos[0] + BASE_ATK_RANGE)) >= ROW_MAX - 1) {
            max_atk_row = ROW_MAX - 1;
        }
        if ((max_atk_col = (pos[1] + BASE_ATK_RANGE)) >= COL_MAX - 1) {
            max_atk_col = COL_MAX - 1;
        }
        uchar damage, min_hp = 230, min_x = 50, min_y = 50, can_atk = 0;
        for (int i = min_atk_row; i <= max_atk_row; i++) {
            for (int j = min_atk_row; j <= max_atk_row; j++) {
                if (s[pos[0]][pos[1]] != s[i][j]) {
                    if (s[i][j] != empty1 ) {
                        if (s[i][j]->side != side && (s[i][j]->side != mid)) {
                            can_atk = 1;
                            min_hp = s[i][j]->hp;
                            if ((damage = damage_calculate(s[i][j], s[pos[0]][pos[1]])) > min_hp)
                            {
                                s[i][j] = empty1;
                                s[i][j]->soldierSprite.setPosition(Vector2f(1000.0f, 1000.0f));
                            }
                            else
                            {
                                s[i][j]->hp -= damage;
                            }
                        }
                    }
                }
            }
        }
        if (can_atk == 1) { return 1; }
        else return 0;
    }


    Base::Base(soldier_type c_type, war_side c_side, int c_pos[]) {

        type = c_type;
        side = c_side;
        price = 0;
        attack = 5;
        defence = 1;
        crit_rate = 15;
        hp = 200;
        attack_range = 3;
        move_range = 0;
        is_moved = 0;
    
        //strcpy(pos,c_pos);
        pos[0] = c_pos[0];
        pos[1] = c_pos[1];
        if (side == atk) {
            soldierTex.loadFromFile("Textures/atk_base.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
        else  if (side == def) {
            soldierTex.loadFromFile("Textures/def_base.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }

    }

    //�����ֹ��캯��
    Bowman::Bowman(soldier_type c_type, war_side c_side, int c_pos[])
    {
        view_range = 5;
        type = c_type;
        side = c_side;
        price = BOWMAN_PRICE;
        attack = 15;
        defence = 1;
        crit_rate = 10;
        hp = 90;
        attack_range = 3;
        move_range = 1;
        is_moved = 0;
        //strcpy(pos,c_pos);
        pos[0] = c_pos[0];
        pos[1] = c_pos[1];
        if (this->side == atk) {
            soldierTex.loadFromFile("Textures/atk_bowman.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
        else  if (this->side == def) {
            soldierTex.loadFromFile("Textures/def_bowman.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
    }

    //�������캯��
    Footman::Footman(soldier_type c_type, war_side c_side, int c_pos[])
    {
        view_range = 5;
        type = c_type;
        side = c_side;
        price = FOOTMAN_PRICE;
        attack = 15;
        defence = 3;
        crit_rate = 5;
        hp = 100;
        attack_range = 1;
        move_range = 1;
        is_moved = 0;
        //strcpy(pos,c_pos);
        pos[0] = c_pos[0];
        pos[1] = c_pos[1];
        if (this->side == atk) {
          soldierTex.loadFromFile("Textures/atk_footman.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
        else  if (this->side == def) {
            soldierTex.loadFromFile("Textures/def_footman.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
    }

    //������캯��
    Knight::Knight(soldier_type c_type, war_side c_side, int c_pos[])
    {
        view_range = 10;
        type = c_type;
        side = c_side;
        price = KNIGHT_PRICE;
        attack = 18;
        defence = 5;
        crit_rate = 8;
        hp = 120;
        attack_range = 1;
        move_range = 3;
        is_moved = 0;
        //strcpy(pos,c_pos);
        pos[0] = c_pos[0];
        pos[1] = c_pos[1];
        if (this->side == atk) {
          soldierTex.loadFromFile("Textures/atk_knight.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
        else  if (this->side == def) {
            soldierTex.loadFromFile("Textures/def_knight.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
           soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
    }

    Soldier::Soldier() {
        type = normal;
        side = mid;
        price = 0;
        attack = 0;
        defence = 0;
        crit_rate = 0;
        hp = 0;
        attack_range = 0;
        move_range = 0;
        is_moved = 0;
        generate_footman_rate = 0, generate_bowman_rate = 0, generate_knight_rate = 0;
        total_footman_num = 0, total_bowman_num = 0, total_knight_num = 0;
        min_generate_row = 0, min_generate_col = 0, max_generate_row = 0, max_generate_col = 0;
        min_atk_row = 0, min_atk_col = 0, max_atk_row = 0, max_atk_col = 0;
        // char pos[2]={0,0}; //����(y,x)y:pos[0],x:pos[1]
        pos[0] = 0; //����(y,x)y:pos[0],x:pos[1]
        pos[1] = 0;


        int pos_base_init[2] = { 0,0 };
        // empty1 = new Soldier;
        // block = new Soldier;
        // atk_base = new Base(base, atk, pos_base_init);
        // def_base = new Base(base, def, pos_base_init);
        g_nearest_row = 0, g_nearest_col = 0, g_step = 0, g_min_distance = 0;
       
    
    }

    Super_soldier::Super_soldier(soldier_type c_type, war_side c_side, int c_pos[])
    {
        view_range = 30;
        type = c_type;
        side = c_side;
        price = 0;
        attack = 25;
        defence = 10;
        crit_rate = 15;
        hp = 150;
        attack_range = 1;
        move_range = 1;
        is_moved = 0;
        //strcpy(pos,c_pos);
        pos[0] = c_pos[0];
        pos[1] = c_pos[1];
        if (this->side == atk) {
            soldierTex.loadFromFile("Textures/atk_super.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
        else  if (this->side == def) {
            soldierTex.loadFromFile("Textures/def_super.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
    }

