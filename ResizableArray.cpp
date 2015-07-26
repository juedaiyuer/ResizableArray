#include"array.h"
#include<stdlib.h>    //declares malloc()
#include<stdio.h>

const BLOCK_SIZE = 20;

Array array_create(int init_size)
{
	Array a;
	a.size = init_size;
	a.array = (int*)malloc(sizeof(int)*a.size);  //return a pointer to the beginning of the block,pointer belong to byte*,so it could transfer to int*
	return a;
}

void array_free(Array *a)
{
	free(a->array);
	a->array = NULL;
	a->size = 0;
}

int array_size(const Array *a)   //封装
{
	return a->size;
}

int* array_at(Array *a,int index)
{
	if( index >=a->size ){         //处理越界问题
	//	array_inflate(a,index-a->size+1);
		array_inflate(a,(index/BLOCK_SIZE+1)*BLOCK_SIZE-a->size);
	}
	return &(a->array[index]);
}

int array_get(const Array *a,int index)
{
	return a->array[index];
}

void array_set(Array *a,int index,int value)
{
	a->array[index] = value;
}

void array_inflate(Array *a,int more_size)
{
	int *p = (int*)malloc(sizeof(int)*(a->size+more_size));
	int i;
	for( i=0;i<a->size;i++){    //memcpy 运用库函数效率高
		p[i]=a->array[i];
	}
	free(a->array);
	a->array = p;
	a->size += more_size;
}

int main(int argc,char const *argv[])
{
	Array a = array_create(100);
	printf("%d\n",array_size(&a));
	*array_at(&a,0) = 10;
	printf("%d\n",*array_at(&a,0));
	int number = 0;
	int cnt = 0;
	while(number != -1){
		scanf("%d",&number);
		if( number !=-1)
			*array_at(&a,cnt++) = number;
	//	scanf("%d",array_at(&a,cnt++));
	}
	array_free(&a);

	return 0;
}