FROM daocloud.io/centos:7

RUN bash -c "mkdir -p /data/tianxing/CLionProjects"
RUN bash -c "yum install -y bzip2 gdb git lrzsz wget vim"