# Code_snippet
Record part of the slam code snippets

### 1. 单应矩阵案列     
利用单应矩阵将墙面倾斜角度拍摄的画报变换成正视图

 源码：[https://github.com/kaiqi0110/slam-code-snippet/tree/main/Homography](https://github.com/kaiqi0110/slam-code-snippet/tree/main/Homography)
 视频：[https://www.bilibili.com/video/BV1gZ4y1V7ob](https://www.bilibili.com/video/BV1gZ4y1V7ob)
**效果：**


<img src="https://github.com/kaiqi0110/slam-code-snippet/blob/main/Homography/%E5%8D%95%E5%BA%94%E7%9F%A9%E9%98%B5%E9%87%8D%E6%8A%95%E5%BD%B1%E6%95%88%E6%9E%9C.png" width = 80% height = 80% />

### 2.极线案例
通过前30个精确匹配点计算基础矩阵，由F计算极线并绘制。

**效果：**
1)冒泡排序匹配距离升序，取前30个点
<img src="https://github.com/kaiqi0110/slam-code-snippet/blob/main/FindEpilines/goodMatches.png" width = 80% height = 80% />


2)由基础矩阵获取点在另一帧图像上的极线


<img src="https://github.com/kaiqi0110/slam-code-snippet/blob/main/FindEpilines/epilines.png" width = 80% height = 80% />
