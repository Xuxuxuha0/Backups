//445. 两数相加 II
package data_structure.list;


import java.util.LinkedList;



public class Solution07 {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        //用栈把两个数的各位数字存起来
        LinkedList<Integer> list1 = new LinkedList<>();
        LinkedList<Integer> list2 = new LinkedList<>();
        while (l1 != null) {
            list1.addLast(l1.val);
            l1 = l1.next;
        }
        while (l2 != null) {
            list2.addLast(l2.val);
            l2 = l2.next;
        }
        //头节点
        ListNode head = null;
        //进位
        int a = 0;
        while (!list1.isEmpty() || !list2.isEmpty() || a != 0) {
            int tempNum = 0;
            if (!list1.isEmpty())
                tempNum += list1.removeLast();
            if (!list2.isEmpty())
                tempNum += list2.removeLast();
            tempNum += a;
            a = tempNum / 10;
            ListNode tempNode = new ListNode(tempNum % 10);
            //头插法
            tempNode.next = head;
            head = tempNode;
        }
        return head;
    }
}