//19. 删除链表的倒数第 N 个结点
package data_structure.list;


//双指针+滑动窗口
public class Solution05 {
    public ListNode removeNthFromEnd(ListNode head, int n) {
        //给一个哑节点
        ListNode temp = new ListNode(-1);
        temp.next = head;

        ListNode first, second;
        first = second = temp;
        //固定双指针的距离
        for (int i = 0; i <= n; i++)
            second = second.next;
        //滑动窗口
        while (second != null) {
            first = first.next;
            second = second.next;
        }
        //删除节点
        first.next = first.next.next;
        //无论head是否被删除，结果的头节点都是temp.next
        return temp.next;
    }
}