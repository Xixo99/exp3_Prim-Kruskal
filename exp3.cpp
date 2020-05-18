/*******************
 * ��������С������ 
 * 		 �ֱ���Prim�㷨��Kruskal�㷨ʵ�� 
 * 		 ������һ��20*20�ľ�����txt�ĸ�ʽ����
 *       �����һ��20*20�ľ�����txt�ĸ�ʽ��� 
 *ʱ�䣺2020/5/11 
 *******************/

#include<stdio.h>
#include<stdlib.h>

const int Size = 20;	//�ڵ�ĸ����������������20
const int INF = 2147483647;		//��Ϊint�ɱ�ʾ������Χ�ڵ��������
int G[Size][Size],Ans[Size][Size],B[Size][Size];	//GΪȫ����ͼ�еı�Ȩ�أ��Խ��߾�Ϊ0��Ans����Ϊ�𰸾���B������Kruskal�㷨����Ӧ��

//Node �� count �ĺ����������㷨�в�ͬ����ע������
int Node[Size];	
int count;

//������Prim�㷨��
//�жϺ����ڵ��Ƿ��Ѿ����롰�����ӵĽڵ㡱
bool NotInNode(int j) {
	for (int i=0;i <= count;i++){
		if (j == Node[i]) {
			return false;
		}
	}
	return true;
} 
 
void Prim(){
	//�ڱ��㷨�У�Node�������ڼ�¼�ѱ��������ӵĽڵ�
	int start,end;
	int node;
	
	for (int i=1; i< Size ; i++) {
		Node[i] = -1;
	}
	Node[0] = 0	;	//��һ������Ľڵ���0 
	
	int min = INF; 
	for(count = 0; count < Size - 1 ; count++) { 	//�ܹ�Ҫ����Size-1���� 
		for (int i = 0;i <= count; i++) {	//�ҳ�count+1���Ѿ�������Ľڵ㣬�������ǵ��������������ڵ�ı�
			node =  Node[i]; 
			for(int j =0; j < Size ; j++) {	//����һ���ڵ�����б� 
				if (j != node && NotInNode(j)) {
					if (G[node][j] < min) {
						min = G[node][j];
						start = node; 
						end = j; 
					} 
				}  
			}  
		} 
		//����Сֵ�Ľ��������Ans������
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
	Node[i] = 0; 	//��ʾ�ڵ�δ������� 
	for (int j = 0;j<Size;j++) {
		if (B[i][j] == 1) {
			if (Node[j] == 0) return true;	//����һ��δ������ɵĽڵ�˵�����ڻ�· 
			B[i][j] = 0;
			B[j][i] = 0;
			if (visit(j)) return true;
		}
	}
	Node[i] = 1;	//��ʾ�ڵ��Ѿ�������� 
	return false;
}

bool IsRoop() {	//�ж�ͼ���Ƿ���ڻ� 
	//��ʼNode[i]��Ϊ-1 
	for (int i=0;i<Size;i++) {
		Node[i] = -1;
	}
	for (int i=0;i<Size-1;i++) {
		if(Node[i] == -1) {
			if (visit(i)) return true;	//����iʱ���ֻ�· 
		}
	}
	return false;	//δ���ֻ�· 
}

void Kruskal(){
	int last_min,start,end;
	for (count = 0; count < Size -1; count++){	//����Size-1���� 
		int min = INF;	//��ʼ����Сֵ
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
					if(!IsRoop()) {	//û�л�·�͸�����Сֵ 
						min = G[i][j];
						start = i;
						end = j;
					} 
				}
			}
		} 
		
		//����Ans���飬�����
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

	//����test.txt,д��output.txt
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
	
	//����Ȩ�أ�˳�㽫Ans�����ʼ��
	for(int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			Ans[i][j] = 0;  
			fscanf(pr,"%d",&G[i][j]);  
		}
	}
	
	//���ַ�������ѡ����ʱע�͵�����Ҫ�õ�����һ�־Ϳ�����
	Prim();
//	Kruskal();
	
	//�������
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

