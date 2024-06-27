//725. 分隔链表
package data_structure.list;


public class Solution09 {
    public ListNode[] splitListToParts(ListNode head, int k) {
        ListNode cur = head;
        int cnt = 0;
        while (cur != null) {
            cnt++;
            cur = cur.next;
        }
        //每个链表至少a个节点；前b个链表有a+1个节点
        int a = cnt / k, b = cnt - a * k;
        cur = head;
        ListNode[] res = new ListNode[k];
        //如果cur为空，表示已经没有节点可选了，即后面的子链表全部为null(数组默认值也恰好为null)
        for (int i = 0; i < k && cur != null; i++) {
            //先把头节点放进去，之后就可以改变cur了
            res[i] = cur;
            //计算子链表应有的长度
            int len = a + ((i < b) ? 1 : 0);
            for (int j = 0; j < len - 1; j++)
                cur = cur.next;
            ListNode next = cur.next;
            cur.next = null;
            cur = next;
        }
        return res;
    }
}
