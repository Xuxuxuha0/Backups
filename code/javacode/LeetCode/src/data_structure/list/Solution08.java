//234. 回文链表
package data_structure.list;


public class Solution08 {
    public boolean isPalindrome(ListNode head) {
        //特判
        if (head == null)
            return true;
        //找到后半部分的头节点
        ListNode secondPart = getSecondPart(head);
        //反转后半部分
        secondPart = reverse(secondPart);
        //判断是否相等
        while (secondPart != null) {
            if (secondPart.val != head.val)
                return false;
            secondPart = secondPart.next;
            head = head.next;
        }
        return true;
    }

    //快慢指针：一次遍历找到链表的中间位置
    public ListNode getSecondPart(ListNode head) {
        ListNode slow, fast;
        slow = fast = head;
        //慢指针走一步，快指针走两步
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        //返回的始终为后半部分的头节点
        //1 2 3 4：返回3
        //1 2 3 4 5：返回4
        return slow.next;
    }

    //反转链表
    public ListNode reverse(ListNode head) {
        //pre表示已经构造好的新链表的头节点
        ListNode pre = null;
        //cur表示当前在处理的节点
        ListNode cur = head;
        while (cur != null) {
            ListNode next = cur.next;
            cur.next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }
}