#include <stdio.h>
#include <stdlib.h>

void buildtree(int N,int &tree_count);
void Print(int arr[],int N,int tree_count);



int main(){
	int N;
	printf("请输入树的节点个数: ");
	scanf("%d",&N);
	
	int tree_count=0;
		
	buildtree(N,tree_count);
	
	printf("tree_count is %d when N is %d\n",tree_count,N);
}

void buildtree(int N,int &tree_count){
	int idx=1;
	int arr[N]={0};
	arr[0]=1;
	int j[N]={0};
	int k[N]={0};
	
	while(idx>0){
		int father=arr[idx-1]/2;//上一节点的父母节点 
		int fapos=0;//父母节点对应的数组下标 
		for(int i=0;i<idx;i++){//在他的父母节点和他之间的数组里有的节点的子节点都可以取 
			if(arr[i]==father){
				fapos=i; 
				break;
			}
		}
		if(j[idx-1]==0){
			j[idx-1]=fapos;
		} 
		
		if(idx==N){
			tree_count++;
			Print(arr,N,tree_count);
			idx--;
		}
		
		for(;j[idx-1]<idx;j[idx-1]++){
			while(k[idx-1]<2){
				arr[idx]=2*arr[j[idx-1]]+k[idx-1];
				k[idx-1]++;
				if(arr[idx]>arr[idx-1]){
					idx++;
				    goto label;
				}
			}
			
		}label:
			
		if(j[idx-1]==idx&&k[idx-1]==2){
			idx--;
			j[idx]++;
		}
	}
}
void Print(int arr[],int N,int tree_count){
	
	printf("%d:",tree_count);
	for(int i=0;i<N;i++){
		printf("%d,",arr[i]);
	}
	printf("\n");
}
