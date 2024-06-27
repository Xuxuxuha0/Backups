//21. 合并两个有序链表
package data_structure.list;

//常规迭代法
//public class Solution03 {
//    public ListNode mergeTwoLists(ListNode list1, ListNode list2) {
//        //先指定一个哑节点
//        ListNode head = new ListNode(-1);
//        //指定移动指针
//        ListNode move = head;
//        while (list1 != null && list2 != null) {
//            if (list1.val <= list2.val) {
//                move.next = list1;
//                list1 = list1.next;
//            } else {
//                move.next = list2;
//                list2 = list2.next;
//            }
//            move=move.next;
//        }
//        move.next = list1 == null ? list2 : list1;
//        return head.next;
//    }
//}

//递归法
public class Solution03 {
    public ListNode mergeTwoLists(ListNode list1, ListNode list2) {
        if (list1 == null)
            return list2;
        else if (list2 == null)
            return list1;
        else if (list1.val <= list2.val) {
            list1.next = mergeTwoLists(list1.next, list2);
            return list1;
        } else {
            list2.next = mergeTwoLists(list1, list2.next);
            return list2;
        }
    }
}

