//160. 相交链表

package data_structure.list;

//利用集合把headA的结点全部存进去，如果在headB里面找到了就说明有相连的
//public class Solution01 {
//    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
//        ArrayList<ListNode> al = new ArrayList<>();
//        //temp是headA的一个引用，地址相同
//        ListNode temp = headA;
//        while (temp != null) {
//            al.add(temp);
//            temp = temp.next;
//        }
//        temp = headB;
//        while (temp != null) {
//            if (al.contains(temp))
//                return temp;
//            temp = temp.next;
//        }
//        return null;
//    }
//}


//???
public class Solution01 {
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        if (headA == null || headB == null) {
            return null;
        }
        ListNode pA = headA, pB = headB;
        while (pA != pB) {
            pA = pA == null ? headB : pA.next;
            pB = pB == null ? headA : pB.next;
        }
        return pA;
    }
}

