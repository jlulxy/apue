# APUE 读书笔记

## 2019-12-22
### 练习题11.2
1. change job中的线程id必须是读写锁，防止与job_find冲突
2. 目前的设计存在的问题是，job_find后，线程id可能被change，所以需要在job中添加一个引用（配合mutex）只能change引用为0的
