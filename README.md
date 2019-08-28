# SpellCorrect
### 简介

客户端输入查询词, 服务端发送相近的候选词

### 特性

- 网络库基于Reactor+线程池实现
- 支持中文utf-8
- 添加了缓存系统, 使用LRU算法实现
- 计算相近候选词使用了最小编辑距离算法
- 服务端采用json格式发送查询结果

#### 编译和安装

###### 依赖的第三方库

1. 中文分词使用了[cppjieba](https://github.com/yanyiwu/cppjieba)

2. [jsoncpp](https://github.com/open-source-parsers/jsoncpp)

   下载[1.8.3版本](https://github.com/open-source-parsers/jsoncpp/archive/1.8.3.tar.gz)

   ```shell
   tar xzvf jsoncpp-1.8.3.tar.gz
   cd jsoncpp-1.8.3/
   python amalgamate.py
   sudo cp include/json/ /usr/include/
   ```

###### 编译

1. 离线阶段

   ```shell
   cd src/offline
   make
   cd ../..
   ./bin/offline.exe
   ```

2. 在线阶段

   ```shell
   make
   ./bin/SpellCorrectServer.exe
   ```



