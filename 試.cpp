#include <iostream>
#include <windows.h>
//哭了
using namespace std;

int board[4][4] = {
    {0, 0, 1, 0},
    {0, 4, 0, 0},
    {0, 0, 2, 0},
    {0, 1, 0, 0},
};

bool editable[4][4];

int cur_r = 0, cur_c = 0;   //第幾橫排 直排 的光標位置 

bool check_horizontal_wrong(int a)
{
    //如果這橫排的任何數字有衝突的話,輸出true
    /*if( board[a][0]!=0 && ( board[a][0]==board[a][1] || board[a][0]==board[a][2] || board[a][0]==board[a][3] ) ) return true;
	else if(board[a][1]!=0 && ( board[a][1]==board[a][2] || board[a][1]==board[a][3])) return true;
	else if (board[a][2]!=0 && board[a][2]==board[a][3]) return true;
	else return false;*/
	
	for(int b=0;b<3;b++){
		for(int t=1;t<4;t++){
			if(b+t<4)
				if(board[a][b]!=0&&board[a][b+t]!=0&&board[a][b]==board[a][b+t]){
					return true;
					break;
				}
		}
	}
	return false;
    
}

bool check_horizontal_right(int a)
{
    //如果這橫排的數字完全正確的話,輸出true
    if( board[a][0]!=0 && board[a][1]!=0 && board[a][2]!=0 && board[a][3]!=0 &&
	board[a][0]!=board[a][1] && board[a][0]!=board[a][2] && board[a][0]!=board[a][3] &&
	board[a][1]!=board[a][2] && board[a][1]!=board[a][3] &&
	board[a][2]!=board[a][3]) return true;
	else return false;
	
	/*for(int b=0;b<3;b++){
		for(int t=1;t<4;t++){
			if(b+t<4)
				if(board[a][b]!=0&&board[a][b+t]!=0&&board[a][b]==board[a][b+t]) continue;
				else {
				return false;
				break;	
				}
		}
	}
	return true;*/
	
    
}

bool check_vertical_wrong(int b)
{
    //如果這直排的任何數字有衝突的話,輸出true 
    /*if( board[0][b]!=0 && ( board[0][b]==board[1][b] || board[0][b]==board[2][b] || board[0][b]==board[3][b] ) ) return true;
	else if(board[1][b]!=0 && ( board[1][b]==board[2][b] || board[1][b]==board[3][b])) return true;
	else if (board[2][b]!=0 && board[2][b]==board[3][b]) return true;
	else return false;*/
	
	for(int a=0;a<3;a++){
		for(int t=1;t<4;t++){
			if(a+t<4)
				if(board[a][b]!=0&&board[a+t][b]!=0&&board[a][b]==board[a+t][b]){
					return true;
					break;
				}
		}
	}
	return false;
	
	
}

bool check_vertical_right(int b)
{
    //如果這直排的數字完全正確的話,輸出true
    if( board[0][b]!=0 && board[1][b]!=0 && board[2][b]!=0 && board[3][b]!=0 &&
	board[0][b]!=board[1][b] && board[0][b]!=board[2][b] && board[0][b]!=board[3][b] &&
	board[1][b]!=board[2][b] && board[1][b]!=board[3][b] &&
	board[2][b]!=board[3][b]) return true;
	else return false;
	
    
}

bool check_block_wrong(int a,int b)
{
    //找尋這個格子所位於的大格中其他格子 
    int a1,b1;
    if(a==0||a==2) a1=a+1;
    else if (a==1||a==3) a1=a-1;
    
    if(b==0||b==2) b1=b+1;
	else if (b==1||b==3) b1=b-1;
	
	//如果這大格的任何數字有衝突的話,輸出true
	if( board[a][b]!=0 && ( board[a][b]==board[a][b1] || board[a][b]==board[a1][b] || board[a][b]==board[a1][b1] ) ) return true;
	else if(board[a1][b]!=0 && ( board[a1][b]==board[a][b1] || board[a1][b]==board[a1][b1])) return true;
	else if (board[a][b1]!=0 && board[a][b1]==board[a1][b1]) return true;
	else return false;

}

bool check_block_right(int a,int b)
{
    //呈上 
    int a1,b1;
    if(a==0||a==2) a1=a+1;
    else if (a==1||a==3) a1=a-1;
    
    if(b==0||b==2) b1=b+1;
	else if (b==1||b==3) b1=b-1;
	
	//如果這大格的數字完全正確的話,輸出true
	if( board[a][b]!=0 && board[a1][b]!=0 && board[a][b1]!=0 && board[a1][b1]!=0 &&
	board[a][b]!=board[a1][b] && board[a][b]!=board[a][b1] && board[a][b]!=board[a1][b1] &&
	board[a1][b]!=board[a][b1] && board[a1][b]!=board[a1][b1] &&
	board[a][b1]!=board[a1][b1]) return true;
	else return false;

}

void fill_number(int c)
{   
	//填入數字 
    board[cur_r][cur_c]= c-48;
}

void move_cursor(char c)
{
    //移動光標 
    int yuan_r=cur_r,yuan_c=cur_c; 		//光標原本位置 
    if((c=='w'||c=='W')&&cur_r>0) {
	    cur_r--;						//先移動光標 
	   	while(!editable[cur_r][cur_c]){ 	//當移動後的光標為不可編輯之格子 
	   		if(cur_r<1){				 		//如果光標再移動一次會碰到邊界 
	   			cur_r=yuan_r;			 		//則退回到原本位置 
	   			break;
			   }
			else cur_r--;					//如果光標再移動不會碰到邊界 即繼續移動 
	   }
	   
	}
	
    else if((c=='s'||c=='S')&&cur_r<3) {	//呈上 
	   cur_r++;
	   while(!editable[cur_r][cur_c]){
	   		if(cur_r>2){
	   			cur_r=yuan_r;
	   			break;
			   }
			else cur_r++;
	}
}
	
    else if((c=='a'||c=='A')&&cur_c>0) {	//呈上 
	   cur_c--;
	   while(!editable[cur_r][cur_c]){
	   		if(cur_c<1){
	   			cur_c=yuan_c;
	   			break;
			   }
			else cur_c--;
	}
}
	
    else if((c=='d'||c=='D')&&cur_c<3) {	//呈上 
	  cur_c++;
	  while(!editable[cur_r][cur_c]){
	   		if(cur_c>2){
	   			cur_c=yuan_c;
	   			break;
			   }
			else cur_c++;
	}

}
}

bool is_invalid(int i, int j)
{
    
	//查看這個格子在的同橫或同列或同大格是否有格子有牴觸 若有輸出true
	if (check_horizontal_wrong(i)||check_vertical_wrong(j)||check_block_wrong(i,j)) return true;
    return false;
}

bool is_done(int i, int j)
{
    //查看這個格子在的同橫或同列或同大格是否有完成的 若有輸出true 
    if (check_horizontal_right(i)||check_vertical_right(j)||check_block_right(i,j)) return true;
    return false;
}

bool check_win()
{
    //查看遊戲是否完成 若有輸出true
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if(!is_done(i,j)) {
            	return false;
            	break;
			}
	return true;
}

bool is_moving_action(char c)
{	
	// 查看輸入的字元是否為移動光標的指令 
    return (c == 'W' || c == 'w' || c == 'S' || c == 's' ||
            c == 'A' || c == 'a' || c == 'D' || c == 'd');
}

bool is_filling_action(char c)
{	
	// 查看輸入的字元是否為填入數字的指令 
    return (c >= '0' && c <= '4');
}

string get_styled_text(string text, string style)
{	
	// 標示這個字元應為甚麼顏色或應為粗體等 
    string color = "", font = "";
    for (char c : style)
    {
        if (c == 'R')
            color = "31";
        if (c == 'G')
            color = "32";
        if (c == 'E')
            color = "41";
        if (c == 'C')
            color = "106";
        if (c == 'B')
            font = ";1";
    }
    return "\x1b[" + color + font + "m" + text + "\x1b[0m";
}

void print_board()
{
    // Flush the screen刷新頁面 
    cout << "\x1b[2J\x1b[1;1H";

    // 輸出遊戲的指令按鍵 
    cout << get_styled_text("W/A/S/D: ", "B") << "move cursor" << endl;
    cout << get_styled_text("    1-4: ", "B") << "fill in number" << endl;
    cout << get_styled_text("      0: ", "B") << "clear the cell" << endl;
    cout << get_styled_text("      Q: ", "B") << "quit" << endl;
    cout << endl;

    // Iterate through and print each cell.輸出遊戲頁面 
    for (int i = 0; i < 4; ++i)
    {
        // Print horizontal divider.
        if (i && i % 2 == 0)
            cout << "---------------" << endl;

        // Print the first vertical divider in each line.
        cout << "|";
        for (int j = 0; j < 4; ++j)
        {
            // Set text style based on the state of the cell.
            string style = "";

            // Set style for the cell the cursor pointing to.
            if (cur_r == i && cur_c == j)
                style = "C";
            // Set style for the cell in an invalid line.
            else if (is_invalid(i, j))
                style = "E";
            // Set style for the cell in a finished line.
            else if (is_done(i, j))
                style = "G";

            // Set style for a the cell that is immutable.
            if (!editable[i][j])
                style += "B";

            // Print the cell out in styled text.
            // If the content is 0, print a dot, else print the number.
            if (board[i][j] == 0)
                cout << get_styled_text(" · ", style);
            else
                cout << get_styled_text(" " + to_string(board[i][j]) + " ", style);

            // Print the vertical divider for each block.
            if ((j + 1) % 2 == 0)
                cout << "|";
        }
        cout << endl;
    }
}

void initialize()
{
    // Set up styled text for Windows.
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    // Mark editable cells
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            editable[i][j] = !board[i][j];

    // Print the initial board out.
    print_board();
}

int main()
{
    char c;
    bool action_ok;

    initialize();
    while (cin >> c)
    {
        action_ok = false;
        if (is_moving_action(c))
        {
            action_ok = true;
            move_cursor(c);
        }

        if (is_filling_action(c))
        {
            action_ok = true;
            fill_number(c);
        }

        if (c == 'Q' || c == 'q')
            break;

        print_board();

        if (check_win())
        {
            cout << "YOU WIN!" << endl;
            break;
        }

        if (!action_ok)
            cout << get_styled_text("!!! Invalid action !!!", "R");
    }

    return 0;
}




