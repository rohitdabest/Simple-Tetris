// TETRIS 
//
//
//「TETRIS」キーボード「←」「↑」「→」で、うごかします　！！

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define BLOCK_HEIGHT 4
#define BLOCK_WIDTH 4

#define FIELD_HEIGHT 23
#define FIELD_WIDTH 21

#define SEARCH_START_Y 19
#define SEARCH_START_X 3

void my_init_var();
void my_init_var2();
void my_op_scene();
void my_make_block();
void my_gameover();
void my_get_key();
void my_make_field();
void my_make_collision_field();
void my_init_field();
void my_save_field();
void my_freeze_block();
void my_search_line();
void my_draw_field();
void my_turn_right();
void my_turn_left();
void my_clear_field();
void my_timer();

int first_block[BLOCK_HEIGHT] [BLOCK_WIDTH];
int block[BLOCK_HEIGHT] [BLOCK_WIDTH];
int stage[FIELD_HEIGHT] [FIELD_WIDTH];
int field[FIELD_HEIGHT] [FIELD_WIDTH];
int collision_field[FIELD_HEIGHT] [FIELD_WIDTH];

int blocks[28][16] =
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0},
	{0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,1,1,0,0,0,1,0,0,1,0,0,0,1,1,1},
	{0,0,1,0,1,1,1,0,0,1,1,0,0,1,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,1,1,0,1,1,1,0,0,0,1,0,0,1,0,0},
	{0,1,0,0,0,0,1,0,0,1,1,0,0,1,1,1},
	{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,1,1,0,0,0,0,1,0,1,1,0,0},
	{0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0},
	{0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,1,1,0,1,0,0,0,0,1,1},
	{0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0},
	{0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0},

	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0},
	{0,1,1,0,1,1,1,0,1,1,0,0,1,1,1,0},
	{0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0},

	{0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,1,0,0,1,1,1,1,0,1,0,0,1,1,1,1},
	{0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
};

int block_index_x[4] = {0,4,8,12};
int block_index_y[7] = {0,4,8,12,16,20,24};
int fall;
int side;
int gameover_flag;
int block_flag;
int block_flag2;
int freeze_flag;
int fall_point;
int ran;
int ran2;
int turn_point;
int score;
int lv;

int main()
{
	my_init_var();
	my_init_field();
	my_draw_field();
	my_op_scene();

	while(1)
	{
		if(gameover_flag == 0)
		{
			my_make_block();
			my_gameover();
			my_get_key();
			my_make_field();
			my_init_field();
			my_freeze_block();
			my_draw_field();
			my_clear_field();
			my_timer();
		}
		else
		{
			printf("\t  GAMEOVER  \n");
			break;
		}
		fall++;
	}
	return 0;
}
void my_init_var()
{
	fall = 0;
	side = 6;
	gameover_flag = 0;
	block_flag = 0;
	block_flag2 = 0;
	freeze_flag = 0;
	fall_point = 0;
	ran = 0;
	ran2 = 0;
	turn_point = 400;
	score = 0;
	lv = 1;
}
void my_init_var2()
{
	fall = 0;
	side = 6;
	block_flag2 = 0;
	freeze_flag = 0;
	fall_point = 0;
	turn_point = 400;
}
void my_op_scene()
{
	int any_key;
	printf("\t  TETRIS  \n");
	printf("Press any key to start");
	any_key = _getch();
	if(any_key == 0 || any_key == 224)any_key = _getch();
}

void my_make_block()
{
	int x, y;

	if(block_flag == 0)
	{
		srand((unsigned)time(NULL));
		ran = (rand()%7);
		for (y=0;y<BLOCK_HEIGHT;y++)
		{
			for (x=0;x<BLOCK_WIDTH;x++)
			{
				first_block[y][x] = blocks[block_index_y[ran] + y][block_index_x[0] + x];
			}
		}
		block_flag = 1;
	}

	if(block_flag2 == 0)
	{
		srand((unsigned)time(NULL));
		ran2 = ran;
		ran = (rand()%7);
		for (y=0;y<BLOCK_HEIGHT;y++)
		{
			for (x=0;x<BLOCK_WIDTH;x++)
			{
				block[y][x] = first_block[y][x];
				first_block[y][x] = blocks[block_index_y[ran] + y][block_index_x[0] + x];
			}
		}
		block_flag2 = 1;
	}
}

void my_gameover()
{
	int x, y;

	my_make_collision_field();

	for (y=0;y<BLOCK_HEIGHT;y++)
		{
			for (x=0;x<BLOCK_WIDTH;x++)
			{
				if(block[y][x] != 0)
				{
					if(collision_field[fall + y][side + x] != 0)
					{
						gameover_flag++;
					}
				}
			}
	}
}

void my_get_key()
{
	int x, y;
	int key = 0;
	int side_flag = 0;
	int fall_flag = 0;
	my_make_collision_field();

	if (_kbhit())
	{

		key = _getch();
		if(key == 0 || key == 224) key = _getch();

		switch(key)
		{
		case 0x4b:
			for (y=0;y<BLOCK_HEIGHT; y++)
			{
				for (x=0;x<BLOCK_WIDTH; x++)
				{
					if(block[y][x] != 0)
					{
						if(collision_field[fall + y][side + (x - 1)] != 0)
						{
							side_flag++;
						}
					}
				}
			}
			if(side_flag == 0)
			{
				side--;
			}
			break;
		case 0x4d:
			for (y=0;y<BLOCK_HEIGHT; y++)
			{
				for (x=0;x<BLOCK_WIDTH; x++)
				{
					if(block[y][x] != 0)
					{
						if(collision_field[fall + y][side + (x + 1)] != 0)
						{
							side_flag++;
						}
					}
				}
			}
			if(side_flag == 0)
			{
				side++;
			}
			break;
		case 0x50:
			while(fall_flag == 0)
			{
				for (y=0;y<BLOCK_HEIGHT; y++)
				{
					for (x=0;x<BLOCK_WIDTH; x++)
					{
						if(block[y][x] != 0)
						{
							if(collision_field[fall + (y + 1)][side + x] != 0)
							{
								fall_flag++;
							}
						}
					}
				}
				if(fall_flag == 0)
				{
					fall++;
				}
			}
			break;
		case 0x48:
			my_turn_right();
			break;
		default:
			break;
		}
	}
}

void my_make_field()
{
	int i, j, x, y;
	for (y=0;y<BLOCK_HEIGHT; y++)
	{
		for (x=0;x<BLOCK_WIDTH; x++)
		{
			field[y+fall][x+side] = block[y][x];
		}
	}
	for(i=0;i<FIELD_HEIGHT;i++)
	{
		for(j=0;j<FIELD_WIDTH;j++)
		{
			field[i][j] = field[i][j] + stage[i][j];
		}
	}
}

void my_make_collision_field()
{
	int i, j;
	for(i=0;i<FIELD_HEIGHT;i++)
	{
		for(j=0;j<FIELD_WIDTH;j++)
		{
			collision_field[i][j] = stage[i][j];
			collision_field[i][0] = 9;
			collision_field[i][1] = 9;
			collision_field[i][2] = 9;
			collision_field[20][j] = 9;
			collision_field[21][j] = 9;
			collision_field[22][j] = 9;
			collision_field[i][13] = 9;
			collision_field[i][14] = 9;
			collision_field[i][15] = 9;
			collision_field[i][16] = 9;
			collision_field[i][17] = 9;
			collision_field[i][18] = 9;
			collision_field[i][19] = 9;
			collision_field[i][20] = 9;
		}
	}
}

void my_init_field()
{
	int i, j, x, y;
	int dispsc[4] = {0};

	for(i=0;i<FIELD_HEIGHT;i++)
	{
		for(j=0;j<FIELD_WIDTH;j++)
		{
			field[i][0] = 9;
			field[i][1] = 9;
			field[i][2] = 9;
			field[20][j] = 9;
			field[21][j] = 9;
			field[22][j] = 9;
			field[i][13] = 9;
			field[i][14] = 9;
			field[i][15] = 9;
		}
	}
	for(i=0;i<FIELD_HEIGHT;i++)
	{
		for(j=16;j<FIELD_WIDTH;j++)
		{
			field[i][j] = 19;
		}
	}

	for(y=0;y<BLOCK_HEIGHT;y++)
	{
		for(x=0;x<FIELD_WIDTH;x++)
		{
			field[y+2][x+16] = first_block[y][x] + 10;
		}
	}

	if(score < 10)
	{
		dispsc[0] = 10;
		dispsc[1] = 10;
		dispsc[2] = 10;
		dispsc[3] = score;
	}
	else if(score < 100)
	{
		dispsc[0] = 10;
		dispsc[1] = 10;
		dispsc[2] = score / 10;
		dispsc[3] = score - ((score / 10) * 10);
	}
	else
	{
		dispsc[0] = 10;
		dispsc[1] = 10;
		dispsc[2] = 9;
		dispsc[3] = 9;
	}

	field[1][16] = 78;
	field[1][17] = 69;
	field[1][18] = 88;
	field[1][19] = 84;

	field[8][17] = 10;
	field[8][18] = 83;
	field[8][19] = 67;
	field[9][16] = dispsc[0];
	field[9][17] = dispsc[1];
	field[9][18] = dispsc[2];
	field[9][19] = dispsc[3];

	field[11][17] = 10;
	field[11][18] = 76;
	field[11][19] = 86;
	field[12][16] = 10;
	field[12][17] = 10;
	field[12][18] = 10;
	field[12][19] = lv;
}

void my_freeze_block()
{
	int x, y;
	my_make_collision_field();

		for(y=0;y<BLOCK_HEIGHT;y++)
		{
			for(x=0;x<BLOCK_WIDTH;x++)
			{
				if(block[y][x] != 0)
				{
					if(collision_field[fall + (y + 1)][side + x] != 0)
					{
						freeze_flag++;
					}
				}
			}
		}
		if(freeze_flag != 0)
		{
			if(fall_point == fall)
			{
				my_search_line();
				my_save_field();
				my_init_var2();
			}
			else
			{
				freeze_flag = 0;
				fall_point = fall;
				fall--;
			}
		}
}
void my_search_line()
{
	int i, j;
	int zero_count = 0;
	int clear_flag = 0;
	int clear_lines_point[4] = {0};
	int clear_line_index = 0;
	int remain_lines_point[20] = {0};
	int remain_line_index = 0;

	for(i=SEARCH_START_Y; i>=SEARCH_START_Y-19; i--)
	{
		for(j=SEARCH_START_X; j<SEARCH_START_X+10; j++)
		{
			if(field[i][j] == 0)
			{
				zero_count++;
			}
		}
		if(zero_count == 0)
		{
			clear_flag++;
			clear_lines_point[clear_line_index] = i;
			clear_line_index++;
			score++;
		}
		else
		{
			remain_lines_point[remain_line_index] = i;
			remain_line_index++;
			zero_count = 0;
		}
	}

	if(clear_flag != 0)
	{
		for(clear_line_index=0;clear_line_index<4;clear_line_index++)
		{
			if(clear_lines_point[clear_line_index] != 0)
			{
				for(j=SEARCH_START_X; j<SEARCH_START_X+10; j++)
				{
					field[clear_lines_point[clear_line_index]][j] = 0;
				}
			}
		}
		my_draw_field();
		my_timer();

		remain_line_index = 0;
		for(i=SEARCH_START_Y; i>=SEARCH_START_Y-19; i--)
		{
			for(j=SEARCH_START_X; j<SEARCH_START_X+10; j++)
			{
				field[i][j] = field[remain_lines_point[remain_line_index]][j];
			}
			remain_line_index++;
		}
	}
}

void my_save_field()
{
	int i,j;
	for(i=0;i<FIELD_HEIGHT;i++)
	{
		for(j=0;j<FIELD_WIDTH;j++)
		{
			stage[i][j] = field[i][j];
		}
	}
}

void my_draw_field()
{
	int i, j;
	system("cls");
	for(i=0;i<FIELD_HEIGHT-2;i++)
	{
		for(j=2;j<14;j++)
		{
			if(field[i][j] == 9)printf("□");
			else if(field[i][j] == 1)printf("■");
			else if(field[i][j] == 2)printf("□");
			else printf("  ");
		}
		for(j=16;j<21;j++)
		{
			if(field[i][j] >= 65)printf(" %c",field[i][j] );
			else if(field[i][j] < 10)printf(" %d",field[i][j] );
			else if(field[i][j] == 19)printf("□");
			else if(field[i][j] == 11)printf("■");
			else printf("  ");
		}
		printf("\n");
	}
}

void my_turn_right()
{
	int x, y;
	int turn_flag = 0;
	int turn_block[4][4] = { 0 };

	turn_point++;
	my_make_collision_field();

	for(y=0;y<BLOCK_HEIGHT;y++)
	{
		for(x=0;x<BLOCK_WIDTH;x++)
		{
			turn_block[y][x] = blocks[block_index_y[ran2] + y] [block_index_x[turn_point % 4] + x];
		}
	}

	for(y=0;y<BLOCK_HEIGHT;y++)
	{
		for(x=0;x<BLOCK_WIDTH;x++)
		{
			if(turn_block[y][x] !=0)
			{
				if(collision_field[fall + y][side + x] != 0)
				{
					turn_flag++;
				}
			}
		}
	}

	if(turn_flag == 0)
	{
		for(y=0;y<BLOCK_HEIGHT;y++)
		{
			for(x=0;x<BLOCK_WIDTH;x++)
			{
				block[y][x] = turn_block[y][x];
			}
		}
	}
	else{
		turn_point--;
	}
}

void my_turn_left()
{
	int x, y;
	int turn_flag = 0;
	int turn_block[4][4] = { 0 };

	turn_point--;
	my_make_collision_field();

	for(y=0;y<BLOCK_HEIGHT;y++)
	{
		for(x=0;x<BLOCK_WIDTH;x++)
		{
			turn_block[y][x] = blocks[block_index_y[ran2] + y] [block_index_x[turn_point % 4] + x];
		}
	}

	for(y=0;y<BLOCK_HEIGHT;y++)
	{
		for(x=0;x<BLOCK_WIDTH;x++)
		{
			if(turn_block[y][x] != 0)
			{
				if(collision_field[fall + y][side + x] != 0)
				{
					turn_flag++;
				}
			}
		}
	}

	if(turn_flag == 0)
	{
		for(y=0;y<BLOCK_HEIGHT;y++)
		{
			for(x=0;x<BLOCK_WIDTH;x++)
			{
				block[y][x] = turn_block[y][x];
			}
		}
	}
	else{
		turn_point++;
	}
}

void my_clear_field()
{
	int i, j;
	for(i=0;i<FIELD_HEIGHT;i++)
	{
		for(j=0;j<FIELD_WIDTH;j++)
		{
			field[i][j] = 0;
		}
	}
}

void my_timer()
{
	int x, y;
	int max;

	lv = (score / 10) + 1;
		max = 9000 - (score * 100);

	for(y=0;y<max;y++)
	{
		for(x=0;x<max;x++)
		{
		}
	}
}
