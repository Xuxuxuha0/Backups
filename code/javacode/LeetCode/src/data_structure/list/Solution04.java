//83. 删除排序链表中的重复元素
package data_structure.list;


//双指针
public class Solution04 {
    public ListNode deleteDuplicates(ListNode head) {
        //记得先判断头节点为空
        if (head == null)
            return head;
        ListNode p1, p2;
        p1 = p2 = head;
        flag:
        while (true) {
            do {
                p2 = p2.next;
                if (p2 == null)
                    break flag;
            } while (p1.val == p2.val);
            p1.next = p2;
            p1 = p2;
        }
        //无论什么链表，最后都要以null结尾
        p1.next = null;
        return head;
    }
}
