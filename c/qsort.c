void　QuickSort(int　a[],int　numsize)/*a是整形数组，numsize是元素个数 10 4 6 3 8 2 5 7 */
{
	int　i=0,j=numsize-1;
	int　val=a[0];/*指定参考值val大小*/
	if(numsize>1)/*确保数组长度至少为2，否则无需排序*/
	{
		　while(i<j)/*循环结束条件*/
			　{
				　/*从后向前搜索比val小的元素，找到后填到a[i]中并跳出循环*/
					　for(;j>i;j--)
					　if(a[j]<val)
					　{
						　a[i++]=a[j];
						　break;
						　}
				　/*从前往后搜索比val大的元素，找到后填到a[j]中并跳出循环*/
					　for(;i<j;i++)
					　if(a[i]>val)
					　{
						　a[j--]=a[i];
						　break;
						　}
				　}
		　a[i]=val;/*将保存在val中的数放到a[i]中*/
		　QuickSort(a,i);/*递归，对前i个数排序*/
		　QuickSort(a+i+1,numsize-i-1);/*对i+2到numsize这numsize-1-i个数排序*/
		　}
}

#include<stdlib.h>
#include<stdio.h>

void Merge(int sourceArr[],int tempArr[],int startIndex,int midIndex,int endIndex)
{
	int i = startIndex,j=midIndex+1,k = startIndex;
	while(i!=midIndex+1 && j!=endIndex+1)
	{
		if(sourceArr[i]>sourceArr[j])
			tempArr[k++] = sourceArr[i++];
		else
			tempArr[k++] = sourceArr[j++];
	}
	while(i!=midIndex+1)
		tempArr[k++] = sourceArr[i++];
	while(j!=endIndex+1)
		tempArr[k++] = sourceArr[j++];
	for(i=startIndex;i<=endIndex;i++)
		sourceArr[i] = tempArr[i];
}

//内部使用递归
void MergeSort(int sourceArr[],int tempArr[],int startIndex,int endIndex)
{
	int midIndex;
	if(startIndex<endIndex)
	{
		midIndex=(startIndex+endIndex)/2;
		MergeSort(sourceArr,tempArr,startIndex,midIndex);
		MergeSort(sourceArr,tempArr,midIndex+1,endIndex);
		Merge(sourceArr,tempArr,startIndex,midIndex,endIndex);
	}
}

int main(int argc,char * argv[])
{
	int a[8]={50,10,20,30,70,40,80,60};
	int i,b[8];
	MergeSort(a,b,0,7);
	for(i=0;i<8;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}
