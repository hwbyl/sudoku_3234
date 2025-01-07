#include <iostream>
#include <windows.h>
//���F
using namespace std;

int board[4][4] = {
    {0, 0, 1, 0},
    {0, 4, 0, 0},
    {0, 0, 2, 0},
    {0, 1, 0, 0},
};

bool editable[4][4];

int cur_r = 0, cur_c = 0;   //�ĴX��� ���� �����Ц�m 

bool check_horizontal_wrong(int a)
{
    //�p�G�o��ƪ�����Ʀr���Ĭ𪺸�,��Xtrue
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
    //�p�G�o��ƪ��Ʀr�������T����,��Xtrue
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
    //�p�G�o���ƪ�����Ʀr���Ĭ𪺸�,��Xtrue 
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
    //�p�G�o���ƪ��Ʀr�������T����,��Xtrue
    if( board[0][b]!=0 && board[1][b]!=0 && board[2][b]!=0 && board[3][b]!=0 &&
	board[0][b]!=board[1][b] && board[0][b]!=board[2][b] && board[0][b]!=board[3][b] &&
	board[1][b]!=board[2][b] && board[1][b]!=board[3][b] &&
	board[2][b]!=board[3][b]) return true;
	else return false;
	
    
}

bool check_block_wrong(int a,int b)
{
    //��M�o�Ӯ�l�Ҧ�󪺤j�椤��L��l 
    int a1,b1;
    if(a==0||a==2) a1=a+1;
    else if (a==1||a==3) a1=a-1;
    
    if(b==0||b==2) b1=b+1;
	else if (b==1||b==3) b1=b-1;
	
	//�p�G�o�j�檺����Ʀr���Ĭ𪺸�,��Xtrue
	if( board[a][b]!=0 && ( board[a][b]==board[a][b1] || board[a][b]==board[a1][b] || board[a][b]==board[a1][b1] ) ) return true;
	else if(board[a1][b]!=0 && ( board[a1][b]==board[a][b1] || board[a1][b]==board[a1][b1])) return true;
	else if (board[a][b1]!=0 && board[a][b1]==board[a1][b1]) return true;
	else return false;

}

bool check_block_right(int a,int b)
{
    //�e�W 
    int a1,b1;
    if(a==0||a==2) a1=a+1;
    else if (a==1||a==3) a1=a-1;
    
    if(b==0||b==2) b1=b+1;
	else if (b==1||b==3) b1=b-1;
	
	//�p�G�o�j�檺�Ʀr�������T����,��Xtrue
	if( board[a][b]!=0 && board[a1][b]!=0 && board[a][b1]!=0 && board[a1][b1]!=0 &&
	board[a][b]!=board[a1][b] && board[a][b]!=board[a][b1] && board[a][b]!=board[a1][b1] &&
	board[a1][b]!=board[a][b1] && board[a1][b]!=board[a1][b1] &&
	board[a][b1]!=board[a1][b1]) return true;
	else return false;

}

void fill_number(int c)
{   
	//��J�Ʀr 
    board[cur_r][cur_c]= c-48;
}

void move_cursor(char c)
{
    //���ʥ��� 
    int yuan_r=cur_r,yuan_c=cur_c; 		//���Э쥻��m 
    if((c=='w'||c=='W')&&cur_r>0) {
	    cur_r--;						//�����ʥ��� 
	   	while(!editable[cur_r][cur_c]){ 	//���ʫ᪺���Ь����i�s�褧��l 
	   		if(cur_r<1){				 		//�p�G���ЦA���ʤ@���|�I����� 
	   			cur_r=yuan_r;			 		//�h�h�^��쥻��m 
	   			break;
			   }
			else cur_r--;					//�p�G���ЦA���ʤ��|�I����� �Y�~�򲾰� 
	   }
	   
	}
	
    else if((c=='s'||c=='S')&&cur_r<3) {	//�e�W 
	   cur_r++;
	   while(!editable[cur_r][cur_c]){
	   		if(cur_r>2){
	   			cur_r=yuan_r;
	   			break;
			   }
			else cur_r++;
	}
}
	
    else if((c=='a'||c=='A')&&cur_c>0) {	//�e�W 
	   cur_c--;
	   while(!editable[cur_r][cur_c]){
	   		if(cur_c<1){
	   			cur_c=yuan_c;
	   			break;
			   }
			else cur_c--;
	}
}
	
    else if((c=='d'||c=='D')&&cur_c<3) {	//�e�W 
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
    
	//�d�ݳo�Ӯ�l�b���P��ΦP�C�ΦP�j��O�_����l����Ĳ �Y����Xtrue
	if (check_horizontal_wrong(i)||check_vertical_wrong(j)||check_block_wrong(i,j)) return true;
    return false;
}

bool is_done(int i, int j)
{
    //�d�ݳo�Ӯ�l�b���P��ΦP�C�ΦP�j��O�_�������� �Y����Xtrue 
    if (check_horizontal_right(i)||check_vertical_right(j)||check_block_right(i,j)) return true;
    return false;
}

bool check_win()
{
    //�d�ݹC���O�_���� �Y����Xtrue
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
	// �d�ݿ�J���r���O�_�����ʥ��Ъ����O 
    return (c == 'W' || c == 'w' || c == 'S' || c == 's' ||
            c == 'A' || c == 'a' || c == 'D' || c == 'd');
}

bool is_filling_action(char c)
{	
	// �d�ݿ�J���r���O�_����J�Ʀr�����O 
    return (c >= '0' && c <= '4');
}

string get_styled_text(string text, string style)
{	
	// �Хܳo�Ӧr�������ƻ��C����������鵥 
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
    // Flush the screen��s���� 
    cout << "\x1b[2J\x1b[1;1H";

    // ��X�C�������O���� 
    cout << get_styled_text("W/A/S/D: ", "B") << "move cursor" << endl;
    cout << get_styled_text("    1-4: ", "B") << "fill in number" << endl;
    cout << get_styled_text("      0: ", "B") << "clear the cell" << endl;
    cout << get_styled_text("      Q: ", "B") << "quit" << endl;
    cout << endl;

    // Iterate through and print each cell.��X�C������ 
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
                cout << get_styled_text(" �P ", style);
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




