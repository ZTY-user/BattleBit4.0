#pragma once
#include<iostream>
#include"define.h"
//#include"BattleBit_Control.h"
#include"BattleBit_Model.h"
#include<thread>
using namespace std;


class BattleBit_View {
public:
    string name;
    //Soldier* empty1;
   // Soldier* block;
   // Soldier* atk_base;
   // Soldier* def_base;
   // Soldier*** s;
    //BattleBit_Control battle_control;
   BattleBit_View(){}
    //BattleBit_View(Soldier***&s1, Soldier*& block1, Soldier*& empty11, Soldier*& atk_base1, Soldier*& def_base1) {
      //  s = s1;
     //   empty1 = empty11;
     //   block = block1;
     //  atk_base = atk_base1;
      //  def_base = def_base1;
      //  s = Soldier::getinstance();
        //battle_control = battle_control1;
    //}

    char hand_mode() {
       // getchar();
        //cout << "���� Enter" << endl;
        return getchar();
    }
    int select_mode() {
        int watch_mode;
        cout << "��ѡ��ۿ�ս��ģʽ��0--�ر�  1--�Զ�  2--�ֶ�" << endl;
        cin >> watch_mode;
        return watch_mode;
    }

    void update(int base_hp, int side) {
        if (side == 1) {
            cout << "�����������������ܹ���!" << endl;
            cout << "����������Ѫ����" << base_hp << endl;
        }
        if (side == 2) {
            cout << "���ط������������ܹ���!" << endl;
            cout << "���ط�����Ѫ����" << base_hp << endl;
        }
    }



    //��ӡʿ����Ϣ���
    void print_init_list()
    {
        printf(YELLOW"-------------------------------------------------------------" NONE);
        cout << endl;
        printf(YELLOW"��������ӭ����BattleBit����һ�����ɳ�̻غ��Ƶ�ս����Ϸ������" NONE);
        cout << endl;
        printf(YELLOW"-------------------------------------------------------------" NONE);
        cout << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "|����  |���� |���|������|������|������|Ѫ��|������Χ|�ƶ�����| " << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "|������ |B    |100 |15    |10%   |1     |90  |1��3    |1       |" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "|����   |F    |75  |15    |5%    |3     |100 |1       |1       |" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "|���   |K    |125 |18    |8%    |5     |120 |1       |3       |" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "|Ӣ��   |S    |0   |25    |15%   |10    |150 |1       |1       |" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "|����   |H    |0   |5     |15%   |1     |200 |3       |0       |" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "������˹�ϵ�������ֿ˲��������������������˹�����,��˻����1.5���˺�" << endl;
    }

    //��ӡս����ͼ
    void print_war_field(Soldier***& s, Soldier*& block, int row, int col)
    {
        cout << "----------------------------------------" << endl;
        int i = 0, j = 0;

      //#pragma omp parallel for 
        for ( i = 0; i < row; i++)
        {
            for (j = 0; j < col; ++j)
            {
                if (s[i][j]->type == bowman)
                {
                    if (s[i][j]->side == def)
                        printf(GREEN"B" NONE);
                    else if (s[i][j]->side == atk)
                        printf(RED"B" NONE);
                }
                else if (s[i][j]->type == footman)
                {
                    if (s[i][j]->side == def)
                        printf(GREEN"F" NONE);
                    else if (s[i][j]->side == atk)
                        printf(RED"F" NONE);
                }
                else if (s[i][j]->type == knight)
                {
                    if (s[i][j]->side == def)
                        printf(GREEN"K" NONE);
                    else if (s[i][j]->side == atk)
                        printf(RED"K" NONE);
                }
                else if (s[i][j]->type == base)
                {
                    if (s[i][j]->side == def)
                        printf(GREEN"H" NONE);
                    else if (s[i][j]->side == atk)
                        printf(RED"H" NONE);
                }
                else if (s[i][j] == block) {
                    printf(NONE"*" NONE);
                }
                else if (s[i][j]->type == normal)
                    cout << " ";
            }
            cout << endl;

        }
        cout << "----------------------------------------" << endl;

    }

    void print_war_state(Soldier***&s,int row, int col,Soldier*&def_base, Soldier*& atk_base)
    {
        int is_def_base_exit = 0;
        int is_atk_base_exit = 0;
        int i = 0, j = 0, def_num = 0, atk_num = 0;

        for (i = 0; i < row; ++i)
        {
            for (j = 0; j < col; ++j)
            {
                if (s[i][j] == def_base) {
                    is_def_base_exit = 1;
                }
                if (s[i][j] == atk_base) {
                    is_atk_base_exit = 1;
                }
                if (s[i][j]->side == def)
                    def_num++;
                else if (s[i][j]->side == atk)
                    atk_num++;
            }
        }
        cout << "********************" << endl;
        cout << "������ʣ��" << atk_num << "ʿ��" << endl;
        cout << "���ط�ʣ��" << def_num << "ʿ��" << endl;

        if (is_def_base_exit == 0 && is_atk_base_exit != 0 || def_num == 0 && atk_num == 0 && def_base->hp < atk_base->hp)
        {
            cout << "ս��������������ʤ����" << endl;
            cout << "********************" << endl;
            getchar();
            exit(0);
        }
        else if (is_def_base_exit != 0 && is_atk_base_exit == 0 || def_num == 0 && atk_num == 0 && def_base->hp > atk_base->hp)
        {
            cout << "ս�����������ط�ʤ����" << endl;
            cout << "********************" << endl;
            getchar();
            //getchar();
            exit(0);
        }
        else if (def_num == 0 && atk_num == 0 && def_base->hp == atk_base->hp) {
            cout << "ս��������˫��ƽ�֣�" << endl;
            cout << "********************" << endl;
            getchar();
            // getchar();
            exit(0);
        }
        cout << "********************" << endl;
    }

    int choice_war_mode()
    {
        char choice;
        cout << "��ѡ���սģʽ 1��100vs100   2����Ǯģʽ  3���˳�" << endl;
        choice = getchar();
        getchar();
        if (choice == '1')
            return 1;
        else if (choice == '2')
            return 2;
        else
            exit(0);
    }

    //����ģʽ
    void  hundred_mode(Soldier***&s,Soldier*& def_base, Soldier*& atk_base)
    {
        cout << "˫����������100��" << endl;
        cout << "�����Ƿ��ط����ñ����ͻ��ؽ׶�" << endl;

        int type, soldier_number, i = 0, j = 0, k = 0, sum = 0, max_number = 100;

       // init_generate_block(s, ROW_MAX, COL_MAX);
        i = 0, j = 0;
        //char pos[2] = { 0,0 };
        int pos[2] = { 0,0 };
        int is_def_base_init = 0;
        int is_atk_base_init = 0;
        while (1)
        {
            cout << "��ѡ��Ҫ���õı��ֻ���أ� 1�������� 2������ 3����� 4������" << endl;
            cin >> type;
            switch (type)
            {
            case 1:
            {
                cout << "����������" << max_number - sum << "��ʿ��" << endl;
                cout << "������������";
                cin >> def_base->total_bowman_num;
                if (def_base->total_bowman_num > max_number - sum)
                {
                    cout << "����������Χ��Ϊ������" << max_number - sum << "��������" << endl;
                    def_base->total_bowman_num = max_number - sum;
                }
                sum = sum + def_base->total_bowman_num;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Bowman(bowman, def, pos);
                    pos[1]++, j++;
                    if (pos[1] >= COL_MAX)
                        pos[1] = 0, pos[0]++, i++, j = 0;

                }
                */
                break;
            }
            case 2:
            {
                cout << "����������" << max_number - sum << "��ʿ��" << endl;
                cout << "������������";
                cin >> def_base->total_footman_num;
                if (def_base->total_footman_num > max_number - sum)
                {
                    cout << "����������Χ��Ϊ������" << max_number - sum << "������" << endl;
                    def_base->total_footman_num = max_number - sum;
                }
                sum = sum + def_base->total_footman_num;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Footman(footman, def, pos);
                    pos[1]++, j++;
                    if (pos[1] >= COL_MAX)
                        pos[1] = 0, pos[0]++, i++, j = 0;

                }
                */
                break;
            }
            case 3:
            {
                cout << "����������" << max_number - sum << "��ʿ��" << endl;
                cout << "������������";
                cin >> def_base->total_knight_num;
                if (def_base->total_knight_num > max_number - sum)
                {
                    cout << "����������Χ��Ϊ������" << max_number - sum << "�����" << endl;
                    def_base->total_knight_num = max_number - sum;
                }
                sum = sum + def_base->total_knight_num;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Knight(knight, def, pos);
                    pos[1]++, j++;
                    if (pos[1] >= COL_MAX)
                        pos[1] = 0, pos[0]++, i++, j = 0;

                }*/
                break;
            }
            case 4:
            {
                cout << "��������ط����ص�����:" << endl;
                cout << "��������ط����ص�����:�����̴��ϵ�����������" << endl;
                cin >> def_base->pos[0];
                cout << "��������ط����ص�����:�����̴�������������" << endl;
                cin >> def_base->pos[1];
                cout << "���ط����������ѳɹ����ã�" << endl;
                is_def_base_init = 1;
                s[def_base->pos[0]][def_base->pos[1]] = def_base;
                break;
            }
            default:
                break;

            }

            if (sum >= max_number && is_def_base_init == 1)
                break;

        }//end while


        cout << "�����ǽ��������ñ�������ؽ׶�" << endl;

        sum = 0, i = ROW_MAX - 1, j = COL_MAX - 1;
        pos[0] = i, pos[1] = j;
        while (1)
        {
            cout << "��ѡ��Ҫ���õı��ֻ���أ� 1�������� 2������ 3����� 4������" << endl;
            cin >> type;
            switch (type)
            {
            case 1:
            {
                cout << "����������" << max_number - sum << "��ʿ��" << endl;
                cout << "������������";
                cin >> atk_base->total_bowman_num;
                if (atk_base->total_bowman_num > max_number - sum)
                {
                    cout << "����������Χ��Ϊ������" << max_number - sum << "��������" << endl;
                    atk_base->total_bowman_num = max_number - sum;
                }
                sum = sum +atk_base->total_bowman_num;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Bowman(bowman, atk, pos);
                    pos[1]--, j--;
                    if (pos[1] < 0)
                        pos[1] = COL_MAX - 1, pos[0]--, i--, j = COL_MAX - 1;

                }*/
                break;
            }
            case 2:
            {
                cout << "����������" << max_number - sum << "��ʿ��" << endl;
                cout << "������������";
                cin >> atk_base->total_footman_num;
                if (atk_base->total_footman_num > max_number - sum)
                {
                    cout << "����������Χ��Ϊ������" << max_number - sum << "������" << endl;
                    atk_base->total_footman_num = max_number - sum;
                }
                sum = sum + atk_base->total_footman_num;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Footman(footman, atk, pos);
                    pos[1]--, j--;
                    if (pos[1] < 0)
                        pos[1] = COL_MAX - 1, pos[0]--, i--, j = COL_MAX - 1;

                }
                */
                break;
            }
            case 3:
            {
                cout << "����������" << max_number - sum << "��ʿ��" << endl;
                cout << "������������";
                cin >> atk_base->total_knight_num;
                if (atk_base->total_knight_num > max_number - sum)
                {
                    cout << "����������Χ��Ϊ������" << max_number - sum << "�����" << endl;
                    atk_base->total_knight_num = max_number - sum;
                }
                sum = sum + atk_base->total_knight_num;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Knight(knight, atk, pos);
                    pos[1]--, j--;
                    if (pos[1] < 0)
                        pos[1] = COL_MAX - 1, pos[0]--, i--, j = COL_MAX - 1;

                }*/
                break;
            }
            case 4:
            {
                cout << "��������������ص�����:" << endl;
                cout << "��������������ص�����:�����̴��ϵ�����������" << endl;
                cin >> atk_base->pos[0];
                cout << "��������������ص�����:�����̴�������������" << endl;
                cin >> atk_base->pos[1];
                cout << "���������������ѳɹ����ã�" << endl;
                is_atk_base_init = 1;
               s[atk_base->pos[0]][atk_base->pos[1]] = atk_base;
                break;
            }
            default:
                break;

            }
            if (sum >= max_number && is_atk_base_init == 1)
                break;
        }//end while

      // start_war(s, ROW_MAX, COL_MAX);
        return;
    }





    //��Ǯģʽ
    void money_mode(Soldier***&s,Soldier*&atk_base,Soldier*&def_base)
    {
        int  is_atk_base_init = 0;
        int  is_def_base_init = 0;
        cout << "�������Ǯ����" << endl;
        int money, type, soldier_number, i, j, k, row, col;
        cin >> money;
        int temp_money = money;
        row = ROW_MAX;
        col = COL_MAX;
        // col = money / CHEAPEST_SOLDIER;
         /*
         if (col > COL_MAX)
         {
             row = col / COL_MAX + 1;
             col = COL_MAX;
         }
         else
             row = 1;
         row = row * 2 + 10;*/
 
      //  init_generate_block(s, ROW_MAX, COL_MAX);
        cout << "�����Ƿ��ط����ñ���" << endl;
        //char pos[2] = { 0,0 };
        int pos[2] = { 0,0 };
        int sum = 0;
        i = 0, j = 0;
        while (1)
        {
            if (money < CHEAPEST_SOLDIER && is_def_base_init == 1)
                break;
            cout << "����" << money << "��Ǯ����ʹ��" << endl;
            cout << "��ѡ��Ҫ���õı��ֻ���أ� 1�������� 2������ 3����� 4������" << endl;
            cin >> type;
            switch (type)
            {
            case 1:
            {
                cout << "�����Թ���" << money / BOWMAN_PRICE << "��������" << endl;
                cout << "������������";
                cin >> def_base->total_bowman_num;
                if (def_base->total_bowman_num > money / BOWMAN_PRICE)
                {
                    def_base->total_bowman_num = money / BOWMAN_PRICE;
                    cout << "Ǯ��������Ϊ������" << def_base->total_bowman_num << "��������" << endl;
                }
                money = money - def_base->total_bowman_num * BOWMAN_PRICE;
                /*
                for (k = 0; k < soldier_number; ++k)
                {
                    s[i][j] = new Bowman(bowman, def, pos);
                    pos[1]++, j++;
                    if (pos[1] >= col)
                        pos[1] = 0, pos[0]++, i++, j = 0;

                }*/
                break;
            }
            case 2:
            {
                cout << "�����Թ���" << money / FOOTMAN_PRICE << "������" << endl;
                cout << "������������";
                cin >> def_base->total_footman_num;
                if (def_base->total_footman_num > money / FOOTMAN_PRICE)
                {
                    def_base->total_footman_num = money / FOOTMAN_PRICE;
                    cout << "Ǯ��������Ϊ������" << def_base->total_footman_num << "������" << endl;
                }
                money = money - def_base->total_footman_num * FOOTMAN_PRICE;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Footman(footman, def, pos);
                    pos[1]++, j++;
                    if (pos[1] >= col)
                        pos[1] = 0, pos[0]++, i++, j = 0;

                }*/
                break;
            }
            case 3:
            {
                cout << "�����Թ���" << money / KNIGHT_PRICE << "�����" << endl;
                cout << "������������";
                cin >> def_base->total_knight_num;
                if (def_base->total_knight_num > money / KNIGHT_PRICE)
                {
                    def_base->total_knight_num = money / KNIGHT_PRICE;
                    cout << "Ǯ��������Ϊ������" << def_base->total_knight_num << "�����" << endl;
                }
                money = money - def_base->total_knight_num * KNIGHT_PRICE;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Knight(knight, def, pos);
                    pos[1]++, j++;
                    if (pos[1] >= col)
                        pos[1] = 0, pos[0]++, i++, j = 0;

                }*/
                break;
            }
            case 4:
            {
                cout << "��������ط����ص�����:" << endl;
                cout << "��������ط����ص�����:�����̴��ϵ�����������" << endl;
                cin >> def_base->pos[0];
                cout << "��������ط����ص�����:�����̴�������������" << endl;
                cin >> def_base->pos[1];
                cout << "���ط����������ѳɹ����ã�" << endl;
                is_def_base_init = 1;
                s[def_base->pos[0]][def_base->pos[1]] = def_base;
                break;
            }
            default:
                break;
            }
        }

        cout << "�����ǽ��������ñ����׶�" << endl;
        sum = 0, i = row - 1, j = 0;
        pos[0] = i, pos[1] = j;
        money = temp_money;
        while (1)
        {
            if (money < CHEAPEST_SOLDIER && is_atk_base_init == 1)
                break;
            cout << "����" << money << "��Ǯ����ʹ��" << endl;
            cout << "��ѡ��Ҫ���õı��֣� 1�������� 2������ 3�����  4������" << endl;
            cin >> type;
            switch (type)
            {
            case 1:
            {
                cout << "�����Թ���" << money / BOWMAN_PRICE << "��������" << endl;
                cout << "������������";
                cin >> atk_base->total_bowman_num;
                if (atk_base->total_bowman_num > money / BOWMAN_PRICE)
                {
                    atk_base->total_bowman_num = money / BOWMAN_PRICE;
                    cout << "Ǯ��������Ϊ������" << atk_base->total_bowman_num << "��������" << endl;
                }
                money = money - atk_base->total_bowman_num * BOWMAN_PRICE;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Bowman(bowman, atk, pos);
                    pos[1]++, j++;
                    if (pos[1] >= col)
                        pos[1] = 0, pos[0]--, i--, j = 0;

                }*/
                break;
            }
            case 2:
            {
                cout << "�����Թ���" << money / FOOTMAN_PRICE << "������" << endl;
                cout << "������������";
                cin >> atk_base->total_footman_num;
                if (atk_base->total_footman_num / FOOTMAN_PRICE)
                {
                    atk_base->total_footman_num / FOOTMAN_PRICE;
                    cout << "Ǯ��������Ϊ������" << atk_base->total_footman_num << "������" << endl;
                }
                money = money - atk_base->total_footman_num * FOOTMAN_PRICE;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Footman(footman, atk, pos);
                    pos[1]++, j++;
                    if (pos[1] >= col)
                        pos[1] = 0, pos[0]--, i--, j = 0;

                }*/
                break;
            }
            case 3:
            {
                cout << "�����Թ���" << money / KNIGHT_PRICE << "�����" << endl;
                cout << "������������";
                cin >> atk_base->total_knight_num;
                if (atk_base->total_knight_num > money / KNIGHT_PRICE)
                {
                    atk_base->total_knight_num = money / KNIGHT_PRICE;
                    cout << "Ǯ��������Ϊ������" << atk_base->total_knight_num << "�����" << endl;
                }
                money = money - atk_base->total_knight_num * KNIGHT_PRICE;
                /*
                for (k = 0; k < soldier_number; ++k)
                {

                    s[i][j] = new Knight(knight, atk, pos);
                    pos[1]++, j++;
                    if (pos[1] >= col)
                        pos[1] = 0, pos[0]--, i--, j = 0;

                }*/
                break;
            }
            case 4:
            {
                cout << "��������������ص�����:" << endl;
                cout << "��������������ص�����:�����̴��ϵ�����������" << endl;
                cin >> atk_base->pos[0];
                cout << "��������������ص�����:�����̴�������������" << endl;
                cin >> atk_base->pos[1];
                cout << "���������������ѳɹ����ã�" << endl;
                is_atk_base_init = 1;
               s[atk_base->pos[0]][atk_base->pos[1]] = atk_base;
                break;
            }
            default:
                break;

            }
        }//end while

       // start_war(s, ROW_MAX, COL_MAX);
        return;
    }
};