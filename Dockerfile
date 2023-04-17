FROM daocloud.io/centos:7

RUN bash -c "mkdir -p /data/tianxing/CLionProjects"
RUN bash -c "yum install -y bzip2 gdb git lrzsz wget vim"












# docker run --name BasicIntentServer -itd -p 13070:13070 daocloud.io/centos:7 /bin/bash

# docker run --name BasicIntentServer --network host --privileged -itd daocloud.io/centos:7 /bin/bash


