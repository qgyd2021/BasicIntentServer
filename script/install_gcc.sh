#!/usr/bin/env bash
# 好像要先安装 cmake.
#


# 参数:
system_version="centos";
gcc_version=11.1.0;

# parse options
while true; do
  [ -z "${1:-}" ] && break;  # break if there are no arguments
  case "$1" in
    --*) name=$(echo "$1" | sed s/^--// | sed s/-/_/g);
      eval '[ -z "${'"$name"'+xxx}" ]' && echo "$0: invalid option $1" 1>&2 && exit 1;
      old_value="(eval echo \\$$name)";
      if [ "${old_value}" == "true" ] || [ "${old_value}" == "false" ]; then
        was_bool=true;
      else
        was_bool=false;
      fi

      # Set the variable to the right value-- the escaped quotes make it work if
      # the option had spaces, like --cmd "queue.pl -sync y"
      eval "${name}=\"$2\"";

      # Check that Boolean-valued arguments are really Boolean.
      if $was_bool && [[ "$2" != "true" && "$2" != "false" ]]; then
        echo "$0: expected \"true\" or \"false\": $1 $2" 1>&2
        exit 1;
      fi
      shift 2;
      ;;

    *) break;
  esac
done

echo "system_version: ${system_version}";

if [ ${system_version} = "centos" ]; then

  yum install -y bzip2 git wget which lrzsz tmux zip unzip

  mkdir -p /data/dep
  # https://github.com/gcc-mirror/gcc/tags
  wget -P /data/dep https://github.com/gcc-mirror/gcc/archive/refs/tags/releases/gcc-${gcc_version}.zip

  cd -P /data/dep || exit 1;
  unzip gcc-${gcc_version}.zip

  cd gcc-releases-gcc-${gcc_version}/ || exit 1;

  ./contrib/download_prerequisites

  ls | grep tar

  tar -xf gmp-6.1.0.tar.bz2
  tar -xf isl-0.18.tar.bz2
  tar -xf mpc-1.0.3.tar.gz
  tar -xf mpfr-3.1.4.tar.bz2

  ln -sf gmp-6.1.0 gmp
  ln -sf isl-0.18 isl
  ln -sf mpc-1.0.3 mpc
  ln -sf mpfr-3.1.4 mpfr

  # 检查基础依赖
  yum install -y gcc automake autoconf libtool make
  yum install -y m4
  yum install -y glibc-headers
  yum install -y gcc-c++
  yum install -y flex
  yum install -y zlib zlib-devel

  # 创建 build 目录
  mkdir build && cd build || exit 1;

  # 配置
  ../configure \
  --prefix=/usr \
  --enable-bootstrap \
  --enable-languages=c,c++,fortran,lto \
  --enable-shared \
  --enable-threads=posix \
  --enable-checking=release \
  --enable-multilib \
  --with-system-zlib \
  --enable-__cxa_atexit \
  --disable-libunwind-exceptions \
  --enable-gnu-unique-object \
  --enable-linker-build-id \
  --with-gcc-major-version-only \
  --with-linker-hash-style=gnu \
  --with-default-libstdcxx-abi=gcc4-compatible \
  --enable-plugin \
  --enable-initfini-array \
  --disable-libmpx \
  --enable-gnu-indirect-function \
  --with-tune=generic \
  --with-arch_32=x86-64 \
  --build=x86_64-redhat-linux


  # 安装32位兼容包
  yum install -y glibc-devel.i686

  # 查看cpu核数
  THREADS=$(grep -c ^processor /proc/cpuinfo)
  export "${THREADS}"="$(grep -c ^processor /proc/cpuinfo)"

  # 安装
  make -j "${THREADS}"
  make install -j "${THREADS}"

fi
