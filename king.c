#include<stdio.h>
#include<stdlib.h>
#define SIZE 52

int front[3], rear[3];
int mainqueue[SIZE][3];
int player1queue[SIZE][3];
int player2queue[SIZE][3];

//for color, 0=black, 1=red
//for type, 1=diamond,2=heart,3=club,4=spade
//for value, 11=joker, 12=queen,13=king and 1=A

void enQueue(int queue[SIZE][3], int qno, int front[], int rear[], int color, int type, int value){
	if(rear[qno] == SIZE-1){
		printf("\nQueue Full");
	}
	else{
		if(front[qno] == -1){
	    front[qno] = 0;
		}
		rear[qno]++;
		queue[rear[qno]][0] = color;
		queue[rear[qno]][1] = type;
		queue[rear[qno]][2] = value;
	}
}

void deQueue(int qno, int front[], int rear[]){
	if(front[qno] == rear[qno]){
		printf("\nQueue empty");
	}
	else{
		front[qno]++;
		if(front[qno] == rear[qno]){
			front[qno] = rear[qno] = -1;
		}
	}
}

void display(int queue[SIZE][3], int qno, int front[], int rear[],int tur){
	if(rear[qno] == -1){
		printf("\nQueue empty");
	}
  else{
		int i;
		printf("\nfor turn %d for player %d:\n",tur,qno);
		for(i=front[qno]; i<=rear[qno]; i++){
			switch(queue[i][0]){
				case 0:
				printf("\nblack   ");
				break;
				case 1:
				printf("\nred   ");
				break;
			}
			switch(queue[i][1]){
				case 1:
				printf("diamond   ");
				break;
				case 2:
				printf("heart   ");
				break;
				case 3:
				printf("club   ");
				break;
				case 4:
				printf("spade   ");
				break;
			}
			switch(queue[i][2]){
				case 1:
				printf("A");
				break;
				case 11:
				printf("joker");
				break;
				case 12:
				printf("queen");
				break;
				case 13:
				printf("KING");
				break;
				default:
				printf("%d",queue[i][2]);
				break;
			}
		}
	}
}

int shuffle(int Matrix[SIZE][3]){
	for (int i=0; i<SIZE; i++){
		int r = (rand() % (52));
		for (int j = 0; j < 3; j++){
			int temp =  Matrix[i][j];
			Matrix[i][j] =  Matrix[r][j];
			Matrix[r][j] = temp;
		}
	}
}

int main(){
	for(int i=0;i<3;i++){
		front[i]=-1;
		rear[i]=-1;
	}

	for(int i=0;i<13;i++){
		enQueue(mainqueue,0,front,rear,1,1,i+1);
    }
    for(int i=0;i<13;i++){
		enQueue(mainqueue,0,front,rear,1,2,i+1);
    }
    for(int i=0;i<13;i++){
		enQueue(mainqueue,0,front,rear,0,3,i+1);
    }
    for(int i=0;i<13;i++){
		enQueue(mainqueue,0,front,rear,0,4,i+1);
    }
	
    int j;
    int countplayer1, countplayer2;
    char opt;
    int turn=1;
	
    do{
		for(j=0;j<SIZE;j+=2){
			shuffle(mainqueue);
			countplayer1=0, countplayer2=0;
			enQueue(player1queue,1,front,rear,mainqueue[j][0],mainqueue[j][1],mainqueue[j][2]);
			enQueue(player2queue,2,front,rear,mainqueue[j+1][0],mainqueue[j+1][1],mainqueue[j+1][2]);
			for(int i= front[1];i<=rear[1];i++){
				if(player1queue[i][2]==13){
					countplayer1++;
				}
			}
			for(int i= front[2];i<=rear[2];i++){
				if(player2queue[i][2]==13){
				  countplayer2++;
				}
			}
      printf("\n \n ------------------\n");
			display(player1queue,1,front,rear,turn);
			printf("\n \n \n");
			display(player2queue,2,front,rear,turn);
			if(countplayer1==4){
				printf("\n\n\nPlayer 1 wins!");
        turn++;
				break;
			}
			if(countplayer2==4){
				printf("\n\n\nPlayer 2 wins!");
        turn++;
				break;
			}
			turn++;
      
		}
		if(countplayer1!=4&&countplayer2!=4){
			printf("\n\n\nBoth lose!");
        
		}
		for(int k=0;k<turn-2;k++){
			deQueue(1,front,rear);
			deQueue(2,front,rear);
		}
    turn=1;
		printf("\nDo you want to restart?(enter y for yes, any other key for no)");
		scanf("\n%c",&opt);
    }while(opt=='y');
}