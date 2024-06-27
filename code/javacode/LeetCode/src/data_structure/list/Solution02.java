//206. 反转链表
package data_structure.list;

//滑动窗口思想
//class Solution02 {
//    public ListNode reverseList(ListNode head) {
//        ListNode pre=null;
//        ListNode cur=head;
//        while(cur!=null)
//        {
//            ListNode temp=cur.next;
//            cur.next=pre;
//
//            pre=cur;
//            cur=temp;
//        }
//        return pre;
//    }
//}


//递归
public class Solution02 {
    public ListNode reverseList(ListNode head) {
        if (head == null || head.next == null)
            return head;

        //假设运行完这句之后head.next后面的全部反转了,并且temp是这个反转的新头节点
        ListNode temp = reverseList(head.next);
        head.next.next = head;
        head.next = null;
        //事实上temp的值在确定之后并没有变化
        return temp;
    }
}