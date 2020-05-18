/*******************
 * 描述：最小生成树 
 * 		 分别用Prim算法和Kruskal算法实现 
 * 		 输入是一个20*20的矩阵，以txt的格式读入
 *       输出是一个20*20的矩阵，以txt的格式输出 
 *时间：2020/5/11 
 *******************/

#include<stdio.h>
#include<stdlib.h>

const int Size = 20;	//节点的个数，这里给定了是20
const int INF = 2147483647;		//此为int可表示整数范围内的最大正数
int G[Size][Size],Ans[Size][Size],B[Size][Size];	//G为全连接图中的边权重，对角线均为0，Ans矩阵为答案矩阵，B矩阵在Kruskal算法中有应用

//Node 和 count 的含义在两种算法中不同，请注意区分
int Node[Size];	
int count;

//用于在Prim算法中
//判断函数节点是否已经加入“被连接的节点”
bool NotInNode(int j) {
	for (int i=0;i <= count;i++){
		if (j == Node[i]) {
			return false;
		}
	}
	return true;
} 
 
void Prim(){
	//在本算法中，Node数组用于记录已被加入连接的节点
	int start,end;
	int node;
	
	for (int i=1; i< Size ; i++) {
		Node[i] = -1;
	}
	Node[0] = 0	;	//第一个引入的节点是0 
	
	int min = INF; 
	for(count = 0; count < Size - 1 ; count++) { 	//总共要新增Size-1条边 
		for (int i = 0;i <= count; i++) {	//找出count+1个已经在树里的节点，遍历他们的所有连向其他节点的边
			node =  Node[i]; 
			for(int j =0; j < Size ; j++) {	//遍历一个节点的所有边 
				if (j != node && NotInNode(j)) {
					if (G[node][j] < min) {
						min = G[node][j];
						start = node; 
						end = j; 
					} 
				}  
			}  
		} 
		//将最小值的结果保存在Ans数组中
		Ans[start][end] = 1; 
		Ans[end][start] = 1;
		min = INF;
		Node[count+1] = end;
		start = -1;
		end = -1;
	}
	return 0; 
}

bool  visit(int i) {
	Node[i] = 0; 	//表示节点未访问完成 
	for (int j = 0;j<Size;j++) {
		if (B[i][j] == 1) {
			if (Node[j] == 0) return true;	//访问一个未访问完成的节点说明存在回路 
			B[i][j] = 0;
			B[j][i] = 0;
			if (visit(j)) return true;
		}
	}
	Node[i] = 1;	//表示节点已经访问完毕 
	return false;
}

bool IsRoop() {	//判断图中是否存在环 
	//初始Node[i]均为-1 
	for (int i=0;i<Size;i++) {
		Node[i] = -1;
	}
	for (int i=0;i<Size-1;i++) {
		if(Node[i] == -1) {
			if (visit(i)) return true;	//访问i时发现环路 
		}
	}
	return false;	//未发现环路 
}

void Kruskal(){
	int last_min,start,end;
	for (count = 0; count < Size -1; count++){	//增加Size-1条边 
		int min = INF;	//初始化最小值
		for(int i = 0; i < Size-1;i++) {
			for (int j = i + 1; j < Size; j++) {
				if (G[i][j] < min && G[i][j] >= last_min) {
					for (int t1=0;t1 < Size;t1++) {
						for (int t2=0;t2 < Size;t2++) {
							B[t1][t2] = Ans[t1][t2];
						}
					}
					B[i][j] = 1;
					B[j][i] = 1;
					if(!IsRoop()) {	//没有环路就更新最小值 
						min = G[i][j];
						start = i;
						end = j;
					} 
				}
			}
		} 
		
		//更新Ans数组，保存答案
		Ans[start][end]=1;
		Ans[end][start]=1; 
		last_min = min;
		G[start][end] = INF;
		G[end][start] = INF;
	}
}
 
int main(void){
	int u, v, w;
	FILE *pr = NULL,*pw = NULL; 

	//读入test.txt,写在output.txt
	pr = fopen("test.txt", "r");
	if (pr == NULL ) {
		printf("Can't open 'test.txt'!\n");
		return 1; 
	}
	pw = fopen("output.txt","w");
	if (pw == NULL) {
		printf("Can't open 'output.txt'!\n"); 
		return 2; 
	}
	
	//更新权重，顺便将Ans数组初始化
	for(int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			Ans[i][j] = 0;  
			fscanf(pr,"%d",&G[i][j]);  
		}
	}
	
	//两种方案均可选，临时注释掉不需要用的另外一种就可以了
	Prim();
//	Kruskal();
	
	//输出数组
	for(int i = 0; i < Size; i++) {
		for(int j = 0 ; j <= i; j++ ) {
			fprintf(pw,"%d\t",Ans[i][j]); 
			printf("%d ",Ans[i][j]);
		}
		fprintf(pw,"\n");
		printf("\n");
	}
	return 0;
}

