//328. 奇偶链表
package data_structure.list;

//思路很简单，就是重组链表，用到了双指针
//关键在于解链拆链，有点复杂
public class Solution10 {
    public ListNode oddEvenList(ListNode head) {
        if (head == null || head.next == null)
            return head;
        ListNode p1 = head, p2 = head.next, temp1, temp2;
        while (p2 != null && p2.next != null) {
            //解链拆链的步骤(直接用临时变量把需要用到的节点存起来)
            temp1 = p1.next;
            temp2 = p2.next.next;
            p1.next = p2.next;
            p2.next.next = temp1;
            p2.next = temp2;

            p1 = p1.next;
            p2 = p2.next;
        }
        return head;
    }
}
