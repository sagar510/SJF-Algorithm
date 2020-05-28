#include<iostream.h>
#include<stdlib.h>
#include<conio.h>
# define MAX_VALUE 9999;

int seq[15],gbt[15],my=1;

void sort(int* a, int *b,int *pro,int n){
	int k,j,key1,key2,key3;
	for(int i=1; i<n; i++){
		j=i-1;
		key1=a[i];
		key2=b[i];
		key3=pro[i];
		while(j>=0 && key1<a[j]){
			a[j+1]=a[j];
			b[j+1]=b[j];
			pro[j+1]=pro[j];
			j--;
		}
		a[j+1]=key1;
		b[j+1]=key2;
		pro[j+1]=key3;
	}
}

int findLeastBurstTime(int* bt, int* at, int ct,int n){
	int min_value=bt[0];
	int min_index=0;
	for(int i=0; i<n && at[i]<=ct; i++){
		if(bt[i]<min_value){
			min_value=bt[i];
			min_index=i;
		}
	}
	return min_index;
}

void ganttchart()
{
   int i,j;
 for(i=my-1;i>=0;i--)
 {
  for(j=i-1;j>=0;j--)
  {
   if(seq[i]==seq[j])
   {
    gbt[j]=gbt[j]-gbt[i];
   }
  }
 }


 cout<<"\nGantt Chart\n";
  cout<<"|";

  for(i=0;i<my;i++)
  {
   for(j=0;j<gbt[i]*2;j++){cout<<"Ä";}
   cout<<"|";
  }
  cout<<endl<<"|";

  for(i=0;i<my;i++)
  {
   for(j=0;j<gbt[i]-1;j++){cout<<" ";}
   cout<<"P"<<seq[i];
   for(j=0;j<gbt[i]-1;j++){cout<<" ";}
   cout<<"|";
  }


  cout<<endl<<"|";

  for(i=0;i<my;i++)
  {
   for(j=0;j<gbt[i]*2;j++){cout<<"Ä";}
   cout<<"|";
  }

}

int main(){
	int n;
	clrscr();
	cout<<"                    Panda's Program";
	cout<<"\nEnter no of processes: ";
	cin>>n;
	int at[20],bt[20],bt1[20],ct[20],tat[20],wt[20],pro[20];
	cout<<"\nat bt\n";
	for(int i=0; i<n; i++){
		cin>>at[i]>>bt[i];
		pro[i]=i+1;
	}

	sort(at,bt,pro,n);
	for(i=0; i<n; i++)
		bt1[i]=bt[i];
	// calculating complete time

      //	cout<<"\nGantt Chart\n";

	int prev_i,c,loop_count=n,max=MAX_VALUE;
	i=findLeastBurstTime(bt,at,at[0],n);
	gbt[0]=bt[i];
	seq[0]=pro[i];
	c=at[i]+1;
	ct[i]=c;
	bt[i]--;

	if(bt[i]==0)
	{
		bt[i]=MAX_VALUE;
		loop_count--;
	}

	while(loop_count>0)
	{
		prev_i=i;
		i=findLeastBurstTime(bt,at,c,n);
		if(prev_i!=i)
		{
			gbt[my]=bt[i];
			seq[my]=pro[i];
			my++;
		}
		c++;
		if(bt[i]!=max)
		{
			ct[i]=c;
			bt[i]--;
			if(bt[i]==0)
			{
				bt[i]=MAX_VALUE;
				loop_count--;
			}
		}
	}


	float sum_tat=0,sum_wt=0;
	for(i=0; i<n; i++){
		tat[i]=ct[i]-at[i];
		wt[i]=tat[i]-bt1[i];
		sum_tat+=tat[i];
		sum_wt+=wt[i];
	}

	ganttchart();

	cout<<"\n\npro     at      bt      ct      tat     wt\n";
	for(i=0; i<n; i++)
	{
		cout<<pro[i]<<" \t"<<at[i]<<" \t"<<bt1[i]<<" \t"<<ct[i]<<" \t"<<tat[i]<<"\t "<<wt[i];
		cout<<endl;
	}

	cout<<"\nAvg Turn Around Time:"<<sum_tat/n;
	cout<<"\nAvg waiting time:"<<sum_wt/n;


	getch();
}