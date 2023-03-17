#!/usr/bin/expect
# 参考链接:
# https://gitee.com/help/articles/4181#article-header0
#
# 交互时输入回车, 参考链接:
# https://www.shuzhiduo.com/A/kvJ3rYQDzg/
# https://www.shuzhiduo.com/A/8Bz8KD1Ndx/
# https://blog.51cto.com/u_15366123/4660499


# params
stage=1

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

echo "stage: ${stage}";

if [ ${stage} -eq 0 ]; then
  # echo -e '\n\n\n' | ssh-keygen -t rsa -C "qgyd2021@gmail.com" -N ""
  echo | ssh-keygen -t rsa -C "qgyd2021@gmail.com" -N ""

  cat ~/.ssh/id_rsa
  cat ~/.ssh/id_rsa.pub
elif [ ${stage} -eq 1 ]; then
  mkdir -p ~/.ssh/

  # ~/.ssh/id_rsa
  echo \
"-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEA7a5oCR5n9eQG/IjNqsh65wni/IRGroHiicZ361/3aqh50Re3
razFOhAuAiGKim6KaviVazZOPcajk4EVpJj5HuV2AXxyLJpVxhjM4AmaWOxKee0g
rdf9BVALkyJfOEcsCwu4JQHa5FRyaT23AraqQb90Ut/p+c1bK0xC/azvrUwCWDjc
gBxldXqsk3tuDEqjGvJlrOg3B23UJL1lXWlIxVfHnp/6dw5PEK7f4QdXKoUArsX8
S81OH32G334SyIVUQHekqoZ1ASen+KvYP7AJjLWxwEXn2K9nbtUtVbizPt21c0BP
c0+A3Jt3YpJFimjHilB5CdtMndo9HQ6+qSp/xwIDAQABAoIBAC9JxtshmI98icNO
uJSlBIbZGbch3io0H01IFm3XDxPCZ1IphNriB+9wbqbv4299ZL65rIjDKjfyQHNF
eHfiE5aJErxi9RhYsH4USxa78mCEyqCNhDXyRh37egIREZ7R0jp0X3PFdbZ98rFr
nPDGRQOFwvAGKrgPmnb32lA8SwdQOPNzHJM/0f93TQ1Eis3qkU4UtxpQxCUDyqhD
HhrcCZgA27YkgJgooK8Ia+/JIJnOnek7aq2Gkcbsllt8fv5I/XEoNwanE8wrdWrc
G00BG47iXZAPMm8mRdeIPlZFyV4v45WLz794hlkF4luK6BAzVIXykAMyDRILlp95
jXuj6rECgYEA92C85kX8VBQG0yPRTPKQ4dy6TR6WszXXmG6Fvtwr6gIG14q7c4u6
4fHyjbTR99/gnJ76d6AqIXsWoDqHwzfFO+EBBNltLiUoTvS+OTi5YO9Lf6rclFRy
NXd1JQpdDmzKX1ZigJzrRv6mVYjtcIx02+UvrnvHWKdDbg6jcS/OEh8CgYEA9fcm
M95t8uJmHY2N+TxU/erL33sjn2NnyXvK8+Frxk8Jyrwlk+JKR7mfG2k6VPc3LP4y
cDatJGf2kpyo/CrBUV2k6pBTeyNmLQzFyCgx4bB6+TKDSqKtNDVWI8VgjypcpupS
gM8LEwV5nGnEfSFiJdpGJ4YgCrxxD27a4U9RbVkCgYAPdA2Y3PpcTjv26J/kjKqc
UWuZ8bU8ULq9HPph5+MeZS4EPPhkyW/NOY4LaCZNs8CWSCAhZPH80XGiZMWiXlOF
4BJuOR7m6Q9Rj1xquq5p7cjrmsLYyUWxLVs2CyWxBv7FYeIZYrQX5USCx2D9zOhn
7DNEVRso4JoHwAZZxcC7xQKBgAjR2e7WNP8Wmy7IGqUrQqjwOGtFERvwBpK0+6wP
EzxDLUi1wmsxHBTCVTA4b70IOFRGsSxQ6Zh6md7b+zs/lTsDrpwynKu3szw+TwFE
X7WGDILPCuIsPyW2G+agdzvq+vOJR3gS9IS0F45CRKdwAQL2drmIF7IK28r/4J1f
qL3RAoGBAMaCHPHZ2WxXhz240lxVHQ2Mtwcrxp4Wqxu5h0uglWEHzoMc8kGTeekW
Tu9XePGJRLHapwVDH9hJTwmhRVkUD7QXBV6aQ2O4LrDKZhil3OymZycijOzph1nv
SBbA4PP7S4HOASM7GcS3viLpvFvjARLYGEOy9NXTucMQKymag0Dy
-----END RSA PRIVATE KEY-----" \
> ~/.ssh/id_rsa

  # ~/.ssh/id_rsa.pub
  echo \
"ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQDtrmgJHmf15Ab8iM2qyHrnCeL8hEaugeKJxnfrX/dqqHnRF7etrMU6EC4CIYqKbopq+JVrNk49xqOTgRWkmPke5XYBfHIsmlXGGMzgCZpY7Ep57SCt1/0FUAuTIl84RywLC7glAdrkVHJpPbcCtqpBv3RS3+n5zVsrTEL9rO+tTAJYONyAHGV1eqyTe24MSqMa8mWs6DcHbdQkvWVdaUjFV8een/p3Dk8Qrt/hB1cqhQCuxfxLzU4ffYbffhLIhVRAd6SqhnUBJ6f4q9g/sAmMtbHARefYr2du1S1VuLM+3bVzQE9zT4Dcm3dikkWKaMeKUHkJ20yd2j0dDr6pKn/H qgyd2021@gmail.com" \
> ~/.ssh/id_rsa.pub

fi
