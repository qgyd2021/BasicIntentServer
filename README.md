## 意图识别

通话场景中用于识别用户意图, 此是对 TorchScript 模型的部署. 

### 基础环境

```text
system==centos:v7

python==3.8.10
cmake==3.25.0
gcc==11.1.0
```


### 安装步骤 - linux 平台

```text
sh install.sh --stage -1 --stop_stage 2 --system_version centos
```
此过程依次执行: 
1. 下载模型文件. 
2. 安装 cmake
3. 安装 gcc
4. 安装 gdb 调试工具


```text
cmake -B build
```
1. 构建 cmake. 

```text
sh build.sh --system_version centos
```
1. 编译. 

```text
sh start.sh --http_port 13070 --build_dir build
```
1. 启动服务. 

```text
sh for_restart.sh --http_port 13070 --build_dir build
```
1. for_restart.sh 脚本是在服务挂掉之后自动拉起. 


### 从 Docker 容器启动

```text
docker run -itd \
--name BasicIntentServer \
-p 13070:13070 \
daocloud.io/centos:7 \
/bin/bash
```


### 备注

上传和下载镜像
```text
bash /data/tianxing/images/transfer_nx.sh push cmake_gcc_py38:v1
bash /data/tianxing/images/transfer_img.sh pull nxtele-docker.pkg.coding.net/ops/callbot-generic/cmake_gcc_py38:v1

sh /data/tianxing/images/transfer_nx.sh push callmonitor:v20230515_1002
bash /data/tianxing/images/transfer_img.sh pull nxtele-docker.pkg.coding.net/ops/callbot-generic/callmonitor:v20230515_1002

```

启动容器 从 cmake_gcc_py38:v1 镜像布署服务, 这样可以避免 cmake, gcc, python 几个工具的下载和编译耗时太长.

```text
docker run -itd \
--name BasicIntentServer \
-p 13070:13070 \
nxtele-docker.pkg.coding.net/ops/callbot-generic/cmake_gcc_py38:v1 \
/bin/bash

```
