#!/usr/bin/env bash

# docker run --name BasicIntentServer -itd -p 13070:13070 daocloud.io/centos:7 /bin/bash


gcc_version=11.1.0
system_version=centos

verbose=true;
stage=-1
stop_stage=1


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


yum install -y bzip2 gdb git lrzsz wget vim


if [ ${stage} -le -1 ] && [ ${stop_stage} -ge -1 ]; then
  $verbose && echo "stage -1: download models"
  cd "${work_dir}" || exit 1;

  mkdir trained_models && cd trained_models || exit 1;

  for model_name in basic_intent_cn_20230414 basic_intent_en_20230414 basic_intent_jp_20230414 basic_intent_vi_20230414
  do
  wget -c "https://huggingface.co/qgyd2021/basic_intent_models/resolve/main/${model_name}.zip"
  unzip "${model_name}.zip"
  rm "${model_name}.zip"
  rm -rf "${model_name}/*.ckpt"
  rm "${model_name}/pytorch_model.bin"
  rm "${model_name}/test_output.xlsx"
  rm -rf "${model_name}/vocabulary"
  done
fi


if [ ${stage} -le 0 ] && [ ${stop_stage} -ge 0 ]; then
  $verbose && echo "stage 0: install cmake"
  cd "${work_dir}" || exit 1;

  sh ./script/install_cmake.sh --system_version "${system_version}"
fi


if [ ${stage} -le 1 ] && [ ${stop_stage} -ge 1 ]; then
  $verbose && echo "stage 1: install gcc"
  cd "${work_dir}" || exit 1;

  sh ./script/install_gcc.sh --gcc_version "${gcc_version}" --system_version "${system_version}"
fi
