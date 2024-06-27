/*
伪代码集合：
1、划分查找
单向：
    LomutoPartition(A[L,R])
    {
        //输入：A[0,n-1]的子数组A[L,R]
        //输出：划分后的A[L,R]，中间数的位置s
        p=A[L];
        S=L;
        for(i=L+1;i<=R;i++)
        {
            if(A[i]<p)
            {
                s++;
                swap(A[i],A[s]);
            }
        }
        swap(A[L],A[s]);
        return s;
    }
    QuickSelect(A[L,R],K)
    {
        //输入：A[0,n-1]的子数组A[L,R],找出第k小的数
        //输出：第k小的数
        s=LomutoPartition(A[L,R]);
        if(s==L+K-1) return A[s];
        else if(s>L+K-1) QuickSelect(A[L,s-1],K);
        else QuickSelect(A[s+1,R],K+L-s-1);
    }


2、折半查找
BinarySearch(A[0,n-1],k)
{
    //输入：升序数组A和查找元素k
    //输出：k的下标；没有则返回-1
    L=0；
    R=n-1;
    while(L<=R)
    {
        mid=(L+R)/2;
        if(k=A[mid]) return mid;
        else if(k<A[mid]) R=mid-1;
        else L=mid+1;
    }
    return -1;
}

3、二叉查找树
递归版：
    BST(root,k)
    {
        //输入：以root为根的二叉树，查找值k的元素
        //输出：成功就返回k在树中的位置；失败返回NULL
        if(root==NULL) return NULL;
        else if(root->data==k) return root;
        else if(root->data > k) return BST(root->lchild,k);
        else return BST(root->rchild,k);
    }
while版：
    BST(root,k)
    {
        //输入：以root为根的二叉树，查找值k的元素
        //输出：成功就返回k在树中的位置；失败返回NULL
        temp=root;
        while(temp!=NULL)
        {
            if(temp->data==k) return temp;
            else if(temp->data > k) temp=temp->lchild;
            else temp=temp->rchild;
        }
    }

4、插入排序
InsertSort(A[0,n-1])
{
    //输入：无序序列A[]
    //输出：升序序列A[]
    for(i=1;i<n;i++)
    {
        temp=A[i];
        j=i-1;
        while(j>=0&&A[j]>temp)//往后挪
        {
            A[j+1]=A[j];
            j--;
        }
        A[j+1]=temp;
    }
}


*/