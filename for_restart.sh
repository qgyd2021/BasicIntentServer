#!/usr/bin/env bash

# nohup sh for_restart.sh --http_port 13070 --build_dir build > nohup.out &


http_port=13070
build_dir="build"

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

work_dir=$(pwd)
chmod 777 "${work_dir}/start.sh"

LOG=/var/log/BasicIntentServer.log
rm -rf $LOG

while true
do
  # ps -ef | grep "build/BasicIntentServer" | grep -v grep |wc -l
  PT=$(ps -ef | grep "${build_dir}/BasicIntentServer" | grep -v grep |wc -l)

  if [ "$PT" -ge 1 ]; then
    echo -e "$(date "+%Y-%m-%d %H:%M:%S.%N")  BasicIntentServer is running, do nothing ..." >>$LOG
  else
    echo -e "$(date "+%Y-%m-%d %H:%M:%S.%N")  BasicIntentServer is not running, starting the BasicIntentServer now ..." >>$LOG

    sh "${work_dir}/start.sh" --build_dir ${build_dir} --http_port ${http_port}

  fi
  sleep 10s

done
