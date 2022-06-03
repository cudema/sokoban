//이학윤
#include <ncurses.h>
#include <locale.h>

#define GYO 10
#define RETU 10

//뒤로가기 추가

int meiro[GYO][RETU] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 1, 1, 1, 1, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int px, py;		
int goal_count;	
int count;		

int moveInfo[100];
int top = -1;

int getBack()
{
  return moveInfo[top--];
}

void play_reset(void)
{
	int x, y;
	count = 0;
  top = -1;
	px = 1;
	py = 1;
	for(y=0; y<GYO; y++)
		for(x=0; x<RETU; x++)
			if(meiro[y][x] == 2) meiro[y][x] = 0;	
}

void play_restore()
{
  if (top > -1)
  {
    meiro[py][px] = 0;
    switch(getBack())
    {
    case 0:
      py++;
      break;
    case 1:
      px--;
      break;
    case 2:
      py--;
      break;
    case 3:
      px++;
      break;
    }
    count--;
  }
}

void goal_count_check(void)
{
	int x, y;
	goal_count = 0;
	for(y=0; y<GYO; y++)
		for(x=0; x<RETU; x++)
			if(meiro[y][x] == 0) goal_count++;	
}

void draw_meiro(void)
{
	int x, y;
	for(y=0; y<GYO; y++){
		for(x=0; x<RETU; x++){
			if(x == px && y == py){	
				meiro[y][x] = 2;	
				count ++;		
				mvprintw(y,x*2,"🍎"); // printf("O");	
			}
			else if(meiro[y][x] == 0)	
        mvprintw(y,x*2,"  "); //			
			else if(meiro[y][x] == 1)	
				mvprintw(y,x*2,"️⬜️");
			else if(meiro[y][x] == 2)
				mvprintw(y,x*2,"🔳");
		}
	}
  mvprintw(GYO,0,"move: ← ↑ → ↓ restart: SPACE restore: R");  // 🟩 🟩 🟩 🟫🟫🟫 ❤️❤️❤️ 🍎🍎🍎🍎 
	// printf("move: ←↑→↓ restart: SPACE\n");	
}

void key_input(void)
{
	int key;
	key = getch();
	
  if(key == KEY_UP && meiro[py-1][px] == 0)		
  {
    py--;
    top++;
    moveInfo[top] = 0;
  }
	else if(key == KEY_DOWN && meiro[py+1][px] == 0)
  {
    py++;
    top++;
    moveInfo[top] = 2;
  }
	else if(key == KEY_LEFT && meiro[py][px-1] == 0)
  {
		px--;
    top++;
    moveInfo[top] = 3;
  }
	else if(key == KEY_RIGHT && meiro[py][px+1] == 0)
  {
		px++;
    top++;
    moveInfo[top] = 1;
  }
	else if(key == ' ')		
		play_reset();	
  else if(key == 'r')
    play_restore();
	else										
		key_input();						
}

int main(void)
{

  setlocale(LC_ALL, ""); // UTF 8 출력

  initscr(); // ncurses 초기화
  keypad(stdscr, TRUE);
  noecho(); // Don't echo any keypresses
  curs_set(FALSE); // Don't display a cursor


	px = 1;		
	py = 1;				
	count = 0;		
	
	goal_count_check();	
	
	while(1){
		clear(); 

		draw_meiro();	

		if(count == goal_count){	
       mvprintw(GYO+1,0," Sucess !!"); 
       getch();
			break;
		}

		key_input();	

    refresh();
	}

	endwin();
	return 0;
}