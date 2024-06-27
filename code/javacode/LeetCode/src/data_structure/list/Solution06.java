//24. 两两交换链表中的节点
package data_structure.list;

//利用linkedlist把奇偶节点分离，再重组
//public class Solution06 {
//    public ListNode swapPairs(ListNode head) {
//        //list1存储奇数位置上的节点
//        LinkedList<ListNode> l1 = new LinkedList<>();
//        LinkedList<ListNode> l2 = new LinkedList<>();
//
//        ListNode temp = head;
//        int count = 0;
//        while (temp != null) {
//            //偶数时：节点加入list1
//            if (count % 2 == 0)
//                l1.addLast(temp);
//            else l2.addLast(temp);
//            temp = temp.next;
//            count++;
//        }
//
//        //链表的节点<=1时
//        if (count == 0 || count == 1) {
//            return head;
//        }
//
//        //先连l2，再连l1
//        head = l2.removeFirst();
//        temp = head;
//        count=0;
//        while (!l2.isEmpty()) {
//            if (count % 2 == 0)
//                temp.next = l1.removeFirst();
//            else temp.next = l2.removeFirst();
//
//            count++;
//            temp = temp.next;
//        }
//
//        //把list1剩余的接进去
//        while (!l1.isEmpty()) {
//            temp.next = l1.removeFirst();
//            temp = temp.next;
//        }
//        temp.next = null;
//        return head;
//    }
//}

//直接交换相邻节点
//public class Solution06 {
//    public ListNode swapPairs(ListNode head) {
//        //节点<=1
//        if (head == null || head.next == null)
//            return head;
//
//        ListNode temp = new ListNode(-1, head);
//        ListNode p1 = temp, p2 = head;
//
//        while (true) {
//            p1.next = p2.next;
//            p2.next = p2.next.next;
//            p1.next.next = p2;
//
//            if (p2.next != null && p2.next.next != null) {
//                p1 = p1.next.next;
//                p2 = p2.next;
//            } else break;
//        }
//
//        return temp.next;
//    }
//}

//递归法
public class Solution06 {
    public ListNode swapPairs(ListNode head) {
        //特殊情况(递归出口)
        if (head == null || head.next == null)
            return head;
        //新链表的头节点
        ListNode newHead = head.next;
        //新链表的第二个节点，它的下一个节点是子链表的新的头节点
        head.next = swapPairs(newHead.next);
        newHead.next = head;
        return newHead;
    }
}