#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<limits.h>
#include<string.h>
#include<string>
#include<vector>
//#include<experimental/filesystem>

using namespace std;

struct Node {
	long long int value;
	int index;
};
void swap(Node* x, Node* y)
{
	Node temp = *x;
	*x = *y;
	*y = temp;
}

class MinHeap {
	Node* root;
	int heap_size;

public:
	MinHeap(Node a[], int size){
		heap_size = size;
		root = a; 
		int i = (heap_size - 1) / 2;
		while (i >= 0) {
			MinHeapify(i);
			i--;
		}
	}
	void MinHeapify(int i){
		int l = left(i);
		int r = right(i);
		int smallest = i;
		if (l < heap_size && root[l].value < root[i].value)
			smallest = l;
		if (r < heap_size && root[r].value < root[smallest].value)
			smallest = r;
		if (smallest != i) {
			swap(&root[i], &root[smallest]);
			MinHeapify(smallest);
		}
	}
	int left(int i) { 
		return (2 * i + 1); 
	}
	int right(int i) {
		return (2 * i + 2); 
	}
	Node getMin() { 
		return root[0];
	}
	void replaceMin(Node x)
	{
		root[0] = x;
		MinHeapify(0);
	}
};


FILE* openFile(char* fileName, char* mode)
{
	FILE* fp = fopen(fileName, mode);
	if (fp == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	return fp;
}

void mergeFiles(char* output_file, int n, int k)
{
	vector<FILE*> in(k);
	string filename;
	char f_name[100];
	for(int i=0;i<k;i++){
		filename="./data/" ;
		filename +=to_string(i)+".txt";
		strcpy(f_name,filename.c_str());
		string str = "r";
		char mode[10];
		strcpy(mode,str.c_str());
		in[i] = openFile(f_name,mode);
	}
	string str = "w";
	char mode[10];
	strcpy(mode,str.c_str());
	FILE* out = openFile(output_file, mode);
	Node* root = new Node[k];
	int i;
	for (i = 0; i < k; i++) {
		if (fscanf(in[i], "%lld,", &root[i].value) != 1)
			break;

		root[i].index = i;
	}
	MinHeap hp(root, i);
	int count = 0;
	while (count != i) {
		Node root = hp.getMin();
		fprintf(out, "%lld,", root.value);
		if (fscanf(in[root.index], "%lld,",&root.value)!= 1) {
			root.value = LLONG_MAX;
			count++;
		}
		hp.replaceMin(root);
	}
	for (int i = 0; i < k; i++)
		fclose(in[i]);
	fclose(out);
}

void runsOnChunk(char* input_file, int run_size,int &num_ways)
{
	string str = "r";
	char mode[10];
	strcpy(mode,str.c_str());
	FILE* in = openFile(input_file, mode);
	string filename ="";
	char f_name[100];
	vector<long long int>arr;
	bool more_input = true;
	int i;
	long long int x;
	while (more_input) {
		arr.clear();
		filename="./data/" ;
		filename +=to_string(num_ways)+".txt";
		strcpy(f_name,filename.c_str());
		
		for (i = 0; i < run_size; i++) {
			if (fscanf(in, "%lld,", &x) != 1) {
				more_input = false;
				break;
			}
			arr.push_back(x);
		}
		sort(arr.begin(),arr.end());
		if(arr.size()>0){
			num_ways++;
			string str = "w";
			char mode[10];
			strcpy(mode,str.c_str());
			FILE* out = openFile(f_name,mode);
			for (int j = 0; j < i; j++)
				fprintf(out,"%lld,", arr[j]);
			fclose(out);
		}
		
		
	}
	//num_ways -=1;
	fclose(in);
}

void externalSort(char* input_file, char* output_file,int &num_ways, int run_size)
{
	runsOnChunk(input_file,run_size, num_ways);
	mergeFiles(output_file, run_size, num_ways);
	string filename;
	char f_name[100];
	for(int i=0;i<num_ways;i++){
		filename="./data/" ;
		filename +=to_string(i)+".txt";
		strcpy(f_name,filename.c_str());
		remove(f_name);
	}
}

int main(int argc,char* argv[])
{
	int num_ways = 0;
	int run_size = 1000000;
	char* input_file = argv[1];
	char* output_file = argv[2];

	externalSort(input_file, output_file, num_ways,run_size);

	return 0;
}
