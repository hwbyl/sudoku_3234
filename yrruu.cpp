#include <iostream>
//­ú¤F
using namespace std;

int board[4][4];

int ye(){
	
	for(int b=0;b<3;b++){
		for(int t=1;t<4;t++){
			if(b+t<4)
				if(board[1][b]!=0&&board[1][b+t]!=0&&board[1][b]!=board[1][b+t]){
					return 3;
					break;
				}
				else return 2;
		}
	}
}

int main(){
	int i;
	for(i=0;i<4;i++)  cin>>board[1][i];
	
	if(ye()==2)cout<<"right"<<endl;
	else cout<<"wrong"<<endl;

}







