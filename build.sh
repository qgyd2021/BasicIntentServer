#!/usr/bin/env bash

# MSVC cmake.
# sh build.sh --stage 0 --stop_stage 0

system_version=windows;
verbose=true;
stage=0
stop_stage=0

work_dir="$(pwd)"

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


if [ ${stage} -le 0 ] && [ ${stop_stage} -ge 0 ]; then
  $verbose && echo "stage 0: build"
  cd "${work_dir}" || exit 1;

  # cmake -B build
  cmake --build ./build --target BasicIntentServer -j "$(grep -c ^processor /proc/cpuinfo)"

  if [ "${system_version}" == "windows" ]; then
    cp ./build/Debug/BasicIntentServer.exe ./build/BasicIntentServer.exe
  fi
  echo "run './build/BasicIntentServer' to test. "
fi
